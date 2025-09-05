#ifndef RENDERER_H
#define RENDERER_H

namespace Raze {

class WindowManager;

class Renderer {
public:
  Renderer(WindowManager& windowManger);
  ~Renderer();

  void draw();
  void onResize();

private:
  WindowManager& m_windowManager;
};

} // namespace Raze

#endif // RENDERER_H
