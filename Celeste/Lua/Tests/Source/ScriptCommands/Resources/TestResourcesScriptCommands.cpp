#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Resources/ResourcesScriptCommands.h"
#include "Lua/LuaState.h"

#include "TestResources/Resources/Data/PrefabLoadingResources.h"
#include "Resources/ResourceManager.h"

#include "CelesteTestUtils/Assert/AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste::Resources;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestResourcesScriptCommands)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    getResourceManager().setResourcesDirectory(TestResources::getResourcesDirectory());
    getResourceManager().unload<Data>(TestResources::getDataXmlFullPath());
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    getResourceManager().setResourcesDirectory(TestResources::getResourcesDirectory());
    getResourceManager().unload<Data>(TestResources::getDataXmlFullPath());
  }

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_ResourcesTableToGlobalTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_getResourcesDirectory_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["getResourcesDirectory"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_loadSound_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["loadSound"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_loadPrefab_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["loadPrefab"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_loadTexture2D_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["loadTexture2D"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_loadData_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["loadData"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_isVertexShaderLoaded_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["isVertexShaderLoaded"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_isFragmentShaderLoaded_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["isFragmentShaderLoaded"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_isSoundLoaded_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["isSoundLoaded"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_isDataLoaded_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["isDataLoaded"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_isTexture2DLoaded_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["isTexture2DLoaded"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_isFontLoaded_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["isFontLoaded"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_isPrefabLoaded_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["isPrefabLoaded"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_isModelLoaded_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["isModelLoaded"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadVertexShader_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadVertexShader"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadFragmentShader_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadFragmentShader"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadSound_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadSound"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadData_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadData"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadTexture2D_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadTexture2D"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadFont_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadFont"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadPrefab_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadPrefab"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadModel_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadModel"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadAllVertexShaders_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadAllVertexShaders"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadAllFragmentShaders_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadAllFragmentShaders"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadAllSounds_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadAllSounds"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadAllData_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadAllData"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadAllTexture2Ds_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadAllTexture2Ds"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadAllFonts_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadAllFonts"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadAllPrefabs_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadAllPrefabs"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadAllModels_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadAllModels"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Adds_unloadAllResources_ToResourcesTable)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Resources"]["unloadAllResources"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Initializes_Texture2DScriptCommands)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Texture2D"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Initializes_ModelScriptCommands)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Model"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Initializes_SoundScriptCommands)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Sound"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Initializes_DataScriptCommands)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Data"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Initializes_PrefabScriptCommands)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Prefab"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Initializes_FontScriptCommands)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["Font"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Initializes_VertexShaderScriptCommands)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["VertexShader"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_Initialize_Initializes_FragmentShaderScriptCommands)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);

    Assert::IsTrue(state.globals()["FragmentShader"].valid());
  }

#pragma endregion

#pragma region Get Resources Directory Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_getResourcesDirectory_ReturnsResourceManagerResourceDirectory)
  {
    Path expected("WubbaLubba", "Dub", "Dub");
    getResourceManager().setResourcesDirectory(expected);

    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);
    sol::protected_function function = state["Resources"]["getResourcesDirectory"].get<sol::protected_function>();

    Assert::IsTrue(function.valid());
    Assert::AreEqual(expected.as_string(), function.call().get<std::string>());
  }

#pragma endregion

#pragma region Load Sound Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_loadSound_InputtingInvalidPath_ReturnsNullptr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);
    sol::protected_function function = state["Resources"]["loadSound"].get<sol::protected_function>();

    Assert::IsTrue(function.valid());

    auto result = function.call("Test");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Resources::Sound*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_loadPrefab_InputtingValidPath_ReturnsSound)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);
    sol::protected_function function = state["Resources"]["loadSound"].get<sol::protected_function>();

    Assert::IsTrue(function.valid());

    auto expected = getResourceManager().load<Resources::Sound>(TestResources::getButtonHoverWavRelativePath());
    auto result = function.call(TestResources::getButtonHoverWavRelativePath());

    Assert::IsTrue(result.valid());

    Resources::Sound* actual = result.get<Resources::Sound*>();

    Assert::IsNotNull(actual);
    Assert::AreEqual(expected, actual);
  }

#pragma endregion

#pragma region Load Prefab Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_loadPrefab_InputtingInvalidPath_ReturnsNullptr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);
    sol::protected_function function = state["Resources"]["loadPrefab"].get<sol::protected_function>();

    Assert::IsTrue(function.valid());

    auto result = function.call(PrefabLoadingResources::getInvalidRelativePath());

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Resources::Prefab*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_loadPrefab_InputtingValidPath_ReturnsPrefab)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);
    sol::protected_function function = state["Resources"]["loadPrefab"].get<sol::protected_function>();

    Assert::IsTrue(function.valid());

    auto expected = getResourceManager().load<Resources::Prefab>(PrefabLoadingResources::getValidSingleGameObjectRelativePath());
    auto result = function.call(PrefabLoadingResources::getValidSingleGameObjectRelativePath());

    Assert::IsTrue(result.valid());

    Resources::Prefab* actual = result.get<Resources::Prefab*>();

    Assert::IsNotNull(actual);
    Assert::AreEqual(expected, actual);
  }

#pragma endregion

#pragma region Load Texture2D Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_loadTexture2D_InputtingInvalidPath_ReturnsNullptr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);
    sol::protected_function function = state["Resources"]["loadTexture2D"].get<sol::protected_function>();

    Assert::IsTrue(function.valid());

    auto result = function.call("Test");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Resources::Texture2D*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_loadTexture2D_InputtingValidPath_ReturnsTexture2D)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);
    sol::protected_function function = state["Resources"]["loadTexture2D"].get<sol::protected_function>();

    Assert::IsTrue(function.valid());

    auto expected = getResourceManager().load<Resources::Texture2D>(TestResources::getBlockPngRelativePath());
    auto result = function.call(TestResources::getBlockPngRelativePath());

    Assert::IsTrue(result.valid());

    Resources::Texture2D* actual = result.get<Resources::Texture2D*>();

    Assert::IsNotNull(actual);
    Assert::AreEqual(expected, actual);
  }

#pragma endregion

#pragma region Load Data Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_loadData_InputtingInvalidPath_ReturnsNullptr)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);
    sol::protected_function function = state["Resources"]["loadData"].get<sol::protected_function>();

    Assert::IsTrue(function.valid());

    auto result = function.call("Test");

    Assert::IsTrue(result.valid());
    Assert::IsNull(result.get<Resources::Data*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourcesScriptCommands_loadData_InputtingValidPath_ReturnsData)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Resources::ScriptCommands::initialize(state);
    sol::protected_function function = state["Resources"]["loadData"].get<sol::protected_function>();

    Assert::IsTrue(function.valid());

    auto expected = getResourceManager().load<Resources::Data>(TestResources::getDataXmlRelativePath());
    auto result = function.call(TestResources::getDataXmlRelativePath());

    Assert::IsTrue(result.valid());

    Resources::Data* actual = result.get<Resources::Data*>();

    Assert::IsNotNull(actual);
    Assert::AreEqual(expected, actual);
  }

#pragma endregion

  };
}