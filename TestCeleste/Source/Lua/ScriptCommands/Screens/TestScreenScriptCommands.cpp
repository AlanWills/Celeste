#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/Screens/ScreenScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Resources/Screens/ScreenLoadingResources.h"
#include "Screens/Screen.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"
#include "FileAssert.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestScreenScriptCommands)

#pragma region Initialize Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScreenScriptCommands_Initialize_Adds_ScreenUserType_ToGlobalTable)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Screen"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Initialize_Adds_load_ToScreenTable)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Screen"]["load"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Initialize_Adds_getName_ToScreenTable)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Screen"]["getName"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Initialize_Adds_allocateGameObject_ToScreenTable)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Screen"]["allocateGameObject"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Initialize_Adds_deallocateGameObject_ToScreenTable)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Screen"]["deallocateGameObject"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Initialize_Adds_findGameObject_ToScreenTable)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    Assert::IsTrue(state.globals()["Screen"]["findGameObject"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Initialize_Adds_as_ToScreenTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["Screen"]["as"].valid());

    Celeste::Lua::ScreenScriptCommands::initialize();

    Assert::IsTrue(state.globals()["Screen"]["as"].valid());
  }

#pragma endregion

#pragma region Screen Load Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_Load_InputtingNonExistentFilePath_ReturnsNullHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    auto result = state["Screen"]["load"].get<sol::protected_function>().call("WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());

    AutoDeallocator<Screen> screen = result.get<observer_ptr<Screen>>();

    Assert::IsNull(screen.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_loadScreen_InputtingExistentFilePath_ToInvalidFile_ReturnsNullHandle)
  {
    Path path(TestResources::getTempDirectory(), "Test.asset");
    File file(path);
    file.append("");

    FileAssert::FileExists(path.as_string());

    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    auto result = state["Screen"]["load"].get<sol::protected_function>().call("WubbaLubbaDubDub");

    Assert::IsTrue(result.valid());

    AutoDeallocator<Screen> screen = result.get<observer_ptr<Screen>>();

    Assert::IsNull(screen.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_loadScreen_InputtingExistentFilePath_ToValidFile_ReturnsNewlyAllocatedScreen)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    auto result = state["Screen"]["load"].get<sol::protected_function>().call(ScreenLoadingResources::getDataElementFullPath().as_string());

    Assert::IsTrue(result.valid());

    AutoDeallocator<Screen> screen = result.get<observer_ptr<Screen>>();

    Assert::IsNotNull(screen.get());
  }

#pragma endregion

#pragma region Get Name Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_getName_ReturnsScreenNameString)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;
    screen.setName("WubbaLubbaDubDub");

    auto result = state["Screen"]["getName"].get<sol::protected_function>().call(screen);

    Assert::IsTrue(result.valid());
    Assert::AreEqual("WubbaLubbaDubDub", result.get<std::string>().c_str());
  }

#pragma endregion

