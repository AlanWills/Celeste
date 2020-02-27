#pragma once

#include "UtilityHeaders/LuaHeaders.h"
#include "Objects/Script.h"


namespace Celeste
{
  namespace Lua
  {
    class LuaComponentManifest;

    class LuaComponent : public Script
    {
      DECLARE_SCRIPT(LuaComponent, CelesteDllExport)
 
      public:
        const sol::table& getInstance() const { return m_instance; }
        void setInstance(const sol::table& instance);

        const sol::function& getOnSetActiveFunc() const { return m_onSetActiveFunc; }
        void setOnSetActiveFunc(const sol::function& func) { m_onSetActiveFunc = func; }

        const sol::function& getOnSetGameObjectFunc() const { return m_onSetGameObjectFunc; }
        void setOnSetGameObjectFunc(const sol::function& func) { m_onSetGameObjectFunc = func; }

        const sol::function& getHandleInputFunc() const { return m_handleInputFunc; }
        void setHandleInputFunc(const sol::function& func) { m_handleInputFunc = func; }

        const sol::function& getUpdateFunc() const { return m_updateFunc; }
        void setUpdateFunc(const sol::function& func) { m_updateFunc = func; }

        CelesteDllExport void setActive(bool active) override;

        CelesteDllExport void handleInput() override;
        CelesteDllExport void update(float elapsedGameTime) override;

      protected:
        void onSetGameObject(GameObject& gameObject) override;

      private:
        using Inherited = Script;

        void resetCallbacks();

        sol::table m_instance;
        sol::function m_onSetActiveFunc;
        sol::function m_onSetGameObjectFunc;
        sol::function m_handleInputFunc;
        sol::function m_updateFunc;
    };
  }
}