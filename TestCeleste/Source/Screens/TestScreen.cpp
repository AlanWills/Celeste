#include "UtilityHeaders/UnitTestHeaders.h"

#include "Screens/Screen.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestScreen)

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_Constructor_SetsNameToZero)
    {
      Screen screen;

      Assert::AreEqual((StringId)0, screen.getName());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_Constructor_CreatesIdentitySceneRoot)
    {
      Screen screen;

      Assert::AreEqual(glm::vec3(), screen.getScreenRoot().getTranslation());
      Assert::AreEqual(glm::vec3(1), screen.getScreenRoot().getScale());
      Assert::AreEqual(0.0f, screen.getScreenRoot().getRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_Constructor_Sets_Active_ToTrue)
    {
      Screen screen;

      Assert::IsTrue(screen.isActive());
    }

#pragma endregion

#pragma region Allocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_Allocate_AllocatesInitializedScreen)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();

      Assert::IsNotNull(screen.get());
    }

#pragma endregion

#pragma region Set Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_SetName_StringId_UpdatesName)
    {
      Screen screen;

      Assert::AreEqual((StringId)0, screen.getName());

      screen.setName(1024);

      Assert::AreEqual((StringId)1024, screen.getName());

      screen.setName(58);

      Assert::AreEqual((StringId)58, screen.getName());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_SetName_String_UpdatesNameWithStringId)
    {
      Screen screen;

      Assert::AreEqual((StringId)0, screen.getName());

      screen.setName("Test");

      Assert::AreEqual(internString("Test"), screen.getName());

      screen.setName("Another Name");

      Assert::AreEqual(internString("Another Name"), screen.getName());
    }

#pragma endregion

#pragma region Set Active Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_SetActiveToFalse_ShouldSetScreenInActive)
    {
      Screen screen;
      screen.setActive(false);

      Assert::IsFalse(screen.isActive());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_SetActiveToTrue_ShouldSetScreenToActive)
    {
      Screen screen;
      screen.setActive(true);

      Assert::IsTrue(screen.isActive());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_SetActiveToFalse_ShouldSetAllGameObjectsToInActive)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject3 = screen.allocateGameObject();

      AssertCel::IsActive(gameObject.get());
      AssertCel::IsActive(gameObject2.get());
      AssertCel::IsActive(gameObject3.get());

      screen.setActive(false);

      AssertCel::IsNotActive(gameObject.get());
      AssertCel::IsNotActive(gameObject2.get());
      AssertCel::IsNotActive(gameObject3.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_SetActiveToTrue_ShouldSetAllGameObjectsToActive)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject3 = screen.allocateGameObject();

      AssertCel::IsActive(gameObject.get());
      AssertCel::IsActive(gameObject2.get());
      AssertCel::IsActive(gameObject3.get());

      screen.setActive(false);

      AssertCel::IsNotActive(gameObject.get());
      AssertCel::IsNotActive(gameObject2.get());
      AssertCel::IsNotActive(gameObject3.get());

      screen.setActive(true);

      AssertCel::IsActive(gameObject.get());
      AssertCel::IsActive(gameObject2.get());
      AssertCel::IsActive(gameObject3.get());
    }

#pragma endregion

#pragma region Deallocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_Deallocate_OnScreenFromAllocator_ReturnsTrue)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();

      Assert::IsTrue(screen->deallocate());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_Deallocate_OnScreenNotFromAllocator_ReturnsTrue)
    {
      Screen screen;

      Assert::IsTrue(screen.deallocate());
    }

#pragma endregion

