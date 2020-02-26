#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/UI/MockTextBox.h"
#include "Mocks/Rendering/MockTextRenderer.h"
#include "Screens/Screen.h"
#include "GraphicalFX/OpacityLerper.h"
#include "Rendering/SpriteRenderer.h"
#include "Input/InputUtils.h"
#include "Input/InputManager.h"
#include "Input/Keyboard.h"
#include "Utils/ObjectUtils.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  using namespace Celeste::UI;
  using namespace Celeste::Rendering;

  CELESTE_TEST_CLASS(TestTextBox)

    //------------------------------------------------------------------------------------------------
    void TestTextBox::testInitialize()
    {
      const_cast<Event<int>&>(getKeyboard().getKeyPressedEvent()).unsubscribeAll();
      const_cast<Event<int>&>(getKeyboard().getKeyReleasedEvent()).unsubscribeAll();
      const_cast<Event<char>&>(getKeyboard().getTextInputtedEvent()).unsubscribeAll();
    }

    //------------------------------------------------------------------------------------------------
    void TestTextBox::testCleanup()
    {
      const_cast<Event<int>&>(getKeyboard().getKeyPressedEvent()).unsubscribeAll();
      const_cast<Event<int>&>(getKeyboard().getKeyReleasedEvent()).unsubscribeAll();
      const_cast<Event<char>&>(getKeyboard().getTextInputtedEvent()).unsubscribeAll();
    }

