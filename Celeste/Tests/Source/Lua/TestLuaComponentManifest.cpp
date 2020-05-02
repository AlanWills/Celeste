#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Lua/Components/LuaComponentManifest.h"
#include "Lua/Components/LuaComponent.h"
#include "Lua/LuaState.h"

#include "Objects/GameObject.h"

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCeleste::Lua
{
  CELESTE_TEST_CLASS(TestLuaComponentManifest)

    //------------------------------------------------------------------------------------------------
    std::string resetScript = R"(
    onSetActiveCalled = false
    updateCalled = false

    onSetActive = nil
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
  std::string updateScript = R"(
    updateCalled = false

    function update(component, time)
      updateCalled = true
    end
    )";

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    LuaState::instance().script(resetScript);
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
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
    GameObject gameObject;
    LuaComponent luaComponent(gameObject);
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.script(onSetActiveScript).valid());
    Assert::IsTrue(state.script(updateScript).valid());

    LuaComponentManifest manifest{ state.globals() };

    Assert::IsTrue(manifest.getOnSetActiveFunc().valid());
    Assert::IsTrue(manifest.getUpdateFunc().valid());

    manifest.initializeComponent(luaComponent);

    Assert::IsTrue(luaComponent.getOnSetActiveFunc().valid());
    Assert::IsTrue(manifest.getOnSetActiveFunc() == luaComponent.getOnSetActiveFunc());

    Assert::IsTrue(luaComponent.getUpdateFunc().valid());
    Assert::IsTrue(manifest.getUpdateFunc() == luaComponent.getUpdateFunc());
  }

#pragma endregion

  };
}