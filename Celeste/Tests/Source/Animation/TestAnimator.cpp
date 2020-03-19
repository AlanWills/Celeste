#include "UtilityHeaders/UnitTestHeaders.h"
#include "Mocks/Animation/MockAnimator.h"
#include "TestResources/TestResources.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"
#include "AssertExt.h"

using namespace Celeste::Resources;
using namespace Celeste::Animation;
using namespace Celeste::Rendering;
using LoopMode = Celeste::Animation::LoopMode;


namespace TestCeleste::Animation
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

    observer_ptr<Component> component = ComponentRegistry::createComponent(Animator::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<Animator*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Constructor_SetsSpriteSheetDimensions_ToOne)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    Assert::AreEqual(glm::uvec2(1), animator.getSpriteSheetDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Constructor_SetsCurrentFrame_ToZero)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    Assert::AreEqual(static_cast<size_t>(0), animator.getCurrentFrame_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Constructor_SetsIsLoopingToTrue)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    Assert::IsTrue(animator.isLooping());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Constructor_SetsIsPlayingToFalse)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    Assert::IsFalse(animator.isPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Constructor_SetsCurrentSecondsPerFrameToZero)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Constructor_SetsSecondsPerFrameToZeroPointOne)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    Assert::AreEqual(0.1f, animator.getSecondsPerFrame());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Constructor_SetsNameToZero)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    Assert::AreEqual(static_cast<StringId>(0), animator.getName());
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_SetName)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    StringId nameId = internString("Test Animation");
    animator.setName(nameId);

    Assert::AreEqual(nameId, animator.getName());

    nameId = internString("Test Animation 2");
    animator.setName("Test Animation 2");

    Assert::AreEqual(nameId, animator.getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_GetFrameCount_ReturnsSpriteSheetDimensionsMultipled)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    animator.setSpriteSheetDimensions(glm::uvec2(4, 5));

    Assert::AreEqual(static_cast<size_t>(20), animator.getFrameCount());
  }

#pragma region Set Sprite Sheet Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_SetSpriteSheetDimensions_SetsSpriteRendererScissorRectangleDimensions_ToSingleFrameDimensions)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer->setTexture(texture1);
    renderer->getScissorRectangle().setDimensions(100, 200);

    Assert::AreEqual(glm::vec2(100, 200), renderer->getScissorRectangle().getDimensions());

    animator.setSpriteSheetDimensions(glm::uvec2(2, 2));

    Assert::AreNotEqual(glm::vec2(100, 200), renderer->getScissorRectangle().getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_SetSpriteSheetDimensions_SetsScissorRectangleCentre)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer->setTexture(texture1);
    renderer->getScissorRectangle().setCentre(100, 200);

    Assert::AreEqual(glm::vec2(100, 200), renderer->getScissorRectangle().getCentre());

    animator.setSpriteSheetDimensions(glm::uvec2(2, 2));

    Assert::AreEqual(glm::vec2(0, 0), renderer->getScissorRectangle().getCentre());
  }

#pragma endregion

#pragma region Pause Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Pause_StopsTheAnimationPlaying)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);
    animator.setPlaying_Public(true);

    Assert::IsTrue(animator.isPlaying());

    animator.pause();

    Assert::IsFalse(animator.isPlaying());
  }

#pragma endregion

#pragma region Play Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Play_WhenLooping_ShouldPlayAnimation)
  {
    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);
    animator.setPlaying_Public(false);
    animator.setLooping(LoopMode::kLooping);

    Assert::IsFalse(animator.isPlaying());
    Assert::IsTrue(animator.isLooping());

    animator.play();

    Assert::IsTrue(animator.isPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Play_WhenNotLooping_CurrentFrameNotAtEnd_ShouldPlayAnimation)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);
    renderer->setTexture(TestResources::getBlockPngRelativePath());
    animator.setPlaying_Public(false);

    Assert::IsFalse(animator.isPlaying());

    animator.play();

    Assert::IsTrue(animator.isPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Play_WhenNotLooping_NoFrames_ShouldNotPlayAnimation)
  {
    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);
    animator.setPlaying_Public(false);
    animator.setLooping(LoopMode::kOneTime);
    animator.setSpriteSheetDimensions(glm::uvec2(0));

    Assert::IsFalse(animator.isPlaying());
    Assert::AreEqual(static_cast<size_t>(0), animator.getFrameCount());

    animator.play();

    Assert::IsFalse(animator.isPlaying());
    Assert::AreEqual(static_cast<size_t>(0), animator.getFrameCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Play_WhenNotLooping_WithFramesAndCurrentFrameIsLastFrame_ShouldNotPlayAnimation)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);
    renderer->setTexture(TestResources::getBlockPngRelativePath());
    animator.setPlaying_Public(false);
    animator.setLooping(LoopMode::kOneTime);

    Assert::AreEqual(animator.getFrameCount() - 1, animator.getCurrentFrame_Public());
    Assert::IsFalse(animator.isPlaying());

    animator.play();

    Assert::IsFalse(animator.isPlaying());
  }

#pragma endregion

