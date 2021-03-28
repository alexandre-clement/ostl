#include "caldera/vulkan/vulkan.hpp"

#include "caldera/vulkan/debugger.hpp"

namespace caldera
{
    vulkan::vulkan(configuration p_configuration) : m_configuration(std::move(p_configuration)) { create_instance(); }

    vulkan::~vulkan()
    {
        log.trace("destroying vulkan instance");
        m_instance.destroy(nullptr);
    }

    void vulkan::create_instance()
    {
        log.trace("creating vulkan instance");
        log.info("instance information : [name : \"{}\", version : {}]", engine_name, engine_version);

        debugger d;
        std::vector<c_str> extensions = m_configuration.required_extensions;
        extensions.insert(extensions.end(), d.extensions.begin(), d.extensions.end());

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

        const vk::InstanceCreateInfo instance_informations = vk::InstanceCreateInfo()
                                                               .setPApplicationInfo(&application_informations)
                                                               .setPNext(&d.messenger_info)
                                                               .setEnabledLayerCount(d.validation_layers.size())
                                                               .setPpEnabledLayerNames(d.validation_layers.data())
                                                               .setEnabledExtensionCount(extensions.size())
                                                               .setPpEnabledExtensionNames(extensions.data());

        m_instance = vk::createInstance(instance_informations);

        log.trace("successfully created vulkan instance");
    }
}  // namespace caldera