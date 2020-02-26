#include "Lua/Components/LuaComponentManifest.h"
#include "Lua/Components/LuaComponent.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua
{
  //------------------------------------------------------------------------------------------------
  LuaComponentManifest::LuaComponentManifest(const sol::table& componentTable) :
    m_componentTable(componentTable),
    m_onSetActiveFunc(),
    m_onSetGameObjectFunc(),
    m_onHandleInputFunc(),
    m_onUpdateFunc(),
    m_onDeathFunc()
  {
    processCallbacks(componentTable);
  }

  //------------------------------------------------------------------------------------------------
  void LuaComponentManifest::processCallbacks(const sol::table& componentTable)
  {
    if (!componentTable.valid())
    {
      ASSERT_FAIL();
      return;
    }

    processCallback(componentTable, "onSetActive", m_onSetActiveFunc);
    processCallback(componentTable, "onSetGameObject", m_onSetGameObjectFunc);
    processCallback(componentTable, "onHandleInput", m_onHandleInputFunc);
    processCallback(componentTable, "onUpdate", m_onUpdateFunc);
    processCallback(componentTable, "onDeath", m_onDeathFunc);
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
    luaComponent.setOnSetGameObjectFunc(m_onSetGameObjectFunc);
    luaComponent.setOnHandleInputFunc(m_onHandleInputFunc);
    luaComponent.setOnUpdateFunc(m_onUpdateFunc);
    luaComponent.setOnDeathFunc(m_onDeathFunc);
    luaComponent.setInstance(instance);
  }
}