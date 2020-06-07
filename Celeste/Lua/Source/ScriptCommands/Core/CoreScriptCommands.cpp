#include "ScriptCommands/Core/CoreScriptCommands.h"
#include "Game/Game.h"
#include "Assert/Assert.h"
#include "Lua/LuaState.h"
#include "CelesteStl/Templates/Unused.h"


namespace Celeste::Lua::Core::ScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void _assert(bool condition)
    {
#if _DEBUG
      ASSERT(condition);
#else
      celstl::unused(condition);
#endif
    }

    //------------------------------------------------------------------------------------------------
    void assertFail()
    {
      ASSERT_FAIL();
    }

    //------------------------------------------------------------------------------------------------
    void assertFailMessage(const std::string& message)
    {
#if _DEBUG
      ASSERT_FAIL_MSG(message.c_str());
#else
      celstl::unused(message);
#endif
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    void log(T message)
    {
      LOG(Celeste::to_string<T>(message));
    }

    //------------------------------------------------------------------------------------------------
    template <>
    void log(const std::string& message)
    {
      LOG(message);
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    void logWarning(T message)
    {
      LOG_WARNING(Celeste::to_string<T>(message));
    }

    //------------------------------------------------------------------------------------------------
    template <>
    void logWarning(const std::string& message)
    {
      LOG_WARNING(message);
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    void logError(T message)
    {
      LOG_ERROR(Celeste::to_string<T>(message));
    }

    //------------------------------------------------------------------------------------------------
    template <>
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
  void initialize(sol::state& state)
  {
    state.set_function("assert", &Internals::_assert);
    state.set_function("assertFail", &Internals::assertFail);
    state.set_function("assertFailMessage", &Internals::assertFailMessage);
    state.set_function("log", sol::overload(
      &Internals::log<const std::string&>, 
      &Internals::log<bool>, 
      &Internals::log<int>,
      &Internals::log<unsigned int>,
      &Internals::log<size_t>,
      &Internals::log<float>));
    state.set_function("logWarning", sol::overload(
      &Internals::logWarning<const std::string&>,
      &Internals::logWarning<bool>,
      &Internals::logWarning<int>,
      &Internals::logWarning<unsigned int>,
      &Internals::logWarning<size_t>,
      &Internals::logWarning<float>));
    state.set_function("logError", sol::overload(
      &Internals::logError<const std::string&>,
      &Internals::logError<bool>,
      &Internals::logError<int>,
      &Internals::logError<unsigned int>,
      &Internals::logError<size_t>,
      &Internals::logError<float>));
    state.set_function("exit", &Internals::exit);

    // Initialize the lua script files for Celeste
    LuaState::requireModule("Core.FileSystem.Path");
  }
}