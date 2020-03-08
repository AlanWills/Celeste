#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Rendering/MockTextRenderer.h"
#include "Resources/ResourceManager.h"
#include "Resources/TestResources.h"
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
  TEST_METHOD(TextRenderer_Constructor_SetsLines_ToEmptyVector)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);

    Assert::AreEqual((size_t)0, textRenderer.getLineCount());
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
    textRenderer.addLine("Test");

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
    textRenderer.addLine("Test");

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
    textRenderer.addLine("Test");

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

    Assert::AreEqual((size_t)0, textRenderer.getLineCount());
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
    textRenderer.addLine("Hello");

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
    textRenderer.addLine("Hello");

    Assert::AreEqual(5.0f, textRenderer.getFont().getHeight());
    Assert::AreEqual(font->createInstance(5).measureString("Hello"), textRenderer.getDimensions());
  }

#pragma endregion

#pragma region Set Text Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingEmptyString_RemovesAllLines)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());

    renderer.setText("");

    Assert::AreEqual((size_t)0, renderer.getLineCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingEmptyString_SetsDimensionsToZero)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreNotEqual(glm::vec2(), renderer.getDimensions());

    renderer.setText("");

    Assert::AreEqual(glm::vec2(), renderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingNonEmptyString_OneLine_SetsLinesCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.setText("WubbaLubbaDubDub");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("WubbaLubbaDubDub", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingNonEmptyString_OneLine_SetsDimensionsToCorrectValue)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual(renderer.getFont().measureString("Test"), renderer.getLineDimensions(0));

    renderer.setText("WubbaLubbaDubDub");

    Assert::AreEqual(renderer.getFont().measureString("WubbaLubbaDubDub"), renderer.getLineDimensions(0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingNonEmptyString_MultipleLines_SetsLinesCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.setText("Wubba\nLubba\nDub\nDub");

    Assert::AreEqual((size_t)4, renderer.getLineCount());
    Assert::AreEqual("Wubba", renderer.getLine(0).c_str());
    Assert::AreEqual("Lubba", renderer.getLine(1).c_str()); 
    Assert::AreEqual("Dub", renderer.getLine(2).c_str());
    Assert::AreEqual("Dub", renderer.getLine(3).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetText_InputtingNonEmptyString_MultipleLines_SetsDimensionsToCorrectValue)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual(renderer.getFont().measureString("Test"), renderer.getLineDimensions(0));

    renderer.setText("Wubba\nLubba\nDub\nDub");

    Assert::AreEqual(renderer.getFont().measureString("Wubba"), renderer.getLineDimensions(0));
    Assert::AreEqual(renderer.getFont().measureString("Lubba"), renderer.getLineDimensions(1));
    Assert::AreEqual(renderer.getFont().measureString("Dub"), renderer.getLineDimensions(2));
    Assert::AreEqual(renderer.getFont().measureString("Dub"), renderer.getLineDimensions(3));
  }

#pragma endregion

#pragma region Clear Lines Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ClearLines_WithNoLines_DoesNothing)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.clearLines();

    Assert::AreEqual((size_t)0, renderer.getLineCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ClearLines_WithLines_RemovesAllLines)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine();

    Assert::AreEqual((size_t)2, renderer.getLineCount());

    renderer.clearLines();

    Assert::AreEqual((size_t)0, renderer.getLineCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ClearLines_SetsDimensionsToVec2Zero)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    Assert::AreNotEqual(glm::vec2(), textRenderer.getDimensions());

    textRenderer.clearLines();

    Assert::AreEqual(glm::vec2(), textRenderer.getDimensions());
  }

#pragma endregion

#pragma region Reset Lines Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ResetLines_NoLines_InputtingEmptyString_SetsRendererToOneEmptyLine)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.resetLines();

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ResetLines_WithLines_InputtingEmptyString_SetsRendererToOneEmptyLine)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.resetLines();

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ResetLines_NoLines_InputtingSingleString_SetsRendererToOneLineContainingString)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.resetLines("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ResetLines_WithLines_InputtingSingleString_SetsRendererToOneLineContainingString)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.resetLines("WubbaLubbaDubDub");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("WubbaLubbaDubDub", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ResetLines_NoLines_InputtingVectorOfStrings_SetsRendererToMultipleLinesContainingString)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    std::vector<std::string> strings
    {
      "Test",
      "Test2"
    };
    renderer.resetLines(strings);

    Assert::AreEqual((size_t)2, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
    Assert::AreEqual("Test2", renderer.getLine(1).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ResetLines_WithLines_InputtingVectorOfString_SetsRendererToMultipleLinesContainingString)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("One");
    renderer.addLine("Two");

    Assert::AreEqual((size_t)2, renderer.getLineCount());
    Assert::AreEqual("One", renderer.getLine(0).c_str());
    Assert::AreEqual("Two", renderer.getLine(1).c_str());

    std::vector<std::string> strings
    {
      "Test",
      "Test2"
    };
    renderer.resetLines(strings);

    Assert::AreEqual((size_t)2, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
    Assert::AreEqual("Test2", renderer.getLine(1).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ResetLines_NoLines_SetsDimensionsToVec2Zero)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.resetLines(std::vector<std::string>());

    Assert::AreEqual(glm::vec2(), textRenderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_ResetLines_WithLines_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.resetLines(std::vector<std::string>
    {
      "Test2",
      "WubbaLubbaDubDub"
    });

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("WubbaLubbaDubDub").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight() * 2, textRenderer.getDimensions().y);
  }

#pragma endregion

#pragma region Add Lines Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLines_InputtingVectorOfStrings_AppendsLinesToLinesList)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    std::vector<std::string> strings
    {
      "Test",
      "Test2"
    };
    renderer.addLines(strings);

    Assert::AreEqual((size_t)2, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
    Assert::AreEqual("Test2", renderer.getLine(1).c_str());

    renderer.addLines(strings);

    Assert::AreEqual((size_t)4, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(2).c_str());
    Assert::AreEqual("Test2", renderer.getLine(3).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLines_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.addLines(std::vector<std::string>
    {
      "Test2",
      "WubbaLubbaDubDub"
    });

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("WubbaLubbaDubDub").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight() * 3, textRenderer.getDimensions().y);
  }

#pragma endregion

#pragma region Add Line Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLine_NoInput_AppendsEmptyLineToLinesList)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.addLine();

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLine_TextInput_AppendsTextToLinesList)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.addLine("Test ");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test ", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLine_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.addLine("WubbaLubbaDubDub");

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("WubbaLubbaDubDub").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight() * 2, textRenderer.getDimensions().y);
  }

