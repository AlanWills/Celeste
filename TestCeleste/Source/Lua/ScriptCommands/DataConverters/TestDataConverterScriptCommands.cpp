#include "Lua/ScriptCommands/DataConverters/DataConverterScriptCommands.h"
#include "Lua/LuaState.h"

#include "UtilityHeaders/UnitTestHeaders.h"
#include "FileAssert.h"

#include "Mocks/DataConverters/MockDataConverter.h"
#include "Resources/TestResources.h"
#include "Resources/ResourceManager.h"

using namespace Celeste::Resources;
using LuaState = Celeste::Lua::LuaState;


namespace TestCeleste::Lua::DataConverterScriptCommands
{
  CELESTE_TEST_CLASS(TestDataConverterScriptCommands)

  //------------------------------------------------------------------------------------------------
  void TestDataConverterScriptCommands::testCleanup()
  {
    getResourceManager().unloadAll<Data>();
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_AddsDataConverterUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["DataConverter"].valid());

    Celeste::Lua::DataConverterScriptCommands::initialize();

    Assert::IsTrue(state.globals()["DataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_Adds_findAttribute_ToDataConverterTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["DataConverter"]["findAttribute"].valid());

    Celeste::Lua::DataConverterScriptCommands::initialize();

    Assert::IsTrue(state.globals()["DataConverter"]["findAttribute"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_Adds_findElement_ToDataConverterTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["DataConverter"]["findElement"].valid());

    Celeste::Lua::DataConverterScriptCommands::initialize();

    Assert::IsTrue(state.globals()["DataConverter"]["findElement"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_Adds_convertFromXML_ToDataConverterTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["DataConverter"]["convertFromXML"].valid());

    Celeste::Lua::DataConverterScriptCommands::initialize();

    Assert::IsTrue(state.globals()["DataConverter"]["convertFromXML"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_InitializesComponentDataConverterScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["ComponentDataConverter"].valid());

    Celeste::Lua::DataConverterScriptCommands::initialize();

    Assert::IsTrue(state.globals()["ComponentDataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_InitializesLuaComponentDataConverterScriptCommands)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["LuaComponentDataConverter"].valid());

    Celeste::Lua::DataConverterScriptCommands::initialize();

    Assert::IsTrue(state.globals()["LuaComponentDataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_RequiresDataConvertersModule)
  {
    Celeste::Lua::DataConverterScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    // Ensure require is in the global namespace
    state.open_libraries(sol::lib::package);

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"]["DataConverters.DataConverters"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_RequiresAnimatorDataConverterModule)
  {
    Celeste::Lua::DataConverterScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    // Ensure require is in the global namespace
    state.open_libraries(sol::lib::package);

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"]["DataConverters.Animation.AnimatorDataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_RequiresAudioSourceDataConverterModule)
  {
    Celeste::Lua::DataConverterScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    // Ensure require is in the global namespace
    state.open_libraries(sol::lib::package);

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"]["DataConverters.Audio.AudioSourceDataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_RequiresKeyboardActivatorDataConverterModule)
  {
    Celeste::Lua::DataConverterScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    // Ensure require is in the global namespace
    state.open_libraries(sol::lib::package);

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"]["DataConverters.Input.KeyboardActivatorDataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_RequiresKeyboardVisibilityDataConverterModule)
  {
    Celeste::Lua::DataConverterScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    // Ensure require is in the global namespace
    state.open_libraries(sol::lib::package);

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"]["DataConverters.Input.KeyboardVisibilityDataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_RequiresEllipseColliderDataConverterModule)
  {
    Celeste::Lua::DataConverterScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    // Ensure require is in the global namespace
    state.open_libraries(sol::lib::package);

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"]["DataConverters.Physics.EllipseColliderDataConverter"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_Initialize_RequiresCanvasDataConverterModule)
  {
    Celeste::Lua::DataConverterScriptCommands::initialize();
    sol::state& state = LuaState::instance();

    // Ensure require is in the global namespace
    state.open_libraries(sol::lib::package);

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"]["DataConverters.Rendering.CanvasDataConverter"].valid());
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_ConvertFromXML_InputtingNonExistentFilePath_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::DataConverterScriptCommands::initialize();

    MockDataConverter dataConverter;

    Assert::IsFalse(state.globals()["DataConverter"]["convertFromXML"](static_cast<DataConverter&>(dataConverter), "WubbaLubbaDubDub").get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_ConvertFromXML_InputtingExistentFilePath_ToEmptyFile_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::DataConverterScriptCommands::initialize();

    Path filePath(TestResources::getTempDirectory(), "Test.xml");
    File file(filePath);
    file.clear();
    file.append("");

    FileAssert::FileExists(filePath.as_string());
    FileAssert::FileContentsEqual(filePath.as_string(), "");

    MockDataConverter dataConverter;

    Assert::IsFalse(state.globals()["DataConverter"]["convertFromXML"](static_cast<DataConverter&>(dataConverter), filePath.as_string()).get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_ConvertFromXML_InputtingExistentFilePath_ToInvalidData_ReturnsFalse)
  {
    // Cannot simulate invalid data as the base data converter has no requirements
    // Derived classes will test this case
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(DataConverterScriptCommands_ConvertFromXML_InputtingExistentFilePath_ToValidData_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::DataConverterScriptCommands::initialize();

    MockDataConverter dataConverter;
    Path filePath(TestResources::getTempDirectory(), "Test.xml");

    FileAssert::FileDoesNotExist(filePath.as_string());

    XMLDocument document;
    document.InsertFirstChild(document.NewElement("DataConverter"));

    Assert::IsTrue(XML_SUCCESS == document.SaveFile(filePath.c_str()));
    FileAssert::FileExists(filePath.as_string());
    Assert::IsTrue(state.globals()["DataConverter"]["convertFromXML"](static_cast<DataConverter&>(dataConverter), filePath.as_string()).get<bool>());
  }

#pragma endregion

  };
}