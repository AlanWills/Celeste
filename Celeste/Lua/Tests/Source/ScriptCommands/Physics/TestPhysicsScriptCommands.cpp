#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Physics/PhysicsScriptCommands.h"
#include "ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/LuaState.h"

#include "Objects/Component.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCelesteLua::Lua::Physics
{
  CELESTE_TEST_CLASS(TestPhysicsScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestPhysicsScriptCommands::testInitialize()
  {
    Celeste::Lua::ComponentScriptCommands::initialize(LuaState::instance());
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsScriptCommands_Initialize_InitializesEllipseColliderScriptCommands)
  {
    Assert::IsFalse(LuaState::instance().globals()["EllipseCollider"].valid());

    Celeste::Lua::Physics::ScriptCommands::initialize(LuaState::instance());

    Assert::IsTrue(LuaState::instance().globals()["EllipseCollider"].valid());
  }

#pragma endregion

  };
}