#include "Lua/ScriptCommands/ObjectFX/LimitedLifeTimeScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"

#include "ObjectFX/LimitedLifeTime.h"


namespace Celeste::Lua::LimitedLifeTimeScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void subscribeOnDeathCallback(
      LimitedLifeTime& limitedLifeTime, 
      sol::protected_function function,
      sol::object extraArgs)
    {
      Celeste::Lua::subscribeToEvent<LimitedLifeTime::DeathEvent, GameObject&>(
        limitedLifeTime.getOnDeathEvent(), function, extraArgs);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    registerUserType<LimitedLifeTime>(
      "LimitedLifeTime",
      "allocate", sol::factories(&LimitedLifeTime::allocate),
      "setLifeTime", &LimitedLifeTime::setLifeTime,
      "subscribeOnDeathCallback", &Internals::subscribeOnDeathCallback);
  }
}