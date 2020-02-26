#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Rendering/MockSpriteBatch.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "Utils/ObjectUtils.h"

using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestSpriteBatch)

#pragma region Render Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteBatch_Render_MatrixInput_AddsRendererAndMatrixToList)
  {
    MockRenderer renderer;
    MockSpriteBatch spriteBatch;

    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    spriteBatch.render(renderer, glm::mat4());

    Assert::AreEqual((size_t)1, spriteBatch.renderers_size_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteBatch_Render_Translation_Rotation_Scale_Input_AddsRendererAndMatrixToList)
  {
    MockRenderer renderer;
    MockSpriteBatch spriteBatch;

    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    spriteBatch.render(renderer, glm::vec3(), 0, glm::vec3(1));

    Assert::AreEqual((size_t)1, spriteBatch.renderers_size_Public());
  }

#pragma endregion

  };
}