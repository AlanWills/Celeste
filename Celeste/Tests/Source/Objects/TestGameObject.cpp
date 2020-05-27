#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "UtilityMacros/Unused.h"

#include "Objects/GameObject.h"
#include "UID/StringId.h"
#include "Mocks/Objects/MockManagedComponent.h"
#include "Mocks/Objects/MockUnmanagedComponent.h"
#include "Mocks/Rendering/MockSpriteBatch.h"
#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "Mocks/Rendering/MockTextRenderer.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste;


ARE_PTRS_EQUAL(MockManagedComponent);
ARE_PTRS_EQUAL(MockUnmanagedComponent);

namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestGameObject)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Constructor_SetsAllInitialValuesCorrectly)
  {
    GameObject gameObject;

    Assert::AreEqual((StringId)0, gameObject.getName());
    Assert::AreEqual((StringId)0, gameObject.getTag());
    Assert::AreEqual((size_t)0, gameObject.getChildCount());
    Assert::IsNotNull(gameObject.getTransform());
  }

#pragma endregion

#pragma region Set Tag Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetTag_WithStringId)
  {
    GameObject gameObject;
      
    Assert::AreEqual((StringId)0, gameObject.getTag());

    StringId id = internString("Test");
    gameObject.setTag(id);

    Assert::AreEqual(id, gameObject.getTag());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetTag_WithString)
  {
    GameObject gameObject;

    Assert::AreEqual((StringId)0, gameObject.getTag());

    StringId id = internString("Test");
    gameObject.setTag("Test");

    Assert::AreEqual(id, gameObject.getTag());
  }

#pragma endregion

#pragma region Set Name Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetName_WithStringId)
  {
    GameObject gameObject;

    Assert::AreEqual((StringId)0, gameObject.getName());

    StringId id = internString("Test");
    gameObject.setName(id);

    Assert::AreEqual(id, gameObject.getName());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetName_WithString)
  {
    GameObject gameObject;

    Assert::AreEqual((StringId)0, gameObject.getName());

    StringId id = internString("Test");
    gameObject.setName("Test");

    Assert::AreEqual(id, gameObject.getName());
  }

#pragma endregion

