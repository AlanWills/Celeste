#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/Components/LuaComponentManifest.h"
#include "Lua/Components/LuaComponent.h"
#include "Lua/LuaState.h"

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
    handleInputCalled = false
    updateCalled = false

    onSetActive = nil
    onSetGameObject = nil
    handleInput = nil
    update = nil
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
    std::string handleInputScript = R"(
    handleInputCalled = false

    function handleInput(component)
      handleInputCalled = true
    end
    )";

    //------------------------------------------------------------------------------------------------
    std::string updateScript = R"(
    updateCalled = false

    function update(component, time)
      updateCalled = true
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
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithoutValidHandleInputCallback_SetsHandleInputToEmptyFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsFalse(state["handleInput"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsFalse(manifest.getHandleInputFunc().valid());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithValidHandleInputCallback_SetsHandleInputToFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsTrue(state.script(handleInputScript).valid());
      Assert::IsTrue(state["handleInput"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsTrue(manifest.getHandleInputFunc().valid());
      Assert::IsFalse(state["handleInputCalled"]);

      manifest.getHandleInputFunc()(nullptr);

      Assert::IsTrue(state["handleInputCalled"]);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithoutValidUpdateCallback_SetsUpdateToEmptyFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsFalse(state["update"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsFalse(manifest.getUpdateFunc().valid());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LuaComponentManifest_Constructor_InputtingTableWithValidUpdateCallback_SetsUpdateToFunc)
    {
      sol::state& state = LuaState::instance();

      Assert::IsTrue(state.script(updateScript).valid());
      Assert::IsTrue(state["update"].valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsTrue(manifest.getUpdateFunc().valid());
      Assert::IsFalse(state["updateCalled"]);

      manifest.getUpdateFunc()(nullptr, 1.0f);

      Assert::IsTrue(state["updateCalled"]);
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
      Assert::IsTrue(state.script(handleInputScript).valid());
      Assert::IsTrue(state.script(updateScript).valid());

      LuaComponentManifest manifest{ state.globals() };

      Assert::IsTrue(manifest.getOnSetActiveFunc().valid());
      Assert::IsTrue(manifest.getOnSetGameObjectFunc().valid());
      Assert::IsTrue(manifest.getHandleInputFunc().valid());
      Assert::IsTrue(manifest.getUpdateFunc().valid());

      manifest.initializeComponent(luaComponent);

      Assert::IsTrue(luaComponent.getOnSetActiveFunc().valid());
      Assert::IsTrue(manifest.getOnSetActiveFunc() == luaComponent.getOnSetActiveFunc());

      Assert::IsTrue(luaComponent.getOnSetGameObjectFunc().valid());
      Assert::IsTrue(manifest.getOnSetGameObjectFunc() == luaComponent.getOnSetGameObjectFunc());

      Assert::IsTrue(luaComponent.getHandleInputFunc().valid());
      Assert::IsTrue(manifest.getHandleInputFunc() == luaComponent.getHandleInputFunc());

      Assert::IsTrue(luaComponent.getUpdateFunc().valid());
      Assert::IsTrue(manifest.getUpdateFunc() == luaComponent.getUpdateFunc());
    }

#pragma endregion

    };
  }
}