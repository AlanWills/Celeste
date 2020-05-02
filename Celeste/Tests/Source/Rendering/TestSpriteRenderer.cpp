#define NOMINMAX

#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"
#include "Registries/ComponentRegistry.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste::Resources;
using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestSpriteRenderer)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<SpriteRenderer>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(SpriteRenderer::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<SpriteRenderer*>(component));
    Assert::AreEqual(&gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_Constructor_SetsTextureToNull)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    Assert::IsNull(renderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_Constructor_SetsDimensionsToZero)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    Assert::AreEqual(glm::vec2(), renderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_Constructor_SetsIsPreserveAspectRatio_ToFalse)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    Assert::IsFalse(renderer.isPreservingAspectRatio());
  }

#pragma endregion

#pragma region Set Texture Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetTexture_WithValidTexture_SetsCurrentTexture)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer.setTexture(texture);

    Assert::IsTrue(texture == renderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetTexture_WithValidTexture_AndTextureAlreadySet_UpdatesTexture)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer.setTexture(texture);

    Assert::IsTrue(texture == renderer.getTexture());

    observer_ptr<Texture2D> texture2 = getResourceManager().load<Texture2D>(TestResources::getContainerJpgRelativePath());
    renderer.setTexture(texture2);

    Assert::IsTrue(texture2 == renderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetTexture_InputtingNullTexture_SetsCurrentTextureToNullptr)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer.setTexture(texture);

    Assert::IsTrue(texture == renderer.getTexture());

    renderer.setTexture(nullptr);

    Assert::IsNull(renderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetTexture_ExistentTexturePath_SetsCurrentTexture)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer.setTexture(TestResources::getBlockPngRelativePath());

    Assert::IsTrue(texture == renderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetTexture_ExistentTexturePath_AndTextureAlreadySet_UpdatesTexture)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer.setTexture(TestResources::getBlockPngRelativePath());

    Assert::IsTrue(texture == renderer.getTexture());

    observer_ptr<Texture2D> texture2 = getResourceManager().load<Texture2D>(TestResources::getContainerJpgRelativePath());
    renderer.setTexture(TestResources::getContainerJpgRelativePath());

    Assert::IsTrue(texture2 == renderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetTexture_NonExistentTexturePath_SetsCurrentTextureToNullptr)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer.setTexture(TestResources::getBlockPngRelativePath());

    Assert::IsTrue(texture == renderer.getTexture());

    renderer.setTexture("ThisTextureShouldn'tExist.png");

    Assert::IsNull(renderer.getTexture());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetTexture_DimensionsZero_SetsDimensionsToTextureDimensions)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    Assert::AreEqual(glm::vec2(), renderer.getDimensions());

    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer.setTexture(TestResources::getBlockPngRelativePath());

    Assert::AreEqual(texture->getDimensions(), renderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetTexture_DimensionsNonZero_DoesNotChangeDimensions)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);
    renderer.setDimensions(400, 200);

    Assert::AreEqual(glm::vec2(400, 200), renderer.getDimensions());

    renderer.setTexture(TestResources::getBlockPngRelativePath());

    Assert::AreEqual(glm::vec2(400, 200), renderer.getDimensions());
  }

#pragma endregion

#pragma region Set Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetDimensions_TextureNull_SetsDimensionsToInput)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);

    Assert::IsNull(renderer.getTexture());

    renderer.setDimensions(100, 200);

    Assert::AreEqual(glm::vec2(100, 200), renderer.getDimensions());

    renderer.setDimensions(500, 140);

    Assert::AreEqual(glm::vec2(500, 140), renderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetDimensions_NotPreservingAspectRatio_SetsDimensionsToInput)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);
    renderer.setTexture(TestResources::getBlockPngFullPath().as_string());

    Assert::IsNotNull(renderer.getTexture());
    Assert::IsFalse(renderer.isPreservingAspectRatio());

    renderer.setDimensions(100, 200);

    Assert::AreEqual(glm::vec2(100, 200), renderer.getDimensions());

    renderer.setDimensions(500, 140);

    Assert::AreEqual(glm::vec2(500, 140), renderer.getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_SetDimensions_PreservingAspectRatio_SetsDimensionsToValuesThatPreserveAspectRatio)
  {
    GameObject gameObject;
    MockSpriteRenderer renderer(gameObject);
    renderer.shouldPreserveAspectRatio(RatioMode::kPreserveAspectRatio);

    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getContainerJpgFullPath().as_string());
    const glm::vec2& textureDims = texture->getDimensions();
    renderer.setTexture(texture);

    Assert::IsNotNull(renderer.getTexture());
    Assert::IsTrue(renderer.isPreservingAspectRatio());

    renderer.setDimensions(100, 100);

    Assert::AreEqual(textureDims * std::min(100.0f / textureDims.x, 100.0f / textureDims.y), renderer.getDimensions());

    renderer.setDimensions(500, 140);

    Assert::AreEqual(textureDims * std::min(500 / textureDims.x, 140.0f / textureDims.y), renderer.getDimensions());
  }

#pragma endregion

#pragma region Render Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SpriteRenderer_Render_WithNoTextureSet_DoesNothing)
  {
    GameObject gameObject;
    SpriteRenderer renderer(gameObject);
    Program program;

    Assert::IsNull(renderer.getTexture());

    renderer.render(program, glm::identity<glm::mat4>());
  }

#pragma endregion

  };
}