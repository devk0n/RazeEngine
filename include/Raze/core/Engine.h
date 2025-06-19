#ifndef ENGINE_H
#define ENGINE_H

#pragma once

#include <memory>

namespace Raze {

class VulkanInstance;

class Engine {
public:
    Engine();
    ~Engine();

    void run();

private:
    void initVulkan();
    void mainLoop();
    void cleanup();

    std::unique_ptr<VulkanInstance> vulkanInstance;
};

} // namespace Raze

#endif // ENGINE_H

