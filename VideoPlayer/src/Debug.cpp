#include "Debug.h"
#include <iostream>

void Debug::Log(const std::string& message) {
    std::cout << message << std::endl;
}

void Debug::LogWarning(const std::string& message) {
    std::cout << "[WARNING] " << message << std::endl;
}

void Debug::LogError(const std::string& message) {
    std::cerr << "[ERROR] " << message << std::endl;
}