#pragma region Allocate Game Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_AllocateGameObject_ShouldReturnGameObject_WithOwnerScreenSetToScreenInstance_AndTransformParentSetToScreenRoot)
    {
      Screen screen;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

      Assert::IsNotNull(gameObject.get());
      Assert::IsNotNull(gameObject->getTransform());
      Assert::IsTrue(gameObject->isActive());
      Assert::IsTrue(&screen == gameObject->getScreen());
      Assert::IsTrue(&screen.getScreenRoot() == gameObject->getTransform()->getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_AllocateGameObject_InputtingTransform_ShouldReturnGameObject_WithOwnerScreenSetToScreenInstance_AndTransformParentSetToInput)
    {
      Screen screen;
      Transform transform;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject(transform);

      Assert::IsNotNull(gameObject.get());
      Assert::IsTrue(gameObject->isActive());
      Assert::IsNotNull(gameObject->getTransform());
      Assert::IsTrue(&transform == gameObject->getTransform()->getParent());
      Assert::IsTrue(&screen == gameObject->getScreen());
    }

#pragma endregion

#pragma region Deallocate Game Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_DeallocateGameObject_InputtingGameObjectNotFromScreen_ShouldReturnFalse)
    {
      Screen screen;
      Screen screen2;
      AutoDeallocator<GameObject> gameObject = screen2.allocateGameObject();

      Assert::IsNotNull(gameObject.get());
      AssertCel::IsActive(gameObject.get());
      Assert::IsFalse(screen.deallocateGameObject(*gameObject));
      Assert::IsNotNull(gameObject.get());
      AssertCel::IsActive(gameObject.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_DeallocateGameObject_InputtingDeallocatedGameObjectFromScreen_ReturnsFalse)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      gameObject->deallocate();

      Assert::IsFalse(screen.deallocateGameObject(*gameObject));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_DeallocateGameObject_InputtingGameObjectFromScreen_ShouldDeallocateGameObject)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

      Assert::IsNotNull(gameObject.get());
      AssertCel::IsActive(gameObject.get());
      
      screen.deallocateGameObject(*gameObject);

      Assert::IsNotNull(gameObject.get());
      AssertCel::IsNotActive(gameObject.get());
    }

#pragma endregion

#pragma region Find Game Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObject_ShouldFindGameObject)
    {
      Screen screen;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();

      const observer_ptr<GameObject> foundGO = screen.findGameObject(
        [&gameObject](const GameObject& go) -> bool
        {
          return &go == gameObject.get();
        });

      Assert::IsTrue(gameObject.get() == foundGO);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObject_ShouldReturnFirstGameObjectInScreenThatMatchesCondition)
    {
      Screen screen;
      Screen screen2;

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2.allocateGameObject();
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();

      const observer_ptr<GameObject> foundGO = screen.findGameObject(
        [](const GameObject& gameObject) -> bool
      {
        return true;
      });

      Assert::IsTrue(gameObject.get() == foundGO);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObject_NoGameObjectsInScreenSatisfyingPredicate_ShouldNotFindGameObject)
    {
      Screen screen;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();

      const observer_ptr<GameObject> foundGO = screen.findGameObject(
        [gameObject](const GameObject& gameObject) -> bool
      {
        return false;
      });

      Assert::IsNull(foundGO);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObject_GameObjectSatisfyingPredicateExists_ButNotInScreen_ShouldNotFindGameObject)
    {
      Screen screen;
      Screen screen2;

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2.allocateGameObject();
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();

      const observer_ptr<GameObject> foundGO = screen.findGameObject(
        [gameObjectNotInScreen](const GameObject& gameObject) -> bool
      {
        return &gameObject == gameObjectNotInScreen.get();
      });

      Assert::IsNull(foundGO);
    }

#pragma endregion

#pragma region Find Const Game Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObject_ShouldFindGameObject)
    {
      Screen screen;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();

      const Screen& constScreen = screen;

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObject(
        [&gameObject](const GameObject& go) -> bool
      {
        return &go == gameObject.get();
      });
      
      Assert::IsTrue(gameObject.get() == foundGO);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObject_ShouldReturnFirstGameObjectInScreenThatMatchesCondition)
    {
      Screen screen;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();

      const Screen& constScreen = screen;

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObject(
        [](const GameObject& gameObject) -> bool
      {
        return true;
      });

      Assert::IsTrue(gameObject.get() == foundGO);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObject_NoGameObjectsInScreenSatisfyingPredicate_ShouldNotFindGameObject)
    {
      Screen screen;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();

      const Screen& constScreen = screen;

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObject(
        [](const GameObject& gameObject) -> bool
      {
        return false;
      });

      Assert::IsNull(foundGO);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObject_GameObjectSatisfyingPredicate_ButNotInScreen_ShouldNotFindGameObject)
    {
      Screen screen;
      Screen screen2;

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2.allocateGameObject();
      AutoDeallocator<GameObject> gameObject = screen2.allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen2.allocateGameObject();

      const Screen& constScreen = screen;

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObject(
        [gameObjectNotInScreen](const GameObject& gameObject) -> bool
      {
        return &gameObject == gameObjectNotInScreen.get();
      });

      Assert::IsNull(foundGO);
    }

