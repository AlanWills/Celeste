#pragma once


namespace sol
{
  class state;
}

namespace Celeste::Lua::DataConverters::ScriptCommands
{
  void initialize(sol::state& state);
}