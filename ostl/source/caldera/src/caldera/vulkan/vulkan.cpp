#include "caldera/vulkan/vulkan.hpp"

#include <algorithm>
#include <set>

#include <SPIRV/GlslangToSpv.h>

#include <glslang/Include/ResourceLimits.h>

namespace caldera
{
    const TBuiltInResource DefaultTBuiltInResource = {.maxLights = 32,
      .maxClipPlanes = 6,
      .maxTextureUnits = 32,
      .maxTextureCoords = 32,
      .maxVertexAttribs = 64,
      .maxVertexUniformComponents = 4096,
      .maxVaryingFloats = 64,
      .maxVertexTextureImageUnits = 32,
      .maxCombinedTextureImageUnits = 80,
      .maxTextureImageUnits = 32,
      .maxFragmentUniformComponents = 4096,
      .maxDrawBuffers = 32,
      .maxVertexUniformVectors = 128,
      .maxVaryingVectors = 8,
      .maxFragmentUniformVectors = 16,
      .maxVertexOutputVectors = 16,
      .maxFragmentInputVectors = 15,
      .minProgramTexelOffset = -8,
      .maxProgramTexelOffset = 7,
      .maxClipDistances = 8,
      .maxComputeWorkGroupCountX = 65535,
      .maxComputeWorkGroupCountY = 65535,
      .maxComputeWorkGroupCountZ = 65535,
      .maxComputeWorkGroupSizeX = 1024,
      .maxComputeWorkGroupSizeY = 1024,
      .maxComputeWorkGroupSizeZ = 64,
      .maxComputeUniformComponents = 1024,
      .maxComputeTextureImageUnits = 16,
      .maxComputeImageUniforms = 8,
      .maxComputeAtomicCounters = 8,
      .maxComputeAtomicCounterBuffers = 1,
      .maxVaryingComponents = 60,
      .maxVertexOutputComponents = 64,
      .maxGeometryInputComponents = 64,
      .maxGeometryOutputComponents = 128,
      .maxFragmentInputComponents = 128,
      .maxImageUnits = 8,
      .maxCombinedImageUnitsAndFragmentOutputs = 8,
      .maxCombinedShaderOutputResources = 8,
      .maxImageSamples = 0,
      .maxVertexImageUniforms = 0,
      .maxTessControlImageUniforms = 0,
      .maxTessEvaluationImageUniforms = 0,
      .maxGeometryImageUniforms = 0,
      .maxFragmentImageUniforms = 8,
      .maxCombinedImageUniforms = 8,
      .maxGeometryTextureImageUnits = 16,
      .maxGeometryOutputVertices = 256,
      .maxGeometryTotalOutputComponents = 1024,
      .maxGeometryUniformComponents = 1024,
      .maxGeometryVaryingComponents = 64,
      .maxTessControlInputComponents = 128,
      .maxTessControlOutputComponents = 128,
      .maxTessControlTextureImageUnits = 16,
      .maxTessControlUniformComponents = 1024,
      .maxTessControlTotalOutputComponents = 4096,
      .maxTessEvaluationInputComponents = 128,
      .maxTessEvaluationOutputComponents = 128,
      .maxTessEvaluationTextureImageUnits = 16,
      .maxTessEvaluationUniformComponents = 1024,
      .maxTessPatchComponents = 120,
      .maxPatchVertices = 32,
      .maxTessGenLevel = 64,
      .maxViewports = 16,
      .maxVertexAtomicCounters = 0,
      .maxTessControlAtomicCounters = 0,
      .maxTessEvaluationAtomicCounters = 0,
      .maxGeometryAtomicCounters = 0,
      .maxFragmentAtomicCounters = 8,
      .maxCombinedAtomicCounters = 8,
      .maxAtomicCounterBindings = 1,
      .maxVertexAtomicCounterBuffers = 0,
      .maxTessControlAtomicCounterBuffers = 0,
      .maxTessEvaluationAtomicCounterBuffers = 0,
      .maxGeometryAtomicCounterBuffers = 0,
      .maxFragmentAtomicCounterBuffers = 1,
      .maxCombinedAtomicCounterBuffers = 1,
      .maxAtomicCounterBufferSize = 16384,
      .maxTransformFeedbackBuffers = 4,
      .maxTransformFeedbackInterleavedComponents = 64,
      .maxCullDistances = 8,
      .maxCombinedClipAndCullDistances = 8,
      .maxSamples = 4,
      .maxMeshOutputVerticesNV = 256,
      .maxMeshOutputPrimitivesNV = 512,
      .maxMeshWorkGroupSizeX_NV = 32,
      .maxMeshWorkGroupSizeY_NV = 1,
      .maxMeshWorkGroupSizeZ_NV = 1,
      .maxTaskWorkGroupSizeX_NV = 32,
      .maxTaskWorkGroupSizeY_NV = 1,
      .maxTaskWorkGroupSizeZ_NV = 1,
      .maxMeshViewCountNV = 4,

      .limits = {
        .nonInductiveForLoops = 1,
        .whileLoops = 1,
        .doWhileLoops = 1,
        .generalUniformIndexing = 1,
        .generalAttributeMatrixVectorIndexing = 1,
        .generalVaryingIndexing = 1,
        .generalSamplerIndexing = 1,
        .generalVariableIndexing = 1,
        .generalConstantMatrixVectorIndexing = 1,
      }};

