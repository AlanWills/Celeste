#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/UI/MockButton.h"
#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"
#include "Input/MouseInteractionHandler.h"
#include "Rendering/SpriteRenderer.h"
#include "Audio/AudioSource.h"
#include "DataConverters/UI/ButtonDataConverter.h"
#include "Registries/ComponentRegistry.h"
#include "TestUtils/Utils/InputUtils.h"
#include "TestUtils/Assert/AssertCel.h"
#include "TestResources/TestResources.h"

using namespace Celeste;
using namespace Celeste::Audio;
using namespace Celeste::Resources;
using namespace Celeste::Input;
using namespace Celeste::Rendering;


namespace TestCeleste
{
  using namespace UI;

  CELESTE_TEST_CLASS(TestButton)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<Button>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<Component> component = ComponentRegistry::createComponent(Button::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<Button*>(component));
    Assert::AreSame(gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_Constructor_SetsButtonStateTo_kIdle)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);
    MockButton button(gameObject);

    Assert::IsTrue(button.getButtonState_Public() == Button::ButtonState::kIdle);
  }

#pragma endregion

#pragma region Subscribe Left Click Callback Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SubscribeLeftClickCallback_WithNullMouseInteractionHandler_DoesNothing)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);
    MockButton button(gameObject);
    button.subscribeLeftClickCallback([](GameObject&) -> void { });
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SubscribeLeftClickCallback_SingleCallback_SubscribesToInteractionHandler)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.findComponent<MouseInteractionHandler>();

    observer_ptr<MouseInteractionHandler> handler = gameObject.findComponent<MouseInteractionHandler>();
    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    handler->setMouseOver(true);
    button->setButtonState_Public(Button::ButtonState::kClicked);

    Assert::AreEqual(handler, mouseInteractionHandler);
    Assert::IsTrue(handler->isMouseOver());

    bool called = false;
    button->subscribeLeftClickCallback([&called](GameObject&) -> void { called = true; });
    handler->getOnLeftButtonUpEvent().invoke(gameObject);

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SubscribeLeftClickCallback_MultipleCallbacks_SubscribesToInteractionHandler)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);
    observer_ptr<MouseInteractionHandler> mouseInteractionHandler = gameObject.findComponent<MouseInteractionHandler>();

    observer_ptr<MouseInteractionHandler> handler = gameObject.findComponent<MouseInteractionHandler>();
    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    handler->setMouseOver(true);
    button->setButtonState_Public(Button::ButtonState::kClicked);

    Assert::AreEqual(handler, mouseInteractionHandler);
    Assert::IsTrue(handler->isMouseOver());

    bool called = false;
    bool called2 = false;
    button->subscribeLeftClickCallback(
      [&called](GameObject&) -> void { called = true; },
      [&called2](GameObject&) -> void { called2 = true; });
    handler->getOnLeftButtonUpEvent().invoke(gameObject);

    Assert::IsTrue(called);
    Assert::IsTrue(called2);
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_OnMouseEnter_SetsTextureToHighlighted_UpdatesSpriteRendererDimensions_PlaysHighlightedAudio_AndSetsStateToHighlighted)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);
    observer_ptr<MouseInteractionHandler> handler = gameObject.findComponent<MouseInteractionHandler>();
    observer_ptr<SpriteRenderer> spriteRenderer = gameObject.findComponent<SpriteRenderer>();
    observer_ptr<AudioSource> audioSource = gameObject.findComponent<AudioSource>();

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());

    handler->update();
    button->update();

    Assert::AreEqual(button->getHighlightedTexture()->getDimensions(), spriteRenderer->getDimensions());
    Assert::AreEqual(button->getHighlightedTexture(), spriteRenderer->getTexture());
    Assert::IsTrue(audioSource->isPlaying());
    Assert::IsTrue(button->getButtonState_Public() == Button::ButtonState::kHighlighted);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_OnMouseLeave_SetsTextureToIdle)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> spriteRenderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<AudioSource> audioSource = gameObject.addComponent<AudioSource>();
    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();  // Make sure this is last so it doesn't create components

    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());

    handler->update();
    button->update();

    Assert::IsTrue(button->getButtonState_Public() == Button::ButtonState::kHighlighted);
    Assert::AreEqual(button->getHighlightedTexture(), spriteRenderer->getTexture());
    Assert::IsTrue(audioSource->isPlaying());

    handler->setMouseOver(false);

    Assert::IsFalse(handler->isMouseOver());

    handler->update();
    button->update();

    Assert::AreEqual(button->getIdleTexture()->getDimensions(), spriteRenderer->getDimensions());
    Assert::AreEqual(button->getIdleTexture(), spriteRenderer->getTexture());
    Assert::IsTrue(button->getButtonState_Public() == Button::ButtonState::kIdle);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_OnMouseLeftClick_WhenNotClicked_SetsTextureToClicked_UpdatesSpriteRendererDimensions_PlaysClickedAudio_AndSetsStateToClicked)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> spriteRenderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<AudioSource> audioSource = gameObject.addComponent<AudioSource>();
    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();

    button->setButtonState_Public(Button::ButtonState::kIdle);

    Assert::AreEqual(button->getIdleTexture(), spriteRenderer->getTexture());
    Assert::IsFalse(audioSource->isPlaying());
    Assert::IsTrue(button->getButtonState_Public() == Button::ButtonState::kIdle);

    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());

    // This must go before the button handle input
    // Simulate a mouse click
    simulateMouseButtonClicked(MouseButton::kLeft);
      
    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));

    handler->update();

    Assert::AreEqual(button->getClickedTexture()->getDimensions(), spriteRenderer->getDimensions());
    Assert::IsTrue(button->getButtonState_Public() == Button::ButtonState::kClicked);
    Assert::AreEqual(button->getClickedTexture(), spriteRenderer->getTexture());
    Assert::IsTrue(audioSource->isPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_OnMouseLeftButtonReleased_ButtonNotClicked_DoesNotRaiseClick)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> spriteRenderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<AudioSource> audioSource = gameObject.addComponent<AudioSource>();
    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();

    bool called = false;
    button->subscribeLeftClickCallback([&called](GameObject&) -> void
    {
      called = true;
    });

    button->setButtonState_Public(Button::ButtonState::kIdle);

    Assert::IsTrue(button->getIdleTexture() == spriteRenderer->getTexture());
    Assert::IsFalse(audioSource->isPlaying());
    Assert::IsTrue(button->getButtonState_Public() == Button::ButtonState::kIdle);

    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());

    // This must go before the button handle input
    // Simulate a mouse click
    simulateMouseButtonClicked(MouseButton::kLeft);

    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));

    button->setButtonState_Public(Button::ButtonState::kIdle);

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_OnMouseLeftButtonReleased_ButtonNotClicked_DoesNotChangeButtonState)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> spriteRenderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<AudioSource> audioSource = gameObject.addComponent<AudioSource>();
    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();

    bool called = false;
    button->subscribeLeftClickCallback([&called](GameObject&) -> void
    {
      called = true;
    });

    button->setButtonState_Public(Button::ButtonState::kIdle);

    Assert::IsTrue(button->getIdleTexture() == spriteRenderer->getTexture());
    Assert::IsFalse(audioSource->isPlaying());
    Assert::IsTrue(button->getButtonState_Public() == Button::ButtonState::kIdle);

    Assert::IsFalse(handler->isMouseOver());

    // This must go before the button handle input
    // Simulate a mouse click
    simulateMouseButtonClicked(MouseButton::kLeft);

    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));

    handler->update();

    Assert::IsTrue(Button::ButtonState::kIdle == button->getButtonState_Public());

    button->setButtonState_Public(Button::ButtonState::kHighlighted);

    Assert::IsTrue(Button::ButtonState::kHighlighted == button->getButtonState_Public());

    simulateMouseButtonReleased(MouseButton::kLeft);
    handler->update();

    Assert::IsFalse(called);
    Assert::IsTrue(Button::ButtonState::kHighlighted == button->getButtonState_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_OnMouseLeftButtonReleased_ButtonClicked_SetsButtonStateTo_kIdle)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> spriteRenderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    observer_ptr<AudioSource> audioSource = gameObject.addComponent<AudioSource>();
    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();

    bool called = false;
    button->subscribeLeftClickCallback([&called](GameObject&) -> void
    {
      called = true;
    });

    button->setButtonState_Public(Button::ButtonState::kHighlighted);

    Assert::IsTrue(button->getIdleTexture() == spriteRenderer->getTexture());
    Assert::IsFalse(audioSource->isPlaying());
    Assert::IsTrue(button->getButtonState_Public() == Button::ButtonState::kHighlighted);

    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());

    // This must go before the button handle input
    // Simulate a mouse click
    simulateMouseButtonClicked(MouseButton::kLeft);

    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));

    handler->update();

    Assert::IsTrue(Button::ButtonState::kClicked == button->getButtonState_Public());

    simulateMouseButtonReleased(MouseButton::kLeft);
    handler->update();

    Assert::IsTrue(called);
    Assert::IsTrue(Button::ButtonState::kIdle == button->getButtonState_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_OnMouseLeftButtonReleased_ButtonClicked_SetsTextureToIdleTexture)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> spriteRenderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();
    gameObject.addComponent<AudioSource>();
    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();

    button->setButtonState_Public(Button::ButtonState::kHighlighted);

    Assert::IsTrue(button->getIdleTexture() == spriteRenderer->getTexture());
    Assert::IsTrue(button->getButtonState_Public() == Button::ButtonState::kHighlighted);

    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());

    // This must go before the button handle input
    // Simulate a mouse click
    simulateMouseButtonClicked(MouseButton::kLeft);

    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));

    handler->update();

    Assert::IsTrue(button->getClickedTexture() == spriteRenderer->getTexture());

    simulateMouseButtonReleased(MouseButton::kLeft);
    handler->update();

    Assert::IsTrue(button->getIdleTexture() == spriteRenderer->getTexture());
  }

