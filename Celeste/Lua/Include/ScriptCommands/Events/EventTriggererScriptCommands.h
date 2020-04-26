#pragma once


namespace sol
{
  class state;
}

namespace Celeste::Lua::Events::EventTriggererScriptCommands
{
  void initialize(sol::state& state);
}