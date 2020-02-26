#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Physics/PhysicsScriptCommands.h"
#include "Lua/LuaState.h"

#include "Objects/Component.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCeleste
{
  namespace Lua
  {
    namespace Physics
    {
      CELESTE_TEST_CLASS(TestPhysicsScriptCommands)

      //------------------------------------------------------------------------------------------------
      void TestPhysicsScriptCommands::testInitialize()
      {
        LuaState::instance().new_usertype<Celeste::Component>("Component");
      }

      //------------------------------------------------------------------------------------------------
      void TestPhysicsScriptCommands::testCleanup()
      {
        LuaState::instance().new_usertype<Celeste::Component>("Component");
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
  }
}