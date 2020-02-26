#include "UtilityHeaders/UnitTestHeaders.h"

#include "Callbacks/RenderGameObject.h"
#include "Screens/Screen.h"
#include "Mocks/Rendering/MockRenderer.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestRenderGameObject);

#pragma region Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderGameObject_Operator_InputtingGameObjectWithNullOwnerScreen_DoesNothing)
  {
    GAMEOBJECT(gameObject);

    Assert::IsNull(gameObject.getScreen());

    RenderGameObject callback;

    // Shouldn't throw
    callback(gameObject, "Test");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderGameObject_Operator_InputtingEmptyArgsString_DoesNothing)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

    Assert::IsTrue(screen.get() == gameObject->getScreen());

    RenderGameObject callback;

    // Shouldn't throw
    callback(*gameObject, "");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderGameObject_Operator_InputtingGameObjectWithSameNameAsArg_NoRenderer_DoesNothing)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
    gameObject->setName("Test");

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    Assert::IsTrue(gameObject->isActive());

    RenderGameObject callback;
    callback(*gameObject, "Test");
    
    Assert::IsTrue(gameObject->isActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderGameObject_Operator_InputtingGameObjectWithSameNameAsArg_AndRenderer_ActivatesRenderer)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
    gameObject->setName("Test");
    AutoDeallocator<MockRenderer> renderer = gameObject->addComponent<MockRenderer>();
    renderer->setActive(false);

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    Assert::IsFalse(renderer->isActive());

    RenderGameObject callback;
    callback(*gameObject, "Test");

    Assert::IsTrue(renderer->isActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderGameObject_Operator_InputtingName_WithNoGameObjectInScreenWithSameName_DoesNothing)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
    AutoDeallocator<MockRenderer> renderer = gameObject->addComponent<MockRenderer>();
    renderer->setActive(false);

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    Assert::IsNull(screen->findGameObject("Test"));
    Assert::IsFalse(renderer->isActive());

    RenderGameObject callback;

    // Check does not throw
    callback(*gameObject, "Test");

    Assert::IsFalse(renderer->isActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderGameObject_Operator_InputtingName_WithGameObjectInScreenWithSameName_SetsGameObjectToRenderable)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
    AutoDeallocator<GameObject> namedGameObject = screen->allocateGameObject();
    AutoDeallocator<MockRenderer> renderer = namedGameObject->addComponent<MockRenderer>();
    renderer->setActive(false);
    namedGameObject->setName("Test");
    renderer->setActive(false);

    Assert::IsTrue(screen.get() == gameObject->getScreen());
    Assert::IsFalse(renderer->isActive());
    Assert::IsNotNull(screen->findGameObject("Test"));

    RenderGameObject callback;
    callback(*gameObject, "Test");

    Assert::IsTrue(renderer->isActive());
  }

#pragma endregion

  };
}