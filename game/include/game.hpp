#pragma once

#include <nexus/engine.hpp>

struct Game : public Nexus::Application
{
  Game(const Nexus::ApplicationInfo& appInfo = {});
  ~Game();

protected:
  virtual void Init() override;
  virtual void Update(float dt) override;
  virtual void Render(float dt) override;
};
