#pragma once


namespace sol
{
  class state;
}

namespace Celeste
{
  namespace Animation
  {
    class Animator;
  }

  namespace Lua::Animation::AnimatorScriptCommands
  {
    void initialize(sol::state& state);
  }
}