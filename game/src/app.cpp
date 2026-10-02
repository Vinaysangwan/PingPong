#include <nexus/entry_point.hpp>

#include "game.hpp"

Nexus::Application* CreateApplication()
{
  Nexus::ApplicationInfo appInfo = {
    .title = "Ping Pong",
    .width = 1280U,
    .height = 720U,
    .isResizable = true,
    .vsync = true,
  };
  
  return new Game(appInfo);
}
