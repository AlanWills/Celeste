#pragma once


namespace sol
{
  class state;
}

namespace Celeste::Lua::Events::ScriptCommands
{
  void initialize(sol::state& state);
}