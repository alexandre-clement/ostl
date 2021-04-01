#pragma once

#include <exception>
#include <optional>
#include <stdint.h>
#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>

#include <detail/detail.hpp>

#include "configuration.hpp"
#include "debugger.hpp"
#include "utility.hpp"

namespace caldera
{
    class queue_family_indices
    {
    public:
        [[nodiscard]] bool is_complete() const;
        [[nodiscard]] queue_family_indices build() const;

        std::optional<std::uint32_t> graphics_family;
        std::optional<std::uint32_t> present_family;
    };

    class physical_device_extensions
    {
    public:
        [[nodiscard]] queue_family_indices build() const;

        bool contains_all_required_extensions = true;
        std::vector<std::string> extensions;
    };

    class swap_chain_details
    {
    public:
        [[nodiscard]] bool is_adequate() const;

        vk::SurfaceCapabilitiesKHR surface_capabilities;
        std::vector<vk::SurfaceFormatKHR> surface_formats;
        std::vector<vk::PresentModeKHR> present_modes;
    };

    class physical_device_properties
    {
    public:
        const std::uint32_t graphics_family;
        const std::uint32_t present_family;
        const std::vector<std::uint32_t> indices;

        const std::vector<std::string> extensions;

        const vk::SurfaceCapabilitiesKHR surface_capabilities;
        const std::vector<vk::SurfaceFormatKHR> surface_formats;
        const std::vector<vk::PresentModeKHR> present_modes;
    };

    class physical_device_evaluation
    {
    public:
        [[nodiscard]] bool is_suitable() const;
        [[nodiscard]] physical_device_properties build() const;
        [[nodiscard]] bool operator>(const physical_device_evaluation&) const;

        unsigned int score = 1;
        bool is_discrete = false;
        queue_family_indices indices;
        physical_device_extensions pde;
        swap_chain_details swap_chain;
    };

    class queue_sharing_mode
    {
    public:
        const vk::SharingMode sharing_mode;
        const std::uint32_t index_count;
        const std::uint32_t* indices;
    };

    class vulkan : private detail::loggable<vulkan>
    {
    public:
        vulkan(configuration);
        ~vulkan();

    private:
        void create_instance();
        void bind_surface();
        void pick_physical_device();
        [[nodiscard]] physical_device_evaluation evaluate_physical_device_properties(const vk::PhysicalDevice&) const;
        [[nodiscard]] queue_family_indices find_queue_families(const vk::PhysicalDevice&) const;
        [[nodiscard]] physical_device_extensions
          look_for_gpu_extensions(const vk::PhysicalDevice&, const std::vector<std::string>&) const;
        [[nodiscard]] std::vector<std::string> get_available_gpu_extensions(const vk::PhysicalDevice&) const;
        [[nodiscard]] std::vector<std::string> get_required_gpu_extensions() const;
        [[nodiscard]] swap_chain_details query_swap_chain_support(const vk::PhysicalDevice&) const;
        [[nodiscard]] physical_device_properties gpu_properties() const;
        void create_logical_device();
        void create_command_pool();
        void create_swap_chain();
        [[nodiscard]] vk::SurfaceFormatKHR choose_swap_surface_format(const std::vector<vk::SurfaceFormatKHR>&) const;
        [[nodiscard]] vk::PresentModeKHR choose_swap_present_mode(const std::vector<vk::PresentModeKHR>&) const;
        [[nodiscard]] vk::Extent2D choose_swap_extent(const vk::SurfaceCapabilitiesKHR&) const;
        [[nodiscard]] queue_sharing_mode select_sharing_mode(const physical_device_properties&) const;
        void create_image_views();
        void create_render_pass();
        void create_framebuffers();
        void create_descriptor_pool();
        void create_uniform_buffer();
        [[nodiscard]] std::uint32_t find_memory_type(std::uint32_t, vk::MemoryPropertyFlags) const;
        void create_descriptor_set_layout();
        void create_descriptor_sets();
        void create_pipeline_layout();
        void create_graphic_pipeline();
        [[nodiscard]] vk::ShaderModule create_shader_module(vk::ShaderStageFlagBits, const std::string&) const;

        configuration m_configuration;
        debugger m_debugger;
        const std::string engine_name = "caldera";
        const std::uint32_t engine_version = caldera_version;

        vk::Instance m_instance;
        vk::SurfaceKHR m_surface;
        vk::PhysicalDevice m_physical_device;
        vk::Device m_device;
        vk::Queue m_graphics_queue;
        vk::Queue m_present_queue;
        vk::CommandPool m_command_pool;
        vk::SwapchainKHR m_swap_chain;
        std::vector<vk::Image> m_images;
        vk::Format m_format;
        vk::Extent2D m_extent;
        std::vector<vk::ImageView> m_image_views;
        vk::RenderPass m_render_pass;
        std::vector<vk::Framebuffer> m_framebuffers;
        vk::DescriptorPool m_descriptor_pool;
        std::vector<vk::Buffer> m_buffers;
        std::vector<vk::DeviceMemory> m_memory;
        vk::DeviceSize m_buffer_size = 256u;
        vk::DescriptorSetLayout m_descriptor_set_layout;
        std::vector<vk::DescriptorSet> m_descriptor_sets;
        vk::PipelineLayout m_layout;
        std::vector<vk::PipelineShaderStageCreateInfo> m_stages;
        vk::Pipeline m_pipeline;
        vk::PipelineCache m_cache;
    };

    class caldera_exception : public std::exception
    {
    };

    class suitable_physical_device_not_found_exception : public caldera_exception
    {
    public:
        const char* what() const noexcept override;
    };

    class graphics_pipeline_creation_exception : public caldera_exception
    {
    public:
        const char* what() const noexcept override;
    };
}  // namespace caldera