#pragma once


namespace sol
{
  class state;
}

namespace Celeste
{
  class ScriptableObject;

  namespace Lua::ScriptableObjectScriptCommands
  {
    void initialize(sol::state& state);
  }
}