#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Lua/Components/LuaComponentManifestRegistryScriptCommands.h"
#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/LuaState.h"

#include "Mocks/Objects/MockComponent.h"

using LuaState = Celeste::Lua::LuaState;
using LuaComponentManifestRegistry = Celeste::Lua::LuaComponentManifestRegistry;


namespace TestCelesteLua
{
  namespace Lua
  {
    namespace ScriptCommands
    {
      CELESTE_TEST_CLASS(TestLuaComponentManifestRegistryScriptCommands)

      //------------------------------------------------------------------------------------------------
      void TestLuaComponentManifestRegistryScriptCommands::testInitialize()
      {
        LuaComponentManifestRegistry::deregisterComponent(MockComponent::type_name());
      }

      //------------------------------------------------------------------------------------------------
      void TestLuaComponentManifestRegistryScriptCommands::testCleanup()
      {
        LuaComponentManifestRegistry::deregisterComponent(MockComponent::type_name());
      }

#pragma region Initialize Tests

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(LuaComponentManifestRegistryScriptCommands_Initialize_Adds_registerComponent_ScriptCommand_ToGlobalTable)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state.globals()["registerComponent"].valid());

        Celeste::Lua::LuaComponentManifestRegistryScriptCommands::initialize(state);

        Assert::IsTrue(state.globals()["registerComponent"].valid());
      }

#pragma endregion

#pragma region Register Component Tests

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(LuaComponentManifestRegistryScriptCommands_registerComponent_InputtingValidTable_RegistersComponent)
      {
        sol::state& state = LuaState::instance();
        Celeste::Lua::LuaComponentManifestRegistryScriptCommands::initialize(state);

        Assert::IsFalse(LuaComponentManifestRegistry::hasComponent(MockComponent::type_name()));

        sol::protected_function_result result = state.globals()["registerComponent"].get<sol::protected_function>().call(MockComponent::type_name(), state.create_table());

        Assert::IsTrue(result.valid());
        Assert::IsTrue(LuaComponentManifestRegistry::hasComponent(MockComponent::type_name()));
      }

#pragma endregion

      };
    }
  }
}