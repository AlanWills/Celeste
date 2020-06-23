#include "ScriptCommands/Time/TimeNotifierSystemScriptCommands.h"
#include "sol/sol.hpp"

#include "Assert/Assert.h"
#include "Log/Log.h"
#include "Time/TimeNotifierSystem.h"
#include "Game/Game.h"

using TimeNotifierSystem = Celeste::Time::TimeNotifierSystem;


namespace Celeste::Lua::Time::TimeNotifierSystemScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    TimeNotifierSystem* getTimeNotifierSystem()
    {
      return Celeste::Game::current().getSystem<TimeNotifierSystem>();
    }

    //------------------------------------------------------------------------------------------------
    StringId subscribeTimePassedCallback(TimeNotifierSystem& timeNotifierSystem, sol::protected_function function, sol::object extraArgs)
    {
      if (!function.valid())
      {
        ASSERT_FAIL();
        return StringId();
      }

      return timeNotifierSystem.subscribe([function, extraArgs](float deltaTime) -> void
        {
          ASSERT(function.valid());
          auto result = function.call(deltaTime, extraArgs);

          if (!result.valid())
          {
            sol::error error = result;
            LOG(error.what());
          }
        });
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    ASSERT(state["System"].valid());
    state["System"]["getTimeNotifierSystem"] = &Internals::getTimeNotifierSystem;

    state.new_usertype<TimeNotifierSystem>(
      "TimeNotifierSystem",
      "subscribe", &Internals::subscribeTimePassedCallback,
      "unsubscribe", &TimeNotifierSystem::unsubscribe);
  }
}