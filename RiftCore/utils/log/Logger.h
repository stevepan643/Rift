#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace Rift {
class Log {
public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
    return CoreLogger;
  }
  inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
    return ClientLogger;
  }

private:
  static std::shared_ptr<spdlog::logger> CoreLogger;
  static std::shared_ptr<spdlog::logger> ClientLogger;
};
} // namespace Rift

#define RF_CORE_TRACE(...) ::Rift::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RF_CORE_DEBUG(...) ::Rift::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define RF_CORE_INFO(...) ::Rift::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RF_CORE_WARN(...) ::Rift::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RF_CORE_ERROR(...) ::Rift::Log::GetCoreLogger()->error(__VA_ARGS__)

#define RF_TRACE(...) ::Rift::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RF_DEBUG(...) ::Rift::Log::GetClientLogger()->debug(__VA_ARGS__)
#define RF_INFO(...) ::Rift::Log::GetClientLogger()->info(__VA_ARGS__)
#define RF_WARN(...) ::Rift::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RF_ERROR(...) ::Rift::Log::GetClientLogger()->error(__VA_ARGS__)
