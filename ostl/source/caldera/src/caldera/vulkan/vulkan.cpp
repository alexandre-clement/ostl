#include "caldera/vulkan/vulkan.hpp"

#include <algorithm>
#include <set>

#include <SPIRV/GlslangToSpv.h>

#include <glslang/Include/ResourceLimits.h>

namespace caldera
{
    const TBuiltInResource DefaultTBuiltInResource = {
      /* .MaxLights = */ 32,
      /* .MaxClipPlanes = */ 6,
      /* .MaxTextureUnits = */ 32,
      /* .MaxTextureCoords = */ 32,
      /* .MaxVertexAttribs = */ 64,
      /* .MaxVertexUniformComponents = */ 4096,
      /* .MaxVaryingFloats = */ 64,
      /* .MaxVertexTextureImageUnits = */ 32,
      /* .MaxCombinedTextureImageUnits = */ 80,
      /* .MaxTextureImageUnits = */ 32,
      /* .MaxFragmentUniformComponents = */ 4096,
      /* .MaxDrawBuffers = */ 32,
      /* .MaxVertexUniformVectors = */ 128,
      /* .MaxVaryingVectors = */ 8,
      /* .MaxFragmentUniformVectors = */ 16,
      /* .MaxVertexOutputVectors = */ 16,
      /* .MaxFragmentInputVectors = */ 15,
      /* .MinProgramTexelOffset = */ -8,
      /* .MaxProgramTexelOffset = */ 7,
      /* .MaxClipDistances = */ 8,
      /* .MaxComputeWorkGroupCountX = */ 65535,
      /* .MaxComputeWorkGroupCountY = */ 65535,
      /* .MaxComputeWorkGroupCountZ = */ 65535,
      /* .MaxComputeWorkGroupSizeX = */ 1024,
      /* .MaxComputeWorkGroupSizeY = */ 1024,
      /* .MaxComputeWorkGroupSizeZ = */ 64,
      /* .MaxComputeUniformComponents = */ 1024,
      /* .MaxComputeTextureImageUnits = */ 16,
      /* .MaxComputeImageUniforms = */ 8,
      /* .MaxComputeAtomicCounters = */ 8,
      /* .MaxComputeAtomicCounterBuffers = */ 1,
      /* .MaxVaryingComponents = */ 60,
      /* .MaxVertexOutputComponents = */ 64,
      /* .MaxGeometryInputComponents = */ 64,
      /* .MaxGeometryOutputComponents = */ 128,
      /* .MaxFragmentInputComponents = */ 128,
      /* .MaxImageUnits = */ 8,
      /* .MaxCombinedImageUnitsAndFragmentOutputs = */ 8,
      /* .MaxCombinedShaderOutputResources = */ 8,
      /* .MaxImageSamples = */ 0,
      /* .MaxVertexImageUniforms = */ 0,
      /* .MaxTessControlImageUniforms = */ 0,
      /* .MaxTessEvaluationImageUniforms = */ 0,
      /* .MaxGeometryImageUniforms = */ 0,
      /* .MaxFragmentImageUniforms = */ 8,
      /* .MaxCombinedImageUniforms = */ 8,
      /* .MaxGeometryTextureImageUnits = */ 16,
      /* .MaxGeometryOutputVertices = */ 256,
      /* .MaxGeometryTotalOutputComponents = */ 1024,
      /* .MaxGeometryUniformComponents = */ 1024,
      /* .MaxGeometryVaryingComponents = */ 64,
      /* .MaxTessControlInputComponents = */ 128,
      /* .MaxTessControlOutputComponents = */ 128,
      /* .MaxTessControlTextureImageUnits = */ 16,
      /* .MaxTessControlUniformComponents = */ 1024,
      /* .MaxTessControlTotalOutputComponents = */ 4096,
      /* .MaxTessEvaluationInputComponents = */ 128,
      /* .MaxTessEvaluationOutputComponents = */ 128,
      /* .MaxTessEvaluationTextureImageUnits = */ 16,
      /* .MaxTessEvaluationUniformComponents = */ 1024,
      /* .MaxTessPatchComponents = */ 120,
      /* .MaxPatchVertices = */ 32,
      /* .MaxTessGenLevel = */ 64,
      /* .MaxViewports = */ 16,
      /* .MaxVertexAtomicCounters = */ 0,
      /* .MaxTessControlAtomicCounters = */ 0,
      /* .MaxTessEvaluationAtomicCounters = */ 0,
      /* .MaxGeometryAtomicCounters = */ 0,
      /* .MaxFragmentAtomicCounters = */ 8,
      /* .MaxCombinedAtomicCounters = */ 8,
      /* .MaxAtomicCounterBindings = */ 1,
      /* .MaxVertexAtomicCounterBuffers = */ 0,
      /* .MaxTessControlAtomicCounterBuffers = */ 0,
      /* .MaxTessEvaluationAtomicCounterBuffers = */ 0,
      /* .MaxGeometryAtomicCounterBuffers = */ 0,
      /* .MaxFragmentAtomicCounterBuffers = */ 1,
      /* .MaxCombinedAtomicCounterBuffers = */ 1,
      /* .MaxAtomicCounterBufferSize = */ 16384,
      /* .MaxTransformFeedbackBuffers = */ 4,
      /* .MaxTransformFeedbackInterleavedComponents = */ 64,
      /* .MaxCullDistances = */ 8,
      /* .MaxCombinedClipAndCullDistances = */ 8,
      /* .MaxSamples = */ 4,
      /* .maxMeshOutputVerticesNV = */ 256,
      /* .maxMeshOutputPrimitivesNV = */ 512,
      /* .maxMeshWorkGroupSizeX_NV = */ 32,
      /* .maxMeshWorkGroupSizeY_NV = */ 1,
      /* .maxMeshWorkGroupSizeZ_NV = */ 1,
      /* .maxTaskWorkGroupSizeX_NV = */ 32,
      /* .maxTaskWorkGroupSizeY_NV = */ 1,
      /* .maxTaskWorkGroupSizeZ_NV = */ 1,
      /* .maxMeshViewCountNV = */ 4,

      /* .limits = */
      {
        /* .nonInductiveForLoops = */ 1,
        /* .whileLoops = */ 1,
        /* .doWhileLoops = */ 1,
        /* .generalUniformIndexing = */ 1,
        /* .generalAttributeMatrixVectorIndexing = */ 1,
        /* .generalVaryingIndexing = */ 1,
        /* .generalSamplerIndexing = */ 1,
        /* .generalVariableIndexing = */ 1,
        /* .generalConstantMatrixVectorIndexing = */ 1,
      }};

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
        create_command_pool();
        create_swap_chain();
        create_image_views();
        create_render_pass();
        create_framebuffers();
        create_descriptor_pool();
        create_uniform_buffer();
        create_descriptor_set_layout();
        create_descriptor_sets();
        create_pipeline_layout();
        create_graphic_pipeline();
        create_command_buffers();
        create_semaphores();
        create_fences();
    }

    vulkan::~vulkan()
    {
        log.info("destroying vulkan");

        m_present_queue.waitIdle();
        for (auto [image_available, render_finished, in_flight] :
             detail::zip(m_image_available_semaphores, m_render_finished_semaphores, m_in_flight_fences))
        {
            m_device.destroySemaphore(image_available);
            m_device.destroySemaphore(render_finished);
            m_device.destroyFence(in_flight);
        }
        m_device.freeCommandBuffers(m_command_pool, m_command_buffers);
        m_device.destroyPipeline(m_pipeline);
        for (const auto& stage : m_stages)
        {
            m_device.destroyShaderModule(stage.module);
        }
        m_device.destroyPipelineLayout(m_layout);
        m_device.destroyDescriptorSetLayout(m_descriptor_set_layout);
        for (auto [buffer, memory] : detail::zip(m_buffers, m_memory))
        {
            m_device.destroyBuffer(buffer);
            m_device.freeMemory(memory);
        }
        m_device.destroyDescriptorPool(m_descriptor_pool);
        for (auto& framebuffer : m_framebuffers)
        {
            m_device.destroyFramebuffer(framebuffer);
        }
        m_device.destroyRenderPass(m_render_pass);
        for (auto& image_view : m_image_views)
        {
            m_device.destroyImageView(image_view);
        }
        m_device.destroySwapchainKHR(m_swap_chain);
        m_device.destroyCommandPool(m_command_pool);
        m_device.destroy();
        m_instance.destroySurfaceKHR(m_surface);
        m_instance.destroy(nullptr);
    }

    void vulkan::render()
    {
        auto result = m_device.waitForFences(in_flight_fence(), VK_TRUE, UINT64_MAX);

        std::uint32_t image_index;

        do
        {
            result = m_device.acquireNextImageKHR(
              m_swap_chain, UINT64_MAX, image_available_semaphore(), nullptr, &image_index);

            if (result == vk::Result::eErrorOutOfDateKHR)
            {
                // recreate image buffer
            }
        } while (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR);

        if (m_images_in_flight.at(image_index))
        {
            result = m_device.waitForFences(m_images_in_flight.at(image_index), VK_TRUE, UINT64_MAX);
        }

        m_images_in_flight.at(image_index) = in_flight_fence();

        // update uniform variables

        vk::PipelineStageFlags wait_dst_stage_mask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        vk::SubmitInfo submit_info = vk::SubmitInfo()
                                       .setWaitSemaphoreCount(1u)
                                       .setPWaitSemaphores(&image_available_semaphore())
                                       .setPWaitDstStageMask(&wait_dst_stage_mask)
                                       .setCommandBufferCount(1u)
                                       .setPCommandBuffers(&current_buffer(image_index))
                                       .setSignalSemaphoreCount(1u)
                                       .setPSignalSemaphores(&render_finished_semaphore());

        m_device.resetFences(in_flight_fence());
        m_graphics_queue.submit(submit_info, in_flight_fence());

        vk::PresentInfoKHR present_info = vk::PresentInfoKHR()
                                            .setWaitSemaphoreCount(1u)
                                            .setPWaitSemaphores(&render_finished_semaphore())
                                            .setSwapchainCount(1u)
                                            .setPSwapchains(&m_swap_chain)
                                            .setPImageIndices(&image_index)
                                            .setPResults(nullptr);

        result = m_present_queue.presentKHR(present_info);
        if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR)
        {
            // recreate image buffer
        }

        next_frame();
    }

    void vulkan::create_instance()
    {
        log.debug("creating vulkan instance");
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

        log.debug("successfully created vulkan instance");
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
        log.debug("evaluate {}", device.getProperties().deviceName);
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
              vk::DeviceQueueCreateInfo().setQueueFamilyIndex(index).setQueueCount(1u).setPQueuePriorities(&priority));
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

    void vulkan::create_command_pool()
    {
        vk::CommandPoolCreateInfo info = vk::CommandPoolCreateInfo()
                                           .setFlags(vk::CommandPoolCreateFlags())
                                           .setQueueFamilyIndex(gpu_properties().graphics_family);

        m_command_pool = m_device.createCommandPool(info);
    }

    void vulkan::create_swap_chain()
    {
        log.debug("creating vulkan swap chain");
        auto properties = gpu_properties();

        vk::SwapchainCreateFlagsKHR flags = vk::SwapchainCreateFlagsKHR();
        std::uint32_t min_image_count = properties.surface_capabilities.minImageCount + 1;
        if (
          properties.surface_capabilities.maxImageCount > 0 &&
          min_image_count > properties.surface_capabilities.maxImageCount)
        {
            min_image_count = properties.surface_capabilities.maxImageCount;
        }
        vk::SurfaceFormatKHR surface_format = choose_swap_surface_format(properties.surface_formats);
        m_format = surface_format.format;
        vk::PresentModeKHR present_mode = choose_swap_present_mode(properties.present_modes);
        m_extent = choose_swap_extent(properties.surface_capabilities);
        queue_sharing_mode qsm = select_sharing_mode(properties);

        vk::SwapchainCreateInfoKHR info = vk::SwapchainCreateInfoKHR()
                                            .setFlags(flags)
                                            .setSurface(m_surface)
                                            .setMinImageCount(min_image_count)
                                            .setImageFormat(m_format)
                                            .setImageColorSpace(surface_format.colorSpace)
                                            .setImageExtent(m_extent)
                                            .setImageArrayLayers(1)
                                            .setImageSharingMode(qsm.sharing_mode)
                                            .setQueueFamilyIndexCount(qsm.index_count)
                                            .setPQueueFamilyIndices(qsm.indices)
                                            .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
                                            .setPreTransform(properties.surface_capabilities.currentTransform)
                                            .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
                                            .setPresentMode(present_mode)
                                            .setClipped(VK_TRUE)
                                            .setOldSwapchain(nullptr);

        m_swap_chain = m_device.createSwapchainKHR(info);
        m_images = m_device.getSwapchainImagesKHR(m_swap_chain);

        log.info("window size {}x{}", m_extent.width, m_extent.height);
        log.info("display format {}", vk::to_string(m_format));

        log.debug("successfully created vulkan swap chain");
    }

    vk::SurfaceFormatKHR
      vulkan::choose_swap_surface_format(const std::vector<vk::SurfaceFormatKHR>& surface_formats) const
    {
        for (const auto& surface_format : surface_formats)
        {
            if (
              surface_format.format == vk::Format::eB8G8R8A8Unorm &&
              surface_format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
            {
                return surface_format;
            }
        }
        return surface_formats.at(0);
    }

    vk::PresentModeKHR vulkan::choose_swap_present_mode(const std::vector<vk::PresentModeKHR>& present_modes) const
    {
        for (const auto& present_mode : present_modes)
        {
            if (present_mode == vk::PresentModeKHR::eMailbox)
            {
                return present_mode;
            }
        }
        return vk::PresentModeKHR::eFifo;
    }

    vk::Extent2D vulkan::choose_swap_extent(const vk::SurfaceCapabilitiesKHR& capabilities) const
    {
        if (capabilities.currentExtent.width != UINT32_MAX)
        {
            return capabilities.currentExtent;
        }
        else
        {
            return {
              std::clamp(
                m_configuration.framebuffer.x, capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
              std::clamp(
                m_configuration.framebuffer.y, capabilities.minImageExtent.height, capabilities.maxImageExtent.height),
            };
        }
    }

    queue_sharing_mode vulkan::select_sharing_mode(const physical_device_properties& properties) const
    {
        if (properties.graphics_family == properties.present_family)
        {
            return {vk::SharingMode::eExclusive, 0u, nullptr};
        }
        else
        {
            return {vk::SharingMode::eConcurrent, 2u, properties.indices.data()};
        }
    }

    const vk::Rect2D vulkan::render_area() const { return vk::Rect2D({0, 0}, m_extent); }

    void vulkan::create_image_views()
    {
        log.debug("creating vulkan image views");

        m_image_views.resize(m_images.size());

        for (auto [image, image_view] : detail::zip(m_images, m_image_views))
        {
            vk::ImageViewCreateInfo info =
              vk::ImageViewCreateInfo()
                .setImage(image)
                .setViewType(vk::ImageViewType::e2D)
                .setFormat(m_format)
                .setComponents(vk::ComponentMapping())
                .setSubresourceRange(vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));

            image_view = m_device.createImageView(info);
        }

        log.debug("successfully created vulkan image views");
    }

    void vulkan::create_render_pass()
    {
        log.debug("creating vulkan render pass");

        std::vector<vk::AttachmentDescription> color_attachments = {
          vk::AttachmentDescription()
            .setFlags(vk::AttachmentDescriptionFlags())
            .setFormat(m_format)
            .setSamples(vk::SampleCountFlagBits::e1)
            .setLoadOp(vk::AttachmentLoadOp::eClear)
            .setStoreOp(vk::AttachmentStoreOp::eStore)
            .setStencilLoadOp(vk::AttachmentLoadOp::eDontCare)
            .setStencilStoreOp(vk::AttachmentStoreOp::eDontCare)
            .setInitialLayout(vk::ImageLayout::eUndefined)
            .setFinalLayout(vk::ImageLayout::ePresentSrcKHR)};

        std::vector<vk::AttachmentReference> color_attachments_refs = {
          vk::AttachmentReference().setAttachment(0u).setLayout(vk::ImageLayout::eColorAttachmentOptimal)};

        std::vector<vk::SubpassDescription> subpasses_descriptions = {
          vk::SubpassDescription()
            .setFlags(vk::SubpassDescriptionFlags())
            .setPipelineBindPoint(vk::PipelineBindPoint::eGraphics)
            .setInputAttachmentCount(0u)
            .setPInputAttachments(nullptr)
            .setColorAttachmentCount(color_attachments_refs.size())
            .setPColorAttachments(color_attachments_refs.data())
            .setPResolveAttachments(nullptr)
            .setPDepthStencilAttachment(nullptr)
            .setPreserveAttachmentCount(0u)
            .setPResolveAttachments(nullptr)};

        std::vector<vk::SubpassDependency> subpasses_dependencies = {
          vk::SubpassDependency()
            .setDependencyFlags(vk::DependencyFlags())
            .setSrcSubpass(VK_SUBPASS_EXTERNAL)
            .setDstSubpass(0u)
            .setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
            .setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput)
            .setSrcAccessMask(static_cast<vk::AccessFlagBits>(0))
            .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite)

        };

        vk::RenderPassCreateInfo info = vk::RenderPassCreateInfo()
                                          .setFlags(vk::RenderPassCreateFlags())
                                          .setAttachmentCount(color_attachments.size())
                                          .setPAttachments(color_attachments.data())
                                          .setSubpassCount(subpasses_descriptions.size())
                                          .setPSubpasses(subpasses_descriptions.data())
                                          .setDependencyCount(subpasses_dependencies.size())
                                          .setPDependencies(subpasses_dependencies.data());

        m_render_pass = m_device.createRenderPass(info);

        log.debug("successfully created vulkan render pass");
    }

    void vulkan::create_framebuffers()
    {
        log.debug("creating vulkan framebuffer");

        m_framebuffers.resize(m_image_views.size());

        for (auto [framebuffer, image_view] : detail::zip(m_framebuffers, m_image_views))
        {
            vk::ImageView attachments[] = {image_view};
            vk::FramebufferCreateInfo info = vk::FramebufferCreateInfo()
                                               .setRenderPass(m_render_pass)
                                               .setAttachmentCount(1u)
                                               .setPAttachments(attachments)
                                               .setWidth(m_extent.width)
                                               .setHeight(m_extent.height)
                                               .setLayers(1u);

            framebuffer = m_device.createFramebuffer(info);
        }

        log.debug("successfully created vulkan framebuffer");
    }

    void vulkan::create_descriptor_pool()
    {
        std::vector<vk::DescriptorPoolSize> pool_sizes = {
          vk::DescriptorPoolSize().setType(vk::DescriptorType::eUniformBuffer).setDescriptorCount(m_images.size())};

        vk::DescriptorPoolCreateInfo info = vk::DescriptorPoolCreateInfo()
                                              .setMaxSets(m_images.size())
                                              .setPoolSizeCount(pool_sizes.size())
                                              .setPPoolSizes(pool_sizes.data());

        m_descriptor_pool = m_device.createDescriptorPool(info);
    }

    void vulkan::create_uniform_buffer()
    {
        m_buffers.resize(m_images.size());
        m_memory.resize(m_images.size());

        for (auto [buffer, memory] : detail::zip(m_buffers, m_memory))
        {
            vk::BufferCreateInfo buffer_info =
              vk::BufferCreateInfo().setSize(m_buffer_size).setUsage(vk::BufferUsageFlagBits::eUniformBuffer);

            {
                buffer = m_device.createBuffer(buffer_info);
            }

            auto requirements = m_device.getBufferMemoryRequirements(buffer);

            vk::MemoryAllocateInfo memory_info =
              vk::MemoryAllocateInfo()
                .setAllocationSize(requirements.size)
                .setMemoryTypeIndex(find_memory_type(
                  requirements.memoryTypeBits,
                  vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent));

            memory = m_device.allocateMemory(memory_info);

            m_device.bindBufferMemory(buffer, memory, 0ul);
        }
    }

    std::uint32_t vulkan::find_memory_type(std::uint32_t type, vk::MemoryPropertyFlags properties) const
    {
        auto gpu_memory_properties = m_physical_device.getMemoryProperties();
        for (std::uint32_t i = 0u; i < gpu_memory_properties.memoryTypeCount; i++)
        {
            if ((type & (1u << i)) && (gpu_memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
            {
                return i;
            }
        }
        return 0;
    }

    void vulkan::create_descriptor_set_layout()
    {
        std::vector<vk::DescriptorSetLayoutBinding> bindings = {vk::DescriptorSetLayoutBinding()
                                                                  .setBinding(0u)
                                                                  .setDescriptorType(vk::DescriptorType::eUniformBuffer)
                                                                  .setDescriptorCount(1u)
                                                                  .setStageFlags(vk::ShaderStageFlagBits::eFragment)};

        vk::DescriptorSetLayoutCreateInfo layout_info =
          vk::DescriptorSetLayoutCreateInfo().setBindingCount(bindings.size()).setPBindings(bindings.data());

        m_descriptor_set_layout = m_device.createDescriptorSetLayout(layout_info);
    }

    void vulkan::create_descriptor_sets()
    {
        std::vector<vk::DescriptorSetLayout> layouts(m_images.size(), m_descriptor_set_layout);

        vk::DescriptorSetAllocateInfo allocate_info = vk::DescriptorSetAllocateInfo()
                                                        .setDescriptorPool(m_descriptor_pool)
                                                        .setDescriptorSetCount(layouts.size())
                                                        .setPSetLayouts(layouts.data());

        m_descriptor_sets = m_device.allocateDescriptorSets(allocate_info);

        std::vector<vk::WriteDescriptorSet> descriptor_writes(m_descriptor_sets.size());

        for (auto [buffer, descriptor_set, writer] : detail::zip(m_buffers, m_descriptor_sets, descriptor_writes))
        {
            vk::DescriptorBufferInfo buffer_info =
              vk::DescriptorBufferInfo().setBuffer(buffer).setOffset(0ul).setRange(m_buffer_size);

            writer.setDstSet(descriptor_set)
              .setDstBinding(0u)
              .setDstArrayElement(0u)
              .setDescriptorCount(1u)
              .setDescriptorType(vk::DescriptorType::eUniformBuffer)
              .setPImageInfo(nullptr)
              .setPBufferInfo(&buffer_info)
              .setPTexelBufferView(nullptr);
        }

        m_device.updateDescriptorSets(descriptor_writes, nullptr);
    }

    void vulkan::create_pipeline_layout()
    {
        log.debug("creating vulkan pipeline layout");

        vk::PipelineLayoutCreateInfo info = vk::PipelineLayoutCreateInfo()
                                              .setFlags(vk::PipelineLayoutCreateFlags())
                                              .setPPushConstantRanges(0)
                                              .setPPushConstantRanges(nullptr)
                                              .setSetLayoutCount(1u)
                                              .setPSetLayouts(&m_descriptor_set_layout);

        m_layout = m_device.createPipelineLayout(info);

        log.debug("successfully created vulkan pipeline layout");
    }

    void vulkan::create_graphic_pipeline()
    {
        log.debug("creating vulkan graphics pipeline");

        glslang::InitializeProcess();
        vk::ShaderModule vertexShaderModule = create_shader_module(vk::ShaderStageFlagBits::eVertex, R"(
            #version 450

            void main()
            {
                vec2 circumscribed_triangle = 4. * vec2(gl_VertexIndex & 1, (gl_VertexIndex >> 1) & 1) - 1.;
                gl_Position = vec4(circumscribed_triangle, 0.0, 1.0);
            }
            )");
        vk::ShaderModule fragmentShaderModule = create_shader_module(vk::ShaderStageFlagBits::eFragment, R"(
            #version 450

            layout(location = 0) out vec4 frag_color;

            void main()
            {
                frag_color = vec4(vec3(0.), 1.);
            }
            )");
        glslang::FinalizeProcess();

        m_stages = {
          vk::PipelineShaderStageCreateInfo(
            vk::PipelineShaderStageCreateFlags(), vk::ShaderStageFlagBits::eVertex, vertexShaderModule, "main"),
          vk::PipelineShaderStageCreateInfo(
            vk::PipelineShaderStageCreateFlags(), vk::ShaderStageFlagBits::eFragment, fragmentShaderModule, "main")};

        vk::PipelineVertexInputStateCreateInfo vertex_input = vk::PipelineVertexInputStateCreateInfo()
                                                                .setVertexBindingDescriptionCount(0u)
                                                                .setVertexAttributeDescriptionCount(0u);

        vk::PipelineInputAssemblyStateCreateInfo assembly = vk::PipelineInputAssemblyStateCreateInfo()
                                                              .setTopology(vk::PrimitiveTopology::eTriangleList)
                                                              .setPrimitiveRestartEnable(VK_FALSE);

        vk::Viewport viewport = vk::Viewport(0.0f, 0.0f, m_extent.width, m_extent.height, 0, 1.0f);
        vk::Rect2D scissors(render_area());

        vk::PipelineViewportStateCreateInfo viewport_state_info = vk::PipelineViewportStateCreateInfo()
                                                                    .setViewportCount(1u)
                                                                    .setPViewports(&viewport)
                                                                    .setScissorCount(1u)
                                                                    .setPScissors(&scissors);

        vk::PipelineRasterizationStateCreateInfo rasterizer = vk::PipelineRasterizationStateCreateInfo()
                                                                .setFlags(vk::PipelineRasterizationStateCreateFlags())
                                                                .setDepthBiasClamp(VK_FALSE)
                                                                .setRasterizerDiscardEnable(VK_FALSE)
                                                                .setPolygonMode(vk::PolygonMode::eFill)
                                                                .setCullMode(vk::CullModeFlagBits::eBack)
                                                                .setFrontFace(vk::FrontFace::eClockwise)
                                                                .setDepthBiasEnable(VK_FALSE)
                                                                .setDepthBiasConstantFactor(.0f)
                                                                .setDepthBiasClamp(.0f)
                                                                .setDepthBiasSlopeFactor(.0f)
                                                                .setLineWidth(1.f);

        vk::PipelineMultisampleStateCreateInfo multisampling =
          vk::PipelineMultisampleStateCreateInfo().setSampleShadingEnable(VK_FALSE).setRasterizationSamples(
            vk::SampleCountFlagBits::e1);

        std::vector<vk::PipelineColorBlendAttachmentState> color_blend_attachments = {
          vk::PipelineColorBlendAttachmentState().setBlendEnable(VK_FALSE).setColorWriteMask(
            vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB |
            vk::ColorComponentFlagBits::eA)};

        vk::PipelineColorBlendStateCreateInfo color_blend_info = vk::PipelineColorBlendStateCreateInfo()
                                                                   .setFlags(vk::PipelineColorBlendStateCreateFlags())
                                                                   .setLogicOpEnable(VK_FALSE)
                                                                   .setLogicOp(vk::LogicOp::eCopy)
                                                                   .setAttachmentCount(color_blend_attachments.size())
                                                                   .setPAttachments(color_blend_attachments.data())
                                                                   .setBlendConstants({0.0f, 0.0f, 0.0f, 0.0f});

        vk::GraphicsPipelineCreateInfo info = vk::GraphicsPipelineCreateInfo()
                                                .setStageCount(m_stages.size())
                                                .setPStages(m_stages.data())
                                                .setPVertexInputState(&vertex_input)
                                                .setPInputAssemblyState(&assembly)
                                                .setPViewportState(&viewport_state_info)
                                                .setPRasterizationState(&rasterizer)
                                                .setPMultisampleState(&multisampling)
                                                .setPDepthStencilState(nullptr)
                                                .setPColorBlendState(&color_blend_info)
                                                .setPDynamicState(nullptr)
                                                .setLayout(m_layout)
                                                .setRenderPass(m_render_pass)
                                                .setSubpass(0u)
                                                .setBasePipelineHandle(nullptr)
                                                .setBasePipelineIndex(-1);

        auto [result, pipeline] = m_device.createGraphicsPipeline(m_cache, info);
        if (result != vk::Result::eSuccess)
        {
            throw graphics_pipeline_creation_exception();
        }
        m_pipeline = std::move(pipeline);

        log.debug("successfully created vulkan graphics pipeline");
    }

    EShLanguage vk_shader_stage_to_glslang(vk::ShaderStageFlagBits stage)
    {
        switch (stage)
        {
            case vk::ShaderStageFlagBits::eVertex:
                return EShLangVertex;
            case vk::ShaderStageFlagBits::eTessellationControl:
                return EShLangTessControl;
            case vk::ShaderStageFlagBits::eTessellationEvaluation:
                return EShLangTessEvaluation;
            case vk::ShaderStageFlagBits::eGeometry:
                return EShLangGeometry;
            case vk::ShaderStageFlagBits::eFragment:
                return EShLangFragment;
            case vk::ShaderStageFlagBits::eCompute:
                return EShLangCompute;
            case vk::ShaderStageFlagBits::eRaygenNV:
                return EShLangRayGenNV;
            case vk::ShaderStageFlagBits::eAnyHitNV:
                return EShLangAnyHitNV;
            case vk::ShaderStageFlagBits::eClosestHitNV:
                return EShLangClosestHitNV;
            case vk::ShaderStageFlagBits::eMissNV:
                return EShLangMissNV;
            case vk::ShaderStageFlagBits::eIntersectionNV:
                return EShLangIntersectNV;
            case vk::ShaderStageFlagBits::eCallableNV:
                return EShLangCallableNV;
            case vk::ShaderStageFlagBits::eTaskNV:
                return EShLangTaskNV;
            case vk::ShaderStageFlagBits::eMeshNV:
                return EShLangMeshNV;
            default:
                return EShLangVertex;
        }
    }

    vk::ShaderModule vulkan::create_shader_module(vk::ShaderStageFlagBits type, const std::string& glsl) const
    {
        std::vector<unsigned int> spir_v;
        EShLanguage stage = vk_shader_stage_to_glslang(type);

        const char* shader_strings[1];
        shader_strings[0] = glsl.data();

        glslang::TShader shader(stage);
        shader.setStrings(shader_strings, 1);

        int input_version = 450;
        glslang::EShTargetClientVersion client_version = glslang::EShTargetVulkan_1_0;
        glslang::EShTargetLanguageVersion target_version = glslang::EShTargetSpv_1_0;

        shader.setEnvInput(glslang::EShSourceGlsl, stage, glslang::EShClientVulkan, input_version);
        shader.setEnvClient(glslang::EShClientVulkan, client_version);
        shader.setEnvTarget(glslang::EShTargetSpv, target_version);
        EShMessages messages = static_cast<EShMessages>(EShMsgSpvRules | EShMsgVulkanRules);

        if (!shader.parse(&DefaultTBuiltInResource, 100, false, messages))
        {
            log.error("{}", shader.getInfoLog());
            log.error("{}", shader.getInfoDebugLog());
            return {};
        }

        glslang::TProgram program;
        program.addShader(&shader);

        if (!program.link(messages))
        {
            log.error("{}", shader.getInfoLog());
            log.error("{}", shader.getInfoDebugLog());
            return {};
        }

        spv::SpvBuildLogger spv_logger;
        glslang::SpvOptions spv_options;
        glslang::GlslangToSpv(*program.getIntermediate(stage), spir_v, &spv_logger, &spv_options);
        return m_device.createShaderModule(vk::ShaderModuleCreateInfo(vk::ShaderModuleCreateFlags(), spir_v));
    }

    void vulkan::create_command_buffers()
    {
        log.debug("creating vulkan command buffer");

        vk::CommandBufferAllocateInfo info = vk::CommandBufferAllocateInfo()
                                               .setCommandPool(m_command_pool)
                                               .setLevel(vk::CommandBufferLevel::ePrimary)
                                               .setCommandBufferCount(m_framebuffers.size());

        m_command_buffers = m_device.allocateCommandBuffers(info);

        std::vector<vk::ClearValue> clear_colors = {vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f})};

        for (auto [command_buffer, framebuffer, descriptor_set] :
             detail::zip(m_command_buffers, m_framebuffers, m_descriptor_sets))
        {
            command_buffer.begin(vk::CommandBufferBeginInfo());
            {
                vk::RenderPassBeginInfo render_pass_info = vk::RenderPassBeginInfo()
                                                             .setRenderPass(m_render_pass)
                                                             .setFramebuffer(framebuffer)
                                                             .setRenderArea(render_area())
                                                             .setClearValueCount(clear_colors.size())
                                                             .setPClearValues(clear_colors.data());

                command_buffer.beginRenderPass(render_pass_info, vk::SubpassContents::eInline);
                {
                    command_buffer.bindPipeline(vk::PipelineBindPoint::eGraphics, m_pipeline);
                    command_buffer.bindDescriptorSets(
                      vk::PipelineBindPoint::eGraphics, m_layout, 0, descriptor_set, nullptr);
                    command_buffer.draw(3, 1, 0, 0);
                }
                command_buffer.endRenderPass();
            }
            command_buffer.end();
        }

        log.debug("successfully created vulkan command buffer");
    }

    vk::CommandBuffer& vulkan::current_buffer(std::uint32_t image_in_flight_index)
    {
        return m_command_buffers.at(image_in_flight_index);
    }

    void vulkan::create_semaphores()
    {
        log.debug("creating vulkan synchronizer");
        m_number_of_frames_in_flight = 2;
        m_image_available_semaphores.resize(m_number_of_frames_in_flight);
        m_render_finished_semaphores.resize(m_number_of_frames_in_flight);
        m_in_flight_fences.resize(m_number_of_frames_in_flight);
        for (auto [image_available, render_finished, in_flight] :
             detail::zip(m_image_available_semaphores, m_render_finished_semaphores, m_in_flight_fences))
        {
            image_available = m_device.createSemaphore(vk::SemaphoreCreateInfo());
            render_finished = m_device.createSemaphore(vk::SemaphoreCreateInfo());
            in_flight = m_device.createFence(vk::FenceCreateInfo().setFlags(vk::FenceCreateFlagBits::eSignaled));
        }
        log.debug("successfully created vulkan synchronizer");
    }

    void vulkan::next_frame() { m_current_frame = (m_current_frame + 1) % m_number_of_frames_in_flight; }

    const vk::Semaphore& vulkan::image_available_semaphore() const
    {
        return m_image_available_semaphores.at(m_current_frame);
    }

    const vk::Semaphore& vulkan::render_finished_semaphore() const
    {
        return m_render_finished_semaphores.at(m_current_frame);
    }

    const vk::Fence& vulkan::in_flight_fence() const { return m_in_flight_fences.at(m_current_frame); }

    void vulkan::create_fences() { m_images_in_flight.resize(m_images.size(), nullptr); }

    const char* suitable_physical_device_not_found_exception::what() const noexcept
    {
        return "failed to find a suitable GPU.";
    }

    const char* graphics_pipeline_creation_exception::what() const noexcept
    {
        return "failed to create the graphics pipeline.";
    }
}  // namespace caldera