#include "CelesteTestUtils/UnitTest/CelesteUnitTest.h"
#include "Input/InputManager.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"
#include "TestUtils/UnitTest/BaseUnitTest.h"
#include "FileSystem/Directory.h"
#include "Input/Mouse.h"
#include "Lua/LuaState.h"
#include "Time/TimeUtils.h"
#include "Time/Clock.h"

#include <unordered_set>

using namespace Celeste;
using namespace Celeste::Input;
using namespace Celeste::Time;


namespace CelesteTestUtils
{
  //------------------------------------------------------------------------------------------------
  void CelesteUnitTest::celesteTestClassInitialize()
  {
    Celeste::Resources::getResourceManager().unloadAllResources();
  }

  //------------------------------------------------------------------------------------------------
  void CelesteUnitTest::celesteTestClassCleanup()
  {
    Celeste::Resources::getResourceManager().unloadAllResources();
  }

  //------------------------------------------------------------------------------------------------
  void CelesteUnitTest::resetState()
  {
    resetClock();
    resetMouse();
    resetKeyboard();
    resetLuaGlobals();
  }

  //------------------------------------------------------------------------------------------------
  void CelesteUnitTest::resetClock()
  {
    getClock().reset();
  }

  //------------------------------------------------------------------------------------------------
  void CelesteUnitTest::resetMouse()
  {
    getMouse().flush();
    getMouse().getTransform().setTranslation(glm::vec3());
  }

  //------------------------------------------------------------------------------------------------
  void CelesteUnitTest::resetKeyboard()
  {
    getKeyboard().flush();
  }

  //------------------------------------------------------------------------------------------------
  void CelesteUnitTest::resetLuaGlobals()
  {
    std::unordered_set<std::string> ignoredGlobals
    {
      "package",
      "require",
      "type",
      "rawlen",
      "pairs",
      "rawset",
      "load",
      "_G",
      "pcall",
      "base",
      "next",
      "dofile",
      "table",
      "math",
      "error",
      "rawget",
      "os",
      "setmetatable",
      "collectgarbage",
      "assert",
      "loadfile",
      "_VERSION",
      "tonumber",
      "xpcall",
      "ipairs",
      "select",
      "string",
      "getmetatable",
      "rawequal",
      "print",
      "tostring",
      "base",
      "coroutine",
    };

    sol::state& state = Lua::LuaState::instance();

    auto func = [&](sol::object key, sol::object value) -> void
    {
      state[key] = sol::nil;
    };

    state.for_each([&](std::pair<sol::object, sol::object> key_value_pair) -> void
    {
      // If the variable isn't one we have marked to ignore, we clear it from the global state
      if (!key_value_pair.first.is<std::string>() ||
          ignoredGlobals.find(key_value_pair.first.as<std::string>()) == ignoredGlobals.end())
      {
        func(key_value_pair.first, key_value_pair.second);
      }
    });

    state.collect_garbage();
  }
}