    bool queue_family_indices::is_complete() const { return graphics_family.has_value() && present_family.has_value(); }

    bool swap_chain_details::is_adequate() const { return !surface_formats.empty() && !present_modes.empty(); }

    bool physical_device_evaluation::is_suitable() const
    {
        return is_discrete && indices.is_complete() && pde.contains_all_required_extensions && swap_chain.is_adequate();
    }

    physical_device_properties physical_device_evaluation::build() const
    {
        return {indices.graphics_family.value(),
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
        create_stages();
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
        destroy_command_buffers();
        destroy_graphic_pipeline();
        destroy_stages();
        destroy_pipeline_layout();
        destroy_descriptor_set_layout();
        for (auto [buffer, memory] : detail::zip(m_buffers, m_memory))
        {
            m_device.destroyBuffer(buffer);
            m_device.freeMemory(memory);
        }
        destroy_descriptor_pool();
        destroy_framebuffers();
        destroy_render_pass();
        destroy_image_views();
        destroy_swap_chain();
        m_device.destroyCommandPool(m_command_pool);
        m_device.destroy();
        m_instance.destroySurfaceKHR(m_surface);
        m_instance.destroy(nullptr);
    }

    void vulkan::update_shader(const glass::shader& p_shader) { m_shader = p_shader; }

    void vulkan::render()
    {
        try
        {
            render_frame();
        }
        catch (vk::OutOfDateKHRError)
        {
            recreate_swap_chain();
            return;
        }
        catch (vk::SystemError e)
        {
            log.error("failed to render frame cause of {}", e.what());
            return;
        }
    }

    void vulkan::render_frame()
    {
        while (vk::Result::eTimeout == m_device.waitForFences(in_flight_fence(), VK_TRUE, UINT64_MAX))
            ;

        auto index = m_device.acquireNextImageKHR(m_swap_chain, UINT64_MAX, image_available_semaphore(), nullptr).value;

        if (in_flight_image(index))
        {
            while (vk::Result::eTimeout == m_device.waitForFences(in_flight_image(index), VK_TRUE, UINT64_MAX))
                ;
        }

        in_flight_image(index) = in_flight_fence();

        update_uniform_variables(index);

        vk::PipelineStageFlags wait_dst_stage_mask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
        vk::SubmitInfo submit_info = vk::SubmitInfo(image_available_semaphore(),
          wait_dst_stage_mask,
          current_buffer(index),
          render_finished_semaphore());

        m_device.resetFences(in_flight_fence());
        m_graphics_queue.submit(submit_info, in_flight_fence());

        vk::PresentInfoKHR present_info = vk::PresentInfoKHR(render_finished_semaphore(), m_swap_chain, index);

        m_present_queue.presentKHR(present_info);

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
                                                               .setApiVersion(VK_MAKE_VERSION(1, 2, VK_HEADER_VERSION));

        const vk::InstanceCreateInfo instance_informations =
          vk::InstanceCreateInfo({}, &application_informations, m_debugger.validation_layers, extensions)
            .setPNext(&m_debugger.messenger_info);

        m_instance = vk::createInstance(instance_informations);

        log.debug("successfully created vulkan instance");
    }

    void vulkan::bind_surface() { m_surface = m_configuration.create_surface(m_instance); }

    void vulkan::pick_physical_device()
    {
        log.info("selecting the best gpu available");
        const auto devices = m_instance.enumeratePhysicalDevices();
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
            if (device.getSurfaceSupportKHR(index, m_surface))
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

    physical_device_extensions vulkan::look_for_gpu_extensions(const vk::PhysicalDevice& device,
      const std::vector<std::string>& required_gpu_extensions) const
    {
        physical_device_extensions pde;
        const std::vector<std::string> available_gpu_extensions = get_available_gpu_extensions(device);
        for (const auto& gpu_extension : required_gpu_extensions)
        {
            if (std::find(available_gpu_extensions.begin(), available_gpu_extensions.end(), gpu_extension)
                == available_gpu_extensions.end())
            {
                log.debug("{} misses extension {}", device.getProperties().deviceName, gpu_extension);
                pde.contains_all_required_extensions = false;
            }
            else
            {
                pde.extensions.emplace_back(gpu_extension);
            }
        }
        return pde;
    }

    std::vector<std::string> vulkan::get_available_gpu_extensions(const vk::PhysicalDevice& device) const
    {
        auto properties = device.enumerateDeviceExtensionProperties();
        std::vector<std::string> available_gpu_extensions{properties.size()};
        for (const auto& extension : properties)
        {
            available_gpu_extensions.push_back(extension.extensionName);
        }
        return available_gpu_extensions;
    }

    std::vector<std::string> vulkan::get_required_gpu_extensions() const { return {VK_KHR_SWAPCHAIN_EXTENSION_NAME}; }

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
        const std::array<const float, 1> priorities{1.0f};
        std::vector<vk::DeviceQueueCreateInfo> queue_informations;
        std::set<std::uint32_t> queues_indices = {properties.graphics_family, properties.present_family};

        for (std::uint32_t index : queues_indices)
        {
            queue_informations.emplace_back(vk::DeviceQueueCreateFlags(), index, priorities);
        }
        log.debug("{} vulkan extensions will be loaded:", properties.extensions.size());
        for (const auto& extension : properties.extensions)
        {
            log.debug("\t{}", extension);
        }

        auto vk_extensions = detail::map(properties.extensions,
          std::function([](const std::string& s) -> const char* { return s.c_str(); }));

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
        vk::CommandPoolCreateInfo info{vk::CommandPoolCreateFlags(), gpu_properties().graphics_family};

        m_command_pool = m_device.createCommandPool(info);
    }

    void vulkan::create_swap_chain()
    {
        log.debug("creating vulkan swap chain");
        auto properties = gpu_properties();

        vk::SwapchainCreateFlagsKHR flags = vk::SwapchainCreateFlagsKHR();
        std::uint32_t min_image_count = properties.surface_capabilities.minImageCount + 1u;
        if (properties.surface_capabilities.maxImageCount > 0u && min_image_count > properties.surface_capabilities.maxImageCount)
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
                                            .setImageArrayLayers(1u)
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

    vk::SurfaceFormatKHR vulkan::choose_swap_surface_format(const std::vector<vk::SurfaceFormatKHR>& surface_formats) const
    {
        for (const auto& surface_format : surface_formats)
        {
            if (surface_format.format == vk::Format::eB8G8R8A8Unorm && surface_format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
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
              std::clamp(std::uint32_t(m_configuration.framebuffer.x),
                capabilities.minImageExtent.width,
                capabilities.maxImageExtent.width),
              std::clamp(std::uint32_t(m_configuration.framebuffer.y),
                capabilities.minImageExtent.height,
                capabilities.maxImageExtent.height),
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
            vk::ImageViewCreateInfo info = vk::ImageViewCreateInfo()
                                             .setImage(image)
                                             .setViewType(vk::ImageViewType::e2D)
                                             .setFormat(m_format)
                                             .setComponents(vk::ComponentMapping())
                                             .setSubresourceRange(
                                               vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));

            image_view = m_device.createImageView(info);
        }

        log.debug("successfully created vulkan image views");
    }

    void vulkan::destroy_swap_chain() { m_device.destroySwapchainKHR(m_swap_chain); }

    void vulkan::destroy_image_views()
    {
        for (auto& image_view : m_image_views)
        {
            m_device.destroyImageView(image_view);
        }
    }

    void vulkan::create_render_pass()
    {
        log.debug("creating vulkan render pass");

        std::vector<vk::AttachmentDescription> color_attachments = {vk::AttachmentDescription()
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

        std::vector<vk::SubpassDescription> subpasses_descriptions = {vk::SubpassDescription()
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
            .setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite)};

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

    void vulkan::destroy_render_pass() { m_device.destroyRenderPass(m_render_pass); }

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

    void vulkan::destroy_framebuffers()
    {
        for (auto& framebuffer : m_framebuffers)
        {
            m_device.destroyFramebuffer(framebuffer);
        }
    }

    void vulkan::create_descriptor_pool()
    {
        std::vector<vk::DescriptorPoolSize> pool_sizes{
          vk::DescriptorPoolSize().setType(vk::DescriptorType::eUniformBuffer).setDescriptorCount(m_images.size())};

        vk::DescriptorPoolCreateInfo info = vk::DescriptorPoolCreateInfo()
                                              .setMaxSets(m_images.size())
                                              .setPoolSizeCount(pool_sizes.size())
                                              .setPPoolSizes(pool_sizes.data());

        m_descriptor_pool = m_device.createDescriptorPool(info);
    }

    void vulkan::destroy_descriptor_pool() { m_device.destroyDescriptorPool(m_descriptor_pool); }

    void vulkan::create_uniform_buffer()
    {
        m_buffers.resize(m_images.size());
        m_memory.resize(m_images.size());

        for (auto [buffer, memory] : detail::zip(m_buffers, m_memory))
        {
            vk::BufferCreateInfo buffer_info =
              vk::BufferCreateInfo().setSize(m_shader.uniform_data_size()).setUsage(vk::BufferUsageFlagBits::eUniformBuffer);

            buffer = m_device.createBuffer(buffer_info);

            auto requirements = m_device.getBufferMemoryRequirements(buffer);

            vk::MemoryAllocateInfo memory_info = vk::MemoryAllocateInfo()
                                                   .setAllocationSize(requirements.size)
                                                   .setMemoryTypeIndex(find_memory_type(requirements.memoryTypeBits,
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

    void vulkan::destroy_descriptor_set_layout() { m_device.destroyDescriptorSetLayout(m_descriptor_set_layout); }

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
            vk::DescriptorBufferInfo buffer_info = vk::DescriptorBufferInfo().setBuffer(buffer).setOffset(0ul).setRange(
              m_shader.uniform_data_size());

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

    void vulkan::destroy_pipeline_layout() { m_device.destroyPipelineLayout(m_layout); }

    void vulkan::create_stages()
    {
        glslang::InitializeProcess();
        vk::ShaderModule vertex = create_shader_module(vk::ShaderStageFlagBits::eVertex, m_shader.vertex());
        vk::ShaderModule fragment = create_shader_module(vk::ShaderStageFlagBits::eFragment, m_shader.fragment());
        glslang::FinalizeProcess();

        m_stages = {{vk::PipelineShaderStageCreateFlags(), vk::ShaderStageFlagBits::eVertex, vertex, "main"},
          {vk::PipelineShaderStageCreateFlags(), vk::ShaderStageFlagBits::eFragment, fragment, "main"}};
    }

    void vulkan::destroy_stages()
    {
        for (const auto& stage : m_stages)
        {
            m_device.destroyShaderModule(stage.module);
        }
    }

    void vulkan::create_graphic_pipeline()
    {
        log.debug("creating vulkan graphics pipeline");

        vk::PipelineVertexInputStateCreateInfo vertex_input =
          vk::PipelineVertexInputStateCreateInfo().setVertexBindingDescriptionCount(0u).setVertexAttributeDescriptionCount(0u);

        vk::PipelineInputAssemblyStateCreateInfo assembly =
          vk::PipelineInputAssemblyStateCreateInfo().setTopology(vk::PrimitiveTopology::eTriangleList).setPrimitiveRestartEnable(VK_FALSE);

        vk::Viewport viewport = vk::Viewport(0.0f, 0.0f, m_extent.width, m_extent.height, 0, 1.0f);
        vk::Rect2D scissors(render_area());

        vk::PipelineViewportStateCreateInfo viewport_state_info =
          vk::PipelineViewportStateCreateInfo().setViewportCount(1u).setPViewports(&viewport).setScissorCount(1u).setPScissors(
            &scissors);

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
            vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB
            | vk::ColorComponentFlagBits::eA)};

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

    void vulkan::destroy_graphic_pipeline() { m_device.destroyPipeline(m_pipeline); }

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

        for (auto [command_buffer, framebuffer, descriptor_set] : detail::zip(m_command_buffers, m_framebuffers, m_descriptor_sets))
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
                    command_buffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, m_layout, 0, descriptor_set, nullptr);
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

    void vulkan::destroy_command_buffers() { m_device.freeCommandBuffers(m_command_pool, m_command_buffers); }

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

    vk::Fence& vulkan::in_flight_image(std::uint32_t p_index) { return m_images_in_flight.at(p_index); }

    const vk::Fence& vulkan::in_flight_image(std::uint32_t p_index) const { return m_images_in_flight.at(p_index); }

    void vulkan::create_fences() { m_images_in_flight.resize(m_images.size(), nullptr); }

    void vulkan::update_uniform_variables(std::uint32_t p_index)
    {
        if (std::uint64_t total_size = m_shader.uniform_data_size() > 0ul)
        {
            char* data = static_cast<char*>(m_device.mapMemory(m_memory.at(p_index), 0ul, total_size));
            std::uint64_t offset = 0ul;
            for (const auto& [address, size] : m_shader.list_uniform_data())
            {
                memcpy(data + offset, address, size);
                offset += size;
            }
            m_device.unmapMemory(m_memory.at(p_index));
        }
    }

    void vulkan::recreate_swap_chain()
    {
        log.warn("recreating swap chain");

        while (m_configuration.framebuffer.x == 0 || m_configuration.framebuffer.y == 0)
        {
            m_configuration.wait();
        }

        m_device.waitIdle();

        destroy_framebuffers();
        destroy_command_buffers();
        destroy_graphic_pipeline();
        destroy_pipeline_layout();
        destroy_descriptor_set_layout();
        destroy_descriptor_pool();

        destroy_render_pass();
        destroy_image_views();
        destroy_swap_chain();

        create_swap_chain();
        create_image_views();
        create_render_pass();

        create_descriptor_pool();
        create_descriptor_set_layout();
        create_descriptor_sets();
        create_pipeline_layout();
        create_graphic_pipeline();
        create_framebuffers();
        create_command_buffers();

        log.info("successfully recreated image buffer.");
    }

    const char* suitable_physical_device_not_found_exception::what() const noexcept
    {
        return "failed to find a suitable GPU.";
    }

    const char* graphics_pipeline_creation_exception::what() const noexcept
    {
        return "failed to create the graphics pipeline.";
    }
}  // namespace caldera