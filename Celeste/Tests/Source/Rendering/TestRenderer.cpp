#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Objects/GameObject.h"
#include "Mocks/Rendering/MockRenderer.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestRenderer)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Renderer_Constructor_SetsColourToWhite)
  {
    GameObject gameObject;
    MockRenderer renderer(gameObject);

    Assert::AreEqual(glm::vec4(1), renderer.getColour());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Renderer_Constructor_SetsOriginTo_ZeroPointFive_ZeroPointFive)
  {
    GameObject gameObject;
    MockRenderer renderer(gameObject);

    Assert::AreEqual(glm::vec2(0.5f), renderer.getOrigin());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Renderer_Constructor_SetsScissorRectangleToEmptyRectangle)
  {
    GameObject gameObject;
    MockRenderer renderer(gameObject);

    Assert::AreEqual(glm::vec2(), renderer.getScissorRectangle().getDimensions());
    Assert::AreEqual(glm::vec2(), renderer.getScissorRectangle().getCentre());
  }

#pragma endregion

#pragma region Set Colour Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Renderer_SetColour_InputtingThreeFloats_UpdatesRGBValues)
  {
    GameObject gameObject;
    MockRenderer renderer(gameObject);
    renderer.setColour(0.2f, 0.2f, 0.2f, 0.2f);

    Assert::AreEqual(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f), renderer.getColour());

    renderer.setColour(0.5f, 0.4f, 0.3f);

    Assert::AreEqual(0.5f, renderer.getColour().r);
    Assert::AreEqual(0.4f, renderer.getColour().g);
    Assert::AreEqual(0.3f, renderer.getColour().b);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Renderer_SetColour_InputtingThreeFloats_KeepsAlphaTheSame)
  {
    GameObject gameObject;
    MockRenderer renderer(gameObject);
    renderer.setColour(0.2f, 0.2f, 0.2f, 0.2f);

    Assert::AreEqual(0.2f, renderer.getColour().a);

    renderer.setColour(0.5f, 0.4f, 0.3f);

    Assert::AreEqual(0.2f, renderer.getColour().a);
  }

#pragma endregion

#pragma region Set Opacity Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Renderer_SetOpacity_ChangesColourAlphaValue)
  {
    GameObject gameObject;
    MockRenderer renderer(gameObject);

    float current = renderer.getOpacity();
    renderer.setOpacity((current + 1) * 0.5f);

    Assert::AreEqual((current + 1) * 0.5f, renderer.getOpacity());
  }

#pragma endregion

  };
}