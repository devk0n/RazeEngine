#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <unistd.h>  // for isatty, fileno

// =====================
// Logger Color Palette
// Gruvbox / S.T.A.L.K.E.R. Inspired
// =====================
namespace LoggerColors {
  // Gruvbox palette: https://github.com/morhetz/gruvbox#palette
  // For 256-color terminals, using xterm color codes.
  // (Change these to whatever you like!)
  static constexpr const char* RESET      = "\033[0m";

  static constexpr const char* DEBUG      = "\033[38;5;108m"; // Gruvbox aqua (#8ec07c)
  static constexpr const char* INFO       = "\033[38;5;109m"; // Gruvbox blue (#83a598)
  static constexpr const char* WARNING    = "\033[38;5;214m"; // Gruvbox yellow/orange (#fabd2f)
  static constexpr const char* ERROR      = "\033[38;5;167m"; // Gruvbox red (#fb4934)

  // Optionally: style the timestamp/source location as subtle/faded
  static constexpr const char* FADED      = "\033[38;5;245m"; // Gruvbox gray (#928374)
}
// =====================

class Logger {
public:
  enum class Level { Debug, Info, Warning, Error };

  struct Config {
    bool showTimestamp;
    bool showLevel;
    bool showSourceLocation;
    bool enableColors;

    constexpr Config()
      : showTimestamp(false),
        showLevel(true),
        showSourceLocation(true),
        enableColors(true) {}

    explicit constexpr Config(
      const bool timestamp,
      const bool level,
      const bool source,
      const bool color)
      : showTimestamp(timestamp),
        showLevel(level),
        showSourceLocation(source),
        enableColors(color) {}
  };

  static void setConfig(const Config& cfg) {
    std::lock_guard lock(mtx);
    m_config = cfg;
  }

  template <typename... Args>
  static void debug(const std::string& file, int line, const std::string& func, Args&&... args) {
    log(Level::Debug, file, line, func, std::forward<Args>(args)...);
  }

  template <typename... Args>
  static void info(const std::string& file, int line, const std::string& func, Args&&... args) {
    log(Level::Info, file, line, func, std::forward<Args>(args)...);
  }

  template <typename... Args>
  static void warn(const std::string& file, int line, const std::string& func, Args&&... args) {
    log(Level::Warning, file, line, func, std::forward<Args>(args)...);
  }

  template <typename... Args>
  static void error(const std::string& file, int line, const std::string& func, Args&&... args) {
    log(Level::Error, file, line, func, std::forward<Args>(args)...);
  }

private:
  static inline std::mutex mtx;
  static inline Config m_config{};

  static const char* levelToStr(const Level level) {
    switch (level) {
      case Level::Debug:   return "DEBUG";
      case Level::Info:    return "INFO";
      case Level::Warning: return "WARNING";
      case Level::Error:   return "ERROR";
    }
    return "UNKNOWN";
  }

  static const char* levelToColor(const Level level) {
    if (!shouldUseColors()) return "";
    using namespace LoggerColors;
    switch (level) {
      case Level::Debug:   return DEBUG;
      case Level::Info:    return INFO;
      case Level::Warning: return WARNING;
      case Level::Error:   return ERROR;
    }
    return RESET;
  }

  static std::string formatSourceLocation(const std::string& file, const int line, const std::string&) {
    const size_t lastSlash = file.find_last_of("/\\");
    const std::string filename = (lastSlash == std::string::npos)
      ? file
      : file.substr(lastSlash + 1);

    return filename + ":" + std::to_string(line);
  }

  static std::tm localTime(std::time_t time) {
    std::tm tm{};
    localtime_r(&time, &tm);  // Linux/POSIX only
    return tm;
  }

  static std::string currentTimestamp() {
    using namespace std::chrono;
    const auto now = system_clock::now();
    const std::time_t time = system_clock::to_time_t(now);
    const std::tm tm = localTime(time);

    char buffer[16];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &tm);
    return {buffer};
  }

  static bool shouldUseColors() {
    return m_config.enableColors && isatty(fileno(stdout));
  }

  template <typename... Args>
  static void log(const Level level, const std::string& file, const int line, const std::string& func, Args&&... args) {
    std::ostringstream oss;

    if (m_config.showTimestamp) {
      if (shouldUseColors())
        oss << LoggerColors::FADED;
      oss << "[" << currentTimestamp() << "] ";
      if (shouldUseColors())
        oss << LoggerColors::RESET;
    }

    if (m_config.showSourceLocation) {
      if (shouldUseColors())
        oss << LoggerColors::FADED;
      oss << "[" << formatSourceLocation(file, line, func) << "] ";
      if (shouldUseColors())
        oss << LoggerColors::RESET;
    }

    if (m_config.showLevel) {
      oss << levelToColor(level) << "[" << levelToStr(level) << "] " << LoggerColors::RESET;
    }

    (oss << ... << std::forward<Args>(args));

    const std::string message = oss.str();

    std::lock_guard lock(mtx);
    std::cout << message << "\n";
  }
};

// Macros to capture source location
#define DEBUG(...) Logger::debug(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define INFO(...)  Logger::info(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define WARN(...)  Logger::warn(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define ERROR(...) Logger::error(__FILE__, __LINE__, __func__, __VA_ARGS__)

#endif // LOGGER_H

