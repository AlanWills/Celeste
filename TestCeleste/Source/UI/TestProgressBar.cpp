#include "UtilityHeaders/UnitTestHeaders.h"

#include "UI/ProgressBar.h"
#include "Rendering/SpriteRenderer.h"
#include "Screens/Screen.h"
#include "Resources/ResourceManager.h"
#include "Resources/TestResources.h"
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

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(ProgressBar::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<ProgressBar*>(component.get()));
      Assert::AreEqual(&gameObject, component->getGameObject());
    }

#pragma endregion

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_Constructor_SetsProgressToZero)
    {
      ProgressBar progress;

      Assert::AreEqual(0.0f, progress.getProgress());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_Constructor_SetsMinToZero)
    {
      ProgressBar progress;

      Assert::AreEqual(0.0f, progress.getMin());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_Constructor_SetsMaxToOneHundred)
    {
      ProgressBar progress;

      Assert::AreEqual(100.0f, progress.getMax());
    }

#pragma endregion

#pragma region On Set GameObject Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetGameObject_WithSpriteRenderer_SetsForegroundScissorRectangleDimensions)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      renderer->setTexture(TestResources::getBlockPngRelativePath());

      Assert::AreEqual(glm::vec2(), renderer->getScissorRectangle().getDimensions());

      AutoDeallocator<ProgressBar> progressBar = gameObject->addComponent<ProgressBar>();

      AssertCel::HasComponent<SpriteRenderer>(*gameObject);
      Assert::AreEqual(glm::vec2(0, renderer->getDimensions().y), renderer->getScissorRectangle().getDimensions());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetGameObject_WithSpriteRenderer_SetsForegroundScissorRectangleCentre)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      renderer->setTexture(TestResources::getBlockPngRelativePath());

      Assert::AreEqual(glm::vec2(), renderer->getScissorRectangle().getCentre());

      AutoDeallocator<ProgressBar> progressBar = gameObject->addComponent<ProgressBar>();

      AssertCel::HasComponent<SpriteRenderer>(*gameObject);
      Assert::AreEqual(glm::vec2(-renderer->getDimensions().x * 0.5f, 0), renderer->getScissorRectangle().getCentre());
    }

#pragma endregion

#pragma region Set Min Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetMin_UpdatesValue)
    {
      ProgressBar progressBar;

      Assert::AreEqual(0.0f, progressBar.getMin());

      progressBar.setMin(-2);

      Assert::AreEqual(-2.0f, progressBar.getMin());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetMin_NoForegroundRenderer_SetsProgressToMin)
    {
      ProgressBar progressBar;

      Assert::AreEqual(0.0f, progressBar.getProgress());

      progressBar.setMin(-2);

      Assert::AreEqual(-2.0f, progressBar.getProgress());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetMin_SetsForegroundScissorRectangleDimensionsAndCentre)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer->setTexture(texture);
      AutoDeallocator<ProgressBar> progressBar = gameObject->addComponent<ProgressBar>();

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
      ProgressBar progressBar;

      Assert::AreEqual(100.0f, progressBar.getMax());

      progressBar.setMax(10);

      Assert::AreEqual(10.0f, progressBar.getMax());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetMax_NoForegroundRenderer_DoesNothing)
    {
      ProgressBar progressBar;

      Assert::AreEqual(0.0f, progressBar.getProgress());

      progressBar.setMax(10);

      Assert::AreEqual(0.0f, progressBar.getProgress());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetMax_SetsForegroundRendererScissorRectangleDimensionsAndCentre)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer->setTexture(texture);
      AutoDeallocator<ProgressBar> progressBar = gameObject->addComponent<ProgressBar>();

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
      ProgressBar progressBar;

      Assert::AreEqual(0.0f, progressBar.getProgress());

      progressBar.setProgress(10);

      Assert::AreEqual(10.0f, progressBar.getProgress());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetProgress_ClampsBetweenMaxAndMin)
    {
      ProgressBar progressBar;

      Assert::AreEqual(progressBar.getMin(), progressBar.getProgress());

      progressBar.setProgress(progressBar.getMin() - 1);

      Assert::AreEqual(progressBar.getMin(), progressBar.getProgress());

      progressBar.setProgress(progressBar.getMax() + 1);

      Assert::AreEqual(progressBar.getMax(), progressBar.getProgress());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetProgress_NoForegroundRenderer_DoesNotThrow)
    {
      ProgressBar progressBar;
      progressBar.setProgress(10);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ProgressBar_SetProgress_ForegroundRenderer_MaxEqualsMin_DoesNothing)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer->setTexture(texture);
      AutoDeallocator<ProgressBar> progressBar = gameObject->addComponent<ProgressBar>();

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
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<SpriteRenderer> renderer = gameObject->addComponent<SpriteRenderer>();
      observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());
      renderer->setTexture(texture);
      AutoDeallocator<ProgressBar> progressBar = gameObject->addComponent<ProgressBar>();

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