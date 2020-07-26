#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "UI/Slider.h"
#include "Rendering/SpriteRenderer.h"
#include "TestResources/TestResources.h"
#include "Input/InputManager.h"
#include "Input/MouseInteractionHandler.h"
#include "CelesteTestUtils/Utils/InputUtils.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "CelesteTestUtils/Assert/AssertCel.h"
#include "TestUtils/Assert/AssertExt.h"


namespace TestCeleste
{
  using namespace UI;
  using namespace Celeste::Input;
  using namespace Celeste::Rendering;

  CELESTE_TEST_CLASS(TestSlider)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    getMouse().flush();
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
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

    observer_ptr<Component> component = ComponentRegistry::createComponent(Slider::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<Slider*>(component));
    Assert::AreSame(gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_Constructor_SetsMinToZero)
  {
    GameObject gameObject;
    Slider slider(gameObject);

    Assert::AreEqual(0.0f, slider.getMin());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_Constructor_SetsMaxToOne)
  {
    GameObject gameObject;
    Slider slider(gameObject);

    Assert::AreEqual(1.0f, slider.getMax());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_Constructor_SetsCurrentValueToZero)
  {
    GameObject gameObject;
    Slider slider(gameObject);

    Assert::AreEqual(0.0f, slider.getCurrentValue());
  }

#pragma endregion

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_HandleInput_MouseLeftButtonNotClicked_AndSliderNotClicked_DoesNothing)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    renderer->setDimensions(400, 20);
    renderer->getScissorRectangle().setDimensions(40, 20);
    observer_ptr<Slider> slider = gameObject.addComponent<Slider>();

    Assert::AreEqual(0.0f, slider->getCurrentValue());
    Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kLeft));
    Assert::IsFalse(handler->isMouseOver());

    getMouse().getTransform().translate(10, 0);
    slider->update();

    Assert::AreEqual(0.0f, slider->getCurrentValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_HandleInput_MouseLeftButtonClicked_AndSliderNotClicked_DoesNothing)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    renderer->setDimensions(400, 20);
    renderer->getScissorRectangle().setDimensions(40, 20);
    observer_ptr<Slider> slider = gameObject.addComponent<Slider>();

    Assert::AreEqual(0.0f, slider->getCurrentValue());

    simulateMouseButtonClicked(Input::MouseButton::kLeft);

    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));
    Assert::IsFalse(handler->isMouseOver());

    getMouse().getTransform().translate(10, 0);
    slider->update();

    Assert::AreEqual(0.0f, slider->getCurrentValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_HandleInput_SliderClicked_SetsValueBasedOnMousePositionRelativeToSlider)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    renderer->setTexture(TestResources::getBlockPngRelativePath());
    renderer->setDimensions(400, 20);
    renderer->getScissorRectangle().setDimensions(30, 20);

    observer_ptr<Slider> slider = gameObject.addComponent<Slider>();
    slider->setMin(0);
    slider->setMax(1);
      
    Assert::AreEqual(0.0f, slider->getCurrentValue());

    handler->setMouseOver(true);
    simulateMouseButtonPressed(Input::MouseButton::kLeft);

    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));
    Assert::IsTrue(handler->isMouseOver());

    slider->update();

    Assert::AreEqual(0.0f, slider->getCurrentValue());

    getMouse().getTransform().setTranslation(renderer->getDimensions().x * 0.25f, 0);

    slider->update();

    Assert::AreEqual((100 / 370.0f) + 0.5f, slider->getCurrentValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_HandleInput_SliderHandleClicked_UpdatesPositionCorrectly)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    renderer->setTexture(TestResources::getBlockPngRelativePath());
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    renderer->setDimensions(400, 20);
    renderer->getScissorRectangle().setDimensions(30, 20);

    observer_ptr<Slider> slider = gameObject.addComponent<Slider>();
    slider->setMin(0);
    slider->setMax(1);

    Assert::AreEqual(0.0f, slider->getCurrentValue());

    handler->setMouseOver(true);
    simulateMouseButtonPressed(Input::MouseButton::kLeft);

    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));
    Assert::IsTrue(handler->isMouseOver());

    slider->update();

    Assert::AreEqual(0.0f, slider->getCurrentValue());

    getMouse().getTransform().setTranslation(renderer->getDimensions().x * 0.25f, 0);
    slider->update();

    AssertExt::AreAlmostEqual(100.0f, renderer->getScissorRectangle().getCentre().x, 0.0001f);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_HandleInput_SliderClicked_TriggersValueChangedEvent)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    renderer->setDimensions(400, 20);
    renderer->getScissorRectangle().setDimensions(40, 20);
    observer_ptr<Slider> slider = gameObject.addComponent<Slider>();
    slider->setMin(0);
    slider->setMax(1);

    Assert::AreEqual(0.0f, slider->getCurrentValue());

    handler->setMouseOver(true);
    simulateMouseButtonPressed(Input::MouseButton::kLeft);

    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));
    Assert::IsTrue(handler->isMouseOver());

    slider->update();

    bool called = false;
    float value = 0;
    slider->subscribeValueChangedCallback([&called, &value](GameObject&, float f) -> void
    {
      called = true;
      value = f;
    });

    // Now that slider is clicked we move it
    getMouse().getTransform().translate(renderer->getDimensions().x * 0.25f, 0);
    slider->update();

    Assert::IsTrue(called);
    Assert::AreEqual(slider->getCurrentValue(), value);
  }

#pragma endregion

#pragma region Set Current Value Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_SetCurrentValue_UpdatesCurrentValue)
  {
    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();
    
    Slider slider(gameObject);
    slider.setCurrentValue(0.5f);

    Assert::AreEqual(0.5f, slider.getCurrentValue());

    slider.setCurrentValue(1);

    Assert::AreEqual(1.0f, slider.getCurrentValue());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Slider_SetCurrentValue_ClampsCurrentValueBetweenMinAndMax)
  {
    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();

    Slider slider(gameObject);
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
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    renderer->setDimensions(400, 200);
    renderer->getScissorRectangle().setDimensions(40, 200);
    observer_ptr<Slider> slider = gameObject.addComponent<Slider>();

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

    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();
    
    Slider slider(gameObject);
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

    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();
    
    Slider slider(gameObject);
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

    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();
    
    Slider slider(gameObject);
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