#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "GraphicalFX/OpacityLerper.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "Rendering/SpriteRenderer.h"
#include "CelesteTestUtils/Assert/AssertCel.h"
#include "TestUtils/Assert/AssertExt.h"
#include "Time/TimeUtils.h"
#include "Time/Clock.h"

using namespace Celeste;
using namespace Celeste::Rendering;
using namespace Celeste::Time;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestOpacityLerper)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerper_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<OpacityLerper>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(OpacityLerper_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(OpacityLerper::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<OpacityLerper*>(component));
    Assert::AreSame(gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Constructor_SetsValuesToDefault)
    {
      GameObject gameObject;
      OpacityLerper opacityLerper(gameObject);

      Assert::AreEqual(0.0f, opacityLerper.getMinOpacity());
      Assert::AreEqual(1.0f, opacityLerper.getMaxOpacity());
      Assert::AreEqual(1.0f, opacityLerper.getLerpUpTime());
      Assert::AreEqual(1.0f, opacityLerper.getLerpDownTime());
      Assert::AreEqual(0.0f, opacityLerper.getMaxOpacityWaitTime());
      Assert::AreEqual(0.0f, opacityLerper.getMinOpacityWaitTime());
      Assert::IsFalse(opacityLerper.isLerpingUp());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_WithGameObjectButNoRenderer_DoesNotThrow)
    {
      GameObject gameObject;
      OpacityLerper opacityLerper(gameObject);

      Assert::IsFalse(gameObject.hasComponent<Renderer>());

      // Check doesnt throw
      getClock().update(1);
      opacityLerper.update();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingUp_LerpUpTimeIsZero_IncreasesOpacityToMaxImmediately)
    {
      GameObject gameObject;
      observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      observer_ptr<OpacityLerper> opacityLerper = gameObject.addComponent<OpacityLerper>();

      getClock().update(0);

      AssertExt::AreAlmostEqual(0.0f, getElapsedDeltaTime());

      renderer->setOpacity(0);
      opacityLerper->setLerpingUp(true);
      opacityLerper->setMaxOpacity(1.0f);
      opacityLerper->setLerpUpTime(0);
      opacityLerper->update();

      Assert::AreEqual(1.0f, renderer->getOpacity());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingUp_WithNoWaitTime_IncreasesOpacityToMax_ThenLerpsDown)
    {
      GameObject gameObject;
      observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      observer_ptr<OpacityLerper> opacityLerper = gameObject.addComponent<OpacityLerper>();

      opacityLerper->setLerpingUp(true);
      opacityLerper->setMaxOpacity(1.0f);
      renderer->setOpacity(0.5f);
      
      Assert::IsTrue(gameObject.hasComponent<Renderer>());
      Assert::IsTrue(opacityLerper->isLerpingUp());

      getClock().update(0.5f);

      AssertExt::AreAlmostEqual(0.5f, getElapsedDeltaTime());

      opacityLerper->update();

      Assert::AreEqual(1.0f, renderer->getOpacity());
      Assert::IsFalse(opacityLerper->isLerpingUp());

      getClock().update(0.5f);

      AssertExt::AreAlmostEqual(0.5f, getElapsedDeltaTime());

      opacityLerper->update();

      Assert::AreEqual(0.5f, renderer->getOpacity());
      Assert::IsFalse(opacityLerper->isLerpingUp());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingUp_WithWaitTime_IncreasesOpacityToMax_ThenWaits_ThenLerpsDown)
    {
      GameObject gameObject;
      observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      observer_ptr<OpacityLerper> opacityLerper = gameObject.addComponent<OpacityLerper>();

      opacityLerper->setLerpingUp(true);
      opacityLerper->setMaxOpacity(1.0f);
      opacityLerper->setMaxOpacityWaitTime(1);
      renderer->setOpacity(0.5f);

      Assert::IsTrue(gameObject.hasComponent<Renderer>());
      Assert::IsTrue(opacityLerper->isLerpingUp());

      getClock().update(0.5f);

      AssertExt::AreAlmostEqual(0.5f, getElapsedDeltaTime());

      opacityLerper->update();

      Assert::AreEqual(1.0f, renderer->getOpacity());
      Assert::IsTrue(opacityLerper->isLerpingUp());

      getClock().update(0.2f);

      AssertExt::AreAlmostEqual(0.2f, getElapsedDeltaTime());

      opacityLerper->update();

      Assert::AreEqual(1.0f, renderer->getOpacity());
      Assert::IsTrue(opacityLerper->isLerpingUp());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingDown_LerpDownTimeIsZero_DecreasesOpacityToMinImmediately)
    {
      GameObject gameObject;
      observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      observer_ptr<OpacityLerper> opacityLerper = gameObject.addComponent<OpacityLerper>();

      getClock().update(0);

      Assert::AreEqual(0.0f, getElapsedDeltaTime());

      renderer->setOpacity(1.0f);
      opacityLerper->setLerpingUp(false);
      opacityLerper->setMinOpacity(0.0f);
      opacityLerper->setLerpDownTime(0);
      opacityLerper->update();

      Assert::AreEqual(0.0f, renderer->getOpacity());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingDown_WithNoWaitTime_DecreasesOpacityToMin_ThenLerpsUp)
    {
      GameObject gameObject;
      observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      observer_ptr<OpacityLerper> opacityLerper = gameObject.addComponent<OpacityLerper>();

      opacityLerper->setLerpingUp(false);
      opacityLerper->setMinOpacity(0);
      renderer->setOpacity(0.5f);
      
      Assert::IsTrue(gameObject.hasComponent<Renderer>());
      Assert::IsFalse(opacityLerper->isLerpingUp());

      getClock().update(0.5f);

      AssertExt::AreAlmostEqual(0.5f, getElapsedDeltaTime());

      opacityLerper->update();

      Assert::AreEqual(0.0f, renderer->getOpacity());
      Assert::IsTrue(opacityLerper->isLerpingUp());

      getClock().update(0.5f);

      AssertExt::AreAlmostEqual(0.5f, getElapsedDeltaTime());

      opacityLerper->update();

      Assert::AreEqual(0.5f, renderer->getOpacity());
      Assert::IsTrue(opacityLerper->isLerpingUp());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingDown_WithNoWaitTime_DecreasesOpacityToMin_ThenWaits_ThenLerpsUp)
    {
      GameObject gameObject;
      observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      observer_ptr<OpacityLerper> opacityLerper = gameObject.addComponent<OpacityLerper>();

      opacityLerper->setLerpingUp(false);
      opacityLerper->setMinOpacity(0);
      opacityLerper->setMinOpacityWaitTime(1);
      renderer->setOpacity(0.5f);

      Assert::IsTrue(gameObject.hasComponent<Renderer>());
      Assert::IsFalse(opacityLerper->isLerpingUp());

      getClock().update(0.5f);

      AssertExt::AreAlmostEqual(0.5f, getElapsedDeltaTime());

      opacityLerper->update();

      Assert::AreEqual(0.0f, renderer->getOpacity());
      Assert::IsFalse(opacityLerper->isLerpingUp());

      getClock().update(0.2f);

      AssertExt::AreAlmostEqual(0.2f, getElapsedDeltaTime());

      opacityLerper->update();

      Assert::AreEqual(0.0f, renderer->getOpacity());
      Assert::IsFalse(opacityLerper->isLerpingUp());
    }

#pragma endregion

  };
}