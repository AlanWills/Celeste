#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/LuaHeaders.h"


namespace Celeste::Lua
{
  class LuaComponent;

  class LuaComponentManifest
  {
    public:
      CelesteDllExport LuaComponentManifest(const sol::table& componentTable);

      inline const sol::function& getOnSetActiveFunc() const { return m_onSetActiveFunc; }
      inline const sol::function& getOnSetGameObjectFunc() const { return m_onSetGameObjectFunc; }
      inline const sol::function& getOnHandleInputFunc() const { return m_onHandleInputFunc; }
      inline const sol::function& getOnUpdateFunc() const { return m_onUpdateFunc; }
      inline const sol::function& getOnDeathFunc() const { return m_onDeathFunc; }

      CelesteDllExport void initializeComponent(LuaComponent& luaComponent) const;

    private:
      void processCallbacks(const sol::table& componentTable);
      void processCallback(const sol::table& componentTable, const std::string& callbackName, sol::function& outputCallback);

      sol::table m_componentTable;
      sol::function m_onSetActiveFunc;
      sol::function m_onSetGameObjectFunc;
      sol::function m_onHandleInputFunc;
      sol::function m_onUpdateFunc;
      sol::function m_onDeathFunc;
  };
}