#include "Lua/ScriptCommands/UI/StackPanelScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "UI/StackPanel.h"


namespace Celeste::Lua::UI::StackPanelScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void addChild(Celeste::UI::StackPanel& stackPanel, GameObject& child)
    {
      stackPanel.addChildren(child);
    }

    //------------------------------------------------------------------------------------------------
    void removeChild(Celeste::UI::StackPanel& stackPanel, GameObject& child)
    {
      stackPanel.removeChildren(child);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using StackPanel = Celeste::UI::StackPanel;

    sol::state& state = Lua::LuaState::instance();
    registerUserType<StackPanel>(
      StackPanel::type_name(),
      "allocate", sol::factories(&StackPanel::allocate),
      "addChild", &Internals::addChild,
      "removeChild", &Internals::removeChild,
      "layout", &StackPanel::layout);
  }
}