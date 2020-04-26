#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Resources/Shaders/ShaderScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestShaderScriptCommands)
  
#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ShaderScriptCommands_Initialize_InitializesFragmentShaderScriptCommands)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(LuaState::instance()["FragmentShader"].valid());

    Celeste::Lua::Resources::ShaderScriptCommands::initialize(state);

    Assert::IsTrue(LuaState::instance()["FragmentShader"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ShaderScriptCommands_Initialize_InitializesVertexShaderScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(LuaState::instance()["VertexShader"].valid());

    Celeste::Lua::Resources::ShaderScriptCommands::initialize(state);

    Assert::IsTrue(LuaState::instance()["VertexShader"].valid());
  }

#pragma endregion

  };
}