#pragma region Registration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_IsRegisteredWithComponentRegistry)
    {
      Assert::IsTrue(ComponentRegistry::hasComponent<TextBox>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_IsAllocatableFromComponentRegistry)
    {
      GameObject gameObject;

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(TextBox::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<TextBox*>(component.get()));
      Assert::AreEqual(&gameObject, component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_Constructor_SetsLineIndexToZero)
    {
      MockTextBox textBox;

      Assert::AreEqual((size_t)0, textBox.getLineIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_Constructor_SetsLetterIndexToZero)
    {
      MockTextBox textBox;

      Assert::AreEqual((size_t)0, textBox.getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_Constructor_SubscribesToKeyboardTextInputtedEvent)
    {
      MockTextBox textBox;

      Assert::AreNotEqual((StringId)0, textBox.getTextInputtedEventHandle_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_Constructor_SubscribesToKeyboardKeyPressedEvent)
    {
      MockTextBox textBox;

      Assert::AreNotEqual((StringId)0, textBox.getKeyPressedEventHandle_Public());
    }

#pragma endregion

#pragma region On Set Game Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_OnSetGameObject_AddsEmptyLineToTextRenderer_IfItHasNoLines)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<TextRenderer> renderer = gameObject->addComponent<TextRenderer>();

      Assert::AreEqual(static_cast<size_t>(0), renderer->getLineCount());

      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(static_cast<size_t>(1), renderer->getLineCount());
      Assert::AreEqual("", renderer->getLine(0).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_OnSetGameObject_SetsLineIndexToZero)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<TextRenderer> renderer = gameObject->addComponent<TextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_OnSetGameObject_SetsLetterIndexToZero)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<TextRenderer> renderer = gameObject->addComponent<TextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Set Line Index Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_SetLineIndex_NullTextRenderer_DoesNothing)
    {
      MockTextBox textBox;

      Assert::AreEqual((size_t)0, textBox.getLineIndex());

      textBox.setLineIndex(2);

      Assert::AreEqual((size_t)0, textBox.getLineIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_SetLineIndex_InputtingValueLessZero_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextRenderer> renderer = gameObject.addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();

      renderer->addLine();
      renderer->addLine();

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)2, renderer->getLineCount());

      textBox->setLineIndex(-1);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_SetLineIndex_InputtingValueGreaterThanOrEqualTextRendererLineCount_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextRenderer> renderer = gameObject.addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();

      renderer->addLine();
      renderer->addLine();

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)2, renderer->getLineCount());

      textBox->setLineIndex(renderer->getLineCount());

      Assert::AreEqual((size_t)0, textBox->getLineIndex());

      textBox->setLineIndex(5);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_SetLineIndex_InputtingValueGreaterThanZeroAndLessThanTextRendererLineCount_UpdatesLineIndex)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextRenderer> renderer = gameObject.addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();

      renderer->addLine();
      renderer->addLine();

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)2, renderer->getLineCount());

      textBox->setLineIndex(1);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());

      textBox->setLineIndex(0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_SetLineIndex_InputtingValueGreaterThanZeroAndLessThanTextRendererLineCount_UpdatesLetterIndexToMinOfCurrentValueAndNewLineLength)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextRenderer> renderer = gameObject.addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();

      renderer->addLine("T");
      renderer->addLine("Test");

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)2, renderer->getLineCount());

      textBox->setLineIndex(1);
      textBox->setLetterIndex(4);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)4, textBox->getLetterIndex());

      textBox->setLineIndex(0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)1, textBox->getLetterIndex());

      textBox->setLineIndex(1);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)1, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Set Letter Index Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_SetLetterIndex_NullTextRenderer_DoesNothing)
    {
      MockTextBox textBox;

      Assert::AreEqual((size_t)0, textBox.getLetterIndex());

      textBox.setLetterIndex(1);

      Assert::AreEqual((size_t)0, textBox.getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_SetLetterIndex_InputtingValueLessThanZero_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextRenderer> renderer = gameObject.addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();
      renderer->addLine("Test");
      renderer->addLine("Test2");

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
      Assert::AreEqual((size_t)4, renderer->getLineLength(0));

      textBox->setLetterIndex(-1);

      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_SetLetterIndex_InputtingValueGreaterThanCurrentLineLength_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextRenderer> renderer = gameObject.addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();
      renderer->addLine("Test");
      renderer->addLine("Test2");

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
      Assert::AreEqual((size_t)4, renderer->getLineLength(0));

      textBox->setLetterIndex(5);

      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_SetLetterIndex_InputtingValueGreaterThanZeroAndLessThanOrEqualToCurrentLineLength_UpdatesLetterIndex)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextRenderer> renderer = gameObject.addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();
      renderer->addLine("Test");
      renderer->addLine("Test2");

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
      Assert::AreEqual((size_t)4, renderer->getLineLength(0));

      textBox->setLetterIndex(2);

      Assert::AreEqual((size_t)2, textBox->getLetterIndex());

      textBox->setLetterIndex(renderer->getLineLength(0));

      Assert::AreEqual(renderer->getLineLength(0), textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Text Inputted Tests
    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_TextInputted_WithNullTextRenderer_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();

      Assert::AreEqual(&gameObject, textBox->getGameObject());
      Assert::AreNotEqual((StringId)0, textBox->getTextInputtedEventHandle_Public());

      Input::charCallback(nullptr, 'a');
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_TextInputted_WhenNotActive_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextRenderer> rendering = gameObject.addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();
      textBox->setActive(false);

      AssertCel::IsNotActive(textBox.get());
      Assert::AreEqual(&gameObject, textBox->getGameObject());
      Assert::AreNotEqual((StringId)0, textBox->getTextInputtedEventHandle_Public());
      Assert::AreEqual((size_t)0, rendering->getLineCount());

      Input::charCallback(nullptr, 'a');

      Assert::AreEqual((size_t)0, rendering->getLineCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_TextInputted_WithTextRenderer_AddsLineIfRendererHasNoText)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual((size_t)1, rendering->getLineCount());

      rendering->removeLine(0);

      Assert::AreEqual((size_t)0, rendering->getLineCount());
      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getTextInputtedEventHandle_Public());

      Input::charCallback(nullptr, 'a');

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("a", rendering->getLine(0).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_TextInputted_WithTextRenderer_AddsCharacterToCorrectLineAndIndexInTextRenderer)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();
      rendering->setLine(0, "Test");
      textBox->setLineIndex(0);
      textBox->setLetterIndex(2);

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getTextInputtedEventHandle_Public());
      Assert::AreEqual((size_t)1, rendering->getLineCount());

      Input::charCallback(nullptr, 'a');

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("Teast", rendering->getLine(0).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_TextInputted_WithTextRenderer_IncreasesLetterIndexByOne)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();
      rendering->setLine(0, "Test");
      textBox->setLineIndex(0);
      textBox->setLetterIndex(2);

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getTextInputtedEventHandle_Public());
      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual((size_t)2, textBox->getLetterIndex());

      Input::charCallback(nullptr, 'a');

      Assert::AreEqual((size_t)3, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Key Down Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_WithNullTextRenderer_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();

      Assert::AreEqual(&gameObject, textBox->getGameObject());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());

      Input::keyCallback(nullptr, GLFW_KEY_ENTER, 0, GLFW_PRESS, 0);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_WhenNotActive_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<MockTextRenderer> rendering = gameObject.addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject.addComponent<MockTextBox>();
      textBox->setActive(false);

      AssertCel::IsNotActive(textBox.get());
      Assert::AreEqual(&gameObject, textBox->getGameObject());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());
      Assert::AreEqual((size_t)0, rendering->getLineCount());

      Input::keyCallback(nullptr, GLFW_KEY_ENTER, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, rendering->getLineCount());

      rendering->addLine("Hello");

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("Hello", rendering->getLine(0).c_str());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("Hello", rendering->getLine(0).c_str());
    }

