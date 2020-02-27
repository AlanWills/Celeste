#include "UtilityHeaders/UnitTestHeaders.h"

#include "GraphicalFX/OpacityLerper.h"
#include "Registries/ComponentRegistry.h"
#include "Rendering/SpriteRenderer.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Rendering;


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

    AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(OpacityLerper::type_name(), gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<OpacityLerper*>(component.get()));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Constructor_SetsValuesToDefault)
    {
      OpacityLerper lerper;

      Assert::AreEqual(0.0f, lerper.getMinOpacity());
      Assert::AreEqual(1.0f, lerper.getMaxOpacity());
      Assert::AreEqual(1.0f, lerper.getLerpUpTime());
      Assert::AreEqual(1.0f, lerper.getLerpDownTime());
      Assert::AreEqual(0.0f, lerper.getMaxOpacityWaitTime());
      Assert::AreEqual(0.0f, lerper.getMinOpacityWaitTime());
      Assert::IsFalse(lerper.isLerpingUp());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_WithNoParent_DoesNotThrow)
    {
      OpacityLerper lerper;

      Assert::IsNull(lerper.getGameObject());

      // Check doesnt throw
      lerper.update(0);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_WithParentButNoRenderer_DoesNotThrow)
    {
      GameObject gameObject;
      AutoDeallocator<OpacityLerper> lerper = gameObject.addComponent<OpacityLerper>();

      Assert::IsNotNull(lerper->getGameObject());
      Assert::IsFalse(gameObject.hasComponent<Renderer>());

      // Check doesnt throw
      lerper->update(0);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingUp_LerpUpTimeIsZero_IncreasesOpacityToMaxImmediately)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<OpacityLerper> lerper = gameObject.addComponent<OpacityLerper>();

      renderer->setOpacity(0);
      lerper->setLerpingUp(true);
      lerper->setMaxOpacity(1.0f);
      lerper->setLerpUpTime(0);
      lerper->update(0);

      Assert::AreEqual(1.0f, renderer->getOpacity());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingUp_WithNoWaitTime_IncreasesOpacityToMax_ThenLerpsDown)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<OpacityLerper> lerper = gameObject.addComponent<OpacityLerper>();

      lerper->setLerpingUp(true);
      lerper->setMaxOpacity(1.0f);
      renderer->setOpacity(0.5f);
      
      Assert::IsNotNull(lerper->getGameObject());
      Assert::IsTrue(gameObject.hasComponent<Renderer>());
      Assert::IsTrue(lerper->isLerpingUp());

      lerper->update(0.5f);

      Assert::AreEqual(1.0f, renderer->getOpacity());
      Assert::IsFalse(lerper->isLerpingUp());

      lerper->update(0.5f);

      Assert::AreEqual(0.5f, renderer->getOpacity());
      Assert::IsFalse(lerper->isLerpingUp());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingUp_WithWaitTime_IncreasesOpacityToMax_ThenWaits_ThenLerpsDown)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<OpacityLerper> lerper = gameObject.addComponent<OpacityLerper>();

      lerper->setLerpingUp(true);
      lerper->setMaxOpacity(1.0f);
      lerper->setMaxOpacityWaitTime(1);
      renderer->setOpacity(0.5f);

      Assert::IsNotNull(lerper->getGameObject());
      Assert::IsTrue(gameObject.hasComponent<Renderer>());
      Assert::IsTrue(lerper->isLerpingUp());

      lerper->update(0.5f);

      Assert::AreEqual(1.0f, renderer->getOpacity());
      Assert::IsTrue(lerper->isLerpingUp());

      lerper->update(0.2f);

      Assert::AreEqual(1.0f, renderer->getOpacity());
      Assert::IsTrue(lerper->isLerpingUp());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingDown_LerpDownTimeIsZero_DecreasesOpacityToMinImmediately)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<OpacityLerper> lerper = gameObject.addComponent<OpacityLerper>();

      renderer->setOpacity(1.0f);
      lerper->setLerpingUp(false);
      lerper->setMinOpacity(0.0f);
      lerper->setLerpDownTime(0);
      lerper->update(0);

      Assert::AreEqual(0.0f, renderer->getOpacity());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingDown_WithNoWaitTime_DecreasesOpacityToMin_ThenLerpsUp)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<OpacityLerper> lerper = gameObject.addComponent<OpacityLerper>();

      lerper->setLerpingUp(false);
      lerper->setMinOpacity(0);
      renderer->setOpacity(0.5f);
      
      Assert::IsNotNull(lerper->getGameObject());
      Assert::IsTrue(gameObject.hasComponent<Renderer>());
      Assert::IsFalse(lerper->isLerpingUp());

      lerper->update(0.5f);

      Assert::AreEqual(0.0f, renderer->getOpacity());
      Assert::IsTrue(lerper->isLerpingUp());

      lerper->update(0.5f);

      Assert::AreEqual(0.5f, renderer->getOpacity());
      Assert::IsTrue(lerper->isLerpingUp());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OpacityLerper_Update_LerpingDown_WithNoWaitTime_DecreasesOpacityToMin_ThenWaits_ThenLerpsUp)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<OpacityLerper> lerper = gameObject.addComponent<OpacityLerper>();

      lerper->setLerpingUp(false);
      lerper->setMinOpacity(0);
      lerper->setMinOpacityWaitTime(1);
      renderer->setOpacity(0.5f);

      Assert::IsNotNull(lerper->getGameObject());
      Assert::IsTrue(gameObject.hasComponent<Renderer>());
      Assert::IsFalse(lerper->isLerpingUp());

      lerper->update(0.5f);

      Assert::AreEqual(0.0f, renderer->getOpacity());
      Assert::IsFalse(lerper->isLerpingUp());

      lerper->update(0.2f);

      Assert::AreEqual(0.0f, renderer->getOpacity());
      Assert::IsFalse(lerper->isLerpingUp());
    }

#pragma endregion

  };
}