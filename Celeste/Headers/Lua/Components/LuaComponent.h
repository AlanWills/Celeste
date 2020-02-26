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

        const sol::function& getOnHandleInputFunc() const { return m_onHandleInputFunc; }
        void setOnHandleInputFunc(const sol::function& func) { m_onHandleInputFunc = func; }

        const sol::function& getOnUpdateFunc() const { return m_onUpdateFunc; }
        void setOnUpdateFunc(const sol::function& func) { m_onUpdateFunc = func; }

        const sol::function& getOnDeathFunc() const { return m_onDeathFunc; }
        void setOnDeathFunc(const sol::function& func) { m_onDeathFunc = func; }

        CelesteDllExport void setActive(bool active) override;

      protected:
        void onSetGameObject(GameObject& gameObject) override;
        void onHandleInput() override;
        void onUpdate(float elapsedGameTime) override;
        void onDeath() override;

      private:
        using Inherited = Script;

        void resetCallbacks();

        sol::table m_instance;
        sol::function m_onSetActiveFunc;
        sol::function m_onSetGameObjectFunc;
        sol::function m_onHandleInputFunc;
        sol::function m_onUpdateFunc;
        sol::function m_onDeathFunc;
    };
  }
}