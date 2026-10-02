#pragma once

#include <nexus/engine.hpp>

class Game : public Nexus::Application
{
public:
  Game(const Nexus::ApplicationInfo& appInfo = {});
  ~Game();

protected:
  virtual void Init() override;
  virtual void Update(float dt) override;
  virtual void Render(float dt) override;
};
