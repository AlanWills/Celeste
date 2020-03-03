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
      inline const sol::function& getHandleInputFunc() const { return m_handleInputFunc; }
      inline const sol::function& getUpdateFunc() const { return m_updateFunc; }

      CelesteDllExport void initializeComponent(LuaComponent& luaComponent) const;

    private:
      void processCallbacks(const sol::table& componentTable);
      void processCallback(const sol::table& componentTable, const std::string& callbackName, sol::function& outputCallback);

      sol::table m_componentTable;
      sol::function m_onSetActiveFunc;
      sol::function m_handleInputFunc;
      sol::function m_updateFunc;
  };
}