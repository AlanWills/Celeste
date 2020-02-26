#include "UtilityHeaders/UnitTestHeaders.h"

#include "UI/Slider.h"
#include "Rendering/SpriteRenderer.h"
#include "Physics/RectangleCollider.h"
#include "Screens/Screen.h"
#include "Resources/TestResources.h"
#include "Input/InputManager.h"
#include "Utils/ObjectUtils.h"
#include "Utils/InputUtils.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"
#include "AssertExt.h"


namespace TestCeleste
{
  using namespace UI;
  using namespace Celeste::Input;
  using namespace Celeste::Physics;
  using namespace Celeste::Rendering;

  CELESTE_TEST_CLASS(TestSlider)

    //------------------------------------------------------------------------------------------------
    void TestSlider::testInitialize()
    {
      getMouse().flush();
    }

    //------------------------------------------------------------------------------------------------
    void TestSlider::testCleanup()
    {
      getMouse().flush();
    }

#pragma region Registration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_IsRegisteredWithComponentRegistry)
    {
      Assert::IsTrue(ComponentRegistry::hasComponent<Slider>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_IsAllocatableFromComponentRegistry)
    {
      GameObject gameObject;

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(Slider::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<Slider*>(component.get()));
      Assert::AreEqual(&gameObject, component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_Constructor_SetsMinToZero)
    {
      Slider slider;

      Assert::AreEqual(0.0f, slider.getMin());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_Constructor_SetsMaxToOne)
    {
      Slider slider;

      Assert::AreEqual(1.0f, slider.getMax());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_Constructor_SetsCurrentValueToZero)
    {
      Slider slider;

      Assert::AreEqual(0.0f, slider.getCurrentValue());
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_HandleInput_MouseLeftButtonNotClicked_AndSliderNotClicked_DoesNothing)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      AutoDeallocator<RectangleCollider> collider = gameObject->addComponent<RectangleCollider>();
      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      renderer->setDimensions(400, 20);
      renderer->getScissorRectangle().setDimensions(40, 20);
      collider->setDimensions(400, 20);
      AutoDeallocator<Slider> slider = gameObject->addComponent<Slider>();

      Assert::AreEqual(0.0f, slider->getCurrentValue());
      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kLeft));
      Assert::IsFalse(gameObject->findComponent<RectangleCollider>()->isHitByRay());

      getMouse().getTransform().translate(10, 0);
      slider->handleInput();

      Assert::AreEqual(0.0f, slider->getCurrentValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_HandleInput_MouseLeftButtonClicked_AndSliderNotClicked_DoesNothing)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      AutoDeallocator<RectangleCollider> collider = gameObject->addComponent<RectangleCollider>();
      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      renderer->setDimensions(400, 20);
      renderer->getScissorRectangle().setDimensions(40, 20);
      collider->setDimensions(400, 20);
      AutoDeallocator<Slider> slider = gameObject->addComponent<Slider>();

      Assert::AreEqual(0.0f, slider->getCurrentValue());

      simulateMouseButtonClicked(Input::MouseButton::kLeft);

      Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));
      Assert::IsFalse(gameObject->findComponent<RectangleCollider>()->isHitByRay());

      getMouse().getTransform().translate(10, 0);
      slider->handleInput();

      Assert::AreEqual(0.0f, slider->getCurrentValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_HandleInput_SliderClicked_SetsValueBasedOnMousePositionRelativeToSlider)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      renderer->setTexture(TestResources::getBlockPngRelativePath());
      renderer->setDimensions(400, 20);
      renderer->getScissorRectangle().setDimensions(30, 20);

      AutoDeallocator<RectangleCollider> collider = gameObject->addComponent<RectangleCollider>();
      collider->setDimensions(400, 20);

      AutoDeallocator<Slider> slider = gameObject->addComponent<Slider>();
      slider->setMin(0);
      slider->setMax(1);
      
      Assert::AreEqual(0.0f, slider->getCurrentValue());

      collider->setHitByRay(true);
      simulateMouseButtonPressed(Input::MouseButton::kLeft);

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));
      Assert::IsTrue(collider->isHitByRay());

      slider->handleInput();

      Assert::AreEqual(0.0f, slider->getCurrentValue());

      getMouse().getTransform().setTranslation(renderer->getDimensions().x * 0.25f, 0);

      slider->handleInput();

      Assert::AreEqual((100 / 370.0f) + 0.5f, slider->getCurrentValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_HandleInput_SliderHandleClicked_UpdatesPositionCorrectly)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      renderer->setTexture(TestResources::getBlockPngRelativePath());
      renderer->setDimensions(400, 20);
      renderer->getScissorRectangle().setDimensions(30, 20);

      AutoDeallocator<RectangleCollider> collider = gameObject->addComponent<RectangleCollider>();
      collider->setDimensions(400, 20);

      AutoDeallocator<Slider> slider = gameObject->addComponent<Slider>();
      slider->setMin(0);
      slider->setMax(1);

      Assert::AreEqual(0.0f, slider->getCurrentValue());

      collider->setHitByRay(true);
      simulateMouseButtonPressed(Input::MouseButton::kLeft);

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));
      Assert::IsTrue(collider->isHitByRay());

      slider->handleInput();

      Assert::AreEqual(0.0f, slider->getCurrentValue());

      getMouse().getTransform().setTranslation(renderer->getDimensions().x * 0.25f, 0);
      slider->handleInput();

      AssertExt::AreAlmostEqual(100.0f, renderer->getScissorRectangle().getCentre().x, 0.0001f);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_HandleInput_SliderClicked_TriggersValueChangedEvent)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      AutoDeallocator<RectangleCollider> collider = gameObject->addComponent<RectangleCollider>();
      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      renderer->setDimensions(400, 20);
      renderer->getScissorRectangle().setDimensions(40, 20);
      collider->setDimensions(400, 20);
      AutoDeallocator<Slider> slider = gameObject->addComponent<Slider>();
      slider->setMin(0);
      slider->setMax(1);

      Assert::AreEqual(0.0f, slider->getCurrentValue());

      collider->setHitByRay(true);
      simulateMouseButtonPressed(Input::MouseButton::kLeft);

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));
      Assert::IsTrue(collider->isHitByRay());

      slider->handleInput();

      bool called = false;
      float value = 0;
      slider->subscribeValueChangedCallback([&called, &value](GameObject&, float f) -> void
      {
        called = true;
        value = f;
      });

      // Now that slider is clicked we move it
      getMouse().getTransform().translate(renderer->getDimensions().x * 0.25f, 0);
      slider->handleInput();

      Assert::IsTrue(called);
      Assert::AreEqual(slider->getCurrentValue(), value);
    }

