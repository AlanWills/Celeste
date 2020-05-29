#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Events/EventTriggerer.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "TestUtils/Utils/InputUtils.h"
#include "TestUtils/Assert/AssertCel.h"
#include "Time/TimeUtils.h"
#include "Time/Clock.h"

using namespace Celeste;
using namespace Celeste::Events;
using namespace Celeste::Time;


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

    getClock().update(0);

    Assert::AreEqual(0.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->setTriggerCondition([](const GameObject&) -> bool { return false; });
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_ConditionTrue_TriggersEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    getClock().update(0);

    Assert::AreEqual(0.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->setTriggerCondition([](const GameObject&) -> bool { return true; });
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_ConditionTrue_TriggerModeOnce_KillsComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kOnce);
    AssertCel::HasComponent<EventTriggerer>(gameObject);

    getClock().update(0);

    Assert::AreEqual(0.0f, getElapsedDeltaTime());

    eventTriggerer->setTriggerCondition([](const GameObject&) -> bool { return true; });
    eventTriggerer->update();

    AssertCel::DoesNotHaveComponent<EventTriggerer>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_ConditionTrue_TriggerModeContinuous_DoesNotKillComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerMode(Celeste::Events::TriggerMode::kUnlimited);

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kUnlimited);

    getClock().update(0);

    Assert::AreEqual(0.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->setTriggerCondition([](const GameObject&) -> bool { return true; });
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->update();

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);

    getClock().update(0);

    Assert::AreEqual(0.0f, getElapsedDeltaTime());

    called = false;
    eventTriggerer->update();

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

    getClock().update(1);

    Assert::AreEqual(1.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TotalTimePassedEqualToTriggerDelay_TriggersEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    getClock().update(2);

    Assert::AreEqual(2.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TotalTimePassedGreaterThanTriggerDelay_TriggersEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    getClock().update(4);

    Assert::AreEqual(4.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TotalTimePassedTriggerDelay_TriggerModeOnce_KillsComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kOnce);
    AssertCel::HasComponent<EventTriggerer>(gameObject);

    getClock().update(3);

    Assert::AreEqual(3.0f, getElapsedDeltaTime());

    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update();

    AssertCel::DoesNotHaveComponent<EventTriggerer>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TotalTimePassedTriggerDelay_TriggerModeContinuous_DoesNotKillComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerMode(Celeste::Events::TriggerMode::kUnlimited);

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kUnlimited);

    getClock().update(3);

    Assert::AreEqual(3.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerDelay(2);
    eventTriggerer->update();

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);

    getClock().update(3);

    Assert::AreEqual(3.0f, getElapsedDeltaTime());

    called = false;
    eventTriggerer->update();

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

    getClock().update(1);

    Assert::AreEqual(1.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerKey(GLFW_KEY_A);
    eventTriggerer->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TriggerKeyPressed_TriggersEvent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    getClock().update(2);

    Assert::AreEqual(2.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerKey(GLFW_KEY_A);
    simulateKeyTapped(GLFW_KEY_A);
    eventTriggerer->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TriggerKeyPressed_TriggerModeOnce_KillsComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kOnce);
    AssertCel::HasComponent<EventTriggerer>(gameObject);

    getClock().update(2);

    Assert::AreEqual(2.0f, getElapsedDeltaTime());

    eventTriggerer->setTriggerKey(GLFW_KEY_A);
    simulateKeyTapped(GLFW_KEY_A);
    eventTriggerer->update();

    AssertCel::DoesNotHaveComponent<EventTriggerer>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(EventTriggerer_Update_TriggerKeyPressed_TriggerModeContinuous_DoesNotKillComponent)
  {
    GameObject gameObject;
    observer_ptr<EventTriggerer> eventTriggerer = gameObject.addComponent<EventTriggerer>();
    eventTriggerer->setTriggerMode(Celeste::Events::TriggerMode::kUnlimited);

    Assert::IsTrue(eventTriggerer->getTriggerMode() == Celeste::Events::TriggerMode::kUnlimited);

    getClock().update(3);

    Assert::AreEqual(3.0f, getElapsedDeltaTime());

    bool called = false;
    auto f = [&called](const GameObject&) -> void { called = true; };
    eventTriggerer->getEvent().subscribe(f);
    eventTriggerer->setTriggerKey(GLFW_KEY_A);
    simulateKeyTapped(GLFW_KEY_A);
    eventTriggerer->update();

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);

    called = false;
    eventTriggerer->update();

    AssertCel::HasComponent<EventTriggerer>(gameObject);
    Assert::IsTrue(called);
  }

#pragma endregion

#pragma endregion

  };
}