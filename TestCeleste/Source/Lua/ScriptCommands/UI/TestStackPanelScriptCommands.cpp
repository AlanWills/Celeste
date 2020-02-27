#include "UtilityHeaders/UnitTestHeaders.h"

#include "Lua/ScriptCommands/Objects/GameObjectScriptCommands.h"
#include "Lua/ScriptCommands/UI/StackPanelScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "UI/StackPanel.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "AssertCel.h"

using LuaState = Celeste::Lua::LuaState;
using StackPanel = Celeste::UI::StackPanel;

using namespace Celeste;


namespace TestCeleste::Lua::UI::StackPanelScriptCommands
{
  CELESTE_TEST_CLASS(TestStackPanelScriptCommands)

#pragma region Initialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_Initialize_Adds_StackPanelUserType_ToGlobalTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[StackPanel::type_name()].valid());

    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::IsTrue(state[StackPanel::type_name()].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_Initialize_Adds_allocate_ToStackPanelTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[StackPanel::type_name()]["allocate"].valid());

    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::IsTrue(state[StackPanel::type_name()]["allocate"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_Initialize_Adds_addChild_ToStackPanelTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[StackPanel::type_name()]["addChild"].valid());

    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::IsTrue(state[StackPanel::type_name()]["addChild"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_Initialize_Adds_removeChild_ToStackPanelTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[StackPanel::type_name()]["removeChild"].valid());

    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::IsTrue(state[StackPanel::type_name()]["removeChild"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_Initialize_Adds_layout_ToStackPanelTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state[StackPanel::type_name()]["layout"].valid());

    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::IsTrue(state[StackPanel::type_name()]["layout"].valid());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_Initialize_Adds_as_ToStackPanelTable)
  {
    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["StackPanel"]["as"].valid());

    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::IsTrue(state.globals()["StackPanel"]["as"].valid());
  }

#pragma endregion

#pragma region Add Child Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_addChild_InputtingGameObjectWithoutRenderer_DoesNotAddChild)
  {
    GameObject gameObject;
    GameObject child;

    AutoDeallocator<StackPanel> stackPanel = gameObject.addComponent<StackPanel>();

    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());
    AssertCel::DoesNotHaveComponent<Rendering::Renderer>(child);

    auto result = state[StackPanel::type_name()]["addChild"].get<sol::protected_function>().call(*stackPanel, child);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_addChild_InputtingGameObjectWithRenderer_AddsChild)
  {
    GameObject gameObject, child;
    AutoDeallocator<StackPanel> stackPanel = gameObject.addComponent<StackPanel>();
    AutoDeallocator<MockRenderer> renderer = child.addComponent<MockRenderer>();

    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());
    AssertCel::HasComponent<Rendering::Renderer>(child);

    auto result = state[StackPanel::type_name()]["addChild"].get<sol::protected_function>().call(*stackPanel, child);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), stackPanel->childCount());
  }

#pragma endregion

#pragma region Remove Child Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_removeChild_InputtingGameObjectNotInStackPanel_DoesNothing)
  {
    GameObject gameObject, child, child2;
    AutoDeallocator<StackPanel> stackPanel = gameObject.addComponent<StackPanel>();
    AutoDeallocator<MockRenderer> renderer = child.addComponent<MockRenderer>();
    stackPanel->addChildren(child);

    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(1), stackPanel->childCount());

    auto result = state[StackPanel::type_name()]["removeChild"].get<sol::protected_function>().call(*stackPanel.get(), child2);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(1), stackPanel->childCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_removeChild_InputtingGameObjectInStackPanel_RemovesChild)
  {
    GameObject gameObject, child;
    AutoDeallocator<StackPanel> stackPanel = gameObject.addComponent<StackPanel>();
    AutoDeallocator<MockRenderer> renderer = child.addComponent<MockRenderer>();
    stackPanel->addChildren(child);

    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(1), stackPanel->childCount());

    auto result = state[StackPanel::type_name()]["removeChild"].get<sol::protected_function>().call(*stackPanel.get(), child);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_removeChild_InputtingGameObjectInStackPanel_PerformsLayout)
  {
    GameObject gameObject;
    GameObject child;
    GameObject child2;

    AutoDeallocator<StackPanel> stackPanel = gameObject.addComponent<StackPanel>();
    AutoDeallocator<MockRenderer> renderer = child.addComponent<MockRenderer>();
    AutoDeallocator<MockRenderer> renderer2 = child2.addComponent<MockRenderer>();
    stackPanel->addChildren(child, child2);

    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    Assert::AreEqual(static_cast<size_t>(2), stackPanel->childCount());
    Assert::AreNotEqual(glm::vec3(), child2.getTransform()->getTranslation());

    auto result = state[StackPanel::type_name()]["removeChild"].get<sol::protected_function>().call(*stackPanel.get(), child);

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec3(), child2.getTransform()->getTranslation());
  }

