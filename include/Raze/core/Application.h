#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

namespace Raze {

class WindowManager;
class Renderer;

class Application {
public:
  Application();
  ~Application();

  void run();

private:
  std::unique_ptr<WindowManager> m_windowManager;
  std::unique_ptr<Renderer> m_renderer;
};

} // namespace Raze

#endif // APPLICATION_H