#pragma endregion

#pragma region Remove Line Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_RemoveLine_InputtingValueGreaterThanOrEqualToLineCount_DoesNothing)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.addLine();

    Assert::AreEqual((size_t)1, renderer.getLineCount());
      
    renderer.removeLine(5);

    Assert::AreEqual((size_t)1, renderer.getLineCount());

    renderer.removeLine(renderer.getLineCount());

    Assert::AreEqual((size_t)1, renderer.getLineCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_RemoveLine_InputtingValueLessThanLineCount_RemovesLine)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.addLine();
    renderer.addLine();

    Assert::AreEqual((size_t)2, renderer.getLineCount());

    renderer.removeLine(1);

    Assert::AreEqual((size_t)1, renderer.getLineCount());

    renderer.removeLine(0);

    Assert::AreEqual((size_t)0, renderer.getLineCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_RemoveLine_NoLinesLeft_SetsDimensionsToVec2Zero)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.removeLine(0);

    Assert::AreEqual(glm::vec2(), textRenderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_RemoveLine_LinesLeft_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");
    textRenderer.addLine("WubbaLubbaDubDub");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("WubbaLubbaDubDub").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight() * 2, textRenderer.getDimensions().y);

    textRenderer.removeLine(1);

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);
  }

#pragma endregion