#pragma endregion

#pragma region FindGameObjectWithTag Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObjectWithTag_ShouldFindGameObject)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();

      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      gameObject->setTag("Tag");
      AutoDeallocator<GameObject> gameObject2 = screen->allocateGameObject();
      gameObject2->setTag("Tag2");

      const observer_ptr<GameObject> foundGO = screen->findGameObjectWithTag("Tag");

      Assert::IsTrue(gameObject.get() == foundGO);

      const observer_ptr<GameObject> foundGO2 = screen->findGameObjectWithTag(internString("Tag2"));

      Assert::IsTrue(gameObject2.get() == foundGO2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObjectWithTag_ShouldReturnFirstGameObjectInScreenWithTag)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<Screen> screen2 = Screen::allocate();

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2->allocateGameObject();
      gameObjectNotInScreen->setTag("Tag");
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      gameObject->setTag("Tag");
      AutoDeallocator<GameObject> gameObject2 = screen->allocateGameObject();
      gameObject2->setTag("Tag");

      const observer_ptr<GameObject> foundGO = screen->findGameObjectWithTag("Tag");

      Assert::IsTrue(gameObject.get() == foundGO);

      const observer_ptr<GameObject> foundGO2 = screen->findGameObjectWithTag(internString("Tag"));

      Assert::IsTrue(gameObject.get() == foundGO2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObjectWithTag_NoGameObjectsInScreenWithTag_ShouldNotFindGameObject)
    {
      Screen screen;
      Screen screen2;

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2.allocateGameObject();
      gameObjectNotInScreen->setTag("Tag2");
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      gameObject->setTag("Tag");
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      gameObject2->setTag("Tag");

      const observer_ptr<GameObject> foundGO = screen.findGameObjectWithTag("Tag2");

      Assert::IsNull(foundGO);

      const observer_ptr<GameObject> foundGO2 = screen.findGameObjectWithTag(internString("Tag2"));

      Assert::IsNull(foundGO2);
    }

#pragma endregion

