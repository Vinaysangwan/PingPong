#pragma once

#include <memory>
#include <string>

#include "defines.hpp"

namespace Nexus
{
  struct WindowInfo
  {
    std::string title = "NX Window";
    unsigned int width = 1280;
    unsigned int height = 720;
    bool isResizable = false;
    bool vsync = true;
  };
  
  class NX_API Window
  {
  public:
    Window(const WindowInfo &wndInfo = {});
    ~Window();

    void PollEvents();
    void SwapBuffers();

    bool ShouldClose();

    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }
    inline std::string GetTitle() const { return m_Title; }
    inline bool GetIsResizable() const { return m_Resizable; }
    inline bool GetVsync() const { return m_Vsync; }
    inline float GetFrameTime() const { return m_FrameTime; }
    inline int GetFPS() const { return m_FPS; }

  private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;

    const std::string m_Title;
    unsigned int m_Width;
    unsigned int m_Height;
    bool m_Resizable;
    bool m_Vsync;

    double m_LastFrameTime;
    float m_FrameTime;

    float m_FpsTimer;
    int m_CurrentFpsCounter;
    int m_FPS;
  };
}
