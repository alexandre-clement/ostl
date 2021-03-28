#include "detail/logging/logger.hpp"

namespace detail
{
    logger create_class_logger(std::string class_name)
    {
        if (auto already_created = spdlog::get(class_name))
        {
            return logger(*already_created.get());
        }
        std::shared_ptr<logger> class_logger = spdlog::stdout_color_mt(std::move(class_name));
        class_logger->set_level(spdlog::default_logger()->level());
        class_logger->set_pattern("[%Y-%m-%d %T.%e] %-24!n %^[%l]\t%v%$");
        return logger(*class_logger.get());
    }
}  // namespace detail
