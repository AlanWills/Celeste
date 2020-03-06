#pragma once

#include "UtilityHeaders/LuaHeaders.h"
#include "Objects/Component.h"


namespace Celeste::Lua
{
  class LuaComponentManifest;

  class LuaComponent : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(LuaComponent, CelesteDllExport)

    public:
      const sol::table& getInstance() const { return m_instance; }
      void setInstance(const sol::table& instance) { m_instance = instance; }

      const sol::function& getOnSetActiveFunc() const { return m_onSetActiveFunc; }
      void setOnSetActiveFunc(const sol::function& func) { m_onSetActiveFunc = func; }

      const sol::function& getHandleInputFunc() const { return m_handleInputFunc; }
      void setHandleInputFunc(const sol::function& func) { m_handleInputFunc = func; }

      const sol::function& getUpdateFunc() const { return m_updateFunc; }
      void setUpdateFunc(const sol::function& func) { m_updateFunc = func; }

      CelesteDllExport void setActive(bool active) override;
      CelesteDllExport void handleInput() override;
      CelesteDllExport void update(float elapsedGameTime) override;

    private:
      using Inherited = Component;

      void resetCallbacks();

      sol::table m_instance;
      sol::function m_onSetActiveFunc;
      sol::function m_handleInputFunc;
      sol::function m_updateFunc;
  };
}