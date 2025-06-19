#include "WindowManager.h"
#include <GLFW/glfw3.h>

namespace Raze {

WindowManager::WindowManager() {
  // Constructor
}

WindowManager::~WindowManager() {
  // Destructor
}

void create() {
  // Get primary monitor video mode
  GLFWwindow *primaryMonitor = glfwGetPrimaryMonitor();
  const GLFWwindow *mode = glfwGetVideoMode(primaryMonitor);
}

} // namespace Raze
