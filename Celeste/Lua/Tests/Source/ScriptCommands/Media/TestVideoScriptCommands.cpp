#include "UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Media/VideoScriptCommands.h"
#include "Lua/LuaState.h"

using LuaState = Celeste::Lua::LuaState;


namespace TestCelesteLua
{
  namespace Lua
  {
    namespace ScriptCommands
    {
      CELESTE_TEST_CLASS(TestVideoScriptCommands)

#pragma region Initialize Tests

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(VideoScriptCommands_Initialize_AddsVideoTable_ToGlobalTable)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state["Video"].valid());

        Celeste::Lua::Media::VideoScriptCommands::initialize(state);

        Assert::IsTrue(state["Video"].valid());
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(VideoScriptCommands_Initialize_Adds_play_Function_ToVideoTable)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state["Video"]["play"].valid());

        Celeste::Lua::Media::VideoScriptCommands::initialize(state);

        Assert::IsTrue(state["Video"]["play"].valid());
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(VideoScriptCommands_Initialize_Adds_playAsync_Function_ToVideoTable)
      {
        sol::state& state = LuaState::instance();

        Assert::IsFalse(state["Video"]["playAsync"].valid());

        Celeste::Lua::Media::VideoScriptCommands::initialize(state);

        Assert::IsTrue(state["Video"]["playAsync"].valid());
      }

#pragma endregion

#pragma region Create Video Settings Tests

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(VideoScriptCommands_CreateVideoSettings_No_AUTO_EXIT_SETTING_KEY_InTable_SetsAutoExitToTrue)
      {
        sol::table table = LuaState::instance().create_table();

        Assert::IsTrue(sol::nil == table.get_or(Celeste::Lua::Media::VideoScriptCommands::AUTO_EXIT_SETTING_KEY, sol::nil));

        auto settings = Celeste::Lua::Media::VideoScriptCommands::createVideoSettings(table);

        Assert::IsTrue(settings.m_autoExit);
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(VideoScriptCommands_CreateVideoSettings_With_AUTO_EXIT_SETTING_KEY_InTable_SetsAutoExitToCorrectValue)
      {
        sol::table table = LuaState::instance().create_table();
        table[Celeste::Lua::Media::VideoScriptCommands::AUTO_EXIT_SETTING_KEY] = false;

        Assert::AreEqual(false, table.get_or(Celeste::Lua::Media::VideoScriptCommands::AUTO_EXIT_SETTING_KEY, true));

        auto settings = Celeste::Lua::Media::VideoScriptCommands::createVideoSettings(table);

        Assert::IsFalse(settings.m_autoExit);
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(VideoScriptCommands_CreateVideoSettings_No_VOLUME_SETTING_KEY_InTable_SetsVolumeToOne)
      {
        sol::table table = LuaState::instance().create_table();

        Assert::IsTrue(sol::nil == table.get_or(Celeste::Lua::Media::VideoScriptCommands::VOLUME_SETTING_KEY, sol::nil));

        auto settings = Celeste::Lua::Media::VideoScriptCommands::createVideoSettings(table);

        Assert::AreEqual(1.0f, settings.m_volume);
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(VideoScriptCommands_CreateVideoSettings_With_VOLUME_SETTING_KEY_InTable_SetsAutoExitToCorrectValue)
      {
        sol::table table = LuaState::instance().create_table();
        table[Celeste::Lua::Media::VideoScriptCommands::VOLUME_SETTING_KEY] = 0.25f;

        Assert::AreEqual(0.25f, table.get_or<sol::object>(Celeste::Lua::Media::VideoScriptCommands::VOLUME_SETTING_KEY, sol::nil).as<float>());

        auto settings = Celeste::Lua::Media::VideoScriptCommands::createVideoSettings(table);

        Assert::AreEqual(0.25f, settings.m_volume);
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(VideoScriptCommands_CreateVideoSettings_No_ON_VIDEO_COMPLETE_SETTING_KEY_InTable_SetsOnVideoCompleteCallbackToNullptr)
      {
        sol::table table = LuaState::instance().create_table();

        Assert::IsTrue(sol::nil == table.get_or(Celeste::Lua::Media::VideoScriptCommands::ON_VIDEO_COMPLETE_SETTING_KEY, sol::nil));

        auto settings = Celeste::Lua::Media::VideoScriptCommands::createVideoSettings(table);

        Assert::IsFalse(static_cast<bool>(settings.m_videoCompleteCallback));
      }

      //------------------------------------------------------------------------------------------------
      TEST_METHOD(VideoScriptCommands_CreateVideoSettings_With_ON_VIDEO_COMPLETE_SETTING_KEY_InTable_SetsOnVideoCompleteCallbackToFunction)
      {
        sol::table table = LuaState::instance().create_table();
        table[Celeste::Lua::Media::VideoScriptCommands::ON_VIDEO_COMPLETE_SETTING_KEY] = []() -> void {};

        Assert::IsTrue(table.get_or<sol::object>(Celeste::Lua::Media::VideoScriptCommands::ON_VIDEO_COMPLETE_SETTING_KEY, sol::nil).valid());

        auto settings = Celeste::Lua::Media::VideoScriptCommands::createVideoSettings(table);

        Assert::IsTrue(static_cast<bool>(settings.m_videoCompleteCallback));
      }

#pragma endregion

      };
    }
  }
}