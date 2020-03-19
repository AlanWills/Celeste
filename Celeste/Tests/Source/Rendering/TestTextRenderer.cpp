#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Rendering/MockTextRenderer.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::UI;
using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestTextRenderer)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<TextRenderer>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(TextRenderer::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<TextRenderer*>(component));
    Assert::AreEqual(&gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_Constructor_SetsText_ToEmptyString)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::AreEqual("", textRenderer.getText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_Constructor_SetsHorizontalAlignment_TokCentre)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::IsTrue(textRenderer.getHorizontalAlignment() == UI::HorizontalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_Constructor_SetsVerticalAlignment_TokCentre)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::IsTrue(textRenderer.getVerticalAlignment() == VerticalAlignment::kCentre);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_Constructor_SetsDimensions_ToVec2Zero)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::AreEqual(glm::vec2(), textRenderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_Constructor_SetsFontHeightToDefault)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::AreEqual(12.0f, textRenderer.getFont().getHeight());
  }

#pragma endregion

#pragma region Set Font Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithExistentFontPathRawString_UpdatesFontToDefaultHeight)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.setFontHeight(20);

    Assert::AreEqual(20.0f, textRenderer.getFont().getHeight());

    textRenderer.setFont(TestResources::getArialTtfRelativePath().c_str());

    Assert::AreEqual(12.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithExistentFontPathString_UpdatesFontToDefaultHeight)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.setFontHeight(20);

    Assert::AreEqual(20.0f, textRenderer.getFont().getHeight());

    textRenderer.setFont(TestResources::getArialTtfRelativePath());

    Assert::AreEqual(12.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithExistentFontPath_UpdatesFontToDefaultHeight)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.setFontHeight(20);

    Assert::AreEqual(20.0f, textRenderer.getFont().getHeight());

    textRenderer.setFont(Path(TestResources::getArialTtfRelativePath()));

    Assert::AreEqual(12.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithExistentFontPathRawString_AndCustomHeight_UpdatesFontToInputtedHeight)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::AreEqual(12.0f, textRenderer.getFont().getHeight());

    textRenderer.setFont(TestResources::getArialTtfRelativePath().c_str(), 5);

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithExistentFontPathString_AndCustomHeight_UpdatesFontToInputtedHeight)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::AreEqual(12.0f, textRenderer.getFont().getHeight());

    textRenderer.setFont(TestResources::getArialTtfRelativePath(), 5);

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithExistentFontPath_AndCustomHeight_UpdatesFontToInputtedHeight)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::AreEqual(12.0f, textRenderer.getFont().getHeight());

    textRenderer.setFont(Path(TestResources::getArialTtfRelativePath()), 5);

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithNonExistentFontPathRawString_DoesNotChangeCurrentFont)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    textRenderer.setFont(TestResources::getArialTtfRelativePath(), 5.0f);

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());

    textRenderer.setFont("ThisFontDoesn'tExist.ttf");

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithNonExistentFontPathString_DoesNotChangeCurrentFont)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    textRenderer.setFont(TestResources::getArialTtfRelativePath(), 5.0f);

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());

    textRenderer.setFont(std::string("ThisFontDoesn'tExist.ttf"));

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithNonExistentFontPath_DoesNotChangeCurrentFont)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    textRenderer.setFont(TestResources::getArialTtfRelativePath(), 5.0f);

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());

    textRenderer.setFont(Path("ThisFontDoesn'tExist.ttf"));

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithExistentFontPath_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.setText("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.setFont(TestResources::getArialTtfRelativePath().c_str(), textRenderer.getFont().getHeight() * 2);

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFont_WithNonExistentFontPath_DoesNotChangeDimensions)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.setText("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.setFont("WubbaLubbaDubDub", textRenderer.getFont().getHeight() * 2);

    Assert::AreEqual(dimensions, textRenderer.getDimensions());
  }

#pragma endregion

#pragma region Set Font Height Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFontHeight_ChangesFontHeightToInputtedValue)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.setFont(TestResources::getArialTtfRelativePath(), 6.0f);

    Assert::AreEqual(6.0f, textRenderer.getFont().getHeight());

    textRenderer.setFontHeight(10);

    Assert::AreEqual(10.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFontHeight_InputtingInvalidHeight_ChangesFontHeightToZero)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.setFont(TestResources::getArialTtfRelativePath(), 6.0f);

    Assert::AreEqual(6.0f, textRenderer.getFont().getHeight());

    textRenderer.setFontHeight(-10);

    Assert::AreEqual(0.0f, textRenderer.getFont().getHeight());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetFontHeight_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.setText("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.setFontHeight(textRenderer.getFont().getHeight() * 2);

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);
  }

#pragma endregion

