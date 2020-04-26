#include "UtilityHeaders/UnitTestHeaders.h"

#include "Registries/ScriptableObjectRegistry.h"
#include "Mocks/Objects/MockScriptableObject.h"
#include "TestResources/Objects/MockScriptableObjectLoadingResources.h"

#include "ScriptCommands/Objects/ScriptableObjectScriptCommands.h"
#include "Lua/LuaState.h"
#include "AssertExt.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua
{
  namespace Lua
  {
    namespace ScriptCommands
    {
      CELESTE_TEST_CLASS(TestScriptableObjectScriptCommands)

#pragma region SetUp/TearDown

      //------------------------------------------------------------------------------------------------
      void TestScriptableObjectScriptCommands::testInitialize()
      {
        ScriptableObjectRegistry::removeScriptableObject<MockScriptableObject>();
      }

      //------------------------------------------------------------------------------------------------
      void TestScriptableObjectScriptCommands::testCleanup()
      {
        ScriptableObjectRegistry::removeScriptableObject<MockScriptableObject>();
      }

#pragma endregion

#pragma region Initialize Tests

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Initialize_Adds_ScriptableObjectUserType_ToGlobalTable)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state.globals()["ScriptableObject"].valid());

        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        Assert::IsTrue(state.globals()["ScriptableObject"].valid());
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Initialize_Adds_load_ScriptCommand_ToScriptableObjectTable)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state.globals()["ScriptableObject"]["load"].valid());

        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        Assert::IsTrue(state.globals()["ScriptableObject"]["load"].valid());
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Initialize_Adds_delete_ScriptCommand_ToScriptableObjectTable)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state.globals()["ScriptableObject"]["delete"].valid());

        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        Assert::IsTrue(state.globals()["ScriptableObject"]["delete"].valid());
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Initialize_Adds_getName_ScriptCommand_ToScriptableObjectTable)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state.globals()["ScriptableObject"]["getName"].valid());

        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        Assert::IsTrue(state.globals()["ScriptableObject"]["getName"].valid());
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Initialize_InitializesGameSettingsScriptCommands)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state.globals()["GameSettings"].valid());

        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        Assert::IsTrue(state.globals()["GameSettings"].valid());
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Initialize_InitializesWindowSettingsScriptCommands)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state.globals()["WindowSettings"].valid());

        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        Assert::IsTrue(state.globals()["WindowSettings"].valid());
      }

#pragma endregion

#pragma region Scriptable Object Load Tests

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Load_InputtingInvalidPath_ReturnsNil)
      {
        ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

        Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

        sol::state& state = LuaState::instance();
        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        auto functionResult = state["ScriptableObject"]["load"].get<sol::protected_function>().call("WubbaLubba");

        Assert::IsTrue(functionResult.valid());

        sol::object obj = functionResult.get<sol::object>();
        
        Assert::IsTrue(obj == sol::nil);
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Load_InputtingValidPathToUnregisteredType_ReturnsNil)
      {
        Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

        sol::state& state = LuaState::instance();
        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        auto functionResult = state["ScriptableObject"]["load"].get<sol::protected_function>().call(
          MockScriptableObjectLoadingResources::getValidFullPath().as_string());

        Assert::IsTrue(functionResult.valid());

        sol::object obj = functionResult.get<sol::object>();

        Assert::IsTrue(obj == sol::nil);
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Load_InputtingValidPathToRegisteredInvalidScriptableObject_ReturnsNil)
      {
        ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

        Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

        sol::state& state = LuaState::instance();
        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        auto functionResult = state["ScriptableObject"]["load"].get<sol::protected_function>().call(
          MockScriptableObjectLoadingResources::getInvalidFullPath().as_string());

        Assert::IsTrue(functionResult.valid());

        sol::object obj = functionResult.get<sol::object>();

        Assert::IsTrue(obj == sol::nil);
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Load_InputtingValidPathToRegisteredValidScriptableObject_ReturnsInstantiatedScriptableObject)
      {
        ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

        Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

        sol::state& state = LuaState::instance();
        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        auto functionResult = state["ScriptableObject"]["load"].get<sol::protected_function>().call(
          MockScriptableObjectLoadingResources::getValidFullPath().as_string());

        Assert::IsTrue(functionResult.valid());

        auto ptr = functionResult.get<ScriptableObject*>();

        Assert::IsNotNull(ptr);
        Assert::IsNotNull(dynamic_cast<MockScriptableObject*>(ptr));
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Load_InputtingValidPathToregisteredValidScriptableObject_SetsValuesOnNewlyCreatedScriptableObject)
      {
        ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

        Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

        sol::state& state = LuaState::instance();
        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);

        auto functionResult = state["ScriptableObject"]["load"].get<sol::protected_function>().call(
          MockScriptableObjectLoadingResources::getValidFullPath().as_string());

        Assert::IsTrue(functionResult.valid());

        auto ptr = functionResult.get<ScriptableObject*>();

        Assert::AreEqual("Valid", ptr->getName().c_str());
        Assert::AreEqual("34b0d489-8485-4391-b3b9-b3f062e90c4a", ptr->getGuid().str().c_str());
      }

#pragma endregion

#pragma region Scriptable Object Delete Tests

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Delete_InputtingNullptr_DoesNothing)
      {
        MockScriptableObject* scriptableObject = nullptr;

        Assert::IsNull(scriptableObject);

        sol::state& state = LuaState::instance();
        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);
        state["ScriptableObject"]["delete"].get<sol::protected_function>().call(scriptableObject);

        Assert::IsNull(scriptableObject);
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_Delete_InputtingNonNullptr_DeletesNullptr)
      {
        // Cannot test this situation - no way to know a pointer has been deleted
        // We leave it to show it has been considered
      }

#pragma endregion

#pragma region Get Name Tests

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_getName_NameEmptyString_ReturnsEmptyString)
      {
        std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("");

        Assert::IsTrue(scriptableObject->getName().empty());
        
        sol::state& state = LuaState::instance();
        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);
        auto result = state["ScriptableObject"]["getName"].get<sol::protected_function>().call(scriptableObject.get());
        sol::error er = result;
        Assert::IsTrue(result.valid());
        Assert::IsTrue(result.get<std::string>().empty());
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(ScriptableObjectScriptCommands_getName_NameNonEmptyString_ReturnsCorrectString)
      {
        std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObject::create<MockScriptableObject>("Test");

        Assert::AreEqual("Test", scriptableObject->getName().c_str());

        sol::state& state = LuaState::instance();
        Celeste::Lua::ScriptableObjectScriptCommands::initialize(state);
        auto result = state["ScriptableObject"]["getName"].get<sol::protected_function>().call(scriptableObject.get());

        Assert::IsTrue(result.valid());
        Assert::AreEqual("Test", result.get<std::string>().c_str());
      }

#pragma endregion

      };
    }
  }
}