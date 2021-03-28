#pragma once

#include <string>
#include <string_view>

#include <spdlog/spdlog.h>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace detail
{
    using logger = spdlog::logger;

    namespace level = spdlog::level;

    using spdlog::set_level;

    logger create_class_logger(std::string);
}  // namespace detail