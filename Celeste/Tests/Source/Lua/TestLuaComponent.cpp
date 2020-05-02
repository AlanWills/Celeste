#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Lua/LuaState.h"
#include "Lua/Components/LuaComponent.h"
#include "Lua/Components/LuaComponentManifest.h"

#include "Objects/GameObject.h"

#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCeleste::Lua
{
  CELESTE_TEST_CLASS(TestLuaComponent)

  //------------------------------------------------------------------------------------------------
  std::string resetScript = R"(
  onSetActiveCalled = false
  handleInputCalled = false
  updateCalled = false

  onSetActive = nil
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
  TEST_METHOD(LuaComponent_Constructor_SetsOnSetActiveFunc_ToEmptyFunc)
  {
    GameObject gameObject;
    LuaComponent luaComponent(gameObject);

    Assert::IsFalse(luaComponent.getOnSetActiveFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Constructor_SetsUpdateFunc_ToEmptyFunc)
  {
    GameObject gameObject;
    LuaComponent luaComponent(gameObject);

    Assert::IsFalse(luaComponent.getUpdateFunc().valid());
  }

#pragma endregion

#pragma region Set Active Function Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_SetActive_WithNoSetActiveFunction_DoesNothing)
  {
    GameObject gameObject;
    LuaComponent luaComponent(gameObject);

    Assert::IsFalse(luaComponent.getOnSetActiveFunc().valid());

    luaComponent.setActive(false);

    Assert::IsFalse(luaComponent.isActive());

    luaComponent.setActive(true);

    Assert::IsTrue(luaComponent.isActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_SetActive_WithSetActiveFunction_CallsSetActiveFunction)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(onSetActiveScript).valid());
    Assert::IsFalse(state["onSetActiveCalled"]);

    GameObject gameObject;
    LuaComponent luaComponent(gameObject);
    luaComponent.setOnSetActiveFunc(state["onSetActive"]);

    Assert::IsTrue(luaComponent.getOnSetActiveFunc().valid());

    luaComponent.setActive(false);

    Assert::IsFalse(luaComponent.isActive());
    Assert::IsTrue(state["onSetActiveCalled"]);

    luaComponent.setActive(true);

    Assert::IsTrue(luaComponent.isActive());
  }

#pragma endregion

#pragma region Update Function Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Update_WithNoUpdateFunction_DoesNothing)
  {
    GameObject gameObject;
    LuaComponent luaComponent(gameObject);

    Assert::IsFalse(luaComponent.getUpdateFunc().valid());

    luaComponent.update(0);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Update_WithUpdateFunction_CallsOnUpdateFunction)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(updateScript).valid());
    Assert::IsFalse(state["updateCalled"]);

    GameObject gameObject;
    LuaComponent luaComponent(gameObject);
    luaComponent.setUpdateFunc(state["update"]);

    Assert::IsTrue(luaComponent.getUpdateFunc().valid());

    luaComponent.update(0);

    Assert::IsTrue(state["updateCalled"]);
  }

#pragma endregion

  };
}