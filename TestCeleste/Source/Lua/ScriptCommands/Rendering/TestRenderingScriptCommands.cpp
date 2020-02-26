#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Rendering/RenderingScriptCommands.h"
#include "Lua/LuaState.h"

#include "Objects/Component.h"
#include "Rendering/Canvas.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"

using LuaState = Celeste::Lua::LuaState;
using Canvas = Celeste::Rendering::Canvas;
using SpriteRenderer = Celeste::Rendering::SpriteRenderer;
using TextRenderer = Celeste::Rendering::TextRenderer;


namespace TestCeleste
{
  namespace Lua
  {
    namespace Rendering
    {
      CELESTE_TEST_CLASS(TestRenderingScriptCommands)

      //------------------------------------------------------------------------------------------------
      void TestRenderingScriptCommands::testInitialize()
      {
        LuaState::instance().new_usertype<Celeste::Component>("Component");
      }

      //------------------------------------------------------------------------------------------------
      void TestRenderingScriptCommands::testCleanup()
      {
        LuaState::instance().new_usertype<Celeste::Component>("Component");
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
  }
}