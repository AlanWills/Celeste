#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Resources/Shaders/ShaderScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestShaderScriptCommands)
  
#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ShaderScriptCommands_Initialize_InitializesFragmentShaderScriptCommands)
  {
    Assert::IsFalse(LuaState::instance()["FragmentShader"].valid());

    Celeste::Lua::Resources::ShaderScriptCommands::initialize();

    Assert::IsTrue(LuaState::instance()["FragmentShader"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ShaderScriptCommands_Initialize_InitializesVertexShaderScriptCommands)
  {
    Assert::IsFalse(LuaState::instance()["VertexShader"].valid());

    Celeste::Lua::Resources::ShaderScriptCommands::initialize();

    Assert::IsTrue(LuaState::instance()["VertexShader"].valid());
  }

#pragma endregion

  };
}