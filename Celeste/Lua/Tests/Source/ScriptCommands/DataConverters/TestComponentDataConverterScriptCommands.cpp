#include "ScriptCommands/DataConverters/Objects/ComponentDataConverterScriptCommands.h"
#include "Lua/LuaState.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "Objects/GameObject.h"

#include "Mocks/Objects/MockComponent.h"
#include "UtilityHeaders/UnitTestHeaders.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::ComponentDataConverterScriptCommands
{
  CELESTE_TEST_CLASS(TestComponentDataConverterScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterScriptCommands_Initialize_AddsComponentDataConverterUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["ComponentDataConverter"].valid());

    Celeste::Lua::Objects::ComponentDataConverterScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["ComponentDataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterScriptCommands_Initialize_Adds_setValues_ToComponentDataConverterTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["ComponentDataConverter"]["setValues"].valid());

    Celeste::Lua::Objects::ComponentDataConverterScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["ComponentDataConverter"]["setValues"].valid());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterScriptCommands_setValues_InputtingNilForComponent_DoesNothing)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Objects::ComponentDataConverterScriptCommands::initialize(state);

    ComponentDataConverter converter("Component");

    auto result = state.globals()["ComponentDataConverter"]["setValues"].get<sol::protected_function>().call(converter, sol::nil);

    Assert::IsTrue(result.valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterScriptCommands_setValues_InputtingNonNilComponent_CallsSetValues)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Objects::ComponentDataConverterScriptCommands::initialize(state);

    ComponentDataConverter converter("Component");
    GameObject gameObject;
    MockComponent mockComponent(gameObject);
    Component& component = static_cast<Component&>(mockComponent);

    auto result = state.globals()["ComponentDataConverter"]["setValues"].get<sol::protected_function>().call(converter, component);

    Assert::IsTrue(result.valid());

    // Can't check setValues is called, but we can at least check the function is valid
  }

#pragma endregion

  };
}