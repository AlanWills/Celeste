#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/Components/LuaComponentManifest.h"
#include "Lua/Components/LuaComponent.h"
#include "Lua/LuaState.h"

#include "Utils/ObjectUtils.h"

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCeleste
{
  namespace Lua
  {
    CELESTE_TEST_CLASS(TestLuaComponentManifest)

    //------------------------------------------------------------------------------------------------
    std::string resetScript = R"(
    onSetActiveCalled = false
    onSetGameObjectCalled = false
    onInitializeCalled = false
    onHandleInputCalled = false
    onUpdateCalled = false
    onDeathCalled = false

    onSetActive = nil
    onSetGameObject = nil
    onInitialize = nil
    onHandleInput = nil
    onUpdate = nil
    onDeath = nil
    )";

    //------------------------------------------------------------------------------------------------
    std::string onSetActiveScript = R"(
    onSetActiveCalled = false

    function onSetActive(component, isActive)
      onSetActiveCalled = true
    end
    )";

    //------------------------------------------------------------------------------------------------
    std::string onSetGameObjectScript = R"(
    onSetGameObjectCalled = false

    function onSetGameObject(component, isActive)
      onSetGameObjectCalled = true
    end
    )";

    //------------------------------------------------------------------------------------------------
    std::string onInitializeScript = R"(
    onInitializeCalled = false

    function onInitialize(component)
      onInitializeCalled = true
    end
    )";

    //------------------------------------------------------------------------------------------------
    std::string onHandleInputScript = R"(
    onHandleInputCalled = false

    function onHandleInput(component)
      onHandleInputCalled = true
    end
    )";

    //------------------------------------------------------------------------------------------------
    std::string onUpdateScript = R"(
    onUpdateCalled = false

    function onUpdate(component, time)
      onUpdateCalled = true
    end
    )";

    //------------------------------------------------------------------------------------------------
    std::string onDeathScript = R"(
    onDeathCalled = false

    function onDeath(component)
      onDeathCalled = true
    end
    )";

    //------------------------------------------------------------------------------------------------
    void TestLuaComponentManifest::testInitialize()
    {
      LuaState::instance().script(resetScript);
    }

    //------------------------------------------------------------------------------------------------
    void TestLuaComponentManifest::testCleanup()
    {
      LuaState::instance().script(resetScript);
    }

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithoutValidOnSetActiveCallback_SetsOnSetActiveToEmptyFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsFalse(state["onSetActive"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsFalse(manifest.getOnSetActiveFunc().valid());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithValidOnSetActiveCallback_SetsOnSetActiveToFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsTrue(state.script(onSetActiveScript).valid());
      Assert::IsTrue(state["onSetActive"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsTrue(manifest.getOnSetActiveFunc().valid());
      Assert::IsFalse(state["onSetActiveCalled"]);

      manifest.getOnSetActiveFunc()(nullptr, false);

      Assert::IsTrue(state["onSetActiveCalled"]);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithoutValidOnSetGameObjectCallback_SetsOnSetGameObjectToEmptyFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsFalse(state["onSetGameObject"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsFalse(manifest.getOnSetGameObjectFunc().valid());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithValidOnSetGameObjectCallback_SetsOnSetGameObjectToFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsTrue(state.script(onSetGameObjectScript).valid());
      Assert::IsTrue(state["onSetGameObject"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsTrue(manifest.getOnSetGameObjectFunc().valid());
      Assert::IsFalse(state["onSetGameObjectCalled"]);

      manifest.getOnSetGameObjectFunc()(nullptr);

      Assert::IsTrue(state["onSetGameObjectCalled"]);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithoutValidOnHandleInputCallback_SetsOnHandleInputToEmptyFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsFalse(state["onHandleInput"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsFalse(manifest.getOnHandleInputFunc().valid());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithValidOnHandleInputCallback_SetsOnHandleInputToFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsTrue(state.script(onHandleInputScript).valid());
      Assert::IsTrue(state["onHandleInput"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsTrue(manifest.getOnHandleInputFunc().valid());
      Assert::IsFalse(state["onHandleInputCalled"]);

      manifest.getOnHandleInputFunc()(nullptr);

      Assert::IsTrue(state["onHandleInputCalled"]);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithoutValidOnUpdateCallback_SetsOnUpdateToEmptyFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsFalse(state["onUpdate"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsFalse(manifest.getOnUpdateFunc().valid());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithValidOnUpdateCallback_SetsOnUpdateToFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsTrue(state.script(onUpdateScript).valid());
      Assert::IsTrue(state["onUpdate"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsTrue(manifest.getOnUpdateFunc().valid());
      Assert::IsFalse(state["onUpdateCalled"]);

      manifest.getOnUpdateFunc()(nullptr, 1.0f);

      Assert::IsTrue(state["onUpdateCalled"]);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithoutValidOnDeathCallback_SetsOnDeathToEmptyFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsFalse(state["onDeath"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsFalse(manifest.getOnDeathFunc().valid());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithValidOnDeathCallback_SetsOnDeathToFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsTrue(state.script(onDeathScript).valid());
      Assert::IsTrue(state["onDeath"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsTrue(manifest.getOnDeathFunc().valid());
      Assert::IsFalse(state["onDeathCalled"]);

      manifest.getOnDeathFunc()(nullptr);

      Assert::IsTrue(state["onDeathCalled"]);
    }

#pragma endregion

#pragma region Initialize Component Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_InitializeComponent_InputtingNonNullComponent_SetsFuncsToManifestValues)
    {
      LuaComponent luaComponent;
      sol::state& state = LuaState::instance();
      
      Assert::IsTrue(state.script(onSetActiveScript).valid());
      Assert::IsTrue(state.script(onSetGameObjectScript).valid());
      Assert::IsTrue(state.script(onInitializeScript).valid());
      Assert::IsTrue(state.script(onHandleInputScript).valid());
      Assert::IsTrue(state.script(onUpdateScript).valid());
      Assert::IsTrue(state.script(onDeathScript).valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsTrue(manifest.getOnSetActiveFunc().valid());
      Assert::IsTrue(manifest.getOnSetGameObjectFunc().valid());
      Assert::IsTrue(manifest.getOnHandleInputFunc().valid());
      Assert::IsTrue(manifest.getOnUpdateFunc().valid());
      Assert::IsTrue(manifest.getOnDeathFunc().valid());

      manifest.initializeComponent(luaComponent);

      Assert::IsTrue(luaComponent.getOnSetActiveFunc().valid());
      Assert::IsTrue(manifest.getOnSetActiveFunc() == luaComponent.getOnSetActiveFunc());

      Assert::IsTrue(luaComponent.getOnSetGameObjectFunc().valid());
      Assert::IsTrue(manifest.getOnSetGameObjectFunc() == luaComponent.getOnSetGameObjectFunc());

      Assert::IsTrue(luaComponent.getOnHandleInputFunc().valid());
      Assert::IsTrue(manifest.getOnHandleInputFunc() == luaComponent.getOnHandleInputFunc());

      Assert::IsTrue(luaComponent.getOnUpdateFunc().valid());
      Assert::IsTrue(manifest.getOnUpdateFunc() == luaComponent.getOnUpdateFunc());

      Assert::IsTrue(luaComponent.getOnDeathFunc().valid());
      Assert::IsTrue(manifest.getOnDeathFunc() == luaComponent.getOnDeathFunc());
    }

#pragma endregion

    };
  }
}