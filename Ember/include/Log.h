#ifndef EMBER_LOG
#define EMBER_LOG

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ember
{

    class EMBER_API Log
    {
    public:

        static void Init();
        static std::shared_ptr<spdlog::logger>& getCoreLogger();
        static std::shared_ptr<spdlog::logger>& getClientLogger();

    private:

        static std::shared_ptr<spdlog::logger> core_logger;
        static std::shared_ptr<spdlog::logger> client_logger;
    };

};

#define ER_CORE_ERR(...) ::Ember::Log::getCoreLogger()->error(__VA_ARGS__)
#define ER_CORE_WRN(...) ::Ember::Log::getCoreLogger()->warn(__VA_ARGS__)
#define ER_CORE_INF(...) ::Ember::Log::getCoreLogger()->info(__VA_ARGS__)
#define ER_CORE_TRC(...) ::Ember::Log::getCoreLogger()->trace(__VA_ARGS__)
#define ER_CORE_FTL(...) ::Ember::Log::getCoreLogger()->fatal(__VA_ARGS__)

#define ER_ERR(...) ::Ember::Log::getClientLogger()->error(__VA_ARGS__)
#define ER_WRN(...) ::Ember::Log::getClientLogger()->warn(__VA_ARGS__)
#define ER_INF(...) ::Ember::Log::getClientLogger()->info(__VA_ARGS__)
#define ER_TRC(...) ::Ember::Log::getClientLogger()->trace(__VA_ARGS__)
#define ER_FTL(...) ::Ember::Log::getClientLogger()->fatal(__VA_ARGS__)

#endif