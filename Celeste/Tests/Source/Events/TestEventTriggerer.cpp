#include "UtilityHeaders/UnitTestHeaders.h"

#include "Events/EventTriggerer.h"
#include "Registries/ComponentRegistry.h"
#include "Registries/ComponentRegistry.h"
#include "Objects/GameObject.h"
#include "Utils/InputUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Events;


namespace TestCeleste::Events
{
  CELESTE_TEST_CLASS(TestEventTriggerer)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<EventTriggerer>());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Constructor_SetsTriggerModeTo_kOnce)
  {
    GameObject gameObject;
    EventTriggerer eventTriggerer(gameObject);

    Assert::IsTrue(Celeste::Events::TriggerMode::kOnce == eventTriggerer.getTriggerMode());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Constructor_SetsTriggerDelayTo_FLT_MAX)
  {
    GameObject gameObject;
    EventTriggerer eventTriggerer(gameObject);

    Assert::AreEqual(FLT_MAX, eventTriggerer.getTriggerDelay());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Constructor_SetsTriggerKeyTo_GLFW_KEY_UNKNOWN)
  {
    GameObject gameObject;
    EventTriggerer eventTriggerer(gameObject);

    Assert::AreEqual(GLFW_KEY_UNKNOWN, eventTriggerer.getTriggerKey());
  }

#pragma endregion

#pragma region Update Tests

#pragma region Condition

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_ConditionFalse_DoesNotTriggerEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->setTriggerCondition([](const GameObject&) -> bool { return false; });
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->update(0);

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_ConditionTrue_TriggersEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->setTriggerCondition([](const GameObject&) -> bool { return true; });
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->update(0);

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_ConditionTrue_TriggerModeOnce_KillsComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kOnce);
    AssertCel::HasComponent<EventTriggerer>(gameObject);

    eventTriggerer->setTriggerCondition([](const GameObject&) -> bool { return true; });
    eventTriggerer->update(0);

    AssertCel::DoesNotHaveComponent<EventTriggerer>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_ConditionTrue_TriggerModeContinuous_DoesNotKillComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerMode(Celeste::Events::TriggerMode::kUnlimited);

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kUnlimited);

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->setTriggerCondition([](const GameObject&) -> bool { return true; });
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->update(0);

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);

    called = false;
    eventTriggerer->update(0);

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);
  }

#pragma endregion

#pragma region Trigger Delay

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TotalTimePassedLessThanTriggerDelay_DoesNotTriggerEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update(1);

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TotalTimePassedEqualToTriggerDelay_TriggersEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update(2);

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TotalTimePassedGreaterThanTriggerDelay_TriggersEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update(4);

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TotalTimePassedTriggerDelay_TriggerModeOnce_KillsComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kOnce);
    AssertCel::HasComponent<EventTriggerer>(gameObject);

    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update(3);

    AssertCel::DoesNotHaveComponent<EventTriggerer>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TotalTimePassedTriggerDelay_TriggerModeContinuous_DoesNotKillComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerMode(Celeste::Events::TriggerMode::kUnlimited);

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kUnlimited);

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update(3);

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);

    called = false;
    eventTriggerer->update(3);

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);
  }

#pragma endregion

#pragma region Trigger Key

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TriggerKeyNotPressed_DoesNotTriggerEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerKey(GLFW_KEY_A);
    eventTriggerer->update(1);

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TriggerKeyPressed_TriggersEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerKey(GLFW_KEY_A);
    simulateKeyTapped(GLFW_KEY_A);
    eventTriggerer->update(2);

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TriggerKeyPressed_TriggerModeOnce_KillsComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kOnce);
    AssertCel::HasComponent<EventTriggerer>(gameObject);

    eventTriggerer->setTriggerKey(GLFW_KEY_A);
    simulateKeyTapped(GLFW_KEY_A);
    eventTriggerer->update(2);

    AssertCel::DoesNotHaveComponent<EventTriggerer>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TriggerKeyPressed_TriggerModeContinuous_DoesNotKillComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerMode(Celeste::Events::TriggerMode::kUnlimited);

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kUnlimited);

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerKey(GLFW_KEY_A);
    simulateKeyTapped(GLFW_KEY_A);
    eventTriggerer->update(3);

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);

    called = false;
    eventTriggerer->update(3);

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);
  }

#pragma endregion

#pragma endregion

  };
}