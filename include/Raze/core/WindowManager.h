#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <GLFW/glfw3.h>

namespace Raze {

class WindowManager {
public:
  WindowManager();
  ~WindowManager();

  void create();

  GLFWwindow *get() const { return m_window; }
  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }

private:
  GLFWwindow *m_window = nullptr;
  int m_width = 1280;
  int m_height = 960;
};

} // namespace Raze

#endif // WINDOW_MANAGER_H
