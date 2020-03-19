#include "UtilityHeaders/UnitTestHeaders.h"
#include "Scene/SceneManager.h"
#include "Objects/GameObject.h"

#include "Mocks/Objects/MockComponent.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestSceneManager)

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_HandleInput_CallsHandleInputOnAllActiveRoots)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> gameObject2(new GameObject());
    gameObject2->setActive(false);
    MockComponent* component = gameObject->addComponent<MockComponent>();
    MockComponent* component2 = gameObject2->addComponent<MockComponent>();

    Assert::IsFalse(component->handleInputCalled());
    Assert::IsFalse(component2->handleInputCalled());

    sceneManager.handleInput();

    Assert::IsTrue(component->handleInputCalled());
    Assert::IsFalse(component2->handleInputCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_HandleInput_RootActive_CallsHandleInputOnChildren)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> child1(new GameObject());
    std::unique_ptr<GameObject> child2(new GameObject());
    child1->setParent(gameObject.get());
    child2->setParent(gameObject.get());

    MockComponent* component1 = child1->addComponent<MockComponent>();
    MockComponent* component2 = child2->addComponent<MockComponent>();

    Assert::IsFalse(component1->handleInputCalled());
    Assert::IsFalse(component2->handleInputCalled());

    sceneManager.handleInput();

    Assert::IsTrue(component1->handleInputCalled());
    Assert::IsTrue(component2->handleInputCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_HandleInput_RootActive_CallsHandleInputOnActiveChildren)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> child1(new GameObject());
    std::unique_ptr<GameObject> child2(new GameObject());
    child1->setParent(gameObject.get());
    child2->setParent(gameObject.get());
    child1->setActive(false);

    MockComponent* component1 = child1->addComponent<MockComponent>();
    MockComponent* component2 = child2->addComponent<MockComponent>();

    Assert::IsFalse(component1->handleInputCalled());
    Assert::IsFalse(component2->handleInputCalled());

    sceneManager.handleInput();

    Assert::IsFalse(component1->handleInputCalled());
    Assert::IsTrue(component2->handleInputCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_HandleInput_RootNotActive_DoesNotCallHandleInputOnRoot)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    gameObject->setActive(false);
    MockComponent* component = gameObject->addComponent<MockComponent>();

    Assert::IsFalse(component->handleInputCalled());

    sceneManager.handleInput();

    Assert::IsFalse(component->handleInputCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_HandleInput_RootNotActive_DoesNotCallHandleInputOnChildren)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> child1(new GameObject());
    std::unique_ptr<GameObject> child2(new GameObject());
    gameObject->setActive(false);
    child1->setParent(gameObject.get());
    child2->setParent(gameObject.get());

    MockComponent* component1 = child1->addComponent<MockComponent>();
    MockComponent* component2 = child2->addComponent<MockComponent>();

    Assert::IsFalse(component1->handleInputCalled());
    Assert::IsFalse(component2->handleInputCalled());

    sceneManager.handleInput();

    Assert::IsFalse(component1->handleInputCalled());
    Assert::IsFalse(component2->handleInputCalled());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Update_CallsUpdateOnAllActiveRoots)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> gameObject2(new GameObject());
    gameObject2->setActive(false);
    MockComponent* component = gameObject->addComponent<MockComponent>();
    MockComponent* component2 = gameObject2->addComponent<MockComponent>();

    Assert::IsFalse(component->updateCalled());
    Assert::IsFalse(component2->updateCalled());

    sceneManager.update(5);

    Assert::IsTrue(component->updateCalled());
    Assert::IsFalse(component2->updateCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Update_RootActive_CallsUpdateOnChildren)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> child1(new GameObject());
    std::unique_ptr<GameObject> child2(new GameObject());
    child1->setParent(gameObject.get());
    child2->setParent(gameObject.get());

    MockComponent* component1 = child1->addComponent<MockComponent>();
    MockComponent* component2 = child2->addComponent<MockComponent>();

    Assert::IsFalse(component1->updateCalled());
    Assert::IsFalse(component2->updateCalled());

    sceneManager.update(5);

    Assert::IsTrue(component1->updateCalled());
    Assert::IsTrue(component2->updateCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Update_RootActive_CallsUpdateOnActiveChildren)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> child1(new GameObject());
    std::unique_ptr<GameObject> child2(new GameObject());
    child1->setParent(gameObject.get());
    child2->setParent(gameObject.get());
    child1->setActive(false);

    MockComponent* component1 = child1->addComponent<MockComponent>();
    MockComponent* component2 = child2->addComponent<MockComponent>();

    Assert::IsFalse(component1->updateCalled());
    Assert::IsFalse(component2->updateCalled());

    sceneManager.update(5);

    Assert::IsFalse(component1->updateCalled());
    Assert::IsTrue(component2->updateCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Update_RootNotActive_DoesNotCallUpdateOnRoot)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    gameObject->setActive(false);
    MockComponent* component = gameObject->addComponent<MockComponent>();

    Assert::IsFalse(component->updateCalled());

    sceneManager.update(5);

    Assert::IsFalse(component->updateCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Update_RootNotActive_DoesNotCallUpdateOnChildren)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> child1(new GameObject());
    std::unique_ptr<GameObject> child2(new GameObject());
    gameObject->setActive(false);
    child1->setParent(gameObject.get());
    child2->setParent(gameObject.get());

    MockComponent* component1 = child1->addComponent<MockComponent>();
    MockComponent* component2 = child2->addComponent<MockComponent>();

    Assert::IsFalse(component1->updateCalled());
    Assert::IsFalse(component2->updateCalled());

    sceneManager.update(5);

    Assert::IsFalse(component1->updateCalled());
    Assert::IsFalse(component2->updateCalled());
  }