#pragma endregion

#pragma region Layout Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_layout_CorrectlyPositionsChildObjects)
  {
    GameObject gameObject;
    GameObject child;
    AutoDeallocator<StackPanel> stackPanel = gameObject.addComponent<StackPanel>();
    AutoDeallocator<MockRenderer> renderer = child.addComponent<MockRenderer>();
    renderer->setDimensions(glm::vec2(100, 200));
    stackPanel->addChildren(child);
    stackPanel->setOrientation(Celeste::UI::Orientation::kVertical);
    child.getTransform()->setTranslation(0, 100);

    Assert::AreEqual(glm::vec3(0, 100, 0), child.getTransform()->getTranslation());

    sol::state& state = LuaState::instance();
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    auto result = state[StackPanel::type_name()]["layout"].get<sol::protected_function>().call(*stackPanel.get());

    Assert::IsTrue(result.valid());
    Assert::AreEqual(glm::vec3(), child.getTransform()->getTranslation());
  }

#pragma endregion

#pragma region StackPanel As Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanel_as_InputtingNull_CastingToBaseType_ReturnsNil)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(nullptr, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanel_as_InputtingNull_CastingToStackPanelType_ReturnsNil)
  {
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(nullptr, "StackPanel");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanel_as_InputtingNull_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockStackPanel : public Celeste::UI::StackPanel {};
    state.new_usertype<MockStackPanel>("MockStackPanel");

    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(nullptr, "MockStackPanel");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanel_as_InputtingNull_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(nullptr, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanelHandle_as_InputtingNullStackPanelHandle_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanel_as_InputtingNonNullStackPanel_CastingToBaseType_ReturnsCorrectPtr)
  {
    Celeste::Lua::registerUserType<Object>("Object");
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsTrue(state["Object"].valid());

    StackPanel stackPanel;
    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(&stackPanel, "Object");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&stackPanel == functionResult.get<Object*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanel_as_InputtingNonNullStackPanel_CastingToStackPanelType_ReturnsCorrectPtr)
  {
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    StackPanel stackPanel;
    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(&stackPanel, "StackPanel");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(&stackPanel == functionResult.get<StackPanel*>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanel_as_InputtingNonNullStackPanel_CastingToDerivedType_ReturnsNil)
  {
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class MockStackPanel : public Celeste::UI::StackPanel {};
    state.new_usertype<MockStackPanel>("MockStackPanel");

    StackPanel stackPanel;
    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(&stackPanel, "MockStackPanel");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanel_as_InputtingNonNullStackPanel_CastingToUnrelatedType_ReturnsNil)
  {
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    class UnrelatedType : public Celeste::Object {};
    Celeste::Lua::registerUserType<UnrelatedType>("UnrelatedType");

    Assert::IsTrue(state.globals()["UnrelatedType"]);

    StackPanel stackPanel;
    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(&stackPanel, "UnrelatedType");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanelScriptCommands_StackPanel_as_InputtingNonNullStackPanel_CastingToNonExistentType_ReturnsNil)
  {
    Celeste::Lua::UI::StackPanelScriptCommands::initialize();

    sol::state& state = LuaState::instance();

    Assert::IsFalse(state.globals()["WubbaLubbaDubDubHandle"]);

    auto functionResult = state.globals()["StackPanel"]["as"].get<sol::protected_function>().call(nullptr, "WubbaLubbaDubDub");

    Assert::IsTrue(functionResult.valid());
    Assert::IsTrue(sol::type::nil == functionResult.get_type());
  }

#pragma endregion

  };
}