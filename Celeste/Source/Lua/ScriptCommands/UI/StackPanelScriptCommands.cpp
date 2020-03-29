#include "Lua/ScriptCommands/UI/StackPanelScriptCommands.h"
#include "UtilityHeaders/ScriptCommandHeaders.h"
#include "UI/StackPanel.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::UI::StackPanel> : std::false_type {};
}

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

    registerUserType<StackPanel>(
      StackPanel::type_name(),
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "addChild", &Internals::addChild,
      "removeChild", &Internals::removeChild,
      "layout", &StackPanel::layout);
  }
}