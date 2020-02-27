#include "UtilityHeaders/UnitTestHeaders.h"
#include "Mocks/Animation/MockAnimator.h"
#include "Resources/TestResources.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"
#include "AssertExt.h"

using namespace Celeste::Resources;
using namespace Celeste::Animation;
using namespace Celeste::Rendering;
using LoopMode = Celeste::Animation::LoopMode;


namespace TestCeleste
{
  namespace Animation
  {
    CELESTE_TEST_CLASS(TestAnimator)

#pragma region Registration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_IsRegisteredWithComponentRegistry)
    {
      Assert::IsTrue(ComponentRegistry::hasComponent<Animator>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_IsAllocatableFromComponentRegistry)
    {
      GameObject gameObject;

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(Animator::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<Animator*>(component.get()));
      Assert::IsTrue(&gameObject == component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Constructor_SetsSpriteSheetDimensions_ToOne)
    {
      MockAnimator animation;

      Assert::AreEqual(glm::uvec2(1), animation.getSpriteSheetDimensions());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Constructor_SetsCurrentFrame_ToZero)
    {
      MockAnimator animation;

      Assert::AreEqual(static_cast<size_t>(0), animation.getCurrentFrame_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Constructor_SetsPlayImmediatelyToTrue)
    {
      MockAnimator animation;

      Assert::IsTrue(animation.getPlayImmediately());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Constructor_SetsIsLoopingToTrue)
    {
      MockAnimator animation;

      Assert::IsTrue(animation.isLooping());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Constructor_SetsIsPlayingToFalse)
    {
      MockAnimator animation;

      Assert::IsFalse(animation.isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Constructor_SetsCurrentSecondsPerFrameToZero)
    {
      MockAnimator animation;

      Assert::AreEqual(0.0f, animation.getCurrentSecondsPerFrame_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Constructor_SetsSecondsPerFrameToZeroPointOne)
    {
      MockAnimator animation;

      Assert::AreEqual(0.1f, animation.getSecondsPerFrame());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Constructor_SetsNameToZero)
    {
      MockAnimator animation;

      Assert::AreEqual(static_cast<StringId>(0), animation.getName());
    }

#pragma endregion

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_SetName)
    {
      MockAnimator animation;

      StringId nameId = internString("Test Animation");
      animation.setName(nameId);

      Assert::AreEqual(nameId, animation.getName());

      nameId = internString("Test Animation 2");
      animation.setName("Test Animation 2");

      Assert::AreEqual(nameId, animation.getName());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_GetFrameCount_ReturnsSpriteSheetDimensionsMultipled)
    {
      MockAnimator animation;

      animation.setSpriteSheetDimensions(glm::uvec2(4, 5));

      Assert::AreEqual(static_cast<size_t>(20), animation.getFrameCount());
    }

#pragma region Set Game Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_SetGameObject_NoSpriteRendererInParent_DoesNotPlayAnimation)
    {
      GameObject gameObject;
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      Assert::IsNotNull(animation->getGameObject());
      Assert::IsFalse(animation->isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_SetGameObject_SpriteRendererInParent_DoesNotPlayAnimation)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      Assert::IsFalse(animation->isPlaying());
    }

#pragma endregion

#pragma region Set Sprite Sheet Dimensions Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_SetSpriteSheetDimensions_SetsSpriteRendererScissorRectangleDimensions_ToSingleFrameDimensions)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer->setTexture(texture1);
      renderer->getScissorRectangle().setDimensions(100, 200);

      Assert::AreEqual(glm::vec2(100, 200), renderer->getScissorRectangle().getDimensions());

      animation->setSpriteSheetDimensions(glm::uvec2(2, 2));

      Assert::AreNotEqual(glm::vec2(100, 200), renderer->getScissorRectangle().getDimensions());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_SetSpriteSheetDimensions_SetsScissorRectangleCentre)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer->setTexture(texture1);
      renderer->getScissorRectangle().setCentre(100, 200);

      Assert::AreEqual(glm::vec2(100, 200), renderer->getScissorRectangle().getCentre());

      animation->setSpriteSheetDimensions(glm::uvec2(2, 2));

      Assert::AreEqual(glm::vec2(0, 0), renderer->getScissorRectangle().getCentre());
    }

#pragma endregion

#pragma region Pause Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Pause_StopsTheAnimationPlaying)
    {
      MockAnimator animation;
      animation.setPlaying_Public(true);

      Assert::IsTrue(animation.isPlaying());

      animation.pause();

      Assert::IsFalse(animation.isPlaying());
    }

#pragma endregion

#pragma region Play Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Play_WhenLooping_ShouldPlayAnimation)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();
      animation->setPlaying_Public(false);
      animation->setLooping(LoopMode::kLooping);

      Assert::IsFalse(animation->isPlaying());
      Assert::IsTrue(animation->isLooping());

      animation->play();

      Assert::IsTrue(animation->isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Play_WhenNotLooping_CurrentFrameNotAtEnd_ShouldPlayAnimation)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();
      renderer->setTexture(TestResources::getBlockPngRelativePath());
      animation->setPlaying_Public(false);

      Assert::IsFalse(animation->isPlaying());

      animation->play();

      Assert::IsTrue(animation->isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Play_WhenNotLooping_NoFrames_ShouldNotPlayAnimation)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();
      animation->setPlaying_Public(false);
      animation->setLooping(LoopMode::kOneTime);
      animation->setSpriteSheetDimensions(glm::uvec2(0));

      Assert::IsFalse(animation->isPlaying());
      Assert::AreEqual(static_cast<size_t>(0), animation->getFrameCount());

      animation->play();

      Assert::IsFalse(animation->isPlaying());
      Assert::AreEqual(static_cast<size_t>(0), animation->getFrameCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Play_WhenNotLooping_WithFramesAndCurrentFrameIsLastFrame_ShouldNotPlayAnimation)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();
      renderer->setTexture(TestResources::getBlockPngRelativePath());
      animation->setPlaying_Public(false);
      animation->setLooping(LoopMode::kOneTime);

      Assert::AreEqual(animation->getFrameCount() - 1, animation->getCurrentFrame_Public());
      Assert::IsFalse(animation->isPlaying());

      animation->play();

      Assert::IsFalse(animation->isPlaying());
    }

#pragma endregion

#pragma region Restart Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Restart_WithFramesButNoSpriteRenderer_ResetsFrameValues)
    {
      GameObject gameObject;
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();
      animation->setCurrentSecondsPerFrame_Public(1);
      animation->setCurrentFrame_Public(1);

      Assert::AreNotEqual(static_cast<size_t>(0), animation->getFrameCount());
      Assert::AreNotEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreNotEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());

      animation->restart();

      Assert::AreEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Restart_WithSpriteRendererButNoFrames_ResetsFrameValues)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();
      animation->setSpriteSheetDimensions(glm::uvec2(0));
      animation->setCurrentFrame_Public(1);
      animation->setCurrentSecondsPerFrame_Public(1);

