#include "ScriptCommands/Layout/LayoutSystemScriptCommands.h"
#include "ScriptCommands/Utils/ScriptCommandUtils.h"
#include "sol/sol.hpp"

#include "Layout/LayoutSystem.h"
#include "Game/Game.h"

using LayoutSystem = Celeste::Layout::LayoutSystem;


namespace Celeste::Lua::Layout::LayoutSystemScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    LayoutSystem* getLayoutSystem()
    {
      return Game::current().getSystem<LayoutSystem>();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    if (!state["System"].valid())
    {
      ASSERT_FAIL();
      state.create_named_table(
        "System",
        "getLayoutSystem", &Internals::getLayoutSystem);
    }
    else
    {
      state["System"]["getLayoutSystem"] = &Internals::getLayoutSystem;
    }

    state.new_usertype<LayoutSystem>(
      "LayoutSystem",
      sol::base_classes, sol::bases<Celeste::System::ISystem>());
  }
}