#pragma endregion

#pragma region Find Tests

#pragma region Predicate Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Find_InputtingPredicate_NoMatchingGameObject_ReturnsNullptr)
  {
    SceneManager sceneManager;
   
    Assert::IsNull(sceneManager.find([](const GameObject& /*gameObject*/) { return false; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Find_InputtingPredicate_OneMatchingGameObject_ReturnsCorrectPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());

    Assert::AreEqual(gameObject.get(), sceneManager.find([](const GameObject& /*gameObject*/) { return true; }));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Find_InputtingPredicate_MultipleMatchingGameObjects_ReturnsFirstMatchingPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> gameObject2(new GameObject());
    std::unique_ptr<GameObject> gameObject3(new GameObject());

    Assert::AreEqual(gameObject2.get(), sceneManager.find([&gameObject](const GameObject& go) { return gameObject.get() != &go; }));
  }

#pragma endregion

#pragma region StringId Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Find_InputtingStringId_NoMatchingGameObject_ReturnsNullptr)
  {
    SceneManager sceneManager;

    Assert::IsNull(sceneManager.find(internString("Test")));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Find_InputtingStringId_OneMatchingGameObject_ReturnsCorrectPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    gameObject->setName(internString("Test"));

    Assert::AreEqual(gameObject.get(), sceneManager.find(internString("Test")));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Find_InputtingStringId_MultipleMatchingGameObjects_ReturnsFirstMatchingPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> gameObject2(new GameObject());
    std::unique_ptr<GameObject> gameObject3(new GameObject());
    gameObject->setName(internString("Test"));
    gameObject2->setName(internString("Test2"));
    gameObject3->setName(internString("Test2"));

    Assert::AreEqual(gameObject2.get(), sceneManager.find(internString("Test2")));
  }

#pragma endregion

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Find_InputtingString_NoMatchingGameObject_ReturnsNullptr)
  {
    SceneManager sceneManager;

    Assert::IsNull(sceneManager.find("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Find_InputtingString_OneMatchingGameObject_ReturnsCorrectPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    gameObject->setName("Test");

    Assert::AreEqual(gameObject.get(), sceneManager.find("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_Find_InputtingString_MultipleMatchingGameObjects_ReturnsFirstMatchingPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> gameObject2(new GameObject());
    std::unique_ptr<GameObject> gameObject3(new GameObject());
    gameObject->setName("Test");
    gameObject2->setName("Test2");
    gameObject3->setName("Test2");

    Assert::AreEqual(gameObject2.get(), sceneManager.find("Test2"));
  }

#pragma endregion

#pragma endregion

#pragma region Find With Tag Tests

#pragma region StringId Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_FindWithTag_InputtingStringId_NoMatchingGameObject_ReturnsNullptr)
  {
    SceneManager sceneManager;

    Assert::IsNull(sceneManager.findWithTag(internString("Test")));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_FindWithTag_InputtingStringId_OneMatchingGameObject_ReturnsCorrectPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    gameObject->setTag(internString("Test"));

    Assert::AreEqual(gameObject.get(), sceneManager.findWithTag(internString("Test")));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_FindWithTag_InputtingStringId_MultipleMatchingGameObjects_ReturnsFirstMatchingPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> gameObject2(new GameObject());
    std::unique_ptr<GameObject> gameObject3(new GameObject());
    gameObject->setTag(internString("Test"));
    gameObject2->setTag(internString("Test2"));
    gameObject3->setTag(internString("Test2"));

    Assert::AreEqual(gameObject2.get(), sceneManager.findWithTag(internString("Test2")));
  }

#pragma endregion

#pragma region String Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_FindWithTag_InputtingString_NoMatchingGameObject_ReturnsNullptr)
  {
    SceneManager sceneManager;

    Assert::IsNull(sceneManager.findWithTag("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_FindWithTag_InputtingString_OneMatchingGameObject_ReturnsCorrectPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    gameObject->setTag("Test");

    Assert::AreEqual(gameObject.get(), sceneManager.findWithTag("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SceneManager_FindWithTag_InputtingString_MultipleMatchingGameObjects_ReturnsFirstMatchingPtr)
  {
    SceneManager sceneManager;
    std::unique_ptr<GameObject> gameObject(new GameObject());
    std::unique_ptr<GameObject> gameObject2(new GameObject());
    std::unique_ptr<GameObject> gameObject3(new GameObject());
    gameObject->setTag("Test");
    gameObject2->setTag("Test2");
    gameObject3->setTag("Test2");

    Assert::AreEqual(gameObject2.get(), sceneManager.findWithTag("Test2"));
  }

#pragma endregion

#pragma endregion

  };
}