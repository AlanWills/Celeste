#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "ScriptCommands/Input/KeyScriptCommands.h"
#include "Lua/LuaState.h"
#include "GLFW/glfw3.h"

using LuaState = Celeste::Lua::LuaState;
using namespace Celeste;


namespace TestCeleste::Lua::ScriptCommands
{
  CELESTE_TEST_CLASS(TestKeyScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsMouseTable_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_Adds_isNumber_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["isNumber"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["isNumber"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_Adds_getNumber_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["getNumber"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["getNumber"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsSpace_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Space"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Space"].valid());
    Assert::AreEqual(GLFW_KEY_SPACE, state["Key"]["Space"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsApostrophe_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Apostrophe"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Apostrophe"].valid());
    Assert::AreEqual(GLFW_KEY_APOSTROPHE, state["Key"]["Apostrophe"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsComma_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Comma"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Comma"].valid());
    Assert::AreEqual(GLFW_KEY_COMMA, state["Key"]["Comma"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsMinus_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Minus"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Minus"].valid());
    Assert::AreEqual(GLFW_KEY_MINUS, state["Key"]["Minus"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsPeriod_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Period"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Period"].valid());
    Assert::AreEqual(GLFW_KEY_PERIOD, state["Key"]["Period"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsForwardSlash_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["ForwardSlash"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["ForwardSlash"].valid());
    Assert::AreEqual(GLFW_KEY_SLASH, state["Key"]["ForwardSlash"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsSemiColon_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["SemiColon"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["SemiColon"].valid());
    Assert::AreEqual(GLFW_KEY_SEMICOLON, state["Key"]["SemiColon"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsEquals_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Equals"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Equals"].valid());
    Assert::AreEqual(GLFW_KEY_EQUAL, state["Key"]["Equals"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsLeftBracket_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["LeftBracket"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["LeftBracket"].valid());
    Assert::AreEqual(GLFW_KEY_LEFT_BRACKET, state["Key"]["LeftBracket"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsBackslash_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["BackSlash"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Backslash"].valid());
    Assert::AreEqual(GLFW_KEY_BACKSLASH, state["Key"]["Backslash"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsRightBracket_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["RightBracket"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["RightBracket"].valid());
    Assert::AreEqual(GLFW_KEY_RIGHT_BRACKET, state["Key"]["RightBracket"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsGraveAccent_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["GraveAccent"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["GraveAccent"].valid());
    Assert::AreEqual(GLFW_KEY_GRAVE_ACCENT, state["Key"]["GraveAccent"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum0_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num0"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num0"].valid());
    Assert::AreEqual(GLFW_KEY_0, state["Key"]["Num0"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum1_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num1"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num1"].valid());
    Assert::AreEqual(GLFW_KEY_1, state["Key"]["Num1"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum2_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num2"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num2"].valid());
    Assert::AreEqual(GLFW_KEY_2, state["Key"]["Num2"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum3_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num3"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num3"].valid());
    Assert::AreEqual(GLFW_KEY_3, state["Key"]["Num3"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum4_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num4"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num4"].valid());
    Assert::AreEqual(GLFW_KEY_4, state["Key"]["Num4"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum5_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num5"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num5"].valid());
    Assert::AreEqual(GLFW_KEY_5, state["Key"]["Num5"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum6_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num6"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num6"].valid());
    Assert::AreEqual(GLFW_KEY_6, state["Key"]["Num6"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum7_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num7"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num7"].valid());
    Assert::AreEqual(GLFW_KEY_7, state["Key"]["Num7"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum8_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num8"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num8"].valid());
    Assert::AreEqual(GLFW_KEY_8, state["Key"]["Num8"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNum9_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Num9"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Num9"].valid());
    Assert::AreEqual(GLFW_KEY_9, state["Key"]["Num9"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsA_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["A"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["A"].valid());
    Assert::AreEqual(GLFW_KEY_A, state["Key"]["A"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsB_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["B"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["B"].valid());
    Assert::AreEqual(GLFW_KEY_B, state["Key"]["B"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsC_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["C"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["C"].valid());
    Assert::AreEqual(GLFW_KEY_C, state["Key"]["C"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsD_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["D"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["D"].valid());
    Assert::AreEqual(GLFW_KEY_D, state["Key"]["D"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsE_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["E"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["E"].valid());
    Assert::AreEqual(GLFW_KEY_E, state["Key"]["E"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F"].valid());
    Assert::AreEqual(GLFW_KEY_F, state["Key"]["F"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsG_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["G"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["G"].valid());
    Assert::AreEqual(GLFW_KEY_G, state["Key"]["G"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsH_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["H"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["H"].valid());
    Assert::AreEqual(GLFW_KEY_H, state["Key"]["H"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsI_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["I"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["I"].valid());
    Assert::AreEqual(GLFW_KEY_I, state["Key"]["I"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsJ_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["J"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["J"].valid());
    Assert::AreEqual(GLFW_KEY_J, state["Key"]["J"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsK_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["K"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["K"].valid());
    Assert::AreEqual(GLFW_KEY_K, state["Key"]["K"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsL_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["L"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["L"].valid());
    Assert::AreEqual(GLFW_KEY_L, state["Key"]["L"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsM_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["M"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["M"].valid());
    Assert::AreEqual(GLFW_KEY_M, state["Key"]["M"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsN_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["N"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["N"].valid());
    Assert::AreEqual(GLFW_KEY_N, state["Key"]["N"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsO_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["O"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["O"].valid());
    Assert::AreEqual(GLFW_KEY_O, state["Key"]["O"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsP_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["P"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["P"].valid());
    Assert::AreEqual(GLFW_KEY_P, state["Key"]["P"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsQ_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Q"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Q"].valid());
    Assert::AreEqual(GLFW_KEY_Q, state["Key"]["Q"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsR_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["R"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["R"].valid());
    Assert::AreEqual(GLFW_KEY_R, state["Key"]["R"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsS_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["S"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["S"].valid());
    Assert::AreEqual(GLFW_KEY_S, state["Key"]["S"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsT_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["T"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["T"].valid());
    Assert::AreEqual(GLFW_KEY_T, state["Key"]["T"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsU_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["U"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["U"].valid());
    Assert::AreEqual(GLFW_KEY_U, state["Key"]["U"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsV_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["V"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["V"].valid());
    Assert::AreEqual(GLFW_KEY_V, state["Key"]["V"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsW_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["W"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["W"].valid());
    Assert::AreEqual(GLFW_KEY_W, state["Key"]["W"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsX_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["X"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["X"].valid());
    Assert::AreEqual(GLFW_KEY_X, state["Key"]["X"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsY_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Y"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Y"].valid());
    Assert::AreEqual(GLFW_KEY_Y, state["Key"]["Y"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsZ_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Z"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Z"].valid());
    Assert::AreEqual(GLFW_KEY_Z, state["Key"]["Z"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsEscape_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Escape"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Escape"].valid());
    Assert::AreEqual(GLFW_KEY_ESCAPE, state["Key"]["Escape"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsEnter_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Enter"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Enter"].valid());
    Assert::AreEqual(GLFW_KEY_ENTER, state["Key"]["Enter"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsTab_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Tab"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Tab"].valid());
    Assert::AreEqual(GLFW_KEY_TAB, state["Key"]["Tab"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsBackspace_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Backspace"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Backspace"].valid());
    Assert::AreEqual(GLFW_KEY_BACKSPACE, state["Key"]["Backspace"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsInsert_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Insert"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Insert"].valid());
    Assert::AreEqual(GLFW_KEY_INSERT, state["Key"]["Insert"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsDelete_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Delete"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Delete"].valid());
    Assert::AreEqual(GLFW_KEY_DELETE, state["Key"]["Delete"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsRight_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Right"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Right"].valid());
    Assert::AreEqual(GLFW_KEY_RIGHT, state["Key"]["Right"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsLeft_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Left"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Left"].valid());
    Assert::AreEqual(GLFW_KEY_LEFT, state["Key"]["Left"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsDown_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Down"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Down"].valid());
    Assert::AreEqual(GLFW_KEY_DOWN, state["Key"]["Down"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsUp_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Up"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Up"].valid());
    Assert::AreEqual(GLFW_KEY_UP, state["Key"]["Up"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsPageUp_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["PageUp"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["PageUp"].valid());
    Assert::AreEqual(GLFW_KEY_PAGE_UP, state["Key"]["PageUp"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsPageDown_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["PageDown"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["PageDown"].valid());
    Assert::AreEqual(GLFW_KEY_PAGE_DOWN, state["Key"]["PageDown"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsHome_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Home"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Home"].valid());
    Assert::AreEqual(GLFW_KEY_HOME, state["Key"]["Home"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsEnd_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["End"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["End"].valid());
    Assert::AreEqual(GLFW_KEY_END, state["Key"]["End"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsCapsLock_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["CapsLock"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["CapsLock"].valid());
    Assert::AreEqual(GLFW_KEY_CAPS_LOCK, state["Key"]["CapsLock"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsScrollLock_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["ScrollLock"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["ScrollLock"].valid());
    Assert::AreEqual(GLFW_KEY_SCROLL_LOCK, state["Key"]["ScrollLock"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsNumLock_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["NumLock"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["NumLock"].valid());
    Assert::AreEqual(GLFW_KEY_NUM_LOCK, state["Key"]["NumLock"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsPrintScreen_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["PrintScreen"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["PrintScreen"].valid());
    Assert::AreEqual(GLFW_KEY_PRINT_SCREEN, state["Key"]["PrintScreen"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsPause_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["Pause"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["Pause"].valid());
    Assert::AreEqual(GLFW_KEY_PAUSE, state["Key"]["Pause"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF1_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F1"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F1"].valid());
    Assert::AreEqual(GLFW_KEY_F1, state["Key"]["F1"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF2_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F2"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F2"].valid());
    Assert::AreEqual(GLFW_KEY_F2, state["Key"]["F2"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF3_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F3"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F3"].valid());
    Assert::AreEqual(GLFW_KEY_F3, state["Key"]["F3"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF4_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F4"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F4"].valid());
    Assert::AreEqual(GLFW_KEY_F4, state["Key"]["F4"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF5_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F5"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F5"].valid());
    Assert::AreEqual(GLFW_KEY_F5, state["Key"]["F5"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF6_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F6"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F6"].valid());
    Assert::AreEqual(GLFW_KEY_F6, state["Key"]["F6"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF7_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F7"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F7"].valid());
    Assert::AreEqual(GLFW_KEY_F7, state["Key"]["F7"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF8_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F8"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F8"].valid());
    Assert::AreEqual(GLFW_KEY_F8, state["Key"]["F8"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF9_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F9"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F9"].valid());
    Assert::AreEqual(GLFW_KEY_F9, state["Key"]["F9"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF10_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F10"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F10"].valid());
    Assert::AreEqual(GLFW_KEY_F10, state["Key"]["F10"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF11_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F11"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F11"].valid());
    Assert::AreEqual(GLFW_KEY_F11, state["Key"]["F11"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsF12_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["F12"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["F12"].valid());
    Assert::AreEqual(GLFW_KEY_F12, state["Key"]["F12"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsLeftShift_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["LeftShift"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["LeftShift"].valid());
    Assert::AreEqual(GLFW_KEY_LEFT_SHIFT, state["Key"]["LeftShift"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsLeftControl_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["LeftControl"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["LeftControl"].valid());
    Assert::AreEqual(GLFW_KEY_LEFT_CONTROL, state["Key"]["LeftControl"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsLeftAlt_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["LeftAlt"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["LeftAlt"].valid());
    Assert::AreEqual(GLFW_KEY_LEFT_ALT, state["Key"]["LeftAlt"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsRightShift_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["RightShift"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["RightShift"].valid());
    Assert::AreEqual(GLFW_KEY_RIGHT_SHIFT, state["Key"]["RightShift"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsRightcontrol_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["RightControl"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["RightControl"].valid());
    Assert::AreEqual(GLFW_KEY_RIGHT_CONTROL, state["Key"]["RightControl"].get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_Initialize_AddsRightAlt_ToKeyTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state["Key"]["RightAlt"].valid());

    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    Assert::IsTrue(state["Key"]["RightAlt"].valid());
    Assert::AreEqual(GLFW_KEY_RIGHT_ALT, state["Key"]["RightAlt"].get<int>());
  }

#pragma endregion

#pragma region Is Number Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_isNumber_InputtingInvalidNumberKey_ReturnsFalse)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    auto result = state["Key"]["isNumber"].get<sol::protected_function>().call(GLFW_KEY_A);

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());

    result = state["Key"]["isNumber"].get<sol::protected_function>().call(GLFW_KEY_ESCAPE);

    Assert::IsTrue(result.valid());
    Assert::IsFalse(result.get<bool>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_isNumber_InputtingValidNumberKey_ReturnsTrue)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    for (size_t i = 0; i < 10; ++i)
    {
      auto result = state["Key"]["isNumber"].get<sol::protected_function>().call(static_cast<int>(GLFW_KEY_0 + i));

      Assert::IsTrue(result.valid());
      Assert::IsTrue(result.get<bool>());
    }
  }

#pragma endregion

#pragma region Get Number Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_getNumber_InputtingInvalidNumberKey_ReturnsMinusOne)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    auto result = state["Key"]["getNumber"].get<sol::protected_function>().call(GLFW_KEY_A);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(-1, result.get<int>());

    result = state["Key"]["getNumber"].get<sol::protected_function>().call(GLFW_KEY_ESCAPE);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(-1, result.get<int>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyScriptCommands_isNumber_InputtingValidNumberKey_ReturnsCorrectNumber)
  {
    sol::state& state = LuaState::instance();
    Celeste::Lua::Input::KeyScriptCommands::initialize(state);

    for (size_t i = 0; i < 10; ++i)
    {
      auto result = state["Key"]["getNumber"].get<sol::protected_function>().call(static_cast<int>(GLFW_KEY_0 + i));

      Assert::IsTrue(result.valid());
      Assert::AreEqual(static_cast<int>(i), result.get<int>());
    }
  }

#pragma endregion

  };
}