#pragma region Set Line Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetLine_InputtingValueGreaterThanOrEqualToLineCount_DoesNothing)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.addLine();

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(0).c_str());

    renderer.setLine(5, "Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(0).c_str());

    renderer.setLine(renderer.getLineCount(), "Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetLine_InputtingValueLessThanLineCount_ChangesLineText)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.addLine();
    renderer.addLine();

    Assert::AreEqual((size_t)2, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(0).c_str());
    Assert::AreEqual("", renderer.getLine(1).c_str());

    renderer.setLine(1, "Test");

    Assert::AreEqual((size_t)2, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(0).c_str());
    Assert::AreEqual("Test", renderer.getLine(1).c_str());

    renderer.setLine(0, "Test    ");

    Assert::AreEqual((size_t)2, renderer.getLineCount());
    Assert::AreEqual("Test    ", renderer.getLine(0).c_str());
    Assert::AreEqual("Test", renderer.getLine(1).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetLine_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.setLine(0, "WubbaLubbaDubDub");

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("WubbaLubbaDubDub").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);
  }

#pragma endregion

#pragma region Get Line Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLine_InputtingValueGreaterThanOrEqualToLineCount_ReturnsEmptyString)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(renderer.getLineCount()).c_str());
    Assert::AreEqual("", renderer.getLine(5).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLine_InputtingValueGreaterThanOrEqualToLineCount_AppendsNothingString)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    std::string text;

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.getLine(renderer.getLineCount(), text);

    Assert::AreEqual("", text.c_str());

    renderer.getLine(5, text);

    Assert::AreEqual("", text.c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLine_InputtingValueLessThanLineCount_ReturnsLineText)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("   Wasd");

    Assert::AreEqual((size_t)2, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
    Assert::AreEqual("   Wasd", renderer.getLine(1).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLine_InputtingValueLessThanLineCount_AppendsLineText)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("   Wasd");

    std::string text;

    Assert::AreEqual((size_t)2, renderer.getLineCount());

    renderer.getLine(0, text);

    Assert::AreEqual("Test", text.c_str());

    text.clear();
    renderer.getLine(1, text);

    Assert::AreEqual("   Wasd", text.c_str());
  }

#pragma endregion

#pragma region Get Line Count Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLineCount_Returns_NumberOfLinesInRenderer)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());

    renderer.addLine();

    Assert::AreEqual((size_t)1, renderer.getLineCount());

    renderer.addLine();

    Assert::AreEqual((size_t)2, renderer.getLineCount());
  }

#pragma endregion

#pragma region Get Line Length Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLineLength_InputtingValueGreaterThanOrEqualToLineCount_ReturnsZero)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());
    Assert::AreEqual((size_t)0, renderer.getLineLength(renderer.getLineCount()));
    Assert::AreEqual((size_t)0, renderer.getLineLength(5));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLineLength_InputtingLessThanLineCount_ReturnsNumberOfCharactersInLine)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine();
    renderer.addLine("Test");

    Assert::AreEqual((size_t)2, renderer.getLineCount());
    Assert::AreEqual((size_t)0, renderer.getLineLength(0));
    Assert::AreEqual((size_t)4, renderer.getLineLength(1));
  }

#pragma endregion

#pragma region Get Line Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLineDimensions_InputtingValueGreaterThanOrEqualToLineCount_ReturnsZeroVector)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);

    Assert::AreEqual((size_t)0, renderer.getLineCount());
    Assert::AreEqual(glm::vec2(), renderer.getLineDimensions(renderer.getLineCount()));
    Assert::AreEqual(glm::vec2(), renderer.getLineDimensions(5));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLineDimensions_InputtingValueLessThanLineCount_EmptyLine_Returns_Zero_FontHeight)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.setFontHeight(5);
    renderer.addLine();

    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("", renderer.getLine(0).c_str());
    Assert::AreEqual(glm::vec2(0, 5), renderer.getLineDimensions(0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLineDimensions_InputtingValueLessThanLineCount_NonEmptyLine_Returns_Width_FontHeight)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.setFontHeight(5);
    renderer.addLine("Test");

    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
    Assert::AreEqual(glm::vec2(renderer.getFont().measureString("Test").x, 5), renderer.getLineDimensions(0));
  }

#pragma endregion

