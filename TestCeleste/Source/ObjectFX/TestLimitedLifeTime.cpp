#include "UtilityHeaders/UnitTestHeaders.h"

#include "ObjectFX/LimitedLifeTime.h"
#include "Objects/GameObject.h"
#include "Utils/InputUtils.h"
#include "Input/InputUtils.h"
#include "Input/Keyboard.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestLimitedLifeTime)

#pragma region Registration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_IsRegisteredWithComponentRegistry)
    {
      Assert::IsTrue(ComponentRegistry::hasComponent<LimitedLifeTime>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_IsAllocatableFromComponentRegistry)
    {
      GameObject gameObject;

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(LimitedLifeTime::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<LimitedLifeTime*>(component.get()));
      Assert::AreEqual(&gameObject, component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_Constructor_SetsLifeTimeToZero)
    {
      LimitedLifeTime lifeTime;

      Assert::AreEqual(0.0f, lifeTime.getLifeTime());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_Constructor_SetsCurrentTimeAliveToZero)
    {
      LimitedLifeTime lifeTime;

      Assert::AreEqual(0.0f, lifeTime.getCurrentTimeAlive());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_Constructor_SetsTriggerKeyToDefault)
    {
      LimitedLifeTime lifeTime;

      Assert::AreEqual(-1, lifeTime.getTriggerKey());
    }

#pragma endregion

#pragma region Subscribe To On Death Event Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_SubscribeToOnDeathEvent_SingleCallback_SubscribesCallback)
    {
      LimitedLifeTime lifeTime;

      bool called = false;
      lifeTime.subscribeOnDeathCallback([&called](GameObject&) -> void { called = true; });

      Assert::IsFalse(called);

      lifeTime.getOnDeathEvent().invoke(GameObject());

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_SubscribeToOnDeathEvent_MultipleCallbacks_SubscribesCallback)
    {
      LimitedLifeTime lifeTime;

      bool called = false;
      bool called2 = false;
      lifeTime.subscribeOnDeathCallback(
        [&called](GameObject&) -> void { called = true; },
        [&called2](GameObject&) -> void { called2 = true; });

      Assert::IsFalse(called);
      Assert::IsFalse(called2);

      lifeTime.getOnDeathEvent().invoke(GameObject());

      Assert::IsTrue(called);
      Assert::IsTrue(called2);
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_Update_UpdatesCurrentTimeAlive)
    {
      LimitedLifeTime lifeTime;
      lifeTime.setLifeTime(2);
      lifeTime.update(0.1f);

      Assert::AreEqual(0.1f, lifeTime.getCurrentTimeAlive());

      lifeTime.update(0.2f);

      Assert::AreEqual(0.3f, lifeTime.getCurrentTimeAlive());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_Update_LifeTimeReached_TriggersOnDeathEvent)
    {
      GameObject gameObject;
      AutoDeallocator<LimitedLifeTime> lifeTime = gameObject.addComponent<LimitedLifeTime>();
      lifeTime->setLifeTime(2);

      bool called = false;
      lifeTime->subscribeOnDeathCallback([&called](GameObject&) -> void { called = true; });

      Assert::IsFalse(called);

      lifeTime->update(3);

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_Update_DeallocatesGameObject_IfCurrentTimeEqualToLifeTime)
    {
      Assert::Fail();

      GameObject gameObject;
      AutoDeallocator<LimitedLifeTime> lifeTime = gameObject.addComponent<LimitedLifeTime>();
      lifeTime->setLifeTime(2);

      //AssertCel::IsAlive(gameObject);

      lifeTime->update(2);

      //AssertCel::IsNotAlive(gameObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_Update_DeallocatesGameObject_IfCurrentTimeGreaterThanLifeTime)
    {
      Assert::Fail();

      GameObject gameObject;
      AutoDeallocator<LimitedLifeTime> lifeTime = gameObject.addComponent<LimitedLifeTime>();
      lifeTime->setLifeTime(2);

      //AssertCel::IsAlive(gameObject);

      lifeTime->update(3);

      //AssertCel::IsNotAlive(gameObject);
    }

#pragma endregion

#pragma region Destructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_Destructor_UnsubscribesFromKeyboardKeyReleasedEvent)
    {
      {
        GameObject gameObject;
        AutoDeallocator<LimitedLifeTime> lifeTime = gameObject.addComponent<LimitedLifeTime>();
        lifeTime->setTriggerKey(GLFW_KEY_A);

        Assert::AreEqual(static_cast<size_t>(1), Celeste::Input::getKeyboard().getKeyReleasedEvent().getSubscriberCount());
      }
    
      Assert::AreEqual(static_cast<size_t>(0), Celeste::Input::getKeyboard().getKeyReleasedEvent().getSubscriberCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_Destructor_TriggersOnDeathEvent)
    {
      bool called = false;
      GameObject gameObject;

      {
        AutoDeallocator<LimitedLifeTime> lifeTime = gameObject.addComponent<LimitedLifeTime>();
        lifeTime->setLifeTime(2);

        lifeTime->subscribeOnDeathCallback([&called, &gameObject](GameObject& caller) -> void
          {
            called = (&caller == &gameObject);
          });

        Assert::IsFalse(called);
      }

      Assert::IsTrue(called);
    }

#pragma endregion

#pragma region On Key Released Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_OnKeyReleased_TriggerKeyNotSet_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<LimitedLifeTime> lifeTime = gameObject.addComponent<LimitedLifeTime>();

      Assert::AreEqual(-1, lifeTime->getTriggerKey());

      bool called = false;
      lifeTime->getOnDeathEvent().subscribe([&called](GameObject&) -> void
      {
        called = true;
      });

      simulateKeyReleased(GLFW_KEY_A);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_OnKeyReleased_TriggerKeyDifferentToKeyReleased_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<LimitedLifeTime> lifeTime = gameObject.addComponent<LimitedLifeTime>();
      lifeTime->setTriggerKey(GLFW_KEY_B);

      Assert::AreEqual(GLFW_KEY_B, lifeTime->getTriggerKey());

      bool called = false;
      lifeTime->getOnDeathEvent().subscribe([&called](GameObject&) -> void
      {
        called = true;
      });

      simulateKeyReleased(GLFW_KEY_A);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_OnKeyReleased_TriggerKeySameAsKeyPressed_ButNotActive_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<LimitedLifeTime> lifeTime = gameObject.addComponent<LimitedLifeTime>();
      lifeTime->setActive(false);
      lifeTime->setTriggerKey(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, lifeTime->getTriggerKey());
      AssertCel::IsNotActive(*lifeTime);

      bool called = false;
      lifeTime->getOnDeathEvent().subscribe([&called](GameObject&) -> void
      {
        called = true;
      });

      simulateKeyReleased(GLFW_KEY_A);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_OnKeyReleased_TriggerKeySameAsKeyReleased_ButGameObjectNull_DoesNothing)
    {
      LimitedLifeTime lifeTime;
      lifeTime.setTriggerKey(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, lifeTime.getTriggerKey());
      Assert::IsNull(lifeTime.getGameObject());

      bool called = false;
      lifeTime.getOnDeathEvent().subscribe([&called](GameObject&) -> void
      {
        called = true;
      });

      simulateKeyReleased(GLFW_KEY_A);

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(LimitedLifeTime_OnKeyReleased_TriggerKeySameAsKeyReleased_DeallocatesGameObject)
    {
      Assert::Fail();

      GameObject gameObject;
      AutoDeallocator<LimitedLifeTime> lifeTime = gameObject.addComponent<LimitedLifeTime>();
      lifeTime->setTriggerKey(GLFW_KEY_A);

      Assert::AreEqual(GLFW_KEY_A, lifeTime->getTriggerKey());
      Assert::IsTrue(&gameObject == lifeTime->getGameObject());

      bool called = false;
      lifeTime->getOnDeathEvent().subscribe([&called](GameObject&) -> void
      {
        called = true;
      });

      simulateKeyReleased(GLFW_KEY_A);

      Assert::IsTrue(called);
      //AssertCel::IsNotAlive(gameObject);
    }

#pragma endregion

  };
}