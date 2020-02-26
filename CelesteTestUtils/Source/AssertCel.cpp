#include "AssertCel.h"
#include "Lua/LuaState.h"
#include "FileSystem/File.h"


namespace CelesteTestUtils
{
  //------------------------------------------------------------------------------------------------
  void AssertCel::FileExists(const Celeste::Path& path) 
  { 
    Assert::IsTrue(Celeste::File::exists(path)); 
  }

  //------------------------------------------------------------------------------------------------
  void AssertCel::FileDoesNotExist(const Celeste::Path& path) 
  { 
    Assert::IsFalse(Celeste::File::exists(path)); 
  }

  //------------------------------------------------------------------------------------------------
  void AssertCel::IsLuaModuleLoaded(const std::string& moduleName)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsTrue(state["package"]["loaded"][moduleName].valid());
  }

  //------------------------------------------------------------------------------------------------
  void AssertCel::IsLuaModuleNotLoaded(const std::string& moduleName)
  {
    sol::state& state = Celeste::Lua::LuaState::instance();

    Assert::IsTrue(state["package"].valid());
    Assert::IsTrue(state["package"]["loaded"].valid());
    Assert::IsFalse(state["package"]["loaded"][moduleName].valid());
  }
}