      Assert::AreEqual(static_cast<size_t>(0), animation->getFrameCount());
      Assert::AreNotEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreNotEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());

      animation->restart();

      Assert::AreEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Restart_WithSpriteRendererAndFrames_ResetsFrameValues_SetsSpriteRendererToFirstFrame)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

      animation->setCurrentFrame_Public(1);
      animation->setCurrentSecondsPerFrame_Public(1);
      renderer->setTexture(texture1);

      Assert::AreNotEqual(static_cast<size_t>(0), animation->getFrameCount());
      Assert::AreNotEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreNotEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
      Assert::IsTrue(texture1 == renderer->getTexture());

      animation->restart();

      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
    }

#pragma endregion

#pragma region Stop Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Stop_WithAnimationPlaying_StopsAnimationFromPlaying)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

      renderer->setTexture(texture1);
      animation->play();

      Assert::IsTrue(animation->isPlaying());

      animation->update(0.1f);
      animation->stop();

      Assert::IsFalse(animation->isPlaying());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Stop_SetsCurrentFrameToZero)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

      renderer->setTexture(texture1);
      animation->setSpriteSheetDimensions(glm::uvec2(2, 2));
      animation->setSecondsPerFrame(0.05f);
      animation->play();

      Assert::IsTrue(animation->isPlaying());

      animation->update(0.06f);

      Assert::AreEqual(static_cast<size_t>(1), animation->getCurrentFrame_Public());

      animation->stop();

      Assert::AreEqual(static_cast<size_t>(0), animation->getCurrentFrame_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Stop_SetsCurrentSecondsPerFrameToZero)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

      renderer->setTexture(texture1);
      animation->setSpriteSheetDimensions(glm::uvec2(2, 2));
      animation->setSecondsPerFrame(0.05f);
      animation->play();

      Assert::IsTrue(animation->isPlaying());

      animation->update(0.12f);

      Assert::AreNotEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());

      animation->stop();

      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Update_WithFramesButNoSpriteRenderer_DoesNotAnimate)
    {
      GameObject gameObject;
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      Assert::AreNotEqual(static_cast<size_t>(0), animation->getFrameCount());

      animation->play();
      Assert::IsTrue(animation->isPlaying());

      float secondsPerFrame = animation->getSecondsPerFrame();
      animation->update(secondsPerFrame);

      Assert::AreEqual(static_cast<size_t>(0), animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Update_WithFramesAndSpriteRenderer_UpdatesFrameValues_AndSetsSpriteRendererTexture)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

      renderer->setTexture(texture1);
      animation->setSpriteSheetDimensions(glm::uvec2(2, 2));
      animation->restart();
      animation->play();

      Assert::IsTrue(animation->isPlaying());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());

      float secondsPerFrame = animation->getSecondsPerFrame();
      animation->update(secondsPerFrame);

      Assert::IsTrue(animation->isPlaying());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)1, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Update_WithValidSetup_Looping_LoopsValues)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

      renderer->setTexture(texture1);
      animation->setLooping(LoopMode::kLooping);
      animation->setSpriteSheetDimensions(glm::uvec2(2, 1));
      animation->restart();
      animation->play();

      Assert::IsTrue(animation->isPlaying());
      Assert::IsTrue(animation->isLooping());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());

      float secondsPerFrame = animation->getSecondsPerFrame();
      animation->update(1.5f * secondsPerFrame);

      Assert::IsTrue(animation->isPlaying());
      Assert::IsTrue(animation->isLooping());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)1, animation->getCurrentFrame_Public());
      AssertExt::AreAlmostEqual(0.5f * secondsPerFrame, animation->getCurrentSecondsPerFrame_Public());

      animation->update(0.5f * secondsPerFrame);

      Assert::IsTrue(animation->isPlaying());
      Assert::IsTrue(animation->isLooping());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)0, animation->getCurrentFrame_Public());
      AssertExt::AreAlmostEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Update_WithValidSetup_NotLooping_StopsUpdatingValuesAndTextureAtLastFrame)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

      renderer->setTexture(texture1);
      animation->setLooping(LoopMode::kOneTime);
      animation->setSpriteSheetDimensions(glm::uvec2(2, 1));
      animation->restart();
      animation->play();

      Assert::IsTrue(animation->isPlaying());
      Assert::IsFalse(animation->isLooping());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());

      float secondsPerFrame = animation->getSecondsPerFrame();
      animation->update(1.5f * secondsPerFrame);

      Assert::IsFalse(animation->isPlaying());
      Assert::IsFalse(animation->isLooping());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)1, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());

      animation->update(0.5f * secondsPerFrame);

      Assert::IsFalse(animation->isPlaying());
      Assert::IsFalse(animation->isLooping());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)1, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Animator_Update_WithValidSetup_NotPlaying_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
      AutoDeallocator<MockAnimator> animation = gameObject.addComponent<MockAnimator>();

      observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

      renderer->setTexture(texture1);
      animation->setLooping(LoopMode::kOneTime);
      animation->restart();
      animation->stop();

      Assert::IsFalse(animation->isLooping());
      Assert::IsFalse(animation->isPlaying());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());

      float secondsPerFrame = animation->getSecondsPerFrame();
      animation->update(secondsPerFrame);

      Assert::IsFalse(animation->isLooping());
      Assert::IsFalse(animation->isPlaying());
      Assert::IsTrue(texture1 == renderer->getTexture());
      Assert::AreEqual((size_t)0, animation->getCurrentFrame_Public());
      Assert::AreEqual(0.0f, animation->getCurrentSecondsPerFrame_Public());
    }

#pragma endregion

    };
  }
}