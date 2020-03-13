#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Physics/PhysicsScriptCommands.h"
#include "Lua/ScriptCommands/Objects/ComponentScriptCommands.h"
#include "Lua/LuaState.h"

#include "Objects/Component.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCeleste::Lua::Physics
{
  CELESTE_TEST_CLASS(TestPhysicsScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestPhysicsScriptCommands::testInitialize()
  {
    Celeste::Lua::ComponentScriptCommands::initialize();
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PhysicsScriptCommands_Initialize_InitializesEllipseColliderScriptCommands)
  {
    Assert::IsFalse(LuaState::instance().globals()["EllipseCollider"].valid());

    Celeste::Lua::Physics::ScriptCommands::initialize();

    Assert::IsTrue(LuaState::instance().globals()["EllipseCollider"].valid());
  }

#pragma endregion

  };
}