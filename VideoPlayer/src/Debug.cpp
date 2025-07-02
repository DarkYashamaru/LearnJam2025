#include "Debug.h"
#include <iostream>
#include <cstdarg>
#include <vector>

void Debug::Log(const std::string& message) {
    std::cout << message << std::endl;
}

void Debug::LogWarning(const std::string& message) {
    std::cout << "[WARNING] " << message << std::endl;
}

void Debug::LogError(const std::string& message) {
    std::cerr << "[ERROR] " << message << std::endl;
}

// printf-style versions
void Debug::LogError(const char* format, ...) {
    va_list args;
    va_start(args, format);

    // Format into a buffer
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    LogError(std::string(buffer));
}

void Debug::LogWarning(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    LogWarning(std::string(buffer));
}

void Debug::Log(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    Log(std::string(buffer));
}