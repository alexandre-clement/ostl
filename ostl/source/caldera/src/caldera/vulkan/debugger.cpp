#include "caldera/vulkan/debugger.hpp"

#include <detail/detail.hpp>
namespace caldera
{
    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
      VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
      VkDebugUtilsMessageTypeFlagsEXT,
      const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
      void*)
    {
        static detail::logger logger = detail::create_class_logger("caldera::debugger");
        switch (messageSeverity)
        {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                logger.trace(pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                logger.info(pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                logger.warn(pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                logger.error(pCallbackData->pMessage);
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
                logger.critical(pCallbackData->pMessage);
                break;
            default:
                break;
        }

        return VK_FALSE;
    }

    debugger::debugger()
    {
        messenger_info
          .setMessageSeverity(
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eError | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo)
          .setMessageType(
            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
            vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation)
          .setPfnUserCallback(debug_callback);

        validation_layers.push_back("VK_LAYER_KHRONOS_validation");
        validation_layers.push_back("VK_LAYER_LUNARG_monitor");
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
}  // namespace caldera