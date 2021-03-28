#pragma once

#include <exception>
#include <optional>
#include <stdint.h>
#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>

#include <detail/detail.hpp>

#include "configuration.hpp"
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

        configuration m_configuration;
        const std::string engine_name = "caldera";
        const std::uint32_t engine_version = caldera_version;

        vk::Instance m_instance;
        vk::SurfaceKHR m_surface;
        vk::PhysicalDevice m_physical_device;
    };

    class caldera_exception : public std::exception
    {
    };

    class suitable_physical_device_not_found_exception : public caldera_exception
    {
    public:
        const char* what() const noexcept override;
    };

}  // namespace caldera