#pragma region Add Letter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLetter_InputtingLineIndexGreaterThanOrEqualToLineCount_DoesNothing)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.addLetter(renderer.getLineCount(), 0, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.addLetter(5, 0, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLetter_InputtingLineIndexLessThanLineCount_AndLetterIndexGreaterThanLineLength_DoesNothing)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.addLetter(0, 5, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLetter_InputtingLineIndexLessThanLineCount_AndLetterIndexEqualToLineLength_AppendsCharacter)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.addLetter(0, 4, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Testa", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLetter_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanLineLength_InsertsCharacter)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.addLetter(0, 2, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Teast", renderer.getLine(0).c_str());

    renderer.addLetter(0, 0, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("aTeast", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_AddLetter_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.addLetter(0, 4, '2');

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("Test2").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);
  }

#pragma endregion

#pragma region Remove Letter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_RemoveLetter_InputtingLineIndexGreaterThanOrEqualToLineCount_DoesNothing)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.removeLetter(renderer.getLineCount(), 0);

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.removeLetter(5, 0);

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_RemoveLetter_InputtingLineIndexLessThanLineCount_AndLetterIndexGreaterThanOrEqualToLineLength_DoesNothing)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.removeLetter(0, 5);

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.removeLetter(0, renderer.getLineLength(0));

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_RemoveLetter_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanLineLength_RemovesCharacter)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.removeLetter(0, 0);

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("est", renderer.getLine(0).c_str());

    renderer.removeLetter(0, renderer.getLineLength(0) - 1);

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("es", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_RemoveLetter_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.removeLetter(0, 3);

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("Tes").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);
  }

#pragma endregion

#pragma region Set Letter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetLetter_InputtingLineIndexGreaterThanOrEqualToLineCount_DoesNothing)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.setLetter(renderer.getLineCount(), 0, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.setLetter(5, 0, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetLetter_InputtingLineIndexLessThanLineCount_AndLetterIndexGreaterThanOrEqualToLineLength_DoesNothing)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.setLetter(0, 5, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.setLetter(0, renderer.getLineLength(0), 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetLetter_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanLineLength_ChangesCharacter)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());

    renderer.setLetter(0, 1, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Tast", renderer.getLine(0).c_str());

    renderer.setLetter(0, 0, 'a');

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("aast", renderer.getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_SetLetter_UpdatesDimensionsCorrectly)
  {
    GameObject gameObject;
    MockTextRenderer textRenderer(gameObject);
    textRenderer.addLine("Test");

    glm::vec2 dimensions = textRenderer.getDimensions();

    Assert::AreEqual(textRenderer.getFont().measureString("Test").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);

    textRenderer.setLetter(0, 3, 's');

    Assert::AreNotEqual(dimensions, textRenderer.getDimensions());
    Assert::AreEqual(textRenderer.getFont().measureString("Tess").x, textRenderer.getDimensions().x);
    Assert::AreEqual(textRenderer.getFont().getHeight(), textRenderer.getDimensions().y);
  }

#pragma endregion

#pragma region Get Letter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetter_InputtingLineIndexGreaterThanOrEqualToLineCount_Returns_NegativeOne)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
    Assert::AreEqual((char)-1, renderer.getLetter(renderer.getLineCount(), 0));
    Assert::AreEqual((char)-1, renderer.getLetter(5, 0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetter_InputtingLineIndexLessThanLineCount_AndLetterIndexGreaterThanOrEqualToLineLength_Returns_NegativeOne)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
    Assert::AreEqual((char)-1, renderer.getLetter(0, 5));
    Assert::AreEqual((char)-1, renderer.getLetter(0, renderer.getLineLength(0)));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetter_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanLineLength_ReturnsCharacter)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual("Test", renderer.getLine(0).c_str());
    Assert::AreEqual('e', renderer.getLetter(0, 1));
    Assert::AreEqual('t', renderer.getLetter(0, 3));
  }

#pragma endregion

