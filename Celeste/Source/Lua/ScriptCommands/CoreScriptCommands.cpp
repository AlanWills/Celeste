#include "Lua/ScriptCommands/CoreScriptCommands.h"
#include "Lua/LuaState.h"
#include "Game/Game.h"
#include "Debug/Assert.h"


namespace Celeste::Lua::CoreScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void _assert(bool condition)
    {
      ASSERT(condition);
    }

    //------------------------------------------------------------------------------------------------
    void assertFail()
    {
      ASSERT_FAIL();
    }

    //------------------------------------------------------------------------------------------------
    void assertFailMessage(const std::string& message)
    {
      ASSERT_FAIL_MSG(message.c_str());
    }

    //------------------------------------------------------------------------------------------------
    void log(const std::string& message)
    {
      LOG(message);
    }

    //------------------------------------------------------------------------------------------------
    void logWarning(const std::string& message)
    {
      LOG_WARNING(message);
    }

    //------------------------------------------------------------------------------------------------
    void logError(const std::string& message)
    {
      LOG_ERROR(message);
    }

    //------------------------------------------------------------------------------------------------
    void exit()
    {
      Game::exit();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = LuaState::instance();

    state.set_function("assert", &Internals::_assert);
    state.set_function("assertFail", &Internals::assertFail);
    state.set_function("assertFailMessage", &Internals::assertFailMessage);
    state.set_function("log", &Internals::log);
    state.set_function("logWarning", &Internals::logWarning);
    state.set_function("logError", &Internals::logError);
    state.set_function("exit", &Internals::exit);

    // Initialize the lua script files for Celeste
    LuaState::requireModule("Core.FileSystem.Path");
  }
}