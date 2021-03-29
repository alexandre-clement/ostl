#include "caldera/vulkan/vulkan.hpp"

#include <set>

namespace caldera
{
    bool queue_family_indices::is_complete() const { return graphics_family.has_value() && present_family.has_value(); }

    bool swap_chain_details::is_adequate() const { return !surface_formats.empty() && !present_modes.empty(); }

    bool physical_device_evaluation::is_suitable() const
    {
        return is_discrete && indices.is_complete() && pde.contains_all_required_extensions && swap_chain.is_adequate();
    }

    physical_device_properties physical_device_evaluation::build() const
    {
        return {
          indices.graphics_family.value(),
          indices.present_family.value(),
          {indices.graphics_family.value(), indices.present_family.value()},
          pde.extensions,
          swap_chain.surface_capabilities,
          swap_chain.surface_formats,
          swap_chain.present_modes};
    }

    bool physical_device_evaluation::operator>(const physical_device_evaluation& right) const
    {
        return is_suitable() * score > right.is_suitable() * right.score;
    }

    vulkan::vulkan(configuration p_configuration) : m_configuration(std::move(p_configuration))
    {
        create_instance();
        bind_surface();
        pick_physical_device();
        create_logical_device();
    }

    vulkan::~vulkan()
    {
        log.trace("destroying vulkan instance");

        m_device.destroy();
        m_instance.destroySurfaceKHR(m_surface);
        m_instance.destroy(nullptr);
    }

    void vulkan::create_instance()
    {
        log.trace("creating vulkan instance");
        log.info("instance information : [name : \"{}\", version : {}]", engine_name, engine_version);

        std::vector<c_str> extensions = m_configuration.required_extensions;
        extensions.insert(extensions.end(), m_debugger.extensions.begin(), m_debugger.extensions.end());

        log.info("{} vulkan extensions required :", extensions.size());
        for (const auto ext : extensions)
        {
            log.info("\t{}", ext);
        }

        const vk::ApplicationInfo application_informations = vk::ApplicationInfo()
                                                               .setPApplicationName(m_configuration.name.c_str())
                                                               .setApplicationVersion(m_configuration.version)
                                                               .setPEngineName(engine_name.c_str())
                                                               .setEngineVersion(engine_version)
                                                               .setApiVersion(VK_MAKE_VERSION(1, 0, 0));

        const vk::InstanceCreateInfo instance_informations =
          vk::InstanceCreateInfo()
            .setPApplicationInfo(&application_informations)
            .setPNext(&m_debugger.messenger_info)
            .setEnabledLayerCount(m_debugger.validation_layers.size())
            .setPpEnabledLayerNames(m_debugger.validation_layers.data())
            .setEnabledExtensionCount(extensions.size())
            .setPpEnabledExtensionNames(extensions.data());

        m_instance = vk::createInstance(instance_informations);

        log.trace("successfully created vulkan instance");
    }

    void vulkan::bind_surface() { m_surface = m_configuration.create_surface(m_instance); }

    void vulkan::pick_physical_device()
    {
        log.info("selecting the best gpu available");
        auto devices = m_instance.enumeratePhysicalDevices();
        physical_device_evaluation current_evaluation, best_evaluation;
        log.debug("{} gpu found:", devices.size());
        for (const auto& device : devices)
        {
            if ((current_evaluation = evaluate_physical_device_properties(device)) > best_evaluation)
            {
                m_physical_device = device;
                best_evaluation = current_evaluation;
            }
            log.debug("\t{} : {}", device.getProperties().deviceName, current_evaluation.score);
        }
        if (!best_evaluation.is_suitable())
        {
            throw suitable_physical_device_not_found_exception();
        }

        log.info("the graphic card \"{}\" has been selected", m_physical_device.getProperties().deviceName);
        std::vector<std::string> extensions = get_available_gpu_extensions(m_physical_device);
        log.debug("{} has {} extensions available:", m_physical_device.getProperties().deviceName, extensions.size());
        for (const auto& extension : extensions)
        {
            log.debug("\t{}", extension);
        }
    }

    physical_device_evaluation vulkan::evaluate_physical_device_properties(const vk::PhysicalDevice& device) const
    {
        log.trace("evaluate {}", device.getProperties().deviceName);
        physical_device_evaluation evaluation;
        auto properties = device.getProperties();
        evaluation.is_discrete = properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu;
        evaluation.indices = find_queue_families(device);
        evaluation.pde = look_for_gpu_extensions(device, get_required_gpu_extensions());

        if (evaluation.pde.contains_all_required_extensions)
        {
            log.debug("{} contains all required extensions", device.getProperties().deviceName);
            evaluation.swap_chain = query_swap_chain_support(device);
        }
        return evaluation;
    }