#pragma endregion

#pragma region Die Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_Die_SetsMinToZero)
    {
      Slider slider;
      slider.setMin(2);

      Assert::AreEqual(2.0f, slider.getMin());

      slider.die();

      Assert::AreEqual(0.0f, slider.getMin());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_Die_SetsMaxToOne)
    {
      Slider slider;
      slider.setMax(2);

      Assert::AreEqual(2.0f, slider.getMax());

      slider.die();

      Assert::AreEqual(1.0f, slider.getMax());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_Die_SetsCurrentValueToZero)
    {
      Slider slider;
      slider.setCurrentValue(0.2f);

      Assert::AreEqual(0.2f, slider.getCurrentValue());

      slider.die();

      Assert::AreEqual(0.0f, slider.getCurrentValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_Die_UnsubscribesAllFromValueChangedEvent)
    {
      bool called = false;

      Slider slider;
      slider.subscribeValueChangedCallback([&called](GameObject&, float) -> void
      {
        called = true;
      });

      slider.setCurrentValue(1);

      Assert::IsTrue(called);

      called = false;
      slider.die();
      slider.setCurrentValue(1);

      Assert::IsFalse(called);
    }

#pragma endregion

#pragma region Set Current Value Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_SetCurrentValue_UpdatesCurrentValue)
    {
      Slider slider;
      slider.setCurrentValue(0.5f);

      Assert::AreEqual(0.5f, slider.getCurrentValue());

      slider.setCurrentValue(1);

      Assert::AreEqual(1.0f, slider.getCurrentValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_SetCurrentValue_ClampsCurrentValueBetweenMinAndMax)
    {
      Slider slider;
      slider.setMin(0.25f);
      slider.setMax(0.5f);
      slider.setCurrentValue(1);

      Assert::AreEqual(0.5f, slider.getCurrentValue());

      slider.setCurrentValue(-2);

      Assert::AreEqual(0.25f, slider.getCurrentValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_SetCurrentValue_UpdatesSliderPositionCorrectly)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      renderer->setDimensions(400, 200);
      renderer->getScissorRectangle().setDimensions(40, 200);
      AutoDeallocator<Slider> slider = gameObject.addComponent<Slider>();

      // Change value so when we set to zero, it doesn't just do nothing because the value is the same
      slider->setCurrentValue(0.1f);
      slider->setMin(-1);
      slider->setMax(1);
      slider->setCurrentValue(0);

      Assert::AreEqual(0.0f, renderer->getScissorRectangle().getCentre().x);

      slider->setCurrentValue(0.5f);

      Assert::AreEqual(90.0f, renderer->getScissorRectangle().getCentre().x);

      slider->setCurrentValue(-0.5f);

      Assert::AreEqual(-90.0f, renderer->getScissorRectangle().getCentre().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_SetCurrentValue_ToDifferentValue_TriggersValueChangedEvent)
    {
      bool called = false;
      float value = 0;

      Slider slider;
      slider.setMin(0);
      slider.setMax(1);
      slider.subscribeValueChangedCallback([&called, &value](GameObject&, float f) -> void
      {
        called = true;
        value = f;
      });

      Assert::AreNotEqual(0.5f, slider.getCurrentValue());
      Assert::AreEqual(0.0f, value);

      slider.setCurrentValue(0.5f);

      Assert::IsTrue(called);
      Assert::AreEqual(0.5f, value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_SetCurrentValue_ToSameValue_TriggersValueChangedEvent)
    {
      bool called = false;
      float value = 0;

      Slider slider;
      slider.setMin(0);
      slider.setMax(1);
      slider.subscribeValueChangedCallback([&called, &value](GameObject&, float f) -> void
      {
        called = true;
        value = f;
      });

      Assert::AreEqual(0.0f, slider.getCurrentValue());
      Assert::AreEqual(0.0f, value);

      slider.setCurrentValue(0.0f);

      Assert::IsTrue(called);
      Assert::AreEqual(0.0f, value);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Slider_SetCurrentValue_ToSameValueWhenClamped_TriggersValueChangedEvent)
    {
      bool called = false;
      float value = 0;

      Slider slider;
      slider.setMin(0);
      slider.setMax(1);
      slider.subscribeValueChangedCallback([&called, &value](GameObject&, float f) -> void
      {
        called = true;
        value = f;
      });

      Assert::AreEqual(0.0f, slider.getCurrentValue());
      Assert::AreEqual(0.0f, value);

      slider.setCurrentValue(-20.0f);

      Assert::IsTrue(called);
      Assert::AreEqual(0.0f, value);
    }

#pragma endregion
  };
}