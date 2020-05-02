#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Rendering/MockSpriteBatch.h"
#include "Mocks/Rendering/MockRenderer.h"

#include "Objects/GameObject.h"

using namespace Celeste;
using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestSpriteBatch)

#pragma region Render Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteBatch_Render_MatrixInput_AddsRendererAndMatrixToList)
  {
    GameObject gameObject;
    MockRenderer renderer(gameObject);
    MockSpriteBatch spriteBatch;

    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    spriteBatch.render(renderer, glm::identity<glm::mat4>());

    Assert::AreEqual((size_t)1, spriteBatch.renderers_size_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteBatch_Render_Translation_Rotation_Scale_Input_AddsRendererAndMatrixToList)
  {
    GameObject gameObject;
    MockRenderer renderer(gameObject);
    MockSpriteBatch spriteBatch;

    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    spriteBatch.render(renderer, glm::vec3(), 0, glm::vec3(1));

    Assert::AreEqual((size_t)1, spriteBatch.renderers_size_Public());
  }

#pragma endregion

  };
}