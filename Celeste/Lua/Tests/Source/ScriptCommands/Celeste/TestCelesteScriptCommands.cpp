#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Celeste/CelesteScriptCommands.h"
#include "ScriptCommands/CelesteScriptCommandsConfig.h"
#include "Lua/LuaState.h"

#include "Resources/ResourceUtils.h"

using LuaState = Celeste::Lua::LuaState;

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestCelesteScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(CelesteScriptCommands_Initialize_AppendsScriptsFolder_ToLuaPackagePath)
  {
    sol::state& state = LuaState::instance();
    std::string oldPath = state["package"]["path"].get_or<std::string>("");

    Celeste::Lua::CelesteScriptCommands::initialize(state);

    std::string newPath = state["package"]["path"].get_or<std::string>("");
    std::string expectedAddition = ";" + Path(LUA_SCRIPTS_DIRECTORY, "?.lua").as_string();

    Assert::AreEqual(expectedAddition.size(), newPath.size() - oldPath.size());
    Assert::AreEqual(expectedAddition, newPath.substr(oldPath.size()));
  }

#pragma endregion

  };
}