#pragma once

#include <iostream>
#include <type_traits>
#include <string>

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK() __builtin_trap()
#endif //_WIN32

namespace Nexus
{
  enum class LogColor
  {
    green = 32,
    yellow = 33,
    red = 31
  };

  inline void _log_impl(std::ostream& os)
  {
    os << "\033[0m"<< "\n";
  }

  template<typename T, typename... Args>
  inline void _log_impl(std::ostream& os, const T &first, Args... args)
  {
    os << first;
    _log_impl(os, args...);
  }

  template<typename... Args>
  inline void _log(LogColor color, const std::string &prefix, const std::string &msg, Args... args)
  {
    std::cout << "\033[0;"<<static_cast<std::underlying_type_t<LogColor>>(color)<<"m["<<prefix<<"]: "<<msg;
    _log_impl(std::cout, args...);
  }
}

// TODO: Add Assert also
#ifdef NX_ENGINE
#define NX_ENGINE_INFO(msg, ...)  Nexus::_log(Nexus::LogColor::green, "Engine Info", msg, ##__VA_ARGS__)
#define NX_ENGINE_WARN(msg, ...)  Nexus::_log(Nexus::LogColor::yellow, "Engine Warn", msg, ##__VA_ARGS__)
#define NX_ENGINE_ERROR(msg, ...) Nexus::_log(Nexus::LogColor::red, "Engine Error", msg, ##__VA_ARGS__)
#define NX_ENGINE_ASSERT(x, msg, ...)                                            \
do {                                                                             \
  if (!(x))                                                                      \
  {                                                                              \
    Nexus::_log(Nexus::LogColor::red, "Engine Assert", msg, ##__VA_ARGS__);  \
    DEBUG_BREAK();                                                               \
  }                                                                              \
} while(0)

#else
#define NX_ENGINE_INFO(msg, ...)
#define NX_ENGINE_WARN(msg, ...)
#define NX_ENGINE_ERROR(msg, ...)
#define NX_ENGINE_ASSERT(x, msg, ...)
#endif // NX_ENGINE

#define NX_GAME_INFO(msg, ...)  Nexus::_log(Nexus::LogColor::green, "Game Info", msg, ##__VA_ARGS__)
#define NX_GAME_WARN(msg, ...)  Nexus::_log(Nexus::LogColor::yellow, "Game Warn", msg, ##__VA_ARGS__)
#define NX_GAME_ERROR(msg, ...) Nexus::_log(Nexus::LogColor::red, "Game Error", msg, ##__VA_ARGS__)
#define NX_GAME_ASSERT(x, msg, ...)                                              \
do {                                                                             \
  if (!(x))                                                                      \
  {                                                                              \
    NX_GAME_ERROR(Nexus::LogColor::red, "Engine Assert", msg, ##__VA_ARGS__);  \
    DEBUG_BREAK();                                                               \
  }                                                                              \
} while(0)