#pragma region Find Const GameObject With Tag Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObjectWithTag_ShouldFindGameObject)
    {
      Screen screen;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      gameObject->setTag("Tag");
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      gameObject2->setTag("Tag2");

      const Screen& constScreen = screen;

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObjectWithTag("Tag");

      Assert::IsTrue(gameObject.get() == foundGO);

      const observer_ptr<const GameObject> foundGO2 = constScreen.findGameObjectWithTag(internString("Tag2"));

      Assert::IsTrue(gameObject2.get() == foundGO2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObjectWithTag_ShouldReturnFirstGameObjectInScreenWithTag)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<Screen> screen2 = Screen::allocate();

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2->allocateGameObject();
      gameObjectNotInScreen->setTag("Tag");
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      gameObject->setTag("Tag");
      AutoDeallocator<GameObject> gameObject2 = screen->allocateGameObject();
      gameObject2->setTag("Tag");

      const Screen& constScreen = *(screen.get());

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObjectWithTag("Tag");

      Assert::IsTrue(gameObject.get() == foundGO);

      const observer_ptr<const GameObject> foundGO2 = constScreen.findGameObjectWithTag(internString("Tag"));

      Assert::IsTrue(gameObject.get() == foundGO2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObjectWithTag_NoGameObjectsInScreenWithTag_ShouldNotFindGameObject)
    {
      Screen screen;
      Screen screen2;

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2.allocateGameObject();
      gameObjectNotInScreen->setTag("Tag2");
      const observer_ptr<GameObject> gameObject = screen.allocateGameObject();
      gameObject->setTag("Tag");
      const observer_ptr<GameObject> gameObject2 = screen.allocateGameObject();
      gameObject2->setTag("Tag");

      const Screen& constScreen = screen;

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObjectWithTag("Tag2");

      Assert::IsNull(foundGO);

      const observer_ptr<const GameObject> foundGO2 = constScreen.findGameObjectWithTag(internString("Tag2"));

      Assert::IsNull(foundGO2);
    }

#pragma endregion

#pragma region Find GameObject With Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObjectWithName_ShouldFindGameObject)
    {
      Screen screen;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      gameObject->setName("Name");
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      gameObject2->setName("Name2");

      const observer_ptr<GameObject> foundGO = screen.findGameObject("Name");

      Assert::IsTrue(gameObject.get() == foundGO);

      const observer_ptr<GameObject> foundGO2 = screen.findGameObject(internString("Name2"));

      Assert::IsTrue(gameObject2.get() == foundGO2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObjectWithName_ShouldReturnFirstGameObjectInScreenWithName)
    {
      Screen screen;
      Screen screen2;

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2.allocateGameObject();
      gameObjectNotInScreen->setTag("Name");
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      gameObject->setName("Name");
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      gameObject2->setName("Name");

      const observer_ptr<GameObject> foundGO = screen.findGameObject("Name");

      Assert::IsTrue(gameObject.get() == foundGO);

      const observer_ptr<GameObject> foundGO2 = screen.findGameObject(internString("Name"));

      Assert::IsTrue(gameObject.get() == foundGO2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObjectWithName_NoGameObjectsInScreenWithName_ShouldNotFindGameObject)
    {
      Screen screen;
      Screen screen2;

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2.allocateGameObject();
      gameObjectNotInScreen->setName("Name2");
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      gameObject->setName("Name");
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      gameObject2->setName("Name");

      const observer_ptr<GameObject> foundGO = screen.findGameObject("Name2");

      Assert::IsNull(foundGO);

      const observer_ptr<GameObject> foundGO2 = screen.findGameObject(internString("Name2"));

      Assert::IsNull(foundGO2);
    }

#pragma endregion

#pragma region Find Const GameObject With Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObjectWithName_ShouldFindGameObject)
    {
      Screen screen;

      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      gameObject->setName("Name");
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      gameObject2->setName("Name2");

      const Screen& constScreen = screen;

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObject("Name");

      Assert::IsTrue(gameObject.get() == foundGO);

      const observer_ptr<const GameObject> foundGO2 = constScreen.findGameObject(internString("Name2"));

      Assert::IsTrue(gameObject2.get() == foundGO2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObjectWithName_ShouldReturnFirstGameObjectInScreenWithName)
    {
      Screen screen;
      Screen screen2;

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2.allocateGameObject();
      gameObjectNotInScreen->setName("Name");
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      gameObject->setName("Name");
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      gameObject2->setName("Name");

      const Screen& constScreen = screen;

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObject("Name");

      Assert::IsTrue(gameObject.get() == foundGO);

      const observer_ptr<const GameObject> foundGO2 = constScreen.findGameObject(internString("Name"));

      Assert::IsTrue(gameObject.get() == foundGO2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObjectWithName_NoGameObjectsInScreenWithName_ShouldNotFindGameObject)
    {
      Screen screen;
      Screen screen2;

      AutoDeallocator<GameObject> gameObjectNotInScreen = screen2.allocateGameObject();
      gameObjectNotInScreen->setName("Name");
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();
      gameObject->setName("Name");
      AutoDeallocator<GameObject> gameObject2 = screen.allocateGameObject();
      gameObject2->setName("Name");

      const Screen& constScreen = screen;

      const observer_ptr<const GameObject> foundGO = constScreen.findGameObject("Name2");

      Assert::IsNull(foundGO);

      const observer_ptr<const GameObject> foundGO2 = constScreen.findGameObject(internString("Name2"));

      Assert::IsNull(foundGO2);
    }

#pragma endregion

#pragma region Find GameObjects Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObjects_ShouldFindGameObjectsInScreenSatisfyingConditionOnly)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<Screen> screen2 = Screen::allocate();

      AutoDeallocator<GameObject> gameObjectNotInScreen1 = screen2->allocateGameObject();
      AutoDeallocator<GameObject> gameObjectNotInScreen2 = screen2->allocateGameObject();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen->allocateGameObject();
      AutoDeallocator<GameObject> gameObject3 = screen->allocateGameObject();

      std::vector<std::reference_wrapper<GameObject>> foundGOs;
      screen->findGameObjects(
        [gameObject](const GameObject& go) -> bool
      {
        return &go != gameObject.get();
      }, foundGOs);

      Assert::AreEqual((size_t)2, foundGOs.size());
      Assert::IsTrue(gameObject2.get() == &foundGOs[0].get());
      Assert::IsTrue(gameObject3.get() == &foundGOs[1].get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindGameObjectsWithTag_ShouldFindGameObjectsWithTagOnly)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<Screen> screen2 = Screen::allocate();

      AutoDeallocator<GameObject> gameObjectNotInScreen1 = screen2->allocateGameObject();
      gameObjectNotInScreen1->setTag("Tag");
      AutoDeallocator<GameObject> gameObjectNotInScreen2 = screen2->allocateGameObject();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      gameObject->setTag("Tag");
      AutoDeallocator<GameObject> gameObject2 = screen->allocateGameObject();
      gameObject2->setTag("Tag2");
      AutoDeallocator<GameObject> gameObject3 = screen->allocateGameObject();
      gameObject3->setTag("Tag");

      {
        std::vector<std::reference_wrapper<GameObject>> foundGOs;
        screen->findGameObjectsWithTag("Tag", foundGOs);

        Assert::AreEqual((size_t)2, foundGOs.size());
        Assert::IsTrue(gameObject.get() == &foundGOs[0].get());
        Assert::IsTrue(gameObject3.get() == &foundGOs[1].get());
      }

      {
        std::vector<std::reference_wrapper<GameObject>> foundGOs;
        screen->findGameObjectsWithTag(internString("Tag"), foundGOs);

        Assert::AreEqual((size_t)2, foundGOs.size());
        Assert::IsTrue(gameObject.get() == &foundGOs[0].get());
        Assert::IsTrue(gameObject3.get() == &foundGOs[1].get());
      }
    }

#pragma endregion

#pragma region Find Const GameObjects Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObjects_ShouldFindGameObjectsInScreenSatisfyingConditionOnly)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<Screen> screen2 = Screen::allocate();

      AutoDeallocator<GameObject> gameObjectNotInScreen1 = screen2->allocateGameObject();
      AutoDeallocator<GameObject> gameObjectNotInScreen2 = screen2->allocateGameObject();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      AutoDeallocator<GameObject> gameObject2 = screen->allocateGameObject();
      AutoDeallocator<GameObject> gameObject3 = screen->allocateGameObject();

      const Screen& constScreen = *(screen.get());

      std::vector<std::reference_wrapper<const GameObject>> foundGOs;
      constScreen.findGameObjects(
        [gameObject](const GameObject& go) -> bool
      {
        return &go != gameObject.get();
      }, foundGOs);

      Assert::AreEqual((size_t)2, foundGOs.size());
      Assert::IsTrue(gameObject2.get() == &foundGOs[0].get());
      Assert::IsTrue(gameObject3.get() == &foundGOs[1].get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Screen_FindConstGameObjectsWithTag_ShouldFindGameObjectsInScreenWithTagOnly)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<Screen> screen2 = Screen::allocate();

      AutoDeallocator<GameObject> gameObjectNotInScreen1 = screen2->allocateGameObject();
      gameObjectNotInScreen1->setTag("Tag");
      AutoDeallocator<GameObject> gameObjectNotInScreen2 = screen2->allocateGameObject();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      gameObject->setTag("Tag");
      AutoDeallocator<GameObject> gameObject2 = screen->allocateGameObject();
      gameObject2->setTag("Tag2");
      AutoDeallocator<GameObject> gameObject3 = screen->allocateGameObject();
      gameObject3->setTag("Tag");

      const Screen& constScreen = *(screen.get());

      {
        std::vector<std::reference_wrapper<const GameObject>> foundGOs;
        constScreen.findGameObjectsWithTag("Tag", foundGOs);

        Assert::AreEqual((size_t)2, foundGOs.size());
        Assert::IsTrue(gameObject.get() == &foundGOs[0].get());
        Assert::IsTrue(gameObject3.get() == &foundGOs[1].get());
      }

      {
        std::vector<std::reference_wrapper<const GameObject>> foundGOs;
        constScreen.findGameObjectsWithTag(internString("Tag"), foundGOs);

        Assert::AreEqual((size_t)2, foundGOs.size());
        Assert::IsTrue(gameObject.get() == &foundGOs[0].get());
        Assert::IsTrue(gameObject3.get() == &foundGOs[1].get());
      }
    }

#pragma endregion

  };
}