#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Rendering/RenderingScriptCommands.h"
#include "ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/LuaState.h"

#include "Objects/Component.h"
#include "Rendering/Canvas.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"

using LuaState = Celeste::Lua::LuaState;
using Canvas = Celeste::Rendering::Canvas;
using SpriteRenderer = Celeste::Rendering::SpriteRenderer;
using TextRenderer = Celeste::Rendering::TextRenderer;
using namespace Celeste;


namespace TestCelesteLua::Lua::Rendering
{
  CELESTE_TEST_CLASS(TestRenderingScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestRenderingScriptCommands::testInitialize()
  {
    Celeste::Lua::ComponentScriptCommands::initialize(LuaState::instance());
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderingScriptCommands_Initialize_InitializesCanvasScriptCommands)
  {
    sol::state& state = LuaState::instance();
    
    Assert::IsFalse(state[Canvas::type_name()].valid());

    Celeste::Lua::Rendering::ScriptCommands::initialize(state);

    Assert::IsTrue(state[Canvas::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderingScriptCommands_Initialize_InitializesTextRendererScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[TextRenderer::type_name()].valid());

    Celeste::Lua::Rendering::ScriptCommands::initialize(state);

    Assert::IsTrue(state[TextRenderer::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderingScriptCommands_Initialize_InitializesSpriteRendererScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[SpriteRenderer::type_name()].valid());

    Celeste::Lua::Rendering::ScriptCommands::initialize(state);

    Assert::IsTrue(state[SpriteRenderer::type_name()].valid());
  }

#pragma endregion

  };
}