#include "core/application.hpp"
#include "core/logger.hpp"

#include <glad/glad.h>

namespace Nexus
{
  Application::Application(const ApplicationInfo &appInfo)
    : m_Title{appInfo.title}, m_Width{appInfo.width}, m_Height{appInfo.height}, 
      m_Resizable{appInfo.isResizable}, m_Vsync{appInfo.vsync}, m_UPS{appInfo.ups}
  {
    // create window
    WindowInfo wndInfo = {
      .title = m_Title,
      .width = m_Width,
      .height = m_Height,
      .isResizable = m_Resizable,
      .vsync = m_Vsync
    };
    m_Window = std::make_unique<Window>(wndInfo);

    m_Running = true;
  }

  Application::~Application()
  {
  }

  void Application::Run()
  {
    Init();

    const float upsTime = 1.0f / m_UPS;
    float upsTimer = 0.0f;

    while (m_Running)
    {
      if (m_Window->ShouldClose())
      {
        m_Running = false;
      }
      
      float dt = m_Window->GetFrameTime();
      
      m_Window->PollEvents();

      upsTimer += dt;
      while (upsTimer >= upsTime)
      {
        Update(upsTime);

        upsTimer -= upsTime;
      }

      glClearColor(0.0, 0.0, 0.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT);
      Render(dt);
      m_Window->SwapBuffers();
    }
  }
}
