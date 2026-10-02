#pragma once

#include "defines.hpp"
#include "core/window.hpp"

namespace Nexus
{
  struct ApplicationInfo
  {
    std::string title = "Nexus App";
    unsigned int width = 1280;
    unsigned int height = 720;
    bool isResizable = false;
    bool vsync = true;
    unsigned int ups = 60;
  };
  
  class NX_API Application
  {
  public:
    Application(const ApplicationInfo &appInfo = {});
    virtual ~Application();

    void Run();

    inline int GetFps() const { return m_Window->GetFPS(); };

  protected:
    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render(float dt) = 0;

  private:
    std::string m_Title;
    unsigned int m_Width;
    unsigned int m_Height;
    bool m_Resizable;
    bool m_Vsync;
    unsigned int m_UPS;
    bool m_Running;

    std::unique_ptr<Window> m_Window;
  };
}
