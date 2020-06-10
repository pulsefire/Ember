#include "Ember/Log.h"

namespace Ember
{
    std::shared_ptr<spdlog::logger> Log::core_logger;
    std::shared_ptr<spdlog::logger> Log::client_logger;

    void Log::Init()
    {
        // Color range | Time & Logger name: | End color range: Message
        spdlog::set_pattern("%^[%T] %n: %$%v");

        Log::core_logger = spdlog::stdout_color_mt("EMBER");
        Log::core_logger->set_level(spdlog::level::trace);

        Log::client_logger = spdlog::stdout_color_mt("CLIENT");
        Log::client_logger->set_level(spdlog::level::trace);
    }

    std::shared_ptr<spdlog::logger>& Log::getCoreLogger()
    {
        return Log::core_logger;
    }

    std::shared_ptr<spdlog::logger>& Log::getClientLogger()
    {
        return Log::client_logger;
    }

};