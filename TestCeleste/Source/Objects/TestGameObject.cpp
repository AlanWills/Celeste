#include "UtilityHeaders/UnitTestHeaders.h"

#include "Objects/GameObject.h"
#include "UID/StringId.h"
#include "Mocks/Objects/MockComponent.h"
#include "Mocks/Objects/MockScript.h"
#include "Mocks/Objects/MockGameObject.h"
#include "Screens/Screen.h"
#include "Mocks/Rendering/MockSpriteBatch.h"
#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "Mocks/Rendering/MockTextRenderer.h"
#include "AssertCel.h"

using namespace Celeste;


ARE_PTRS_EQUAL(MockComponent);
ARE_PTRS_EQUAL(MockScript);

namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestGameObject)

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_Constructor_SetsAllInitialValuesCorrectly)
    {
      MockGameObject gameObject;

      Assert::AreEqual((StringId)0, gameObject.getName());
      Assert::AreEqual((StringId)0, gameObject.getTag());
      Assert::AreEqual((size_t)0, gameObject.getChildCount());
      Assert::IsNull(gameObject.getTransform());
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
    TEST_METHOD(GameObject_SetActive_ToFalse_ShouldSetAllScriptsToAddToInActive)
    {
      GameObject gameObject;

      AutoDeallocator<MockScript> component1 = gameObject.addComponent<MockScript>();
      AutoDeallocator<MockScript> component2 = gameObject.addComponent<MockScript>();
      component2->setActive(false);

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(component1.get());
      AssertCel::IsNotActive(component2.get());

      gameObject.setActive(false);

      AssertCel::IsNotActive(gameObject);
      AssertCel::IsNotActive(component1.get());
      AssertCel::IsNotActive(component2.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_SetActive_ToFalse_ShouldSetAllScriptsToInActive)
    {
      GameObject gameObject;

      AutoDeallocator<MockScript> component1 = gameObject.addComponent<MockScript>();
      AutoDeallocator<MockScript> component2 = gameObject.addComponent<MockScript>();
      component2->setActive(false);

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(component1.get());
      AssertCel::IsNotActive(component2.get());

      // Add components now
      gameObject.update(0);
      gameObject.setActive(false);

      AssertCel::IsNotActive(gameObject);
      AssertCel::IsNotActive(component1.get());
      AssertCel::IsNotActive(component2.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_SetActive_ToFalse_ShouldSetAllComponentsToInActive)
    {
      GameObject gameObject;

      AutoDeallocator<MockComponent> component1 = gameObject.addComponent<MockComponent>();
      AutoDeallocator<MockComponent> component2 = gameObject.addComponent<MockComponent>();
      component2->setActive(false);

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(component1.get());
      AssertCel::IsNotActive(component2.get());

      // Add components now
      gameObject.update(0);
      gameObject.setActive(false);

      AssertCel::IsNotActive(gameObject);
      AssertCel::IsNotActive(component1.get());
      AssertCel::IsNotActive(component2.get());
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
    TEST_METHOD(GameObject_SetActive_ToTrue_ShouldSetAllScriptsToAddToActive)
    {
      GameObject gameObject;

      AutoDeallocator<MockScript> component1 = gameObject.addComponent<MockScript>();
      AutoDeallocator<MockScript> component2 = gameObject.addComponent<MockScript>();
      component2->setActive(false);

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(component1.get());
      AssertCel::IsNotActive(component2.get());

      gameObject.setActive(true);

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(component1.get());
      AssertCel::IsActive(component2.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_SetActive_ToTrue_ShouldSetAllScriptsToActive)
    {
      GameObject gameObject;

      AutoDeallocator<MockScript> component1 = gameObject.addComponent<MockScript>();
      AutoDeallocator<MockScript> component2 = gameObject.addComponent<MockScript>();
      component2->setActive(false);

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(component1.get());
      AssertCel::IsNotActive(component2.get());

      // Add components now
      gameObject.update(0);
      gameObject.setActive(true);

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(component1.get());
      AssertCel::IsActive(component2.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_SetActive_ToTrue_ShouldSetAllComponentsToActive)
    {
      GameObject gameObject;

      AutoDeallocator<MockComponent> component1 = gameObject.addComponent<MockComponent>();
      AutoDeallocator<MockComponent> component2 = gameObject.addComponent<MockComponent>();
      component2->setActive(false);

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(component1.get());
      AssertCel::IsNotActive(component2.get());

      // Add components now
      gameObject.update(0);
      gameObject.setActive(true);

      AssertCel::IsActive(gameObject);
      AssertCel::IsActive(component1.get());
      AssertCel::IsActive(component2.get());
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
    TEST_METHOD(GameObject_GetParentTransform_WithNullTransform_ReturnsNull)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());
      Assert::IsNull(gameObject.getParentTransform());
    }

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
      GameObject gameObject;
      
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      
      Assert::IsNotNull(gameObject.getTransform());

      gameObject.setParentTransform(parent.get());

      Assert::AreEqual(parent.get(), gameObject.getTransform()->getParent());
      Assert::AreEqual(parent.get(), gameObject.getParentTransform());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetConstParentTransform_WithNullTransform_ReturnsConstNull)
    {
      GameObject gameObject;
      const GameObject& cgameObject = gameObject;

      Assert::IsNull(cgameObject.getTransform());
      Assert::IsNull(cgameObject.getParentTransform());
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
      GameObject gameObject;

      const GameObject& cgameObject = gameObject;
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());

      Assert::IsNotNull(cgameObject.getTransform());

      gameObject.setParentTransform(parent.get());

      Assert::AreEqual(static_cast<const Transform*>(parent.get()), cgameObject.getTransform()->getParent());
      Assert::AreEqual(static_cast<const Transform*>(parent.get()), cgameObject.getParentTransform());
    }

#pragma endregion

#pragma region Set Parent Transform Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_SetParentTransform_WithNullTransform_InputtingTransform_DoesNothing)
    {
      GameObject gameObject;
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());

      Assert::IsNull(gameObject.getTransform());

      gameObject.setParentTransform(transform.get());
    }

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

#pragma region Get Parent Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetParent_WithNullTransform_ReturnsNull)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());
      Assert::IsNull(gameObject.getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetParent_WithNullTransformParent_ReturnsNull)
    {
      GameObject gameObject;

      Assert::IsNotNull(gameObject.getTransform());
      Assert::IsNull(gameObject.getParentTransform());
      Assert::IsNull(gameObject.getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetParent_WithTransformParentGameObject_ReturnsCorrectGameObject)
    {
      GameObject gameObject;
      GameObject parentGameObject;
     
      AutoDeallocator<Transform> parent = Transform::allocate(parentGameObject);
      gameObject.setParentTransform(parent.get());

      Assert::AreEqual(parent.get(), gameObject.getParentTransform());
      Assert::IsTrue(&parentGameObject == parent->getGameObject());
      Assert::IsTrue(&parentGameObject == gameObject.getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetConstParent_WithNullTransform_ReturnsConstNull)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());
      Assert::IsNull(static_cast<const GameObject&>(gameObject).getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetConstParent_WithNullTransformParent_ReturnsConstNull)
    {
      GameObject gameObject;

      Assert::IsNotNull(gameObject.getTransform());
      Assert::IsNull(gameObject.getParentTransform());
      Assert::IsNull(static_cast<const GameObject&>(gameObject).getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetConstParent_WithTransformParentGameObject_ReturnsCorrectConstGameObject)
    {
      GameObject gameObject;
      GameObject parentGameObject;
      
      AutoDeallocator<Transform> parent = Transform::allocate(parentGameObject);
      gameObject.setParentTransform(parent.get());

      Assert::AreEqual(parent.get(), gameObject.getParentTransform());
      Assert::IsTrue(&parentGameObject == parent->getGameObject());
      Assert::IsTrue(&parentGameObject == static_cast<const GameObject*>(&gameObject)->getParent());
    }

#pragma endregion

#pragma region Set Parent Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_SetParent_WithNullTransform_InputtingGameObject_DoesNothing)
    {
      GameObject parent;
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());

      gameObject.setParent(&parent);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_SetParent_InputtingNullGameObject_DoesNothing)
    {
      GameObject parent;
      GameObject gameObject;

      Assert::IsNotNull(gameObject.getTransform());

      gameObject.setParent(&parent);

      Assert::AreEqual(parent.getTransform(), gameObject.getTransform()->getParent());

      gameObject.setParent(nullptr);

      Assert::AreEqual(parent.getTransform(), gameObject.getTransform()->getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_SetParent_InputtingGameObject_SetsTransformParentToGameObjectTransform)
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
    TEST_METHOD(GameObject_GetChildCount_NoTransform_ReturnsZero)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());
      Assert::AreEqual((size_t)0, gameObject.getChildCount());
    }

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

#pragma region Get Child Transform Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetChildTransform_NoTransform_ReturnsNullTransform)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());
      Assert::IsNull(gameObject.getChildTransform(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetChildTransform_NoChildren_ReturnsNullTransform)
    {
      GameObject gameObject;

      Assert::IsNotNull(gameObject.getTransform());
      Assert::IsNull(gameObject.getTransform()->getChildTransform(0));
      Assert::IsNull(gameObject.getChildTransform(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetChildTransform_WithChildren_ReturnsCorrectTransform)
    {
      GameObject gameObject;
      GameObject child1;
      GameObject child2;
      
      child1.getTransform()->setParent(gameObject.getTransform());
      child2.getTransform()->setParent(gameObject.getTransform());

      Assert::IsNotNull(gameObject.getTransform());
      Assert::AreEqual(child1.getTransform(), gameObject.getTransform()->getChildTransform(0));
      Assert::AreEqual(child2.getTransform(), gameObject.getTransform()->getChildTransform(1));
      Assert::AreEqual(child1.getTransform(), gameObject.getChildTransform(0));
      Assert::AreEqual(child2.getTransform(), gameObject.getChildTransform(1));
    }

#pragma endregion

#pragma region Get Child GameObject Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetChildGameObject_NoTransform_ReturnsNullGameObject)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());
      Assert::IsNull(gameObject.getChildGameObject(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetChildGameObject_NoChildren_ReturnsNullGameObject)
    {
      GameObject gameObject;

      Assert::IsNotNull(gameObject.getTransform());
      Assert::IsNull(gameObject.getTransform()->getChildGameObject(0));
      Assert::IsNull(gameObject.getChildGameObject(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetChildGameObject_WithChildren_ReturnsCorrectGameObject)
    {
      GameObject gameObject;
      GameObject child1;
      GameObject child2;
      
      child1.getTransform()->setParent(gameObject.getTransform());
      child2.getTransform()->setParent(gameObject.getTransform());

      Assert::IsNotNull(gameObject.getTransform());
      Assert::IsTrue(&child1 == gameObject.getTransform()->getChildGameObject(0));
      Assert::IsTrue(&child2 == gameObject.getTransform()->getChildGameObject(1));
      Assert::IsTrue(&child1 == gameObject.getChildGameObject(0));
      Assert::IsTrue(&child2 == gameObject.getChildGameObject(1));
    }

#pragma endregion

#pragma region Find Child Game Object Tests

#pragma region String Id Input

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_StringId_NoTransform_ReturnsNull)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());
      Assert::IsNull(gameObject.findChildGameObject(internString("Test")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_StringId_NoChildren_ReturnsNull)
    {
      GameObject gameObject;

      Assert::AreEqual((size_t)0, gameObject.getChildCount());
      Assert::IsNull(gameObject.findChildGameObject(internString("Test")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_StringId_InputtingNameWhichDoesntHaveMatch_ReturnsNull)
    {
      GameObject gameObject;
      GameObject child1;
      
      child1.setParent(&gameObject);
      child1.setName("Test_2");

      Assert::AreEqual((size_t)1, gameObject.getChildCount());
      Assert::IsNull(gameObject.findChildGameObject(internString("Test")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_StringId_InputtingNameWhichDoesHaveMatch_ReturnsGameObject)
    {
      GameObject gameObject;
      GameObject child1;
      
      child1.setParent(&gameObject);
      child1.setName("Test");

      Assert::AreEqual((size_t)1, gameObject.getChildCount());
      Assert::IsTrue(&child1 == gameObject.findChildGameObject(internString("Test")));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_StringId_InputtingNameWhichDoesHaveMultipleMatchs_ReturnsFirstMatchingGameObject)
    {
      GameObject gameObject;
      GameObject child1;
      GameObject child2;
      
      child1.setParent(&gameObject);
      child1.setName("Test");
      child2.setParent(&gameObject);
      child2.setName("Test");

      Assert::AreEqual((size_t)2, gameObject.getChildCount());
      Assert::IsTrue(&child1 == gameObject.findChildGameObject(internString("Test")));
    }

#pragma endregion

#pragma region String Input

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_String_NoTransform_ReturnsNull)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());
      Assert::IsNull(gameObject.findChildGameObject("Test"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_String_NoChildren_ReturnsNull)
    {
      GameObject gameObject;

      Assert::AreEqual((size_t)0, gameObject.getChildCount());
      Assert::IsNull(gameObject.findChildGameObject("Test"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_String_InputtingNameWhichDoesntHaveMatch_ReturnsNull)
    {
      GameObject gameObject;
      GameObject child1;
      
      child1.setParent(&gameObject);
      child1.setName("Test_2");

      Assert::AreEqual((size_t)1, gameObject.getChildCount());
      Assert::IsNull(gameObject.findChildGameObject("Test"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_String_InputtingNameWhichDoesHaveMatch_ReturnsGameObject)
    {
      GameObject gameObject;
      GameObject child1;
      
      child1.setParent(&gameObject);
      child1.setName("Test");

      Assert::AreEqual((size_t)1, gameObject.getChildCount());
      Assert::IsTrue(&child1 == gameObject.findChildGameObject("Test"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindChildGameObject_String_InputtingNameWhichDoesHaveMultipleMatchs_ReturnsFirstMatchingGameObject)
    {
      GameObject gameObject;
      GameObject child1;
      GameObject child2;
      
      child1.setParent(&gameObject);
      child1.setName("Test");
      child2.setParent(&gameObject);
      child2.setName("Test");

      Assert::AreEqual((size_t)2, gameObject.getChildCount());
      Assert::IsTrue(&child1 == gameObject.findChildGameObject("Test"));
    }

#pragma endregion

#pragma endregion

#pragma region For Each Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_ForEach_WithNullTransform_PerformsNoIteration)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getTransform());

      int counter = 0;
      for (observer_ptr<GameObject> child : gameObject)
      {
        ++counter;
      }

      Assert::AreEqual(0, counter);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_ForEach_TransformHasNoChildren_PerformsNoIteration)
    {
      GameObject gameObject;

      Assert::IsNotNull(gameObject.getTransform());
      Assert::AreEqual((size_t)0, gameObject.getTransform()->getChildCount());

      int counter = 0;
      for (observer_ptr<GameObject> child : gameObject)
      {
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
        gameObjects.push_back(child);
      }

      Assert::AreEqual((size_t)2, gameObjects.size());
      Assert::IsTrue(&child1 == gameObjects[0]);
      Assert::IsTrue(&child2 == gameObjects[1]);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_Constructor_Sets_ActiveToTrue)
    {
      MockGameObject gameObject;

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
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      
      Assert::IsTrue(gameObject.hasComponent<MockComponent>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_AddComponent_SetsComponentGameObject_ToGameObject)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      Assert::IsTrue(component->getGameObject() == &gameObject);
    }

#pragma endregion

#pragma region Has Component Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_HasComponent_NonScriptComponent_ShouldReturnTrue)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      Assert::IsTrue(gameObject.hasComponent<MockComponent>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_HasComponent_NonScriptComponent_ShouldReturnFalse)
    {
      GameObject gameObject;

      Assert::IsFalse(gameObject.hasComponent<MockComponent>());
      Assert::IsFalse(gameObject.hasComponent<Component>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_HasComponent_NonScriptComponentWhichWasDeallocated_ShouldReturnFalse)
    {
      GameObject gameObject;

      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      component->deallocate();

      Assert::IsFalse(gameObject.hasComponent<MockComponent>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_HasComponent_ScriptComponent_ShouldReturnTrue)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();

      Assert::IsTrue(gameObject.findComponent<MockScript>() == script.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_HasComponent_ScriptComponent_ShouldReturnFalse)
    {
      GameObject gameObject;

      Assert::IsFalse(gameObject.hasComponent<MockScript>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_HasComponent_ScriptComponentWhichIsDeallocated_ShouldReturnFalse)
    {
      GameObject gameObject;

      AutoDeallocator<MockScript> component = gameObject.addComponent<MockScript>();
      component->deallocate();

      Assert::IsFalse(gameObject.hasComponent<MockScript>());
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
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      AutoDeallocator<MockComponent> component2 = gameObject.addComponent<MockComponent>();

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

      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());

      Assert::IsNull(gameObject.getComponent(1));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetComponent_InputtingValidIndex_ReturnsCorrect)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      AutoDeallocator<MockComponent> component2 = gameObject.addComponent<MockComponent>();

      Assert::AreEqual(static_cast<size_t>(2), gameObject.getComponentCount());
      Assert::IsTrue(component.get() == gameObject.getComponent(0));
      Assert::IsTrue(component2.get() == gameObject.getComponent(1));
    }

#pragma endregion

#pragma region Get Const Component Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetConstComponent_InputtingInvalidIndex_ReturnsNull)
    {
      GameObject gameObject;

      Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
      Assert::IsNull(gameObject.getConstComponent(0));

      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());

      Assert::IsNull(gameObject.getConstComponent(1));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_GetConstComponent_InputtingValidIndex_ReturnsCorrect)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      AutoDeallocator<MockComponent> component2 = gameObject.addComponent<MockComponent>();

      Assert::AreEqual(static_cast<size_t>(2), gameObject.getComponentCount());
      Assert::IsTrue(component.get() == gameObject.getConstComponent(0));
      Assert::IsTrue(component2.get() == gameObject.getConstComponent(1));
    }

#pragma endregion

#pragma region Find Component Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponent_WithNonScriptComponent_ShouldFindComponent)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      Assert::IsTrue(gameObject.findComponent<MockComponent>() == component.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponent_WithNonScriptComponent_ShouldntFindComponent)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.findComponent<MockComponent>());
      Assert::IsNull(gameObject.findComponent<Component>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponent_WithNonScriptComponentThatIsDeallocated_ShouldntFindComponent)
    {
      GameObject gameObject;

      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      component->deallocate();

      Assert::IsNull(gameObject.findComponent<MockComponent>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponent_WithScriptComponent_ShouldFindComponent)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();

      Assert::IsTrue(gameObject.findComponent<MockScript>() == script.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponent_WithScriptComponent_ShouldntFindComponent)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.findComponent<MockScript>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponent_WithScriptComponentThatIsDeallocated_ShouldntFindComponent)
    {
      GameObject gameObject;

      AutoDeallocator<MockScript> component = gameObject.addComponent<MockScript>();
      component->deallocate();

      Assert::IsNull(gameObject.findComponent<MockScript>());
    }

#pragma endregion

#pragma region Find Const Component Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponent_WithNonScriptComponent_ShouldFindComponent)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      const MockComponent* handle = static_cast<const GameObject*>(&gameObject)->findComponent<MockComponent>();

      Assert::IsTrue(handle == component.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponent_WithNonScriptComponent_ShouldntFindComponent)
    {
      GameObject gameObject;

      Assert::IsNull(static_cast<const GameObject*>(&gameObject)->findComponent<MockComponent>());
      Assert::IsNull(static_cast<const GameObject*>(&gameObject)->findComponent<Component>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponent_WithNonScriptComponentThatIsDeallocated_ShouldntFindComponent)
    {
      GameObject gameObject;

      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      component->deallocate();

      Assert::IsNull(static_cast<const GameObject*>(&gameObject)->findComponent<MockComponent>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponent_WithScriptComponent_ShouldFindComponent)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();

      const MockScript* handle = static_cast<const GameObject*>(&gameObject)->findComponent<MockScript>();

      Assert::IsTrue(handle == script.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponent_WithScriptComponent_ShouldntFindComponent)
    {
      GameObject gameObject;

      Assert::IsNull(static_cast<const GameObject*>(&gameObject)->findComponent<MockScript>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponent_WithScriptComponentThatIsDeallocated_ShouldntFindComponent)
    {
      GameObject gameObject;

      AutoDeallocator<MockScript> component = gameObject.addComponent<MockScript>();
      component->deallocate();

      Assert::IsNull(static_cast<const GameObject*>(&gameObject)->findComponent<MockScript>());
    }

#pragma endregion

#pragma region Find Component With Predicate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponentWithPredicate_WithMatchingNonScriptComponent_ReturnsCorrectPtr)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      auto predicate = [](const MockComponent* component) -> bool
      {
        return true;
      };

      Assert::IsTrue(gameObject.findComponent<MockComponent>(predicate) == component.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponentWithPredicate_WithNoMatchingNonScriptComponent_ReturnsNullptr)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.findComponent<MockComponent>());
      Assert::IsNull(gameObject.findComponent<Component>());

      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      auto predicate = [](const MockComponent* component) -> bool
      {
        return false;
      };

      Assert::IsNull(gameObject.findComponent<MockComponent>(predicate));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponentWithPredicate_WithNonScriptComponentThatIsDeallocated_ReturnsNullptr)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      component->deallocate();

      auto predicate = [](const MockComponent* component) -> bool
      {
        return true;
      };

      Assert::IsNull(gameObject.findComponent<MockComponent>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponentWithPredicate_WithMatchingScriptComponent_ReturnsCorrectPtr)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();

      auto predicate = [](const MockScript* script) -> bool
      {
        return true;
      };

      Assert::IsTrue(gameObject.findComponent<MockScript>() == script.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponentWithPredicate_WithNoMatchingScriptComponent_ReturnsNullptr)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.findComponent<MockScript>());

      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();

      auto predicate = [](const MockScript* script) -> bool
      {
        return false;
      };

      Assert::IsNull(gameObject.findComponent<MockScript>(predicate));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindComponentWithPredicate_WithScriptComponentThatIsDeallocated_ReturnsNullptr)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();
      script->deallocate();

      auto predicate = [](const MockScript* script) -> bool
      {
        return true;
      };

      Assert::IsNull(gameObject.findComponent<MockScript>());
    }

#pragma endregion

#pragma region Find Const Component With Predicate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponentWithPredicate_WithMatchingNonScriptComponent_ReturnsCorrectPtr)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      auto predicate = [](const MockComponent* component) -> bool
      {
        return true;
      };

      const MockComponent* handle = static_cast<const GameObject*>(&gameObject)->findComponent<MockComponent>(predicate);

      Assert::IsTrue(handle == component.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponentWithPredicate_WithNoMatchingNonScriptComponent_ReturnsNullptr)
    {
      GameObject gameObject;

      const MockComponent* mockComponent = static_cast<const GameObject*>(&gameObject)->findComponent<MockComponent>();
      const Component* component = static_cast<const GameObject*>(&gameObject)->findComponent<Component>();

      Assert::IsNull(mockComponent);
      Assert::IsNull(component);

      AutoDeallocator<MockComponent> component2 = gameObject.addComponent<MockComponent>();

      auto predicate = [](const MockComponent* component) -> bool
      {
        return false;
      };

      const MockComponent* result2 = static_cast<const GameObject*>(&gameObject)->findComponent<MockComponent>(predicate);

      Assert::IsNull(result2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponentWithPredicate_WithNonScriptComponentThatIsDeallocated_ReturnsNullptr)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
      component->deallocate();

      auto predicate = [](const MockComponent* component) -> bool
      {
        return true;
      };

      Assert::IsNull(static_cast<const GameObject*>(&gameObject)->findComponent<MockComponent>(predicate));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponentWithPredicate_WithMatchingScriptComponent_ReturnsCorrectPtr)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();

      auto predicate = [](const MockScript* component) -> bool
      {
        return true;
      };

      const MockScript* handle = static_cast<const GameObject*>(&gameObject)->findComponent<MockScript>(predicate);

      Assert::IsTrue(handle == script.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponentWithPredicate_WithNoMatchingScriptComponent_ReturnsNullptr)
    {
      GameObject gameObject;

      const MockScript* handle = static_cast<const GameObject*>(&gameObject)->findComponent<MockScript>();

      Assert::IsNull(handle);

      AutoDeallocator<MockScript> component2 = gameObject.addComponent<MockScript>();

      auto predicate = [](const MockScript* component) -> bool
      {
        return false;
      };

      const MockScript* result2 = static_cast<const GameObject*>(&gameObject)->findComponent<MockScript>(predicate);

      Assert::IsNull(result2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_FindConstComponentWithPredicate_WithScriptComponentThatIsDeallocated_ReturnsNullptr)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();
      script->deallocate();

      auto predicate = [](const MockScript* component) -> bool
      {
        return true;
      };

      Assert::IsNull(static_cast<const GameObject*>(&gameObject)->findComponent<MockScript>(predicate));
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
    TEST_METHOD(GameObject_RemoveComponent_InputtingComponentNotInGameObject_DoesNothing)
    {
      GameObject gameObject;
      MockComponent component;

      AssertCel::IsActive(component);
      Assert::AreNotEqual(&gameObject, component.getGameObject());

      gameObject.removeComponent(&component);

      AssertCel::IsActive(component);

      GameObject gameObject2;
      AutoDeallocator<MockComponent> component2 = gameObject2.addComponent<MockComponent>();

      Assert::IsNotNull(component2.get());
      AssertCel::IsActive(component2.get());
      Assert::AreNotEqual(&gameObject, component2.get()->getGameObject());

      gameObject.removeComponent(component2.get());

      Assert::IsNotNull(component2.get());
      AssertCel::IsActive(component2.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_RemoveComponent_InputtingComponentInGameObject_SetsGameObjectToNull)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      Assert::IsNotNull(component.get());
      AssertCel::IsActive(component.get());
      Assert::AreEqual(&gameObject, component.get()->getGameObject());
      AssertCel::HasComponent<MockComponent>(gameObject);

      gameObject.removeComponent(component.get());

      Assert::IsNotNull(component.get());
      AssertCel::IsActive(component.get());
      Assert::AreEqual(&gameObject, component.get()->getGameObject());
      AssertCel::DoesNotHaveComponent<MockComponent>(gameObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_RemoveComponent_InputtingScriptInGameObject_SetsGameObjectToNull)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();
      gameObject.update(0);   // Make sure it's added

      Assert::IsNotNull(script.get());
      AssertCel::IsActive(script.get());
      Assert::AreEqual(&gameObject, script.get()->getGameObject());
      AssertCel::HasComponent<MockScript>(gameObject);

      gameObject.removeComponent(script.get());

      Assert::IsNotNull(script.get());
      AssertCel::IsActive(script.get());
      Assert::AreEqual(&gameObject, script.get()->getGameObject());
      AssertCel::DoesNotHaveComponent<MockScript>(gameObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_RemoveComponent_InputtingScriptToAddInGameObject_SetsGameObjectToNull)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();

      Assert::IsNotNull(script.get());
      AssertCel::IsActive(script.get());
      Assert::AreEqual(&gameObject, script.get()->getGameObject());
      AssertCel::HasComponent<MockScript>(gameObject);

      gameObject.removeComponent(script.get());

      Assert::IsNotNull(script.get());
      AssertCel::IsActive(script.get());
      Assert::AreEqual(&gameObject, script.get()->getGameObject());
      AssertCel::DoesNotHaveComponent<MockScript>(gameObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_RemoveComponent_InputtingComponentInGameObject_MakesHasComponentReturnFalse)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> script = gameObject.addComponent<MockComponent>();

      AssertCel::HasComponent<MockComponent>(gameObject);

      gameObject.removeComponent(script.get());

      AssertCel::DoesNotHaveComponent<MockComponent>(gameObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_RemoveComponent_InputtingComponentInGameObject_MakesFindComponentReturnNull)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      Assert::AreEqual(component.get(), gameObject.findComponent<MockComponent>());

      gameObject.removeComponent(component.get());

      Assert::IsNull(gameObject.findComponent<MockComponent>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_RemoveComponent_InputtingComponentInGameObject_RemovesFromGameObject)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());

      gameObject.removeComponent(component.get());

      Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_RemoveComponent_InputtingScriptInGameObject_RemovesFromGameObject)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script = gameObject.addComponent<MockScript>();

      Assert::AreEqual(static_cast<size_t>(1), gameObject.getComponentCount());

      gameObject.removeComponent(script.get());

      Assert::AreEqual(static_cast<size_t>(0), gameObject.getComponentCount());
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_HandleInput_CallsHandleInputOnAllUnmanagedComponents_WhichAreActive)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script1 = gameObject.addComponent<MockScript>();
      AutoDeallocator<MockScript> script2 = gameObject.addComponent<MockScript>();

      script2->setActive(false);

      // Have to call update to move components to the active components vector
      gameObject.update(0);
      gameObject.handleInput();

      Assert::IsTrue(script1->handleInputCalled());
      Assert::IsFalse(script2->handleInputCalled());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_HandleInput_DoesNotCallHandleInputOnManagedComponents)
    {
      GameObject gameObject;
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

      gameObject.handleInput();

      Assert::IsFalse(component->handleInputCalled());
    }

#pragma endregion

#pragma region Update Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_Update_CallsUpdateOnAllScripts_WhichAreActive)
    {
      GameObject gameObject;
      AutoDeallocator<MockScript> script1 = gameObject.addComponent<MockScript>();
      AutoDeallocator<MockScript> script2 = gameObject.addComponent<MockScript>();
      AutoDeallocator<MockScript> script3 = gameObject.addComponent<MockScript>();

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
      AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

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
      AutoDeallocator<MockSpriteRenderer> spriteRenderer = gameObject.addComponent<MockSpriteRenderer>();
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
      AutoDeallocator<MockSpriteRenderer> spriteRenderer = gameObject.addComponent<MockSpriteRenderer>();
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
      AutoDeallocator<MockTextRenderer> textRenderer = gameObject.addComponent<MockTextRenderer>();
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
      AutoDeallocator<MockTextRenderer> textRenderer = gameObject.addComponent<MockTextRenderer>();
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
      AutoDeallocator<MockSpriteRenderer> spriteRenderer = gameObject.addComponent<MockSpriteRenderer>();
      AutoDeallocator<MockTextRenderer> textRenderer = gameObject.addComponent<MockTextRenderer>();
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
      AutoDeallocator<MockSpriteRenderer> spriteRenderer = gameObject.addComponent<MockSpriteRenderer>();
      AutoDeallocator<MockTextRenderer> textRenderer = gameObject.addComponent<MockTextRenderer>();
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

#pragma region Deallocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_Deallocate_WithNoScreen_AndDead_ReturnsFalse)
    {
      GameObject gameObject;
      gameObject.deallocate();

      Assert::IsNull(gameObject.getScreen());
      Assert::IsFalse(gameObject.deallocate());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_Deallocate_WithScreen_DeallocatesObject_ReturnsTrue)
    {
      AutoDeallocator<Screen> screen = Screen::allocate();
      AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();
      const GameObject* ptr = gameObject.get();

      Assert::IsNotNull(gameObject->getScreen());
      Assert::IsTrue(gameObject->deallocate());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_Deallocate_WithScreenAndGameObjectNotFromAllocator_ReturnsFalse)
    {
      GameObject gameObject;

      Assert::IsFalse(gameObject.deallocate());
    }

#pragma endregion

#pragma region Allocate Game Object In Screen Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_AllocateGameObjectInScreen_WithScreenNull_ShouldReturnNullGameObject)
    {
      GameObject gameObject;

      Assert::IsNull(gameObject.getScreen());

      observer_ptr<GameObject> createdGameObject = gameObject.allocateGameObjectInScreen();

      Assert::IsNull(createdGameObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_AllocateGameObjectInScreen_WithScreenSet_ShouldReturnAllocatedGameObject_WithScreenSetToSame)
    {
      Screen screen;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

      Assert::IsTrue(&screen == gameObject->getScreen());

      AutoDeallocator<GameObject> createdGameObject = gameObject->allocateGameObjectInScreen();

      Assert::IsNotNull(createdGameObject.get());
      AssertCel::IsActive(createdGameObject.get());
      Assert::IsNotNull(createdGameObject->getTransform());
      Assert::IsTrue(&screen == createdGameObject->getScreen());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_AllocateGameObjectInScreen_WithScreenNull_InputtingTransform_ShouldReturnNullGameObject)
    {
      GameObject gameObject;
      Transform transform;

      Assert::IsNull(gameObject.getScreen());

      observer_ptr<GameObject> createdGameObject = gameObject.allocateGameObjectInScreen(transform);

      Assert::IsNull(createdGameObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GameObject_AllocateGameObjectInScreen_WithScreenSet_InputtingTransform_ShouldReturnGameObject_WithScreenSetToSame_AndTransformParentSetToInput)
    {
      Screen screen;
      Transform transform;
      AutoDeallocator<GameObject> gameObject = screen.allocateGameObject();

      Assert::IsTrue(&screen == gameObject->getScreen());

      AutoDeallocator<GameObject> createdGameObject = gameObject->allocateGameObjectInScreen(transform);

      Assert::IsNotNull(createdGameObject.get());
      AssertCel::IsActive(createdGameObject.get());
      Assert::IsNotNull(createdGameObject->getTransform());
      Assert::AreEqual(&transform, createdGameObject->getTransform()->getParent());
      Assert::IsTrue(&screen == createdGameObject->getScreen());
    }

#pragma endregion

  };
}