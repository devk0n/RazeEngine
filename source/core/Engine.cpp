#include "Engine.h"
#include "VulkanInstance.h"
#include <iostream>

namespace Raze {

Engine::Engine() {
    initVulkan();
}

Engine::~Engine() {
    cleanup();
}

void Engine::initVulkan() {
    vulkanInstance = std::make_unique<VulkanInstance>();
}

void Engine::mainLoop() {
    // Main rendering loop placeholder
    std::cout << "Main loop running...\n";
}

void Engine::cleanup() {
    vulkanInstance.reset();
    std::cout << "Engine cleaned up.\n";
}

void Engine::run() {
    mainLoop();
}

} // namespace Raze

