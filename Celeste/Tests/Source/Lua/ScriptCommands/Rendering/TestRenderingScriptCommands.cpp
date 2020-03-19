#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Rendering/RenderingScriptCommands.h"
#include "Lua/ScriptCommands/Objects/ComponentScriptCommands.h"
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


namespace TestCeleste::Lua::Rendering
{
  CELESTE_TEST_CLASS(TestRenderingScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestRenderingScriptCommands::testInitialize()
  {
    Celeste::Lua::ComponentScriptCommands::initialize();
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderingScriptCommands_Initialize_InitializesCanvasScriptCommands)
  {
    Assert::IsFalse(LuaState::instance()[Canvas::type_name()].valid());

    Celeste::Lua::Rendering::ScriptCommands::initialize();

    Assert::IsTrue(LuaState::instance()[Canvas::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderingScriptCommands_Initialize_InitializesTextRendererScriptCommands)
  {
    Assert::IsFalse(LuaState::instance()[TextRenderer::type_name()].valid());

    Celeste::Lua::Rendering::ScriptCommands::initialize();

    Assert::IsTrue(LuaState::instance()[TextRenderer::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderingScriptCommands_Initialize_InitializesSpriteRendererScriptCommands)
  {
    Assert::IsFalse(LuaState::instance()[SpriteRenderer::type_name()].valid());

    Celeste::Lua::Rendering::ScriptCommands::initialize();

    Assert::IsTrue(LuaState::instance()[SpriteRenderer::type_name()].valid());
  }

#pragma endregion

  };
}