#pragma region Get Letter Offset Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexGreaterThanOrEqualToLineCount_ReturnsZeroVector)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine();

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual(glm::vec2(), renderer.getLetterOffset(renderer.getLineCount(), 0));
    Assert::AreEqual(glm::vec2(), renderer.getLetterOffset(renderer.getLineCount(), 0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexGreaterThanLineLength_ReturnsZeroVector)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");

    Assert::AreEqual((size_t)1, renderer.getLineCount());
    Assert::AreEqual(glm::vec2(), renderer.getLetterOffset(0, 5));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanOrEqualToLineLength_kLeft_kTop_ReturnsCorrectOffset)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("Test2");
    renderer.setHorizontalAlignment(UI::HorizontalAlignment::kLeft);
    renderer.setVerticalAlignment(UI::VerticalAlignment::kTop);
    renderer.setFontHeight(5);

    Assert::IsTrue(renderer.getHorizontalAlignment() == UI::HorizontalAlignment::kLeft);
    Assert::IsTrue(renderer.getVerticalAlignment() == UI::VerticalAlignment::kTop);
    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec2(renderer.getFont().measureString("T").x, 0), renderer.getLetterOffset(0, 1));
    Assert::AreEqual(glm::vec2(renderer.getFont().measureString("Test").x, -5), renderer.getLetterOffset(1, 4));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanOrEqualToLineLength_kLeft_kCentre_ReturnsCorrectOffset)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("Test2");
    renderer.setHorizontalAlignment(UI::HorizontalAlignment::kLeft);
    renderer.setVerticalAlignment(UI::VerticalAlignment::kCentre);
    renderer.setFontHeight(5);

    Assert::IsTrue(renderer.getHorizontalAlignment() == UI::HorizontalAlignment::kLeft);
    Assert::IsTrue(renderer.getVerticalAlignment() == UI::VerticalAlignment::kCentre);
    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec2(renderer.getFont().measureString("T").x, 5), renderer.getLetterOffset(0, 1));
    Assert::AreEqual(glm::vec2(renderer.getFont().measureString("Test").x, 0), renderer.getLetterOffset(1, 4));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanOrEqualToLineLength_kLeft_kBottom_ReturnsCorrectOffset)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("Test2");
    renderer.setHorizontalAlignment(UI::HorizontalAlignment::kLeft);
    renderer.setVerticalAlignment(UI::VerticalAlignment::kBottom);
    renderer.setFontHeight(5);

    Assert::IsTrue(renderer.getHorizontalAlignment() == UI::HorizontalAlignment::kLeft);
    Assert::IsTrue(renderer.getVerticalAlignment() == UI::VerticalAlignment::kBottom);
    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec2(renderer.getFont().measureString("T").x, 10), renderer.getLetterOffset(0, 1));
    Assert::AreEqual(glm::vec2(renderer.getFont().measureString("Test").x, 5), renderer.getLetterOffset(1, 4));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanOrEqualToLineLength_kCentre_kTop_ReturnsCorrectOffset)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("Test2");
    renderer.setHorizontalAlignment(UI::HorizontalAlignment::kCentre);
    renderer.setVerticalAlignment(UI::VerticalAlignment::kTop);
    renderer.setFontHeight(5);

    const FontInstance& font = renderer.getFont();

    Assert::IsTrue(renderer.getHorizontalAlignment() == UI::HorizontalAlignment::kCentre);
    Assert::IsTrue(renderer.getVerticalAlignment() == UI::VerticalAlignment::kTop);
    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec2(font.measureString("T").x - font.measureString("Test").x * 0.5f, 0), renderer.getLetterOffset(0, 1));
    Assert::AreEqual(glm::vec2(font.measureString("Test").x - font.measureString("Test2").x * 0.5f, -5), renderer.getLetterOffset(1, 4));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanOrEqualToLineLength_kCentre_kCentre_ReturnsCorrectOffset)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("Test2");
    renderer.setHorizontalAlignment(UI::HorizontalAlignment::kCentre);
    renderer.setVerticalAlignment(UI::VerticalAlignment::kCentre);
    renderer.setFontHeight(5);

    const FontInstance& font = renderer.getFont();

    Assert::IsTrue(renderer.getHorizontalAlignment() == UI::HorizontalAlignment::kCentre);
    Assert::IsTrue(renderer.getVerticalAlignment() == UI::VerticalAlignment::kCentre);
    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec2(font.measureString("T").x - font.measureString("Test").x * 0.5f, 5), renderer.getLetterOffset(0, 1));
    Assert::AreEqual(glm::vec2(font.measureString("Test").x - font.measureString("Test2").x * 0.5f, 0), renderer.getLetterOffset(1, 4));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanOrEqualToLineLength_kCentre_kBottom_ReturnsCorrectOffset)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("Test2");
    renderer.setHorizontalAlignment(UI::HorizontalAlignment::kCentre);
    renderer.setVerticalAlignment(UI::VerticalAlignment::kBottom);
    renderer.setFontHeight(5);

    const FontInstance& font = renderer.getFont();

    Assert::IsTrue(renderer.getHorizontalAlignment() == UI::HorizontalAlignment::kCentre);
    Assert::IsTrue(renderer.getVerticalAlignment() == UI::VerticalAlignment::kBottom);
    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec2(font.measureString("T").x - font.measureString("Test").x * 0.5f, 10), renderer.getLetterOffset(0, 1));
    Assert::AreEqual(glm::vec2(font.measureString("Test").x - font.measureString("Test2").x * 0.5f, 5), renderer.getLetterOffset(1, 4));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanOrEqualToLineLength_kRight_kTop_ReturnsCorrectOffset)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("Test2");
    renderer.setHorizontalAlignment(UI::HorizontalAlignment::kRight);
    renderer.setVerticalAlignment(UI::VerticalAlignment::kTop);
    renderer.setFontHeight(5);

    const FontInstance& font = renderer.getFont();

    Assert::IsTrue(renderer.getHorizontalAlignment() == UI::HorizontalAlignment::kRight);
    Assert::IsTrue(renderer.getVerticalAlignment() == UI::VerticalAlignment::kTop);
    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec2(font.measureString("T").x - font.measureString("Test").x, 0), renderer.getLetterOffset(0, 1));
    Assert::AreEqual(glm::vec2(font.measureString("Test").x - font.measureString("Test2").x, -5), renderer.getLetterOffset(1, 4));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanOrEqualToLineLength_kRight_kCentre_ReturnsCorrectOffset)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("Test2");
    renderer.setHorizontalAlignment(UI::HorizontalAlignment::kRight);
    renderer.setVerticalAlignment(UI::VerticalAlignment::kCentre);
    renderer.setFontHeight(5);

    const FontInstance& font = renderer.getFont();

    Assert::IsTrue(renderer.getHorizontalAlignment() == UI::HorizontalAlignment::kRight);
    Assert::IsTrue(renderer.getVerticalAlignment() == UI::VerticalAlignment::kCentre);
    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec2(font.measureString("T").x - font.measureString("Test").x, 5), renderer.getLetterOffset(0, 1));
    Assert::AreEqual(glm::vec2(font.measureString("Test").x - font.measureString("Test2").x, 0), renderer.getLetterOffset(1, 4));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextRenderer_GetLetterOffset_InputtingLineIndexLessThanLineCount_AndLetterIndexLessThanOrEqualToLineLength_kRight_kBottom_ReturnsCorrectOffset)
  {
    GameObject gameObject;
    MockTextRenderer renderer(gameObject);
    renderer.addLine("Test");
    renderer.addLine("Test2");
    renderer.setHorizontalAlignment(UI::HorizontalAlignment::kRight);
    renderer.setVerticalAlignment(UI::VerticalAlignment::kBottom);
    renderer.setFontHeight(5);

    const FontInstance& font = renderer.getFont();

    Assert::IsTrue(renderer.getHorizontalAlignment() == UI::HorizontalAlignment::kRight);
    Assert::IsTrue(renderer.getVerticalAlignment() == UI::VerticalAlignment::kBottom);
    Assert::AreEqual(5.0f, renderer.getFontHeight());
    Assert::AreEqual(glm::vec2(font.measureString("T").x - font.measureString("Test").x, 10), renderer.getLetterOffset(0, 1));
    Assert::AreEqual(glm::vec2(font.measureString("Test").x - font.measureString("Test2").x, 5), renderer.getLetterOffset(1, 4));
  }

#pragma endregion

  };
}