#pragma region Allocate Game Object Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_allocateGameObject_ReturnsGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;

    auto result = state["Screen"]["allocateGameObject"].get<sol::protected_function>().call(screen);

    Assert::IsTrue(result.valid());

    observer_ptr<GameObject> gameObject = result.get<observer_ptr<GameObject>>();

    Assert::IsNotNull(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_allocateGameObject_AllocatesGameObjectInScreen)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;

    auto result = state["Screen"]["allocateGameObject"].get<sol::protected_function>().call(screen);

    Assert::IsTrue(result.valid());

    observer_ptr<GameObject> gameObject = result.get<observer_ptr<GameObject>>();
    gameObject->setName("Test");

    Assert::AreEqual(&screen, gameObject->getScreen());
    Assert::AreEqual(gameObject, screen.findGameObject("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_allocateGameObject_SetsGameObjectParentToScreenRoot)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;

    auto result = state["Screen"]["allocateGameObject"].get<sol::protected_function>().call(screen);

    Assert::IsTrue(result.valid());

    observer_ptr<GameObject> gameObject = result.get<observer_ptr<GameObject>>();

    Assert::IsTrue(&screen.getScreenRoot() == gameObject->getParentTransform());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_allocateGameObject_WithTransformParent_ReturnsGameObject)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;
    Transform transform;

    auto result = state["Screen"]["allocateGameObject"].get<sol::protected_function>().call(screen, transform);

    Assert::IsTrue(result.valid());

    observer_ptr<GameObject> gameObject = result.get<observer_ptr<GameObject>>();

    Assert::IsNotNull(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_allocateGameObject_WithTransformParent_AllocatesGameObjectInScreen)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;
    Transform transform;

    auto result = state["Screen"]["allocateGameObject"].get<sol::protected_function>().call(screen, transform);

    Assert::IsTrue(result.valid());

    observer_ptr<GameObject> gameObject = result.get<observer_ptr<GameObject>>();
    gameObject->setName("Test");

    Assert::AreEqual(&screen, gameObject->getScreen());
    Assert::AreEqual(gameObject, screen.findGameObject("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_allocateGameObject_WithTransformParent_SetsGameObjectParentToInputtedTransform)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;
    Transform transform;

    auto result = state["Screen"]["allocateGameObject"].get<sol::protected_function>().call(screen, transform);

    Assert::IsTrue(result.valid());

    observer_ptr<GameObject> gameObject = result.get<observer_ptr<GameObject>>();

    Assert::AreEqual(&screen, gameObject->getScreen());
    Assert::AreEqual(&transform, gameObject->getParentTransform());
  }

#pragma endregion

#pragma region Find Game Object Tests

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_findGameObject_InputtingEmptyString_ReturnsNullGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;

    auto result = state["Screen"]["findGameObject"].get<sol::protected_function>().call(screen, "");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<observer_ptr<GameObject>>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_findGameObject_InputtingNonEmptyString_ForNonExistentGameObject_ReturnsNullGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;

    Assert::IsNull(screen.findGameObject("Test"));

    auto result = state["Screen"]["findGameObject"].get<sol::protected_function>().call(screen, "Test");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<observer_ptr<GameObject>>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_findGameObject_InputtingNonEmptyString_ForSingleExistentGameObject_ReturnsCorrectGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;
    observer_ptr<GameObject> gameObject = screen.allocateGameObject();
    gameObject->setName("Test");

    Assert::AreEqual(gameObject, screen.findGameObject("Test"));

    auto result = state["Screen"]["findGameObject"].get<sol::protected_function>().call(screen, "Test");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(gameObject, result.get<observer_ptr<GameObject>>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_findGameObject_InputtingNonEmptyString_ForMultipleExistentGameObject_ReturnsFirstMatchingGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;
    observer_ptr<GameObject> gameObject = screen.allocateGameObject();
    gameObject->setName("Test");

    observer_ptr<GameObject> gameObject2 = screen.allocateGameObject();
    gameObject2->setName("Test");

    Assert::AreEqual(gameObject, screen.findGameObject("Test"));

    auto result = state["Screen"]["findGameObject"].get<sol::protected_function>().call(screen, "Test");

    Assert::IsTrue(result.valid());
    Assert::AreEqual(gameObject, result.get<observer_ptr<GameObject>>());
  }

#pragma endregion

#pragma region StringId Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_findGameObject_InputtingEmptyStringId_ReturnsNullGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;

    auto result = state["Screen"]["findGameObject"].get<sol::protected_function>().call(screen, internString(""));

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<observer_ptr<GameObject>>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_findGameObject_InputtingNonZeroStringId_ForNonExistentGameObject_ReturnsNullGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;
    StringId name = internString("Test");

    Assert::IsNull(screen.findGameObject(name));

    auto result = state["Screen"]["findGameObject"].get<sol::protected_function>().call(screen, name);

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<observer_ptr<GameObject>>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_findGameObject_InputtingNonZeroStringId_ForSingleExistentGameObject_ReturnsCorrectGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;
    StringId name = internString("Test");
    observer_ptr<GameObject> gameObject = screen.allocateGameObject();
    gameObject->setName(name);

    Assert::AreEqual(gameObject, screen.findGameObject(name));

    auto result = state["Screen"]["findGameObject"].get<sol::protected_function>().call(screen, name);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(gameObject, result.get<observer_ptr<GameObject>>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_findGameObject_InputtingNonZeroStringId_ForMultipleExistentGameObject_ReturnsFirstMatchingGameObjectHandle)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::ScreenScriptCommands::initialize();

    Screen screen;
    StringId name = internString("Test");
    observer_ptr<GameObject> gameObject = screen.allocateGameObject();
    gameObject->setName("Test");

    observer_ptr<GameObject> gameObject2 = screen.allocateGameObject();
    gameObject2->setName(name);

    Assert::AreEqual(gameObject, screen.findGameObject(name));

    auto result = state["Screen"]["findGameObject"].get<sol::protected_function>().call(screen, name);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(gameObject, result.get<observer_ptr<GameObject>>());
  }

#pragma endregion

#pragma endregion

#pragma region Screen As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_as_InputtingNull_CastingToScreenType_ReturnsNil)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(nullptr, "Screen");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class Screen : public Celeste::Screen {};
    state.new_usertype<Screen>("Screen");

    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(nullptr, "Screen");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_ScreenHandle_as_InputtingNullScreenHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_as_InputtingNonNullScreen_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    Screen screen;
    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(&screen, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&screen == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_as_InputtingNonNullScreen_CastingToScreenType_ReturnsCorrectPtr)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Screen screen;
    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(&screen, "Screen");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&screen == functionResult.get<Screen*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_as_InputtingNonNullScreen_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class Screen : public Celeste::Screen {};
    state.new_usertype<Screen>("Screen");

    Screen screen;
    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(&screen, "Screen");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_as_InputtingNonNullScreen_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    Screen screen;
    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(&screen, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenScriptCommands_Screen_as_InputtingNonNullScreen_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::ScreenScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["Screen"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}
