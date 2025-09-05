#include "Application.h"
#include "Logger.h"
#include "Renderer.h"
#include "WindowManager.h"

namespace Raze {

Application::Application() {
  m_windowManager = std::make_unique<WindowManager>();
  m_windowManager->create("RazeEngine");

  m_renderer = std::make_unique<Renderer>(*m_windowManager);

  m_windowManager->setResizeCallback([this](int, int) { m_renderer->onResize(); });
}

Application::~Application() {
  m_renderer.reset();
  m_windowManager.reset();
}

void Application::run() {
  INFO("Starting main loop");
  while (!m_windowManager->shouldClose()) {
    INFO("Loop tick"); // <---- Add this
    glfwPollEvents();
    m_renderer->draw();
  }
  INFO("Main loop exited");
}

} // namespace Raze
