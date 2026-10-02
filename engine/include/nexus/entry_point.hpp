#pragma once

#include "core/application.hpp"

#ifndef NX_ENGINE
extern Nexus::Application* CreateApplication();

int main()
{
  auto app = CreateApplication();
  app->Run();

  delete app;
}
#endif // NX_ENGINE