#pragma region Enter Key Down Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Enter_CaretAtEndOfLine_AddsNewEmptyLineToTextRenderer)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());
      Assert::AreEqual((size_t)1, rendering->getLineCount());

      rendering->setLine(0, "Test");
      textBox->setLetterIndex(4);

      Input::keyCallback(nullptr, GLFW_KEY_ENTER, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)2, rendering->getLineCount());
      Assert::AreEqual("Test", rendering->getLine(0).c_str());
      Assert::AreEqual("", rendering->getLine(1).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Enter_CaretNotAtEndOfLine_AddsAllTextAfterCaretToNewLineInTextRenderer)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());
      Assert::AreEqual((size_t)1, rendering->getLineCount());

      rendering->setLine(0, "Test");
      textBox->setLetterIndex(2);

      Input::keyCallback(nullptr, GLFW_KEY_ENTER, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)2, rendering->getLineCount());
      Assert::AreEqual("Te", rendering->getLine(0).c_str());
      Assert::AreEqual("st", rendering->getLine(1).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Enter_IncrementsLineIndexByOne)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());
      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual((size_t)0, textBox->getLineIndex());

      Input::keyCallback(nullptr, GLFW_KEY_ENTER, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());

      Input::keyCallback(nullptr, GLFW_KEY_ENTER, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)2, textBox->getLineIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Enter_SetsLetterIndexToZero)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());
      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_ENTER, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      rendering->setLine(0, "Test");
      textBox->setLetterIndex(2);

      Input::keyCallback(nullptr, GLFW_KEY_ENTER, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Backspace Key Down Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LineIndexZero_LetterIndexZero_DoesNothing)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());

      rendering->setLine(0, "Hello");

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
      Assert::AreEqual("Hello", rendering->getLine(0).c_str());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("Hello", rendering->getLine(0).c_str());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("Hello", rendering->getLine(0).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LetterIndexGreaterThanZero_DeletesCorrectLetterOfCorrespondingLineFromTextRenderer)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());
      Assert::AreEqual((size_t)1, rendering->getLineCount());

      rendering->setLine(0, "Hello");
      textBox->setLetterIndex(2);

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)2, textBox->getLetterIndex());
      Assert::AreEqual("Hello", rendering->getLine(0).c_str());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("Hllo", rendering->getLine(0).c_str());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("llo", rendering->getLine(0).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LetterIndexGreaterThanZero_DecrementsLetterIndexByOne)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      rendering->setLine(0, "Hello");
      textBox->setLetterIndex(2);

      Assert::AreEqual((size_t)2, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LetterIndexZero_LineIndexGreaterThanZero_EmptyLine_RemovesLineFromRenderer)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();
      
      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());

      rendering->addLine();
      textBox->setLineIndex(1);
      textBox->setLetterIndex(0);

      Assert::AreEqual((size_t)2, rendering->getLineCount());
      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, rendering->getLineCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LetterIndexZero_LineIndexGreaterThanZero_NonEmptyLine_AppendsLineTextToPreviousLine)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());

      rendering->setLine(0, "Test");
      rendering->addLine("Test2");
      textBox->setLineIndex(1);
      textBox->setLetterIndex(0);

      Assert::AreEqual((size_t)2, rendering->getLineCount());
      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("TestTest2", rendering->getLine(0).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LetterIndexZero_LineIndexGreaterThanZero_DecrementsLineIndex)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());

      rendering->addLine();
      textBox->setLineIndex(1);
      textBox->setLetterIndex(0);

      Assert::AreEqual((size_t)2, rendering->getLineCount());
      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LetterIndexZero_LineIndexGreaterThanZero_SetsLetterIndexToLengthOfPreviousLine)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual(gameObject.get(), textBox->getGameObject());
      Assert::AreEqual(&screen, textBox->getGameObject()->getScreen());
      AssertCel::IsActive(rendering->getGameObject()->getScreen());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());

      rendering->setLine(0, "Test");
      rendering->addLine("Test2");
      textBox->setLineIndex(1);
      textBox->setLetterIndex(0);

      Assert::AreEqual((size_t)2, rendering->getLineCount());
      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)4, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Delete Key Down Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Delete_LineIndexMax_LetterIndexMax_DoesNothing)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->addLine("Test");
      textBox->setLineIndex(1);
      textBox->setLetterIndex(4);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)4, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_DELETE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)4, textBox->getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LetterIndexLessThanLineLength_DeletesCorrectLetterOfCorrespondingLineFromTextRenderer)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->addLine("Test");
      textBox->setLineIndex(1);
      textBox->setLetterIndex(2);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)2, textBox->getLetterIndex());
      Assert::AreEqual("Test", rendering->getLine(1).c_str());

      Input::keyCallback(nullptr, GLFW_KEY_DELETE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)2, textBox->getLetterIndex());
      Assert::AreEqual("Tet", rendering->getLine(1).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LetterIndexLineLength_LineIndexZero_LineCountGreaterThanOne_EmptyLine_RemovesNextLineFromRenderer)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      rendering->addLine("");
      textBox->setLineIndex(0);
      textBox->setLetterIndex(4);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)4, textBox->getLetterIndex());
      Assert::AreEqual((size_t)2, rendering->getLineCount());

      Input::keyCallback(nullptr, GLFW_KEY_DELETE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)4, textBox->getLetterIndex());
      Assert::AreEqual((size_t)1, rendering->getLineCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Backspace_LetterIndexLineLength_LineIndexZero_LineCountGreaterThanOne_NonEmptyLine_AppendsNextLineTextToCurrentLine)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      rendering->addLine("Delete");
      textBox->setLineIndex(0);
      textBox->setLetterIndex(4);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)4, textBox->getLetterIndex());
      Assert::AreEqual((size_t)2, rendering->getLineCount());

      Input::keyCallback(nullptr, GLFW_KEY_DELETE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)4, textBox->getLetterIndex());
      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("TestDelete", rendering->getLine(0).c_str());
    }

