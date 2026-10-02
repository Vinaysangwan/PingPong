#include "core/window.hpp"
#include "core/logger.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Nexus
{
  struct Window::Impl
  {
    GLFWwindow* window;
  };

  static void glfw_error_callback(int err, const char* msg)
  {
    NX_ENGINE_ERROR("GLFW ERROR", err, ": ", msg);
  }

  static void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    glViewport(0, 0, width, height);
  }
  
  Window::Window(const WindowInfo& wndInfo)
    : m_Title{wndInfo.title}, m_Width{wndInfo.width}, m_Height{wndInfo.height}, m_Resizable{wndInfo.isResizable}, m_Vsync{wndInfo.vsync}
  {
    glfwSetErrorCallback(glfw_error_callback);
    
    // init glfw
    if (!glfwInit())
    {
      NX_ENGINE_ASSERT(false, "Failed to Init GLFW");
      return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, m_Resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    m_Impl = std::make_unique<Impl>();
    m_Impl->window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    if (!m_Impl->window)
    {
      NX_ENGINE_ASSERT(false, "Failed to Create Window");
      return;
    }
    glfwMakeContextCurrent(m_Impl->window);
    glfwSwapInterval(m_Vsync ? 1 : 0);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      NX_ENGINE_ASSERT(false, "Failed to Init Glad");
      return;
    }

    // glfw callbacks
    glfwSetFramebufferSizeCallback(m_Impl->window, glfw_framebuffer_size_callback);

    glViewport(0, 0, m_Width, m_Height);

    glfwShowWindow(m_Impl->window);

    m_LastFrameTime = 0;
    m_FrameTime = 0.0f;

    m_FpsTimer = 0.0f;
    m_CurrentFpsCounter = 0;
    m_FPS = 0;
  }

  Window::~Window()
  {
    glfwDestroyWindow(m_Impl->window);
    glfwTerminate();
  }

  void Window::PollEvents()
  {
    glfwPollEvents();
  }

  void Window::SwapBuffers()
  {
    glfwSwapBuffers(m_Impl->window);
  }

  bool Window::ShouldClose()
  {
    double currentFrameTime = glfwGetTime();
    m_FrameTime = static_cast<float>(currentFrameTime - m_LastFrameTime);
    m_LastFrameTime = currentFrameTime;

    m_FpsTimer += m_FrameTime;
    m_CurrentFpsCounter++;
    if (m_FpsTimer >= 1.0f)
    {
      m_FpsTimer -= 1.0f;
      m_FPS = m_CurrentFpsCounter;
      m_CurrentFpsCounter = 0;
    }
    
    return glfwWindowShouldClose(m_Impl->window);
  }
}
