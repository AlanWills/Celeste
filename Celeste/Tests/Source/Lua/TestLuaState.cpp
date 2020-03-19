#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/LuaState.h"
#include "TestResources/Lua/LuaScriptResources.h"

#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCeleste::Lua
{
  CELESTE_TEST_CLASS(TestLuaState)

  std::string m_originalPackagePath;

  //------------------------------------------------------------------------------------------------
  void TestLuaState::testInitialize()
  {
    m_originalPackagePath = LuaState::instance()["package"]["path"].get_or<std::string>("");
    LuaState::instance()["Test"] = sol::nil;
    LuaState::instance()["package"]["loaded"]["EmptyModule"] = sol::nil;
  }

  //------------------------------------------------------------------------------------------------
  void TestLuaState::testCleanup()
  {
    LuaState::instance()["package"]["path"] = m_originalPackagePath;
    LuaState::instance()["Test"] = sol::nil;
    LuaState::instance()["package"]["loaded"]["EmptyModule"] = sol::nil;
  }

#pragma region Script Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_Script_InputtingEmptyString_ReturnsValidResult)
  {
    Assert::IsTrue(Celeste::Lua::LuaState::script("").valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_Script_InputtingInvalidCode_ReturnsInvalidResult)
  {
    Assert::IsFalse(Celeste::Lua::LuaState::script("Wubba.Lubba.Dub.Dub").valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_Script_InputtingValidCode_ReturnsValidResult)
  {
    Assert::IsTrue(Celeste::Lua::LuaState::script("local Test = 5 + 2").valid());
  }

#pragma endregion

#pragma region Script File Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_ScriptFile_InputtingNonExistentScriptPath_ReturnsInvalidResult)
  {
    Assert::IsFalse(Celeste::Lua::LuaState::scriptFile("WubbaLubbaDubDub").valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_ScriptFile_InputtingExistentScriptPath_InvalidScript_ReturnsInvalidResult)
  {
    Path path(TestResources::getTempDirectory(), "Test.lua");
    File file(path);
    file.append("path.print()");

    Assert::IsFalse(Celeste::Lua::LuaState::scriptFile(path).valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_ScriptFile_InputtingExistentScriptPath_ValidScript_ReturnsValidResult)
  {
    Path path(TestResources::getTempDirectory(), "Test.lua");
    File file(path);
    file.append("local var = 5");

    Assert::IsTrue(Celeste::Lua::LuaState::scriptFile(path).valid());
  }

#pragma endregion

#pragma region Require Module Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_RequireModule_InvalidModuleName_ReturnsFalseResult)
  {
    Assert::IsFalse(Celeste::Lua::LuaState::requireModule("WubbaLubbaDubDub").valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_RequireModule_ValidModuleName_ModuleNotLoaded_ReturnsTrue)
  {
    AssertCel::IsLuaModuleNotLoaded(LuaScriptResources::getEmptyModuleName());
    Assert::IsTrue(Celeste::Lua::LuaState::requireModule(LuaScriptResources::getEmptyModuleName()).valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_RequireModule_ValidModuleName_ModuleNotLoaded_LoadsModule)
  {
    AssertCel::IsLuaModuleNotLoaded(LuaScriptResources::getEmptyModuleName());

    Celeste::Lua::LuaState::requireModule(LuaScriptResources::getEmptyModuleName()).valid();

    AssertCel::IsLuaModuleLoaded(LuaScriptResources::getEmptyModuleName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_RequireModule_ValidModuleName_ModuleLoaded_ReturnsTrue)
  {
    Celeste::Lua::LuaState::requireModule(LuaScriptResources::getEmptyModuleName()).valid();

    AssertCel::IsLuaModuleLoaded(LuaScriptResources::getEmptyModuleName());
    Assert::IsTrue(Celeste::Lua::LuaState::requireModule(LuaScriptResources::getEmptyModuleName()).valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_RequireModule_ValidModuleName_DoesNothing)
  {
    Celeste::Lua::LuaState::requireModule(LuaScriptResources::getEmptyModuleName()).valid();

    AssertCel::IsLuaModuleLoaded(LuaScriptResources::getEmptyModuleName());

    Celeste::Lua::LuaState::requireModule(LuaScriptResources::getEmptyModuleName()).valid();

    AssertCel::IsLuaModuleLoaded(LuaScriptResources::getEmptyModuleName());
  }

#pragma endregion

#pragma region Append To Lua Package Path Tests

#pragma region Path Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_AppendToPackagePath_InputtingEmptyPath_OriginalPathDoesNotEndInSeparator_AppendsSeparator)
  {
    std::string originalPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::IsFalse(originalPath.empty());

    if (originalPath.back() == ';')
    {
      originalPath.pop_back();
    }
    size_t pathLength = originalPath.size();

    Assert::AreNotEqual(';', originalPath.back());

    LuaState::appendToLuaPackagePath(Path(""));

    std::string newPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::AreEqual(pathLength + 1, newPath.size());
    Assert::AreEqual(';', newPath.back());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_AppendToPackagePath_InputtingEmptyPath_OriginalPathDoesEndInSeparator_DoesNothing)
  {
    std::string originalPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::IsFalse(originalPath.empty());

    if (originalPath.back() != ';')
    {
      originalPath.push_back(';');
    }
    size_t pathLength = originalPath.size();

    Assert::AreEqual(';', originalPath.back());

    LuaState::appendToLuaPackagePath(Path(""));

    std::string newPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::AreEqual(pathLength, newPath.size());
    Assert::AreEqual(';', newPath.back());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_AppendToPackagePath_InputtingNonEmptyPath_OriginalPathDoesNotEndInSeparator_AppendsSeparatorAndPath)
  {
    std::string originalPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::IsFalse(originalPath.empty());

    if (originalPath.back() == ';')
    {
      originalPath.pop_back();
    }
    size_t pathLength = originalPath.size();

    Assert::AreNotEqual(';', originalPath.back());

    std::string path("WubbaLubbaDubDub");
    LuaState::appendToLuaPackagePath(Path(path));

    std::string newPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::AreEqual(pathLength + path.size() + 1, newPath.size());
    Assert::AreEqual(path, newPath.substr(pathLength + 1));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_AppendToPackagePath_InputtingNonEmptyPath_OriginalPathDoesEndInSeparator_AppendsPath)
  {
    std::string originalPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::IsFalse(originalPath.empty());

    if (originalPath.back() != ';')
    {
      originalPath.push_back(';');
    }
    size_t pathLength = originalPath.size();

    Assert::AreEqual(';', originalPath.back());

    std::string path("WubbaLubbaDubDub");
    LuaState::appendToLuaPackagePath(Path(path));

    std::string newPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::AreEqual(pathLength + path.size(), newPath.size());
    Assert::AreEqual(path, newPath.substr(pathLength));
  }

#pragma endregion

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_AppendToPackagePath_InputtingEmptyString_OriginalPathDoesNotEndInSeparator_AppendsSeparator)
  {
    std::string originalPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::IsFalse(originalPath.empty());

    if (originalPath.back() == ';')
    {
      originalPath.pop_back();
    }
    size_t pathLength = originalPath.size();

    Assert::AreNotEqual(';', originalPath.back());

    LuaState::appendToLuaPackagePath(std::string(""));

    std::string newPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::AreEqual(pathLength + 1, newPath.size());
    Assert::AreEqual(';', newPath.back());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_AppendToPackagePath_InputtingEmptyString_OriginalPathDoesEndInSeparator_DoesNothing)
  {
    std::string originalPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::IsFalse(originalPath.empty());

    if (originalPath.back() != ';')
    {
      originalPath.push_back(';');
    }
    size_t pathLength = originalPath.size();

    Assert::AreEqual(';', originalPath.back());

    LuaState::appendToLuaPackagePath(std::string(""));

    std::string newPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::AreEqual(pathLength, newPath.size());
    Assert::AreEqual(';', newPath.back());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_AppendToPackagePath_InputtingNonEmptyString_OriginalPathDoesNotEndInSeparator_AppendsSeparatorAndString)
  {
    std::string originalPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::IsFalse(originalPath.empty());

    if (originalPath.back() == ';')
    {
      originalPath.pop_back();
    }
    size_t pathLength = originalPath.size();

    Assert::AreNotEqual(';', originalPath.back());

    std::string path("WubbaLubbaDubDub");
    LuaState::appendToLuaPackagePath(path);

    std::string newPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::AreEqual(pathLength + path.size() + 1, newPath.size());
    Assert::AreEqual(path, newPath.substr(pathLength + 1));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaState_AppendToPackagePath_InputtingNonEmptyString_OriginalPathDoesEndInSeparator_AppendsString)
  {
    std::string originalPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::IsFalse(originalPath.empty());

    if (originalPath.back() != ';')
    {
      originalPath.push_back(';');
    }
    size_t pathLength = originalPath.size();

    Assert::AreEqual(';', originalPath.back());

    std::string path("WubbaLubbaDubDub");
    LuaState::appendToLuaPackagePath(path);

    std::string newPath = LuaState::instance()["package"]["path"].get_or<std::string>("");

    Assert::AreEqual(pathLength + path.size(), newPath.size());
    Assert::AreEqual(path, newPath.substr(pathLength));
  }

#pragma endregion

#pragma endregion

  };
}