#pragma region Set Idle Texture Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetIdleTexture_InputtingInvalidPath_SetsIdleTextureToNull)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setIdleTexture(TestResources::getBlockPngRelativePath());

    Assert::IsNotNull(button->getHighlightedTexture());

    button->setIdleTexture("WubbaLubbaDubDub.png");

    Assert::IsNull(button->getIdleTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetIdleTexture_InputtingValidPath_SetsIdleTextureToCorrectTexture)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setIdleTexture(TestResources::getBlockPngRelativePath());

    Assert::IsNotNull(button->getIdleTexture());
    Assert::AreEqual(getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath()), button->getIdleTexture());
  }

#pragma endregion

#pragma region Set Highlighted Texture Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetHighlightedTexture_InputtingInvalidPath_SetsHighlightedTextureToNull)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setIdleTexture(TestResources::getBlockPngRelativePath());

    Assert::IsNotNull(button->getHighlightedTexture());

    button->setHighlightedTexture("WubbaLubbaDubDub.png");

    Assert::IsNull(button->getHighlightedTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetHighlightedTexture_InputtingValidPath_SetsHighlightedTextureToCorrectTexture)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setHighlightedTexture(TestResources::getBlockPngRelativePath());

    Assert::IsNotNull(button->getHighlightedTexture());
    Assert::AreEqual(getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath()), button->getHighlightedTexture());
  }

