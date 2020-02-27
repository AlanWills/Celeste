#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/LuaState.h"
#include "Lua/Components/LuaComponent.h"
#include "Lua/Components/LuaComponentManifest.h"

#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCeleste::Lua
{
  CELESTE_TEST_CLASS(TestLuaComponent)

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
  void TestLuaComponent::testInitialize()
  {
    LuaState::instance().script(resetScript);
  }

  //------------------------------------------------------------------------------------------------
  void TestLuaComponent::testCleanup()
  {
    LuaState::instance().script(resetScript);
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Constructor_SetsOnSetActiveFunc_ToEmptyFunc)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getOnSetActiveFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Constructor_SetsOnSetGameObjectFunc_ToEmptyFunc)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getOnSetGameObjectFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Constructor_SetsHandleInputFunc_ToEmptyFunc)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getHandleInputFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Constructor_SetsUpdateFunc_ToEmptyFunc)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getUpdateFunc().valid());
  }

#pragma endregion

#pragma region Set Active Function Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_SetActive_WithNoSetActiveFunction_DoesNothing)
  {
    LuaComponent luaComponent;

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

    LuaComponent luaComponent;
    luaComponent.setOnSetActiveFunc(state["onSetActive"]);

    Assert::IsTrue(luaComponent.getOnSetActiveFunc().valid());

    luaComponent.setActive(false);

    Assert::IsFalse(luaComponent.isActive());
    Assert::IsTrue(state["onSetActiveCalled"]);

    luaComponent.setActive(true);

    Assert::IsTrue(luaComponent.isActive());
  }

#pragma endregion

#pragma region Handle Input Function Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_HandleInput_WithNoHandleInputFunction_DoesNothing)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getHandleInputFunc().valid());

    luaComponent.handleInput();
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_HandleInput_WithHandleInputFunction_CallsHandleInputFunction)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(handleInputScript).valid());
    Assert::IsFalse(state["handleInputCalled"]);

    LuaComponent luaComponent;
    luaComponent.setHandleInputFunc(state["handleInput"]);

    Assert::IsTrue(luaComponent.getHandleInputFunc().valid());

    luaComponent.handleInput();

    Assert::IsTrue(state["handleInputCalled"]);
  }

#pragma endregion

#pragma region Update Function Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Update_WithNoUpdateFunction_DoesNothing)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getUpdateFunc().valid());

    luaComponent.update(0);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Update_WithUpdateFunction_CallsOnUpdateFunction)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(updateScript).valid());
    Assert::IsFalse(state["updateCalled"]);

    LuaComponent luaComponent;
    luaComponent.setUpdateFunc(state["update"]);

    Assert::IsTrue(luaComponent.getUpdateFunc().valid());

    luaComponent.update(0);

    Assert::IsTrue(state["updateCalled"]);
  }

#pragma endregion

  };
}