#pragma endregion

#pragma region Left Key Down Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Left_LineIndexZero_LetterIndexZero_DoesNothing)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_LEFT, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Left_LineIndexGreaterThanZero_LetterIndexZero_DecrementsLineIndex_AndSetsLetterIndexToLengthOfLastLine)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      rendering->addLine("Test 2");
      textBox->setLineIndex(1);
      textBox->setLetterIndex(0);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_LEFT, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)4, textBox->getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Left_LetterIndexNonZero_DecrementsLetterIndex)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      textBox->setLetterIndex(2);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)2, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_LEFT, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)1, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_LEFT, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Up Key Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Up_LineIndexZero_DoesNothing)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_UP, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Up_LineIndexGreaterThanZero_DecrementsLineIndex)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();
      rendering->addLine("Test");
      textBox->setLineIndex(1);
      textBox->setLetterIndex(3);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)3, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_UP, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Right Key Down Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Right_LineIndexMax_LetterIndexMax_DoesNothing)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      rendering->addLine("Test 2");
      textBox->setLineIndex(1);
      textBox->setLetterIndex(6);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)6, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_RIGHT, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)6, textBox->getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Right_LineIndexLessThanMax_LetterIndexLengthOfLine_IncrementsLineIndex_AndSetsLetterIndexToZero)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      rendering->addLine("Test 2");
      textBox->setLineIndex(0);
      textBox->setLetterIndex(4);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)4, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_RIGHT, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Right_LetterIndexNotLengthOfLine_IncrementsLetterIndex)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      textBox->setLetterIndex(1);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)1, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_RIGHT, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)2, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_RIGHT, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)3, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Down Key Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Down_LineIndexIsMax_DoesNothing)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();
      rendering->addLine("Test");
      textBox->setLineIndex(1);
      textBox->setLetterIndex(0);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_DOWN, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Down_LineIndexLessThanMax_IncrementsLineIndex)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();
      rendering->setLine(0, "Test");
      rendering->addLine();
      textBox->setLineIndex(0);
      textBox->setLetterIndex(3);

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
      Assert::AreEqual((size_t)3, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_DOWN, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region Home Key Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_Home_SetsLetterIndexToZero)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      textBox->setLineIndex(0);
      textBox->setLetterIndex(2);

      Assert::AreEqual((size_t)2, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_HOME, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

#pragma endregion

#pragma region End Key Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_KeyPressed_End_SetsLetterIndexToLineLength)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      textBox->setLineIndex(0);
      textBox->setLetterIndex(2);

      Assert::AreEqual((size_t)2, textBox->getLetterIndex());

      Input::keyCallback(nullptr, GLFW_KEY_END, 0, GLFW_PRESS, 0);

      Assert::AreEqual((size_t)4, textBox->getLetterIndex());
    }