#pragma region Restart Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Restart_WithFramesButNoSpriteRenderer_ResetsFrameValues)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);
    animator.setCurrentSecondsPerFrame_Public(1);
    animator.setCurrentFrame_Public(1);

    Assert::AreNotEqual(static_cast<size_t>(0), animator.getFrameCount());
    Assert::AreNotEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreNotEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());

    animator.restart();

    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Restart_WithSpriteRendererButNoFrames_ResetsFrameValues)
  {
    GameObject gameObject;
    gameObject.addComponent<SpriteRenderer>();

    MockAnimator animator(gameObject);
    animator.setSpriteSheetDimensions(glm::uvec2(0));
    animator.setCurrentFrame_Public(1);
    animator.setCurrentSecondsPerFrame_Public(1);

    Assert::AreEqual(static_cast<size_t>(0), animator.getFrameCount());
    Assert::AreNotEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreNotEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());

    animator.restart();

    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Restart_WithSpriteRendererAndFrames_ResetsFrameValues_SetsSpriteRendererToFirstFrame)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

    animator.setCurrentFrame_Public(1);
    animator.setCurrentSecondsPerFrame_Public(1);
    renderer->setTexture(texture1);

    Assert::AreNotEqual(static_cast<size_t>(0), animator.getFrameCount());
    Assert::AreNotEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreNotEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
    Assert::IsTrue(texture1 == renderer->getTexture());

    animator.restart();

    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

#pragma endregion

#pragma region Stop Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Stop_WithAnimationPlaying_StopsAnimationFromPlaying)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

    renderer->setTexture(texture1);
    animator.play();

    Assert::IsTrue(animator.isPlaying());

    animator.update(0.1f);
    animator.stop();

    Assert::IsFalse(animator.isPlaying());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Stop_SetsCurrentFrameToZero)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

    renderer->setTexture(texture1);
    animator.setSpriteSheetDimensions(glm::uvec2(2, 2));
    animator.setSecondsPerFrame(0.05f);
    animator.play();

    Assert::IsTrue(animator.isPlaying());

    animator.update(0.06f);

    Assert::AreEqual(static_cast<size_t>(1), animator.getCurrentFrame_Public());

    animator.stop();

    Assert::AreEqual(static_cast<size_t>(0), animator.getCurrentFrame_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Stop_SetsCurrentSecondsPerFrameToZero)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

    renderer->setTexture(texture1);
    animator.setSpriteSheetDimensions(glm::uvec2(2, 2));
    animator.setSecondsPerFrame(0.05f);
    animator.play();

    Assert::IsTrue(animator.isPlaying());

    animator.update(0.12f);

    Assert::AreNotEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());

    animator.stop();

    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Update_WithFramesButNoSpriteRenderer_DoesNotAnimate)
  {
    GameObject gameObject;
    MockAnimator animator(gameObject);

    Assert::AreNotEqual(static_cast<size_t>(0), animator.getFrameCount());

    animator.play();
    Assert::IsTrue(animator.isPlaying());

    float secondsPerFrame = animator.getSecondsPerFrame();
    animator.update(secondsPerFrame);

    Assert::AreEqual(static_cast<size_t>(0), animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Update_WithFramesAndSpriteRenderer_UpdatesFrameValues_AndSetsSpriteRendererTexture)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

    renderer->setTexture(texture1);
    animator.setSpriteSheetDimensions(glm::uvec2(2, 2));
    animator.restart();
    animator.play();

    Assert::IsTrue(animator.isPlaying());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());

    float secondsPerFrame = animator.getSecondsPerFrame();
    animator.update(secondsPerFrame);

    Assert::IsTrue(animator.isPlaying());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)1, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Update_WithValidSetup_Looping_LoopsValues)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

    renderer->setTexture(texture1);
    animator.setLooping(LoopMode::kLooping);
    animator.setSpriteSheetDimensions(glm::uvec2(2, 1));
    animator.restart();
    animator.play();

    Assert::IsTrue(animator.isPlaying());
    Assert::IsTrue(animator.isLooping());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());

    float secondsPerFrame = animator.getSecondsPerFrame();
    animator.update(1.5f * secondsPerFrame);

    Assert::IsTrue(animator.isPlaying());
    Assert::IsTrue(animator.isLooping());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)1, animator.getCurrentFrame_Public());
    AssertExt::AreAlmostEqual(0.5f * secondsPerFrame, animator.getCurrentSecondsPerFrame_Public());

    animator.update(0.5f * secondsPerFrame);

    Assert::IsTrue(animator.isPlaying());
    Assert::IsTrue(animator.isLooping());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    AssertExt::AreAlmostEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Update_WithValidSetup_NotLooping_StopsUpdatingValuesAndTextureAtLastFrame)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

    renderer->setTexture(texture1);
    animator.setLooping(LoopMode::kOneTime);
    animator.setSpriteSheetDimensions(glm::uvec2(2, 1));
    animator.restart();
    animator.play();

    Assert::IsTrue(animator.isPlaying());
    Assert::IsFalse(animator.isLooping());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());

    float secondsPerFrame = animator.getSecondsPerFrame();
    animator.update(1.5f * secondsPerFrame);

    Assert::IsFalse(animator.isPlaying());
    Assert::IsFalse(animator.isLooping());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)1, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());

    animator.update(0.5f * secondsPerFrame);

    Assert::IsFalse(animator.isPlaying());
    Assert::IsFalse(animator.isLooping());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)1, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Animator_Update_WithValidSetup_NotPlaying_DoesNothing)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    MockAnimator animator(gameObject);

    observer_ptr<Texture2D> texture1 = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

    renderer->setTexture(texture1);
    animator.setLooping(LoopMode::kOneTime);
    animator.restart();
    animator.stop();

    Assert::IsFalse(animator.isLooping());
    Assert::IsFalse(animator.isPlaying());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());

    float secondsPerFrame = animator.getSecondsPerFrame();
    animator.update(secondsPerFrame);

    Assert::IsFalse(animator.isLooping());
    Assert::IsFalse(animator.isPlaying());
    Assert::IsTrue(texture1 == renderer->getTexture());
    Assert::AreEqual((size_t)0, animator.getCurrentFrame_Public());
    Assert::AreEqual(0.0f, animator.getCurrentSecondsPerFrame_Public());
  }

#pragma endregion

  };
}