#pragma region Set Active Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetActive_ToFalse_ShouldSetAllUnmanagedComponentsToAddToInActive)
  {
    GameObject gameObject;

    observer_ptr<MockUnmanagedComponent> component1 = gameObject.addComponent<MockUnmanagedComponent>();
    observer_ptr<MockUnmanagedComponent> component2 = gameObject.addComponent<MockUnmanagedComponent>();
    component2->setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(component1);
    AssertCel::IsNotActive(component2);

    gameObject.setActive(false);

    AssertCel::IsNotActive(gameObject);
    AssertCel::IsNotActive(component1);
    AssertCel::IsNotActive(component2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetActive_ToFalse_ShouldSetAllUnmanagedComponentsToInActive)
  {
    GameObject gameObject;

    observer_ptr<MockUnmanagedComponent> component1 = gameObject.addComponent<MockUnmanagedComponent>();
    observer_ptr<MockUnmanagedComponent> component2 = gameObject.addComponent<MockUnmanagedComponent>();
    component2->setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(component1);
    AssertCel::IsNotActive(component2);

    // Add components now
    gameObject.update(0);
    gameObject.setActive(false);

    AssertCel::IsNotActive(gameObject);
    AssertCel::IsNotActive(component1);
    AssertCel::IsNotActive(component2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetActive_ToFalse_ShouldSetAllManagedComponentsToInActive)
  {
    GameObject gameObject;

    observer_ptr<MockManagedComponent> component1 = gameObject.addComponent<MockManagedComponent>();
    observer_ptr<MockManagedComponent> component2 = gameObject.addComponent<MockManagedComponent>();
    component2->setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(component1);
    AssertCel::IsNotActive(component2);

    // Add components now
    gameObject.update(0);
    gameObject.setActive(false);

    AssertCel::IsNotActive(gameObject);
    AssertCel::IsNotActive(component1);
    AssertCel::IsNotActive(component2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetActive_ToFalse_DoesNotModifyChildGameObjectActiveFlag)
  {
    GameObject gameObject;
    GameObject child1;
    GameObject child2;
      
    child1.getTransform()->setParent(gameObject.getTransform());
    child2.getTransform()->setParent(gameObject.getTransform());
    child2.setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(child1);
    AssertCel::IsNotActive(child2);

    gameObject.setActive(false);

    AssertCel::IsNotActive(gameObject);
    AssertCel::IsActive(child1);
    AssertCel::IsNotActive(child2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetActive_ToTrue_ShouldSetAllUnmanagedComponentsToAddToActive)
  {
    GameObject gameObject;

    observer_ptr<MockUnmanagedComponent> component1 = gameObject.addComponent<MockUnmanagedComponent>();
    observer_ptr<MockUnmanagedComponent> component2 = gameObject.addComponent<MockUnmanagedComponent>();
    component2->setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(component1);
    AssertCel::IsNotActive(component2);

    gameObject.setActive(true);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(component1);
    AssertCel::IsActive(component2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetActive_ToTrue_ShouldSetAllUnmanagedComponentsToActive)
  {
    GameObject gameObject;

    observer_ptr<MockUnmanagedComponent> component1 = gameObject.addComponent<MockUnmanagedComponent>();
    observer_ptr<MockUnmanagedComponent> component2 = gameObject.addComponent<MockUnmanagedComponent>();
    component2->setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(component1);
    AssertCel::IsNotActive(component2);

    // Add components now
    gameObject.update(0);
    gameObject.setActive(true);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(component1);
    AssertCel::IsActive(component2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetActive_ToTrue_ShouldSetAllManagedComponentsToActive)
  {
    GameObject gameObject;

    observer_ptr<MockManagedComponent> component1 = gameObject.addComponent<MockManagedComponent>();
    observer_ptr<MockManagedComponent> component2 = gameObject.addComponent<MockManagedComponent>();
    component2->setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(component1);
    AssertCel::IsNotActive(component2);

    // Add components now
    gameObject.update(0);
    gameObject.setActive(true);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(component1);
    AssertCel::IsActive(component2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetActive_ToTrue_DoesNotModifyChildGameObjectActiveFlag)
  {
    GameObject gameObject;
    GameObject child1;
    GameObject child2;

    child1.getTransform()->setParent(gameObject.getTransform());
    child2.getTransform()->setParent(gameObject.getTransform());
    child2.setActive(false);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(child1);
    AssertCel::IsNotActive(child2);

    gameObject.setActive(true);

    AssertCel::IsActive(gameObject);
    AssertCel::IsActive(child1);
    AssertCel::IsNotActive(child2);
  }

#pragma endregion

#pragma region Get Parent Transform Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetParentTransform_WithNullTransformParent_ReturnsNull)
  {
    GameObject gameObject;

    Assert::IsNotNull(gameObject.getTransform());
    Assert::IsNull(gameObject.getTransform()->getParent());
    Assert::IsNull(gameObject.getParentTransform());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetParentTransform_WithTransformParent_ReturnsCorrectTransformParent)
  {
    GameObject gameObject, parent;
      
    Assert::IsNotNull(gameObject.getTransform());

    gameObject.setParentTransform(parent.getTransform());

    Assert::AreEqual(parent.getTransform(), gameObject.getTransform()->getParent());
    Assert::AreEqual(parent.getTransform(), gameObject.getParentTransform());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetConstParentTransform_WithNullTransformParent_ReturnsConstNull)
  {
    GameObject gameObject;
    const GameObject& cgameObject = gameObject;

    Assert::IsNotNull(cgameObject.getTransform());
    Assert::IsNull(cgameObject.getTransform()->getParent());
    Assert::IsNull(cgameObject.getParentTransform());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetConstParentTransform_WithTransformParent_ReturnsCorrectTransformParentConst)
  {
    GameObject gameObject, parent;

    const GameObject& cgameObject = gameObject;

    Assert::IsNotNull(cgameObject.getTransform());

    gameObject.setParentTransform(parent.getTransform());

    Assert::AreEqual(static_cast<const Transform*>(parent.getTransform()), cgameObject.getTransform()->getParent());
    Assert::AreEqual(static_cast<const Transform*>(parent.getTransform()), cgameObject.getParentTransform());
  }

#pragma endregion

#pragma region Set Parent Transform Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetParentTransform_InputtingTransform_SetsTransformParentToInput)
  {
    GameObject parent;
    GameObject parent2;
    GameObject gameObject;

    Assert::IsNotNull(gameObject.getTransform());

    gameObject.setParentTransform(parent.getTransform());

    Assert::AreEqual(parent.getTransform(), gameObject.getTransform()->getParent());

    gameObject.setParentTransform(parent2.getTransform());

    Assert::AreEqual(parent2.getTransform(), gameObject.getTransform()->getParent());
  }

#pragma endregion

#pragma region Set Parent Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetParent_InputtingNullGameObject_SetsParentToNullptr)
  {
    GameObject parent;
    GameObject gameObject;
    gameObject.setParent(&parent);

    Assert::AreEqual(&parent, gameObject.getParent());

    gameObject.setParent(nullptr);

    Assert::IsNull(gameObject.getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetParent_InputtingGameObject_SetsParentToInputtedGameObject)
  {
    GameObject parent;
    GameObject parent2;
    GameObject gameObject;

    Assert::IsNotNull(gameObject.getTransform());

    gameObject.setParent(&parent);

    Assert::AreEqual(&parent, gameObject.getParent());

    gameObject.setParent(&parent2);

    Assert::AreEqual(&parent2, gameObject.getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_SetParent_InputtingGameObject_SetsParentTransformToInputtedGameObjectTransform)
  {
    GameObject parent;
    GameObject parent2;
    GameObject gameObject;

    Assert::IsNotNull(gameObject.getTransform());

    gameObject.setParent(&parent);

    Assert::AreEqual(parent.getTransform(), gameObject.getTransform()->getParent());

    gameObject.setParent(&parent2);

    Assert::AreEqual(parent2.getTransform(), gameObject.getTransform()->getParent());
  }

#pragma endregion

#pragma region Get Child Count Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetChildCount_NoChildren_ReturnsZero)
  {
    GameObject gameObject;

    Assert::IsNotNull(gameObject.getTransform());
    Assert::AreEqual((size_t)0, gameObject.getTransform()->getChildCount());
    Assert::AreEqual((size_t)0, gameObject.getChildCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetChildCount_WithChildren_ReturnsCorrectChildCount)
  {
    GameObject gameObject;
    GameObject child1;
    GameObject child2;
      
    child1.getTransform()->setParent(gameObject.getTransform());
    child2.getTransform()->setParent(gameObject.getTransform());

    Assert::IsNotNull(gameObject.getTransform());
    Assert::AreEqual((size_t)2, gameObject.getTransform()->getChildCount());
    Assert::AreEqual((size_t)2, gameObject.getChildCount());
  }

#pragma endregion

#pragma region Get Child Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetChild_NoChildren_ReturnsNullGameObject)
  {
    GameObject gameObject;

    Assert::IsNotNull(gameObject.getTransform());
    Assert::IsNull(gameObject.getTransform()->getChildGameObject(0));
    Assert::IsNull(gameObject.getChild(0));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetChild_WithChildren_ReturnsCorrectGameObject)
  {
    GameObject gameObject;
    GameObject child1;
    GameObject child2;
      
    child1.getTransform()->setParent(gameObject.getTransform());
    child2.getTransform()->setParent(gameObject.getTransform());

    Assert::IsNotNull(gameObject.getTransform());
    Assert::IsTrue(&child1 == gameObject.getTransform()->getChildGameObject(0));
    Assert::IsTrue(&child2 == gameObject.getTransform()->getChildGameObject(1));
    Assert::IsTrue(&child1 == gameObject.getChild(0));
    Assert::IsTrue(&child2 == gameObject.getChild(1));
  }

#pragma endregion

#pragma region Find Child Tests

#pragma region String Id Input

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindChild_StringId_NoChildren_ReturnsNull)
  {
    GameObject gameObject;

    Assert::AreEqual((size_t)0, gameObject.getChildCount());
    Assert::IsNull(gameObject.findChild(internString("Test")));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindChild_StringId_InputtingNameWhichDoesntHaveMatch_ReturnsNull)
  {
    GameObject gameObject;
    GameObject child1;
      
    child1.setParent(&gameObject);
    child1.setName("Test_2");

    Assert::AreEqual((size_t)1, gameObject.getChildCount());
    Assert::IsNull(gameObject.findChild(internString("Test")));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindChild_StringId_InputtingNameWhichDoesHaveMatch_ReturnsGameObject)
  {
    GameObject gameObject;
    GameObject child1;
      
    child1.setParent(&gameObject);
    child1.setName("Test");

    Assert::AreEqual((size_t)1, gameObject.getChildCount());
    Assert::IsTrue(&child1 == gameObject.findChild(internString("Test")));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindChild_StringId_InputtingNameWhichDoesHaveMultipleMatchs_ReturnsFirstMatchingGameObject)
  {
    GameObject gameObject;
    GameObject child1;
    GameObject child2;
      
    child1.setParent(&gameObject);
    child1.setName("Test");
    child2.setParent(&gameObject);
    child2.setName("Test");

    Assert::AreEqual((size_t)2, gameObject.getChildCount());
    Assert::IsTrue(&child1 == gameObject.findChild(internString("Test")));
  }

#pragma endregion

#pragma region String Input

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindChild_String_NoChildren_ReturnsNull)
  {
    GameObject gameObject;

    Assert::AreEqual((size_t)0, gameObject.getChildCount());
    Assert::IsNull(gameObject.findChild("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindChild_String_InputtingNameWhichDoesntHaveMatch_ReturnsNull)
  {
    GameObject gameObject;
    GameObject child1;
      
    child1.setParent(&gameObject);
    child1.setName("Test_2");

    Assert::AreEqual((size_t)1, gameObject.getChildCount());
    Assert::IsNull(gameObject.findChild("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindChild_String_InputtingNameWhichDoesHaveMatch_ReturnsGameObject)
  {
    GameObject gameObject;
    GameObject child1;
      
    child1.setParent(&gameObject);
    child1.setName("Test");

    Assert::AreEqual((size_t)1, gameObject.getChildCount());
    Assert::IsTrue(&child1 == gameObject.findChild("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindChild_String_InputtingNameWhichDoesHaveMultipleMatchs_ReturnsFirstMatchingGameObject)
  {
    GameObject gameObject;
    GameObject child1;
    GameObject child2;
      
    child1.setParent(&gameObject);
    child1.setName("Test");
    child2.setParent(&gameObject);
    child2.setName("Test");

    Assert::AreEqual((size_t)2, gameObject.getChildCount());
    Assert::IsTrue(&child1 == gameObject.findChild("Test"));
  }

#pragma endregion

#pragma endregion

#pragma region For Each Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_ForEach_TransformHasNoChildren_PerformsNoIteration)
  {
    GameObject gameObject;

    Assert::IsNotNull(gameObject.getTransform());
    Assert::AreEqual((size_t)0, gameObject.getTransform()->getChildCount());

    int counter = 0;
    for (observer_ptr<GameObject> child : gameObject)
    {
      UNUSED(child);
      ++counter;
    }

    Assert::AreEqual(0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_ForEach_TransformHasChildren_PerformsIterationOverEachChildTransformsGameObject)
  {
    GameObject gameObject;
    GameObject child1;
    GameObject child2;
      
    child1.setParent(&gameObject);
    child2.setParent(&gameObject);

    Assert::IsNotNull(gameObject.getTransform());
    Assert::AreEqual((size_t)2, gameObject.getTransform()->getChildCount());

    std::vector<observer_ptr<GameObject>> gameObjects;
    for (observer_ptr<GameObject> child : gameObject)
    {
      UNUSED(child);
      gameObjects.push_back(child);
    }

    Assert::AreEqual((size_t)2, gameObjects.size());
    Assert::IsTrue(&child1 == gameObjects[0]);
    Assert::IsTrue(&child2 == gameObjects[1]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Constructor_Sets_ActiveToTrue)
  {
    GameObject gameObject;

    Assert::IsTrue(gameObject.isActive());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Constructor_AllocatesTransform_AndSetsTransformGameObjectToGameObject)
  {
    GameObject gameObject;

    Assert::IsNotNull(gameObject.getTransform());
    Assert::AreEqual(&gameObject, gameObject.getTransform()->getGameObject());
  }

#pragma endregion

#pragma region Add Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_AddComponent_WhenInitialized_AddsComponent)
  {
    GameObject gameObject;
    gameObject.addComponent<MockManagedComponent>();
      
    Assert::IsTrue(gameObject.hasComponent<MockManagedComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_AddComponent_SetsComponentGameObject_ToGameObject)
  {
    GameObject gameObject;
    observer_ptr<MockManagedComponent> component = gameObject.addComponent<MockManagedComponent>();

    Assert::AreSame(component->getGameObject(), gameObject);
  }

#pragma endregion

#pragma region Has Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_HasComponent_ManagedComponent_ShouldReturnTrue)
  {
    GameObject gameObject;
    gameObject.addComponent<MockManagedComponent>();

    Assert::IsTrue(gameObject.hasComponent<MockManagedComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_HasComponent_ManagedComponent_ShouldReturnFalse)
  {
    GameObject gameObject;

    Assert::IsFalse(gameObject.hasComponent<MockManagedComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_HasComponent_UnmanagedComponent_ShouldReturnTrue)
  {
    GameObject gameObject;
    observer_ptr<MockUnmanagedComponent> script = gameObject.addComponent<MockUnmanagedComponent>();

    Assert::IsTrue(gameObject.findComponent<MockUnmanagedComponent>() == script);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_HasComponent_UnmanagedComponent_ShouldReturnFalse)
  {
    GameObject gameObject;

    Assert::IsFalse(gameObject.hasComponent<MockUnmanagedComponent>());
  }

#pragma endregion

#pragma region Get Component Count Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetComponentCount_NoComponents_ReturnsZero)
  {
    GameObject gameObject;

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetComponentCount_WithComponents_ReturnsCorrectNumberOfComponents)
  {
    GameObject gameObject;
    gameObject.addComponent<MockManagedComponent>();
    gameObject.addComponent<MockManagedComponent>();

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getComponentCount());
  }

#pragma endregion

#pragma region Get Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetComponent_InputtingInvalidIndex_ReturnsNull)
  {
    GameObject gameObject;

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    Assert::IsNull(gameObject.getComponent(0));

    gameObject.addComponent<MockManagedComponent>();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());
    Assert::IsNull(gameObject.getComponent(1));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetComponent_InputtingValidIndex_ReturnsCorrect)
  {
    GameObject gameObject;
    observer_ptr<MockManagedComponent> component = gameObject.addComponent<MockManagedComponent>();
    observer_ptr<MockManagedComponent> component2 = gameObject.addComponent<MockManagedComponent>();

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getComponentCount());
    Assert::IsTrue(component == gameObject.getComponent(0));
    Assert::IsTrue(component2 == gameObject.getComponent(1));
  }

#pragma endregion

#pragma region Get Const Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetConstComponent_InputtingInvalidIndex_ReturnsNull)
  {
    GameObject gameObject;

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    Assert::IsNull(gameObject.getConstComponent(0));

    gameObject.addComponent<MockManagedComponent>();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());
    Assert::IsNull(gameObject.getConstComponent(1));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_GetConstComponent_InputtingValidIndex_ReturnsCorrect)
  {
    GameObject gameObject;
    observer_ptr<MockManagedComponent> component = gameObject.addComponent<MockManagedComponent>();
    observer_ptr<MockManagedComponent> component2 = gameObject.addComponent<MockManagedComponent>();

    Assert::AreEqual(static_cast<size_t>(2), gameObject.getComponentCount());
    Assert::IsTrue(component == gameObject.getConstComponent(0));
    Assert::IsTrue(component2 == gameObject.getConstComponent(1));
  }

#pragma endregion

#pragma region Find Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindComponent_WithManagedComponent_ShouldFindComponent)
  {
    GameObject gameObject;
    observer_ptr<MockManagedComponent> component = gameObject.addComponent<MockManagedComponent>();

    Assert::IsTrue(gameObject.findComponent<MockManagedComponent>() == component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindComponent_WithManagedComponent_ShouldntFindComponent)
  {
    GameObject gameObject;

    Assert::IsNull(gameObject.findComponent<MockManagedComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindComponent_WithUnmanagedComponent_ShouldFindComponent)
  {
    GameObject gameObject;
    observer_ptr<MockUnmanagedComponent> script = gameObject.addComponent<MockUnmanagedComponent>();

    Assert::IsTrue(gameObject.findComponent<MockUnmanagedComponent>() == script);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindComponent_WithUnmanagedComponent_ShouldntFindComponent)
  {
    GameObject gameObject;

    Assert::IsNull(gameObject.findComponent<MockUnmanagedComponent>());
  }

#pragma endregion

#pragma region Find Const Component Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindConstComponent_WithManagedComponent_ShouldFindComponent)
  {
    GameObject gameObject;
    observer_ptr<MockManagedComponent> component = gameObject.addComponent<MockManagedComponent>();

    const MockManagedComponent* handle = static_cast<const GameObject*>(&gameObject)->findComponent<MockManagedComponent>();

    Assert::IsTrue(handle == component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindConstComponent_WithManagedComponent_ShouldntFindComponent)
  {
    GameObject gameObject;

    Assert::IsNull(static_cast<const GameObject*>(&gameObject)->findComponent<MockManagedComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindConstComponent_WithUnmanagedComponent_ShouldFindComponent)
  {
    GameObject gameObject;
    observer_ptr<MockUnmanagedComponent> script = gameObject.addComponent<MockUnmanagedComponent>();

    const MockUnmanagedComponent* handle = static_cast<const GameObject*>(&gameObject)->findComponent<MockUnmanagedComponent>();

    Assert::IsTrue(handle == script);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_FindConstComponent_WithUnmanagedComponent_ShouldntFindComponent)
  {
    GameObject gameObject;

    Assert::IsNull(static_cast<const GameObject*>(&gameObject)->findComponent<MockUnmanagedComponent>());
  }

#pragma endregion

#pragma region Remove Component

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_RemoveComponent_InputtingNull_DoesNothing)
  {
    GameObject gameObject;
    gameObject.removeComponent(nullptr);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_RemoveComponent_InputtingManagedComponentNotInGameObject_DoesNothing)
  {
    GameObject gameObject, ownerGameObject;
    MockManagedComponent component(ownerGameObject);

    AssertCel::IsActive(component);
    Assert::AreNotSame(gameObject, component.getGameObject());

    gameObject.removeComponent(&component);

    AssertCel::IsActive(component);

    GameObject gameObject2;
    observer_ptr<MockManagedComponent> component2 = gameObject2.addComponent<MockManagedComponent>();

    Assert::IsNotNull(component2);
    AssertCel::IsActive(component2);
    Assert::AreNotSame(gameObject, component2->getGameObject());

    gameObject.removeComponent(component2);

    Assert::IsNotNull(component2);
    AssertCel::IsActive(component2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_RemoveComponent_InputtingManagedComponentInGameObject_MakesHasComponentReturnFalse)
  {
    GameObject gameObject;
    observer_ptr<MockManagedComponent> script = gameObject.addComponent<MockManagedComponent>();

    AssertCel::HasComponent<MockManagedComponent>(gameObject);

    gameObject.removeComponent(script);

    AssertCel::DoesNotHaveComponent<MockManagedComponent>(gameObject);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_RemoveComponent_InputtingManagedComponentInGameObject_MakesFindComponentReturnNull)
  {
    GameObject gameObject;
    observer_ptr<MockManagedComponent> component = gameObject.addComponent<MockManagedComponent>();

    Assert::AreEqual(component, gameObject.findComponent<MockManagedComponent>());

    gameObject.removeComponent(component);

    Assert::IsNull(gameObject.findComponent<MockManagedComponent>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_RemoveComponent_InputtingManagedComponentInGameObject_RemovesFromGameObject)
  {
    GameObject gameObject;
    observer_ptr<MockManagedComponent> component = gameObject.addComponent<MockManagedComponent>();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());

    gameObject.removeComponent(component);

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_RemoveComponent_InputtingUnmanagedComponentInGameObject_RemovesFromGameObject)
  {
    GameObject gameObject;
    observer_ptr<MockUnmanagedComponent> script = gameObject.addComponent<MockUnmanagedComponent>();

    Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());

    gameObject.removeComponent(script);

    Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
  }

#pragma endregion

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Update_CallsUpdateOnAllUnmanagedComponents_WhichAreActive)
  {
    GameObject gameObject;
    observer_ptr<MockUnmanagedComponent> script1 = gameObject.addComponent<MockUnmanagedComponent>();
    observer_ptr<MockUnmanagedComponent> script2 = gameObject.addComponent<MockUnmanagedComponent>();
    observer_ptr<MockUnmanagedComponent> script3 = gameObject.addComponent<MockUnmanagedComponent>();

    script2->setActive(false);
    gameObject.update(0);

    Assert::IsTrue(script1->updateCalled());
    Assert::IsFalse(script2->updateCalled());
    Assert::IsTrue(script3->updateCalled());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Update_DoesNotCallUpdateOnComponents)
  {
    GameObject gameObject;
    observer_ptr<MockManagedComponent> component = gameObject.addComponent<MockManagedComponent>();

    gameObject.update(0);

    Assert::IsFalse(component->updateCalled());
  }

#pragma endregion

#pragma region Render Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Render_WithNoRenderComponents_DoesNotThrow)
  {
    GameObject gameObject;
    MockSpriteBatch spriteBatch;
    spriteBatch.initialize();

    Assert::IsFalse(gameObject.hasComponent<Celeste::Rendering::Renderer>());
    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    gameObject.render(spriteBatch, 0);

    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Render_WithActiveSpriteRenderer_AddsToSpriteBatch)
  {
    GameObject gameObject;
    observer_ptr<MockSpriteRenderer> spriteRenderer = gameObject.addComponent<MockSpriteRenderer>();
    MockSpriteBatch spriteBatch;
    spriteBatch.initialize();

    Assert::IsTrue(gameObject.hasComponent<Celeste::Rendering::SpriteRenderer>());
    AssertCel::IsActive(*spriteRenderer);
    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    gameObject.render(spriteBatch, 0);

    Assert::AreEqual((size_t)1, spriteBatch.renderers_size_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Render_WithNonActiveSpriteRenderer_DoesNotAddToSpriteBatch)
  {
    GameObject gameObject;
    observer_ptr<MockSpriteRenderer> spriteRenderer = gameObject.addComponent<MockSpriteRenderer>();
    spriteRenderer->setActive(false);
    MockSpriteBatch spriteBatch;
    spriteBatch.initialize();

    Assert::IsTrue(gameObject.hasComponent<Celeste::Rendering::SpriteRenderer>());
    AssertCel::IsNotActive(*spriteRenderer);
    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    gameObject.render(spriteBatch, 0);

    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Render_WithActiveTextRenderer_AddsToSpriteBatch)
  {
    GameObject gameObject;
    observer_ptr<MockTextRenderer> textRenderer = gameObject.addComponent<MockTextRenderer>();
    MockSpriteBatch spriteBatch;
    spriteBatch.initialize();

    Assert::IsTrue(gameObject.hasComponent<Celeste::Rendering::TextRenderer>());
    AssertCel::IsActive(*textRenderer);
    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    gameObject.render(spriteBatch, 0);

    Assert::AreEqual((size_t)1, spriteBatch.renderers_size_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Render_WithNonActiveTextRenderer_DoesNotAddToSpriteBatch)
  {
    GameObject gameObject;
    observer_ptr<MockTextRenderer> textRenderer = gameObject.addComponent<MockTextRenderer>();
    textRenderer->setActive(false);
    MockSpriteBatch spriteBatch;
    spriteBatch.initialize();

    Assert::IsTrue(gameObject.hasComponent<Celeste::Rendering::TextRenderer>());
    AssertCel::IsNotActive(*textRenderer);
    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    gameObject.render(spriteBatch, 0);

    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Render_WithActiveSpriteAndTextRenderers_AddsBothToSpriteBatch)
  {
    GameObject gameObject;
    observer_ptr<MockSpriteRenderer> spriteRenderer = gameObject.addComponent<MockSpriteRenderer>();
    observer_ptr<MockTextRenderer> textRenderer = gameObject.addComponent<MockTextRenderer>();
    MockSpriteBatch spriteBatch;
    spriteBatch.initialize();

    Assert::IsTrue(gameObject.hasComponent<Celeste::Rendering::SpriteRenderer>());
    Assert::IsTrue(gameObject.hasComponent<Celeste::Rendering::TextRenderer>());
    AssertCel::IsActive(*spriteRenderer);
    AssertCel::IsActive(*textRenderer);
    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    gameObject.render(spriteBatch, 0);

    Assert::AreEqual((size_t)2, spriteBatch.renderers_size_Public());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(GameObject_Render_WithNonActiveSpriteAndTextRenderers_DoesNotAddEitherToSpriteBatch)
  {
    GameObject gameObject;
    observer_ptr<MockSpriteRenderer> spriteRenderer = gameObject.addComponent<MockSpriteRenderer>();
    observer_ptr<MockTextRenderer> textRenderer = gameObject.addComponent<MockTextRenderer>();
    spriteRenderer->setActive(false);
    textRenderer->setActive(false);
    MockSpriteBatch spriteBatch;
    spriteBatch.initialize();

    Assert::IsTrue(gameObject.hasComponent<Celeste::Rendering::SpriteRenderer>());
    Assert::IsTrue(gameObject.hasComponent<Celeste::Rendering::TextRenderer>());
    AssertCel::IsNotActive(*spriteRenderer);
    AssertCel::IsNotActive(*textRenderer);
    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());

    gameObject.render(spriteBatch, 0);

    Assert::AreEqual((size_t)0, spriteBatch.renderers_size_Public());
  }

#pragma endregion

  };
}