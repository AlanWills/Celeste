#include "UtilityHeaders/UnitTestHeaders.h"

#include "UI/ProgressBar.h"
#include "Rendering/SpriteRenderer.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"
#include "AssertExt.h"

using namespace Celeste::Resources;
using namespace Celeste::UI;
using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestProgressBar)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<ProgressBar>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(ProgressBar::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<ProgressBar*>(component));
    Assert::AreEqual(&gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_Constructor_SetsProgressToZero)
  {
    GameObject gameObject;
    ProgressBar progress(gameObject);

    Assert::AreEqual(0.0f, progress.getProgress());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_Constructor_SetsMinToZero)
  {
    GameObject gameObject;
    ProgressBar progress(gameObject);

    Assert::AreEqual(0.0f, progress.getMin());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_Constructor_SetsMaxToOneHundred)
  {
    GameObject gameObject;
    ProgressBar progress(gameObject);

    Assert::AreEqual(100.0f, progress.getMax());
  }

#pragma endregion

#pragma region Set Min Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetMin_UpdatesValue)
  {
    GameObject gameObject;
    ProgressBar progressBar(gameObject);

    Assert::AreEqual(0.0f, progressBar.getMin());

    progressBar.setMin(-2);

    Assert::AreEqual(-2.0f, progressBar.getMin());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetMin_NoForegroundRenderer_SetsProgressToMin)
  {
    GameObject gameObject;
    ProgressBar progressBar(gameObject);

    Assert::AreEqual(0.0f, progressBar.getProgress());

    progressBar.setMin(-2);

    Assert::AreEqual(-2.0f, progressBar.getProgress());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetMin_SetsForegroundScissorRectangleDimensionsAndCentre)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer->setTexture(texture);
    observer_ptr<ProgressBar> progressBar = gameObject.addComponent<ProgressBar>();

    Assert::AreEqual(glm::vec2(-texture->getDimensions().x * 0.5f, 0), renderer->getScissorRectangle().getCentre());
    Assert::AreEqual(glm::vec2(0, texture->getDimensions().y), renderer->getScissorRectangle().getDimensions());

    progressBar->setMin(-100);

    Assert::AreEqual(glm::vec2(-texture->getDimensions().x * 0.5f, 0), renderer->getScissorRectangle().getCentre());
    Assert::AreEqual(glm::vec2(0, texture->getDimensions().y), renderer->getScissorRectangle().getDimensions());
  }

#pragma endregion

#pragma region Set Max Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetMax_UpdatesValue)
  {
    GameObject gameObject;
    ProgressBar progressBar(gameObject);

    Assert::AreEqual(100.0f, progressBar.getMax());

    progressBar.setMax(10);

    Assert::AreEqual(10.0f, progressBar.getMax());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetMax_NoForegroundRenderer_DoesNothing)
  {
    GameObject gameObject;
    ProgressBar progressBar(gameObject);

    Assert::AreEqual(0.0f, progressBar.getProgress());

    progressBar.setMax(10);

    Assert::AreEqual(0.0f, progressBar.getProgress());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetMax_SetsForegroundRendererScissorRectangleDimensionsAndCentre)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer->setTexture(texture);
    observer_ptr<ProgressBar> progressBar = gameObject.addComponent<ProgressBar>();

    progressBar->setProgress(10);

    Assert::AreEqual(glm::vec2(-texture->getDimensions().x * 0.45f, 0), renderer->getScissorRectangle().getCentre());
    Assert::AreEqual(glm::vec2(texture->getDimensions().x * 0.1f, texture->getDimensions().y), renderer->getScissorRectangle().getDimensions());

    progressBar->setMax(20);

    AssertExt::AreAlmostEqual(-texture->getDimensions().x * 0.25f, renderer->getScissorRectangle().getCentre().x);
    AssertExt::AreAlmostEqual(0, renderer->getScissorRectangle().getCentre().y);
    Assert::AreEqual(glm::vec2(texture->getDimensions().x * 0.5f, texture->getDimensions().y), renderer->getScissorRectangle().getDimensions());
  }

#pragma endregion

#pragma region Set Progress Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetProgress_UpdatesValue)
  {
    GameObject gameObject;
    ProgressBar progressBar(gameObject);

    Assert::AreEqual(0.0f, progressBar.getProgress());

    progressBar.setProgress(10);

    Assert::AreEqual(10.0f, progressBar.getProgress());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetProgress_ClampsBetweenMaxAndMin)
  {
    GameObject gameObject;
    ProgressBar progressBar(gameObject);

    Assert::AreEqual(progressBar.getMin(), progressBar.getProgress());

    progressBar.setProgress(progressBar.getMin() - 1);

    Assert::AreEqual(progressBar.getMin(), progressBar.getProgress());

    progressBar.setProgress(progressBar.getMax() + 1);

    Assert::AreEqual(progressBar.getMax(), progressBar.getProgress());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetProgress_NoForegroundRenderer_DoesNotThrow)
  {
    GameObject gameObject;
    ProgressBar progressBar(gameObject);
    progressBar.setProgress(10);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetProgress_ForegroundRenderer_MaxEqualsMin_DoesNothing)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer->setTexture(texture);
    observer_ptr<ProgressBar> progressBar = gameObject.addComponent<ProgressBar>();

    progressBar->setMin(0);
    progressBar->setMax(0);

    Assert::AreEqual(glm::vec2(-texture->getDimensions().x * 0.5f, 0), renderer->getScissorRectangle().getCentre());
    Assert::AreEqual(glm::vec2(0, texture->getDimensions().y), renderer->getScissorRectangle().getDimensions());

    progressBar->setProgress(0);

    Assert::AreEqual(0.0f, progressBar->getProgress());
    Assert::AreEqual(glm::vec2(-texture->getDimensions().x * 0.5f, 0), renderer->getScissorRectangle().getCentre());
    Assert::AreEqual(glm::vec2(0, texture->getDimensions().y), renderer->getScissorRectangle().getDimensions());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ProgressBar_SetProgress_SetsForegroundRendererScissorRectangleCentreAndDimensionsCorrectly)
  {
    GameObject gameObject;
    observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();
    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
    renderer->setTexture(texture);
    observer_ptr<ProgressBar> progressBar = gameObject.addComponent<ProgressBar>();

    progressBar->setMin(0);
    progressBar->setMax(100);

    Assert::AreEqual(glm::vec2(-texture->getDimensions().x * 0.5f, 0), renderer->getScissorRectangle().getCentre());
    Assert::AreEqual(glm::vec2(0, texture->getDimensions().y), renderer->getScissorRectangle().getDimensions());

    progressBar->setProgress(30);

    Assert::AreEqual(30.0f, progressBar->getProgress());
    Assert::AreEqual(glm::vec2(-texture->getDimensions().x * 0.35f, 0), renderer->getScissorRectangle().getCentre());
    Assert::AreEqual(glm::vec2(texture->getDimensions().x * 0.3f, texture->getDimensions().y), renderer->getScissorRectangle().getDimensions());
  }

#pragma endregion
  };
}