#pragma endregion

#pragma endregion

#pragma region Die Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_Die_UnsubscribesFromKeyboardTextInputtedEvent)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();
      rendering->removeLine(0);

      Assert::AreNotEqual((StringId)0, textBox->getTextInputtedEventHandle_Public());
      Assert::AreEqual((size_t)0, rendering->getLineCount());

      textBox->die();
      Input::charCallback(nullptr, 'a');

      Assert::AreEqual((StringId)0, textBox->getTextInputtedEventHandle_Public());
      Assert::AreEqual((size_t)0, rendering->getLineCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_Die_UnsubscribesFromKeyboardKeyPressedEvent)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();
      rendering->setLine(0, "Hello");

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("Hello", rendering->getLine(0).c_str());
      Assert::AreNotEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());

      textBox->die();

      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("Hello", rendering->getLine(0).c_str());

      Input::keyCallback(nullptr, GLFW_KEY_BACKSPACE, 0, GLFW_PRESS, 0);

      Assert::AreEqual((StringId)0, textBox->getKeyPressedEventHandle_Public());
      Assert::AreEqual((size_t)1, rendering->getLineCount());
      Assert::AreEqual("Hello", rendering->getLine(0).c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_Die_SetsLineIndexToZero)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();
      
      rendering->addLine();
      rendering->addLine();
      textBox->setLineIndex(1);

      Assert::AreEqual((size_t)1, textBox->getLineIndex());
      
      textBox->die();

      Assert::AreEqual((size_t)0, textBox->getLineIndex());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(TextBox_Die_SetsLetterIndexToZero)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<MockTextRenderer> rendering = gameObject->addComponent<MockTextRenderer>();
      AutoDeallocator<MockTextBox> textBox = gameObject->addComponent<MockTextBox>();

      rendering->setLine(0, "Test");
      textBox->setLetterIndex(2);

      Assert::AreEqual((size_t)2, textBox->getLetterIndex());

      textBox->die();

      Assert::AreEqual((size_t)0, textBox->getLetterIndex());
    }

#pragma endregion

  };
}