#pragma endregion

#pragma region Set Clicked Texture Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetClickedTexture_InputtingInvalidPath_SetsClickedTextureToNull)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setIdleTexture(TestResources::getBlockPngRelativePath());

    Assert::IsNotNull(button->getHighlightedTexture());

    button->setClickedTexture("WubbaLubbaDubDub.png");

    Assert::IsNull(button->getClickedTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetClickedTexture_InputtingValidPath_SetsClickedTextureToCorrectTexture)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setClickedTexture(TestResources::getBlockPngRelativePath());

    Assert::IsNotNull(button->getClickedTexture());
    Assert::AreEqual(getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath()), button->getClickedTexture());
  }

#pragma endregion

#pragma region Set Highlighted Sound Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetHighlightedSound_InputtingInvalidPath_SetsHighlightedSoundToNull)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setHighlightedSound(TestResources::getButtonHoverWavRelativePath());

    Assert::IsNotNull(button->getHighlightedSound());

    button->setHighlightedSound("WubbaLubbaDubDub.wav");

    Assert::IsNull(button->getHighlightedSound());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetHighlightedSound_InputtingValidPath_SetsHighlightedSoundToCorrectSound)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setHighlightedSound(TestResources::getButtonHoverWavRelativePath());

    Assert::IsNotNull(button->getHighlightedSound());
    Assert::AreEqual(getResourceManager().load<Sound>(TestResources::getButtonHoverWavRelativePath()), button->getHighlightedSound());
  }

#pragma endregion

#pragma region Set Clicked Sound Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetClickedSound_InputtingInvalidPath_SetsClickedSoundToNull)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setHighlightedSound(TestResources::getButtonHoverWavRelativePath());

    Assert::IsNotNull(button->getClickedSound());

    button->setClickedSound("WubbaLubbaDubDub.wav");

    Assert::IsNull(button->getClickedSound());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Button_SetClickedSound_InputtingValidPath_SetsClickedSoundToCorrectSound)
  {
    GameObject gameObject;
    setUpButtonComponents(gameObject);

    observer_ptr<MockButton> button = gameObject.addComponent<MockButton>();
    button->setClickedSound(TestResources::getButtonHoverWavRelativePath());

    Assert::IsNotNull(button->getClickedSound());
    Assert::AreEqual(getResourceManager().load<Sound>(TestResources::getButtonHoverWavRelativePath()), button->getClickedSound());
  }

#pragma endregion

#pragma region Utility Functions

  //------------------------------------------------------------------------------------------------
  void setUpButtonComponents(GameObject& gameObject)
  {
    gameObject.addComponent<SpriteRenderer>();
    gameObject.addComponent<MouseInteractionHandler>();
    gameObject.addComponent<AudioSource>();
  }

  //------------------------------------------------------------------------------------------------
  void setUpButtonComponents(observer_ptr<GameObject> gameObject)
  {
    setUpButtonComponents(*gameObject);
  }

#pragma endregion

  };
}