    queue_family_indices vulkan::find_queue_families(const vk::PhysicalDevice& device) const
    {
        queue_family_indices indices;
        std::vector<vk::QueueFamilyProperties> properties = device.getQueueFamilyProperties();
        for (auto [index, queue_family] : detail::enumerate(properties))
        {
            if (queue_family.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                indices.graphics_family = index;
            }
            auto supported = device.getSurfaceSupportKHR(index, m_surface);
            if (supported)
            {
                indices.present_family = index;
            }
            if (indices.is_complete())
            {
                break;
            }
        }
        return indices;
    }

    physical_device_extensions vulkan::look_for_gpu_extensions(
      const vk::PhysicalDevice& device,
      const std::vector<std::string>& required_gpu_extensions) const
    {
        physical_device_extensions extensions;
        const std::vector<std::string> available_gpu_extensions = get_available_gpu_extensions(device);
        for (const auto& gpu_extension : required_gpu_extensions)
        {
            if (
              std::find(required_gpu_extensions.begin(), required_gpu_extensions.end(), gpu_extension) ==
              required_gpu_extensions.end())
            {
                log.debug("{} misses extension {}", device.getProperties().deviceName, gpu_extension);
                extensions.contains_all_required_extensions = false;
            }
            else
            {
                extensions.extensions.push_back(gpu_extension);
            }
        }
        return extensions;
    }

    std::vector<std::string> vulkan::get_available_gpu_extensions(const vk::PhysicalDevice& device) const
    {
        auto properties = device.enumerateDeviceExtensionProperties();
        std::vector<std::string> available_gpu_extensions(properties.size());
        for (const auto& extension : properties)
        {
            available_gpu_extensions.push_back(extension.extensionName);
        }
        return available_gpu_extensions;
    }

    std::vector<std::string> vulkan::get_required_gpu_extensions() const
    {
        const std::vector<std::string> required_gpu_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
        return required_gpu_extensions;
    }

    swap_chain_details vulkan::query_swap_chain_support(const vk::PhysicalDevice& device) const
    {
        auto capabilities = device.getSurfaceCapabilitiesKHR(m_surface);
        auto formats = device.getSurfaceFormatsKHR(m_surface);
        auto present_modes = device.getSurfacePresentModesKHR(m_surface);
        return {capabilities, formats, present_modes};
    }

    physical_device_properties vulkan::gpu_properties() const
    {
        return evaluate_physical_device_properties(m_physical_device).build();
    }

    void vulkan::create_logical_device()
    {
        log.debug("create logical device");
        physical_device_properties properties = gpu_properties();
        float priority = 1.0f;
        std::vector<vk::DeviceQueueCreateInfo> queue_informations;
        std::set<std::uint32_t> queues_indices = {properties.graphics_family, properties.present_family};

        for (std::uint32_t index : queues_indices)
        {
            queue_informations.push_back(
              vk::DeviceQueueCreateInfo().setQueueFamilyIndex(index).setQueueCount(1).setPQueuePriorities(&priority));
        }
        log.debug("{} vulkan extensions will be loaded:", properties.extensions.size());
        for (const auto& extension : properties.extensions)
        {
            log.debug("\t{}", extension);
        }

        auto vk_extensions = detail::map(
          properties.extensions, std::function([](const std::string& s) -> const char* { return s.c_str(); }));

        vk::PhysicalDeviceFeatures features = vk::PhysicalDeviceFeatures().setShaderFloat64(true);

        vk::DeviceCreateInfo device_info = vk::DeviceCreateInfo()
                                             .setFlags(vk::DeviceCreateFlags())
                                             .setPQueueCreateInfos(queue_informations.data())
                                             .setQueueCreateInfoCount(queue_informations.size())
                                             .setEnabledLayerCount(m_debugger.validation_layers.size())
                                             .setPpEnabledLayerNames(m_debugger.validation_layers.data())
                                             .setPpEnabledExtensionNames(vk_extensions.data())
                                             .setEnabledExtensionCount(properties.extensions.size())
                                             .setPEnabledFeatures(&features);

        m_device = m_physical_device.createDevice(device_info);
        m_graphics_queue = m_device.getQueue(properties.graphics_family, 0);
        m_present_queue = m_device.getQueue(properties.present_family, 0);
    }

    const char* suitable_physical_device_not_found_exception::what() const noexcept
    {
        return "failed to find a suitable GPU.";
    }
}  // namespace caldera