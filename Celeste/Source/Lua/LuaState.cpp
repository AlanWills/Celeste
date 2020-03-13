#include "Lua/LuaState.h"
#include "Debug/Assert.h"
#include "Debug/Log.h"


namespace Celeste::Lua
{
  //------------------------------------------------------------------------------------------------
  LuaState::LuaState() :
    m_state()
  {
    m_state.open_libraries(
      sol::lib::base,
      sol::lib::package,
      sol::lib::string,
      sol::lib::math,
      sol::lib::os,
      sol::lib::table);
  }

  //------------------------------------------------------------------------------------------------
  sol::state& LuaState::instance()
  {
    static LuaState L;
    return L.m_state;
  }

  //------------------------------------------------------------------------------------------------
  sol::protected_function_result LuaState::script(const std::string& code)
  {
    // In release, maybe use the unsafe version of script
    sol::protected_function_result result;

    try
    {
      result = instance().safe_script(code);
    }
    catch (const sol::error & e)
    {
      LOG(e.what());
      ASSERT_FAIL_MSG(e.what());
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  sol::protected_function_result LuaState::scriptFile(const Path& path)
  {
    // In release, maybe use the unsafe version of script_file
    sol::protected_function_result result;

    try
    {
      result = instance().safe_script_file(path.as_string());
    }
    catch (const sol::error & e)
    {
      LOG(e.what());
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  sol::protected_function_result LuaState::requireModule(const std::string& moduleName)
  {
    std::string code("require \"");
    code.append(moduleName);
    code.append("\"");

    return LuaState::script(code);
  }

  //------------------------------------------------------------------------------------------------
  void LuaState::appendToLuaPackagePath(const Path& pathToAppend)
  {
    appendToLuaPackagePath(pathToAppend.as_string());
  }

  //------------------------------------------------------------------------------------------------
  void LuaState::appendToLuaPackagePath(const std::string& pathToAppend)
  {
    sol::state& state = Lua::LuaState::instance();
    std::string oldPath = state["package"]["path"].get_or<std::string>("");

    if (!oldPath.empty() &&
      oldPath.back() != ';')
    {
      // Make sure we add a separator if it's needed
      oldPath.push_back(';');
    }

    oldPath.append(pathToAppend);
    state["package"]["path"] = oldPath;
  }
}