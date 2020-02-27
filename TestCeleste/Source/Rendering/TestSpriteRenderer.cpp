#define NOMINMAX

#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "Resources/ResourceManager.h"
#include "Resources/TestResources.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"

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

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(SpriteRenderer::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<SpriteRenderer*>(component.get()));
      Assert::AreEqual(&gameObject, component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_Constructor_SetsTextureToNull)
    {
      MockSpriteRenderer renderer;

      Assert::IsNull(renderer.getTexture());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_Constructor_SetsDimensionsToZero)
    {
      MockSpriteRenderer renderer;

      Assert::AreEqual(glm::vec2(), renderer.getDimensions());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_Constructor_SetsIsPreserveAspectRatio_ToFalse)
    {
      MockSpriteRenderer renderer;

      Assert::IsFalse(renderer.isPreservingAspectRatio());
    }

#pragma endregion

#pragma region Set Texture Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_SetTexture_WithValidTexture_SetsCurrentTexture)
    {
      MockSpriteRenderer renderer;

      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer.setTexture(texture);

      Assert::IsTrue(texture == renderer.getTexture());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_SetTexture_WithValidTexture_AndTextureAlreadySet_UpdatesTexture)
    {
      MockSpriteRenderer renderer;

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
      MockSpriteRenderer renderer;

      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer.setTexture(texture);

      Assert::IsTrue(texture == renderer.getTexture());

      renderer.setTexture(nullptr);

      Assert::IsNull(renderer.getTexture());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_SetTexture_ExistentTexturePath_SetsCurrentTexture)
    {
      MockSpriteRenderer renderer;

      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer.setTexture(TestResources::getBlockPngRelativePath());

      Assert::IsTrue(texture == renderer.getTexture());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_SetTexture_ExistentTexturePath_AndTextureAlreadySet_UpdatesTexture)
    {
      MockSpriteRenderer renderer;

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
      MockSpriteRenderer renderer;

      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer.setTexture(TestResources::getBlockPngRelativePath());

      Assert::IsTrue(texture == renderer.getTexture());

      renderer.setTexture("ThisTextureShouldn'tExist.png");

      Assert::IsNull(renderer.getTexture());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_SetTexture_DimensionsZero_SetsDimensionsToTextureDimensions)
    {
      MockSpriteRenderer renderer;

      Assert::AreEqual(glm::vec2(), renderer.getDimensions());

      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer.setTexture(TestResources::getBlockPngRelativePath());

      Assert::AreEqual(texture->getDimensions(), renderer.getDimensions());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_SetTexture_DimensionsNonZero_DoesNotChangeDimensions)
    {
      MockSpriteRenderer renderer;
      renderer.setDimensions(400, 200);

      Assert::AreEqual(glm::vec2(400, 200), renderer.getDimensions());

      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer.setTexture(TestResources::getBlockPngRelativePath());

      Assert::AreEqual(glm::vec2(400, 200), renderer.getDimensions());
    }

#pragma endregion

#pragma region Set Dimensions Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_SetDimensions_TextureNull_SetsDimensionsToInput)
    {
      MockSpriteRenderer renderer;

      Assert::IsNull(renderer.getTexture());

      renderer.setDimensions(100, 200);

      Assert::AreEqual(glm::vec2(100, 200), renderer.getDimensions());

      renderer.setDimensions(500, 140);

      Assert::AreEqual(glm::vec2(500, 140), renderer.getDimensions());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpriteRenderer_SetDimensions_NotPreservingAspectRatio_SetsDimensionsToInput)
    {
      MockSpriteRenderer renderer;
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
      MockSpriteRenderer renderer;
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
      SpriteRenderer renderer;
      Program program;

      Assert::IsNull(renderer.getTexture());

      renderer.render(program, glm::mat4());
    }

#pragma endregion

  };
}