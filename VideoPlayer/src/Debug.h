#pragma once
#include <string>

class Debug {
public:
    static void Log(const std::string& message);
    static void LogWarning(const std::string& message);
    static void LogError(const std::string& message);

    // New printf-style versions
    static void LogError(const char* format, ...);
    static void LogWarning(const char* format, ...);
    static void Log(const char* format, ...);
};
