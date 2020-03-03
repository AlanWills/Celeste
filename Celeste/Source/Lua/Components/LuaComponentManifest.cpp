#include "Lua/Components/LuaComponentManifest.h"
#include "Lua/Components/LuaComponent.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua
{
  //------------------------------------------------------------------------------------------------
  LuaComponentManifest::LuaComponentManifest(const sol::table& componentTable) :
    m_componentTable(componentTable),
    m_onSetActiveFunc(),
    m_handleInputFunc(),
    m_updateFunc()
  {
    processCallbacks(componentTable);
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentManifest::processCallbacks(const sol::table& componentTable)
  {
#if _DEBUG
    if (!componentTable.valid())
    {
      ASSERT_FAIL();
      return;
    }
#endif

    processCallback(componentTable, "onSetActive", m_onSetActiveFunc);
    processCallback(componentTable, "handleInput", m_handleInputFunc);
    processCallback(componentTable, "update", m_updateFunc);
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentManifest::processCallback(const sol::table& componentTable, const std::string& callbackName, sol::function& outputCallback)
  {
    auto callback = componentTable[callbackName];
    if (callback.valid())
    {
      outputCallback = callback;
    }
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentManifest::initializeComponent(LuaComponent& luaComponent) const
  {
    sol::table instance = LuaState::instance().create_table();
    instance[sol::metatable_key] = m_componentTable;

    // Set up callbacks
    luaComponent.setOnSetActiveFunc(m_onSetActiveFunc);
    luaComponent.setHandleInputFunc(m_handleInputFunc);
    luaComponent.setUpdateFunc(m_updateFunc);
    luaComponent.setInstance(instance);
  }
}