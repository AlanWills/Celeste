#pragma once

#include <string>


namespace sol
{
  class state;
}

namespace Celeste::Lua::Settings::GameSettingsScriptCommands
{
  void initialize(sol::state& state);
}