#pragma region Horizontal Alignment Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_HorizontalAlignment_kLeft_CalculatesCorrectLineXPosition)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    textRenderer.setHorizontalAlignment(UI::HorizontalAlignment::kLeft);

    Assert::IsTrue(textRenderer.getHorizontalAlignment() == UI::HorizontalAlignment::kLeft);
    Assert::AreEqual(0.0f, textRenderer.getXPosition_Public(50));
    Assert::AreEqual(0.0f, textRenderer.getXPosition_Public(200));
    Assert::AreEqual(0.0f, textRenderer.getXPosition_Public(0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_HorizontalAlignment_kCentre_CalculatesCorrectLineXPosition)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    textRenderer.setHorizontalAlignment(UI::HorizontalAlignment::kCentre);

    Assert::IsTrue(textRenderer.getHorizontalAlignment() == UI::HorizontalAlignment::kCentre);
    Assert::AreEqual(-50.0f, textRenderer.getXPosition_Public(50));
    Assert::AreEqual(-200.0f, textRenderer.getXPosition_Public(200));
    Assert::AreEqual(0.0f, textRenderer.getXPosition_Public(0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_HorizontalAlignment_kRight_CalculatesCorrectLineXPosition)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    textRenderer.setHorizontalAlignment(UI::HorizontalAlignment::kRight);

    Assert::IsTrue(textRenderer.getHorizontalAlignment() == UI::HorizontalAlignment::kRight);
    Assert::AreEqual(-100.0f, textRenderer.getXPosition_Public(50));
    Assert::AreEqual(-400.0f, textRenderer.getXPosition_Public(200));
    Assert::AreEqual(0.0f, textRenderer.getXPosition_Public(0));
  }

#pragma endregion

#pragma region Vertical Alignment Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_VerticalAlignment_kTop_CalculatesCorrectLineXPosition)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    textRenderer.setVerticalAlignment(UI::VerticalAlignment::kTop);

    Assert::IsTrue(textRenderer.getVerticalAlignment() == UI::VerticalAlignment::kTop);
    Assert::AreEqual(0.0f, textRenderer.getYPosition_Public(100));
    Assert::AreEqual(0.0f, textRenderer.getYPosition_Public(200));
    Assert::AreEqual(0.0f, textRenderer.getYPosition_Public(0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_VerticalAlignment_kCentre_CalculatesCorrectLineXPosition)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    textRenderer.setVerticalAlignment(UI::VerticalAlignment::kCentre);

    Assert::IsTrue(textRenderer.getVerticalAlignment() == UI::VerticalAlignment::kCentre);
    Assert::AreEqual(100.0f, textRenderer.getYPosition_Public(100));
    Assert::AreEqual(200.0f, textRenderer.getYPosition_Public(200));
    Assert::AreEqual(0.0f, textRenderer.getYPosition_Public(0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_VerticalAlignment_kBottom_CalculatesCorrectLineXPosition)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    textRenderer.setVerticalAlignment(UI::VerticalAlignment::kBottom);

    Assert::IsTrue(textRenderer.getVerticalAlignment() == UI::VerticalAlignment::kBottom);
    Assert::AreEqual(200.0f, textRenderer.getYPosition_Public(100));
    Assert::AreEqual(400.0f, textRenderer.getYPosition_Public(200));
    Assert::AreEqual(0.0f, textRenderer.getYPosition_Public(0));
  }

#pragma endregion

#pragma region Get Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetDimensions_WithNoText_ReturnsZeroVector)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::AreEqual("", textRenderer.getText().c_str());
    Assert::AreNotEqual(0.0f, textRenderer.getFont().getHeight());
    Assert::AreEqual(glm::zero<glm::vec2>(), textRenderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetDimensions_WithFont_SingleLineOfText_ReturnsMeasuredString)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    observer_ptr<Font> font = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath());
    textRenderer.setFont(TestResources::getArialTtfRelativePath(), 5);
    textRenderer.setText("Hello");

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());
    Assert::AreEqual(font->createInstance(5).measureString("Hello"), textRenderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetDimensions_WithFont_MultipleLinesOfText_ReturnsMeasuredString)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    observer_ptr<Font> font = getResourceManager().load<Font>(TestResources::getArialTtfRelativePath());
    textRenderer.setFont(TestResources::getArialTtfRelativePath(), 5);
    textRenderer.setText("Hello");

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());
    Assert::AreEqual(font->createInstance(5).measureString("Hello"), textRenderer.getDimensions());
  }

#pragma endregion

#pragma region Set Text Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingEmptyString_RemovesAllText)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.setText("Test");

    Assert::AreEqual("Test", renderer.getText().c_str());

    renderer.setText("");

    Assert::AreEqual("", renderer.getText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingEmptyString_SetsDimensionsToZero)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.setText("Test");

    Assert::AreNotEqual(glm::vec2(), renderer.getDimensions());

    renderer.setText("");

    Assert::AreEqual(glm::vec2(), renderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingNonEmptyString_OneLine_SetsTextCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.setText("Test");

    Assert::AreEqual("Test", renderer.getText().c_str());

    renderer.setText("WubbaLubbaDubDub");

    Assert::AreEqual("WubbaLubbaDubDub", renderer.getText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingNonEmptyString_OneLine_SetsDimensionsToCorrectValue)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.setText("Test");

    Assert::AreEqual(renderer.getFont().measureString("Test"), renderer.getDimensions());

    renderer.setText("WubbaLubbaDubDub");

    Assert::AreEqual(renderer.getFont().measureString("WubbaLubbaDubDub"), renderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingNonEmptyString_MultipleLines_SetsTextCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.setText("Test");

    Assert::AreEqual("Test", renderer.getText().c_str());

    renderer.setText("Wubba\nLubba\nDub\nDub");

    Assert::AreEqual("Wubba\nLubba\nDub\nDub", renderer.getText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingNonEmptyString_MultipleLines_SetsDimensionsToCorrectValue)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.setText("Test");

    Assert::AreEqual(renderer.getFont().measureString("Test"), renderer.getDimensions());

    renderer.setText("Wubba\nLubba\nDub\nDub");

    Assert::AreEqual(renderer.getFont().measureString("Wubba\nLubba\nDub\nDub"), renderer.getDimensions());
  }

#pragma endregion

  };
}