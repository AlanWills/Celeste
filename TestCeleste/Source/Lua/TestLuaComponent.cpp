#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/LuaState.h"
#include "Lua/Components/LuaComponent.h"
#include "Lua/Components/LuaComponentManifest.h"

#include "Utils/ObjectUtils.h"
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
  TEST_METHOD(LuaComponent_Constructor_SetsOnHandleInputFunc_ToEmptyFunc)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getOnHandleInputFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Constructor_SetsOnUpdateFunc_ToEmptyFunc)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getOnUpdateFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_Constructor_SetsOnDeathFunc_ToEmptyFunc)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getOnDeathFunc().valid());
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

#pragma region On Handle Input Function Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnHandleInput_WithNoOnHandleInputFunction_DoesNothing)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getOnHandleInputFunc().valid());

    luaComponent.handleInput();
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnHandleInput_WithOnHandleInputFunction_CallsOnHandleInputFunction)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(onHandleInputScript).valid());
    Assert::IsFalse(state["onHandleInputCalled"]);

    LuaComponent luaComponent;
    luaComponent.setOnHandleInputFunc(state["onHandleInput"]);

    Assert::IsTrue(luaComponent.getOnHandleInputFunc().valid());

    luaComponent.handleInput();

    Assert::IsTrue(state["onHandleInputCalled"]);
  }

#pragma endregion

#pragma region On Update Function Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnUpdate_WithNoOnUpdateFunction_DoesNothing)
  {
    LuaComponent luaComponent;

    Assert::IsFalse(luaComponent.getOnUpdateFunc().valid());

    luaComponent.update(0);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnUpdate_WithOnUpdateFunction_CallsOnUpdateFunction)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(onUpdateScript).valid());
    Assert::IsFalse(state["onUpdateCalled"]);

    LuaComponent luaComponent;
    luaComponent.setOnUpdateFunc(state["onUpdate"]);

    Assert::IsTrue(luaComponent.getOnUpdateFunc().valid());

    luaComponent.update(0);

    Assert::IsTrue(state["onUpdateCalled"]);
  }

#pragma endregion

#pragma region On Death Function Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnDeath_WithNoOnDeathFunction_DoesNothing)
  {
    LuaComponent luaComponent;

    Assert::IsTrue(luaComponent.isAlive());
    Assert::IsTrue(luaComponent.isActive());
    Assert::IsFalse(luaComponent.getOnDeathFunc().valid());

    luaComponent.die();

    Assert::IsFalse(luaComponent.isAlive());
    Assert::IsFalse(luaComponent.isActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnDeath_WithOnDeathFunction_CallsOnDeathFunction)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(onDeathScript).valid());
    Assert::IsFalse(state["onDeathCalled"]);

    LuaComponent luaComponent;
    luaComponent.setOnDeathFunc(state["onDeath"]);

    Assert::IsTrue(luaComponent.isAlive());
    Assert::IsTrue(luaComponent.isActive());
    Assert::IsTrue(luaComponent.getOnDeathFunc().valid());

    luaComponent.die();

    Assert::IsFalse(luaComponent.isAlive());
    Assert::IsFalse(luaComponent.isActive());
    Assert::IsTrue(state["onDeathCalled"]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnDeath_ResetsOnSetActiveFunc)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(onSetActiveScript).valid());
    Assert::IsFalse(state["onSetActiveCalled"]);

    LuaComponent luaComponent;
    luaComponent.setOnSetActiveFunc(state["onSetActive"]);

    Assert::IsTrue(luaComponent.getOnSetActiveFunc().valid());

    luaComponent.die();

    Assert::IsFalse(luaComponent.getOnSetActiveFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnDeath_ResetsOnSetGameObjectFunc)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(onSetGameObjectScript).valid());
    Assert::IsFalse(state["onSetGameObjectCalled"]);

    LuaComponent luaComponent;
    luaComponent.setOnSetGameObjectFunc(state["onSetGameObject"]);

    Assert::IsTrue(luaComponent.getOnSetGameObjectFunc().valid());

    luaComponent.die();

    Assert::IsFalse(luaComponent.getOnSetGameObjectFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnDeath_ResetsOnHandleInputFunc)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(onHandleInputScript).valid());
    Assert::IsFalse(state["onHandleInputCalled"]);

    LuaComponent luaComponent;
    luaComponent.setOnHandleInputFunc(state["onHandleInput"]);

    Assert::IsTrue(luaComponent.getOnHandleInputFunc().valid());

    luaComponent.die();

    Assert::IsFalse(luaComponent.getOnHandleInputFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnDeath_ResetsOnUpdateFunc)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(onUpdateScript).valid());
    Assert::IsFalse(state["onUpdateCalled"]);

    LuaComponent luaComponent;
    luaComponent.setOnUpdateFunc(state["onUpdate"]);

    Assert::IsTrue(luaComponent.getOnUpdateFunc().valid());

    luaComponent.die();

    Assert::IsFalse(luaComponent.getOnUpdateFunc().valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponent_OnDeath_ResetsOnDeathFunc)
  {
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.safe_script(onDeathScript).valid());
    Assert::IsFalse(state["onDeathCalled"]);

    LuaComponent luaComponent;
    luaComponent.setOnDeathFunc(state["onDeath"]);

    Assert::IsTrue(luaComponent.getOnDeathFunc().valid());

    luaComponent.die();

    Assert::IsFalse(luaComponent.getOnDeathFunc().valid());
  }

#pragma endregion

  };
}