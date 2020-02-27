#include "UtilityHeaders/UnitTestHeaders.h"

#include "Maths/Transform.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"
#include "AssertExt.h"

using namespace Celeste;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestTransform)

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Constructor_SetsTransformValues)
    {
      Transform transform;

      Assert::AreEqual(0.0f, transform.getRotation());
      Assert::IsTrue(glm::vec3() == transform.getTranslation());
      Assert::IsTrue(glm::vec3(1, 1, 1) == transform.getScale());
      Assert::IsTrue(glm::mat4() == transform.getLocalMatrix());
      
      Assert::IsNull(transform.getParent());
      Assert::IsNull(transform.getGameObject());
      Assert::AreEqual((size_t)0, transform.getChildCount());
      Assert::AreEqual(0.0f, transform.getWorldRotation());
      Assert::IsTrue(glm::vec3() == transform.getWorldTranslation());
      Assert::IsTrue(glm::vec3(1, 1, 1) == transform.getWorldScale());
      Assert::IsTrue(glm::mat4() == transform.getWorldMatrix());
    }

#pragma endregion

#pragma region Get GameObject Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Transform_GetGameObject_NoGameObjectSet_ReturnsNullGameObjectHandle)
  {
    Transform transform;

    Assert::IsNull(transform.getGameObject());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Transform_GetGameObject_GameObjectSet_ReturnsCorrectGameObjectHandle)
  {
    GameObject gameObject;
    AutoDeallocator<Transform> transform = Transform::allocate(gameObject);

    Assert::AreEqual(&gameObject, transform->getGameObject());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Transform_GetConstGameObject_NoGameObjectSet_ReturnsConstNullGameObjectHandle)
  {
    Transform transform;

    Assert::IsNull(static_cast<const Transform&>(transform).getGameObject());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Transform_GetConstGameObject_GameObjectSet_ReturnsCorrectConstGameObjectHandle)
  {
    GameObject gameObject;
    AutoDeallocator<Transform> transform = Transform::allocate(gameObject);

    Assert::AreEqual(&gameObject, transform->getGameObject());
  }

#pragma endregion

#pragma region Get Parent Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Transform_GetParent_NoParentSet_ReturnsNullTransformHandle)
  {
    Transform transform;

    Assert::IsNull(transform.getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Transform_GetParent_ParentSet_ReturnsCorrectTransformHandle)
  {
    Transform parent;
    Transform transform;
    transform.setParent(&parent);

    Assert::AreEqual(&parent, transform.getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Transform_GetConstParent_NoParentSet_ReturnsConstNullTransformHandle)
  {
    Transform transform;

    Assert::IsNull(static_cast<const Transform&>(transform).getParent());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Transform_GetConstParent_ParentSet_ReturnsCorrectConstTransformHandle)
  {
    Transform parent;
    Transform transform;
    transform.setParent(&parent);

    Assert::AreEqual(static_cast<const Transform*>(&parent), static_cast<const Transform&>(transform).getParent());
  }

#pragma endregion

#pragma region Set Parent Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetParent_InputtingHandleToSameTransform_DoesNotSetParent)
    {
      Transform transform;

      Assert::IsNull(transform.getParent());

      transform.setParent(&transform);

      Assert::IsNull(transform.getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetParent_InputtingHandleToDifferentTransform_DoesSetParent)
    {
      Transform transform;
      Transform parent;

      Assert::IsNull(transform.getParent());

      transform.setParent(&parent);

      Assert::AreEqual(&parent, transform.getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetParent_InputtingHandleEqualToCurrentParent_DoesNothing)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());

      Assert::IsNull(transform->getParent());

      transform->setParent(parent.get());

      Assert::AreEqual(parent.get(), transform->getParent());
      Assert::AreEqual((size_t)1, parent->getChildCount());

      transform->setParent(parent.get());

      Assert::AreEqual(parent.get(), transform->getParent());
      Assert::AreEqual((size_t)1, parent->getChildCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetParent_NoParent_SettingToNull_DoesNothing)
    {
      Transform transform;

      Assert::IsNull(transform.getParent());

      transform.setParent(nullptr);

      Assert::IsNull(transform.getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetParent_NoParent_SettingParent_AddsTransformToParentChildren)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());

      Assert::IsNull(transform->getParent());
      Assert::AreEqual((size_t)0, parent->getChildCount());

      transform->setParent(parent.get());

      Assert::AreEqual(parent.get(), transform->getParent());
      Assert::AreEqual((size_t)1, parent->getChildCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetParent_Parent_SettingParent_RemovesTransformFromOldParentChildren_AddsTransformToParentChildren)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());

      Assert::IsNull(transform->getParent());
      Assert::AreEqual((size_t)0, parent->getChildCount());

      transform->setParent(parent.get());

      Assert::AreEqual(parent.get(), transform->getParent());
      Assert::AreEqual((size_t)1, parent->getChildCount());

      AutoDeallocator<Transform> parent2 = Transform::allocate(GameObject());

      transform->setParent(parent2.get());

      Assert::AreEqual(parent2.get(), transform->getParent());
      Assert::AreEqual((size_t)0, parent->getChildCount());
      Assert::AreEqual((size_t)1, parent2->getChildCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetParent_Parent_SettingToNull_RemovesTransformFromOldParentChildren)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());

      Assert::IsNull(transform->getParent());
      Assert::AreEqual((size_t)0, parent->getChildCount());

      transform->setParent(parent.get());

      Assert::AreEqual(parent.get(), transform->getParent());
      Assert::AreEqual((size_t)1, parent->getChildCount());

      transform->setParent(nullptr);

      Assert::IsNull(transform->getParent());
      Assert::AreEqual((size_t)0, parent->getChildCount());
    }

#pragma endregion

#pragma region Get Child Transform Tests

#pragma region Non Const

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildTransform_NonConst_NoChildren_ReturnsNullTransformHandle)
    {
      Transform transform;

      Assert::AreEqual((size_t)0, transform.getChildCount());
      Assert::IsNull(transform.getChildTransform(0));
      Assert::IsNull(transform.getChildTransform(2));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildTransform_NonConst_IndexGreaterThanOrEqualToChildCount_ReturnsNullTransformHandle)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      transform->setParent(parent.get());

      Assert::AreEqual((size_t)1, parent->getChildCount());
      Assert::IsNull(parent->getChildTransform(parent->getChildCount()));
      Assert::IsNull(parent->getChildTransform(10));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildTransform_NonConst_IndexLessThanChildCount_ReturnsChildTransformHandle)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      transform->setParent(parent.get());

      Assert::AreEqual((size_t)1, parent->getChildCount());
      Assert::AreEqual(transform.get(), parent->getChildTransform(0));
    }

#pragma endregion

#pragma region Const

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildTransform_Const_NoChildren_ReturnsNullConstTransformHandle)
    {
      const Transform transform;

      Assert::AreEqual((size_t)0, transform.getChildCount());
      Assert::IsNull(transform.getChildTransform(0));
      Assert::IsNull(transform.getChildTransform(2));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildTransform_Const_IndexGreaterThanOrEqualToChildCount_ReturnsNullConstTransformHandle)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      transform->setParent(parent.get());

      Assert::AreEqual((size_t)1, parent->getChildCount());
      Assert::IsNull(static_cast<const Transform*>(parent.get())->getChildTransform(parent->getChildCount()));
      Assert::IsNull(static_cast<const Transform*>(parent.get())->getChildTransform(10));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildTransform_Const_IndexLessThanChildCount_ReturnsChildConstTransformHandle)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      transform->setParent(parent.get());

      Assert::AreEqual((size_t)1, parent->getChildCount());
      Assert::AreEqual(static_cast<const Transform*>(transform.get()), static_cast<const Transform*>(parent.get())->getChildTransform(0));
    }

#pragma endregion

#pragma endregion

#pragma region Get Child GameObject Tests

#pragma region Non Const

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildGameObject_NonConst_NoChildren_ReturnsNullGameObjectHandle)
    {
      Transform transform;

      Assert::AreEqual((size_t)0, transform.getChildCount());
      Assert::IsNull(transform.getChildGameObject(0));
      Assert::IsNull(transform.getChildGameObject(2));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildGameObject_NonConst_IndexGreaterThanOrEqualToChildCount_ReturnsNullGameObjectHandle)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      transform->setParent(parent.get());

      Assert::AreEqual((size_t)1, parent->getChildCount());
      Assert::IsNull(parent->getChildGameObject(parent->getChildCount()));
      Assert::IsNull(parent->getChildGameObject(10));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildGameObject_NonConst_IndexLessThanChildCount_ReturnsChildTransformsGameObjectHandle)
    {
      GameObject gameObject;
      AutoDeallocator<Transform> transform = Transform::allocate(gameObject);
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      transform->setParent(parent.get());

      Assert::AreEqual((size_t)1, parent->getChildCount());
      Assert::AreEqual(transform->getGameObject(), parent->getChildGameObject(0));
    }

#pragma endregion

#pragma region Const

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildGameObject_Const_NoChildren_ReturnsNullConstGameObjectHandle)
    {
      const Transform transform;

      Assert::AreEqual((size_t)0, transform.getChildCount());
      Assert::IsNull(transform.getChildGameObject(0));
      Assert::IsNull(transform.getChildGameObject(2));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildGameObject_Const_IndexGreaterThanOrEqualToChildCount_ReturnsNullConstGameObjectHandle)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      transform->setParent(parent.get());

      Assert::AreEqual((size_t)1, parent->getChildCount());
      Assert::IsNull(static_cast<const Transform*>(parent.get())->getChildGameObject(parent->getChildCount()));
      Assert::IsNull(static_cast<const Transform*>(parent.get())->getChildGameObject(10));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetChildGameObject_Const_IndexLessThanChildCount_ReturnsChildTransformsConstcnGameObjectHandle)
    {
      GameObject gameObject;
      AutoDeallocator<Transform> transform = Transform::allocate(gameObject);
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      transform->setParent(parent.get());

      Assert::AreEqual((size_t)1, parent->getChildCount());
      Assert::AreEqual(static_cast<const GameObject*>(transform->getGameObject()), static_cast<const Transform*>(parent.get())->getChildGameObject(0));
    }

#pragma endregion

#pragma endregion

#pragma region For Each Iteration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Foreach_NoChildren_DoesNothing)
    {
      Transform transform;

      Assert::AreEqual((size_t)0, transform.getChildCount());

      int count = 0;
      for (observer_ptr<Transform> child : transform)
      {
        ++count;
      }

      Assert::AreEqual(0, count);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Foreach_WithChildren_IteratesOverChildren)
    {
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      AutoDeallocator<Transform> child1 = Transform::allocate(GameObject());
      AutoDeallocator<Transform> child2 = Transform::allocate(GameObject());
      AutoDeallocator<Transform> child3 = Transform::allocate(GameObject());

      child1->setParent(parent.get());
      child2->setParent(parent.get());
      child3->setParent(parent.get());

      std::vector<observer_ptr<Transform>> children;
      for (observer_ptr<Transform> child : *parent.get())
      {
        children.push_back(child);
      }

      Assert::AreEqual((size_t)3, children.size());
      Assert::AreEqual(children[0], child1.get());
      Assert::AreEqual(children[1], child2.get());
      Assert::AreEqual(children[2], child3.get());
    }

#pragma endregion

#pragma region Rotation Modification Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Rotate_AppliesDeltaValue)
    {
      Transform transform;
      transform.rotate(0);

      Assert::AreEqual(0.0f, transform.getRotation());

      transform.rotate(2);

      Assert::AreEqual(2.0f, transform.getRotation());

      transform.rotate(-0.15f);

      Assert::AreEqual(1.85f, transform.getRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetRotation)
    {
      Transform transform;
      transform.setRotation(0);

      Assert::AreEqual(0.0f, transform.getRotation());

      transform.setRotation(2);

      Assert::AreEqual(2.0f, transform.getRotation());
    }

#pragma endregion

#pragma region Translation Modification Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Translate_AppliesDeltaValue)
    {
      Transform transform;
      transform.translate(0, 0);

      Assert::IsTrue(glm::vec3() == transform.getTranslation());

      transform.translate(glm::vec2(2, -1.5f));

      Assert::IsTrue(glm::vec3(2, -1.5f, 0) == transform.getTranslation());

      transform.translate(-0.15f, 1, -1);

      Assert::IsTrue(glm::vec3(1.85f, -0.5f, -1) == transform.getTranslation());

      transform.translate(glm::vec3(-1, 0, 1));

      Assert::IsTrue(glm::vec3(0.85f, -0.5f, 0) == transform.getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetTranslation)
    {
      Transform transform;
      transform.setTranslation(0, 0);

      Assert::IsTrue(glm::vec3() == transform.getTranslation());

      transform.setTranslation(glm::vec2(2, -1.5f));

      Assert::IsTrue(glm::vec3(2, -1.5f, 0) == transform.getTranslation());

      transform.setTranslation(-0.15f, 1, -1);

      Assert::IsTrue(glm::vec3(-0.15f, 1, -1) == transform.getTranslation());

      transform.setTranslation(glm::vec3(-1, 0, 1));

      Assert::IsTrue(glm::vec3(-1, 0, 1) == transform.getTranslation());
    }

#pragma endregion

#pragma region Scale Modification Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Scale_AppliesDeltaValue)
    {
      Transform transform;
      transform.scale(1, 1);

      Assert::IsTrue(glm::vec3(1, 1, 1) == transform.getScale());

      transform.scale(glm::vec2(2, -1.5f));

      Assert::IsTrue(glm::vec3(2, -1.5f, 1) == transform.getScale());

      transform.scale(-0.1f, 1, -1);

      Assert::IsTrue(glm::vec3(-0.2f, -1.5f, -1) == transform.getScale());

      transform.scale(glm::vec3(-1, 0.5f, 1));

      Assert::IsTrue(glm::vec3(0.2f, -0.75f, -1) == transform.getScale());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetScale)
    {
      Transform transform;
      transform.setScale(0, 0);

      Assert::IsTrue(glm::vec3(0, 0, 1) == transform.getScale());

      transform.setScale(glm::vec2(2, -1.5f));

      Assert::IsTrue(glm::vec3(2, -1.5f, 1) == transform.getScale());

      transform.setScale(-0.15f, 1, -1);

      Assert::IsTrue(glm::vec3(-0.15f, 1, -1) == transform.getScale());

      transform.setScale(glm::vec3(-1, 0, 1));

      Assert::IsTrue(glm::vec3(-1, 0, 1) == transform.getScale());
    }

#pragma endregion

#pragma region Has Parent Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_HasParent_ShouldReturnTrue)
    {
      Transform transform, transform2;

      transform.setParent(&transform2);

      Assert::IsTrue(transform.hasParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_HasParent_ShouldReturnFalse)
    {
      Transform transform;

      Assert::IsFalse(transform.hasParent());

      transform.setParent(nullptr);

      Assert::IsFalse(transform.hasParent());
    }

#pragma endregion

#pragma region Get Local Matrix Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetLocalMatrix)
    {
      Transform transform;
      transform.setRotation(glm::half_pi<float>());
      transform.setTranslation(glm::vec3(2, -1, 1));
      transform.setScale(glm::vec3(0.5f, 0.25f, 1));

      glm::mat4 expected;
      expected[3] = glm::vec4(2, -1, 1, 1);
      expected = glm::rotate(expected, -glm::half_pi<float>(), glm::vec3(0, 0, 1));
      expected = glm::scale(expected, glm::vec3(0.5f, 0.25f, 1));

      Assert::IsTrue(expected == transform.getLocalMatrix());
    }

#pragma endregion

#pragma region Get Inverse Value Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseTranslation)
    {
      Transform transform;
      transform.setTranslation(glm::vec3());

      Assert::AreEqual(glm::vec3(), transform.getInverseTranslation());

      transform.setTranslation(glm::vec3(1, -2, 3.2123f));

      Assert::AreEqual(glm::vec3(-1, 2, -3.2123f), transform.getInverseTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseRotation)
    {
      Transform transform;
      transform.setRotation(0);

      Assert::AreEqual(0.0f, transform.getInverseRotation());

      transform.setRotation(21);

      Assert::AreEqual(-21.0f, transform.getInverseRotation());

      transform.setRotation(-0.3f);

      Assert::AreEqual(0.3f, transform.getInverseRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseScale)
    {
      Transform transform;
      transform.setScale(glm::vec3(1, -2, 3.2123f));

      Assert::AreEqual(glm::vec3(1, -0.5f, 1 / 3.2123f), transform.getInverseScale());

      transform.setScale(glm::vec3(0.1f, -0.2f, 3));

      Assert::AreEqual(glm::vec3(10, -5, 1 / 3.0f), transform.getInverseScale());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseLocalMatrix)
    {
      Transform transform;
      transform.setRotation(glm::half_pi<float>());
      transform.setTranslation(glm::vec3(2, -1, 1));
      transform.setScale(glm::vec3(0.5f, 0.25f, 1));

      glm::mat4 expected = glm::inverse(transform.getLocalMatrix());

      AssertExt::AreAlmostEqual(expected, transform.getInverseLocalMatrix());
      AssertExt::AreAlmostEqual(glm::mat4(), transform.getLocalMatrix() * transform.getInverseLocalMatrix());
      AssertExt::AreAlmostEqual(glm::mat4(), transform.getInverseLocalMatrix() * transform.getLocalMatrix());
    }

#pragma endregion

#pragma region Get World Rotation Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetWorldRotation_WithNoParent)
    {
      Transform transform;
      transform.setRotation(glm::half_pi<float>());

      Assert::AreEqual(glm::half_pi<float>(), transform.getWorldRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetWorldRotation_WithParent)
    {
      Transform transform, transform2;
      Transform* txPtr = &transform2;

      transform2.setRotation(glm::half_pi<float>());
      transform.setRotation(glm::half_pi<float>());
      transform.setParent(txPtr);

      Assert::AreEqual(glm::pi<float>(), transform.getWorldRotation());
    }

#pragma endregion

#pragma region Set World Rotation Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetWorldRotation_WithNoParent)
    {
      Transform transform;
      transform.setWorldRotation(0);

      Assert::AreEqual(0.0f, transform.getRotation());
      Assert::AreEqual(0.0f, transform.getWorldRotation());

      transform.setWorldRotation(2);

      Assert::AreEqual(2.0f, transform.getRotation());
      Assert::AreEqual(2.0f, transform.getWorldRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetWorldRotation_WithParent)
    {
      Transform transform, transform2;
      Transform* txPtr = &transform2;

      transform2.setRotation(1);
      transform.setParent(txPtr);

      transform.setWorldRotation(1.5f);

      Assert::AreEqual(0.5f, transform.getRotation());
      Assert::AreEqual(1.5f, transform.getWorldRotation());

      transform.setWorldRotation(-1.0f);

      Assert::AreEqual(-2.0f, transform.getRotation());
      Assert::AreEqual(-1.0f, transform.getWorldRotation());
    }

#pragma endregion

#pragma region Get Inverse World Rotation Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseWorldRotation_WithNoParent)
    {
      Transform transform;
      transform.setRotation(glm::half_pi<float>());

      Assert::IsNull(transform.getParent());
      Assert::AreEqual(-glm::half_pi<float>(), transform.getInverseWorldRotation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseWorldRotation_WithParent)
    {
      Transform transform, transform2;
      Transform* txPtr = &transform2;

      transform2.setRotation(glm::half_pi<float>());
      transform.setRotation(glm::half_pi<float>());
      transform.setParent(txPtr);

      Assert::AreEqual(txPtr, transform.getParent());
      Assert::AreEqual(-glm::pi<float>(), transform.getInverseWorldRotation());
    }

#pragma endregion

#pragma region Get World Translation Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetWorldTranslation_WithNoParent)
    {
      Transform transform;
      transform.setTranslation(glm::vec3(1, -0.5f, 0));

      Assert::IsTrue(glm::vec3(1, -0.5f, 0) == transform.getWorldTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetWorldTranslation_WithParent)
    {
      Transform transform, transform2;
      Transform* txPtr = &transform2;

      transform2.setTranslation(glm::vec3(-0.5f, 2, -1));
      transform.setTranslation(glm::vec3(1.5f, -2.5f, 1));
      transform.setParent(txPtr);

      Assert::IsTrue(glm::vec3(1, -0.5f, 0) == transform.getWorldTranslation());
    }

#pragma endregion

#pragma region Set World Translation Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetWorldTranslation_WithNoParent)
    {
      Transform transform;
      transform.setWorldTranslation(0, 0);

      Assert::IsTrue(glm::vec3() == transform.getTranslation());
      Assert::IsTrue(glm::vec3() == transform.getWorldTranslation());

      transform.setWorldTranslation(glm::vec2(2, -1.5f));

      Assert::IsTrue(glm::vec3(2, -1.5f, 0) == transform.getTranslation());
      Assert::IsTrue(glm::vec3(2, -1.5f, 0) == transform.getWorldTranslation());

      transform.setWorldTranslation(-0.15f, 1, -1);

      Assert::IsTrue(glm::vec3(-0.15f, 1, -1) == transform.getTranslation());
      Assert::IsTrue(glm::vec3(-0.15f, 1, -1) == transform.getWorldTranslation());

      transform.setWorldTranslation(glm::vec3(-1, 0, 1));

      Assert::IsTrue(glm::vec3(-1, 0, 1) == transform.getTranslation());
      Assert::IsTrue(glm::vec3(-1, 0, 1) == transform.getWorldTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetWorldTranslation_WithParent)
    {
      Transform transform, transform2;
      Transform* txPtr = &transform2;

      transform2.setTranslation(glm::vec3(-0.5f, 2, -1));
      transform.setParent(txPtr);

      Assert::IsTrue(glm::vec3() == transform.getTranslation());
      Assert::IsTrue(glm::vec3(-0.5f, 2, -1) == transform.getWorldTranslation());

      transform.setWorldTranslation(glm::vec2(2, -1.5f));

      Assert::IsTrue(glm::vec3(2.5f, -3.5f, 1.0f) == transform.getTranslation());
      Assert::IsTrue(glm::vec3(2, -1.5f, 0) == transform.getWorldTranslation());

      transform.setWorldTranslation(-0.15f, 1, -1);

      Assert::IsTrue(glm::vec3(0.35f, -1, 0) == transform.getTranslation());
      Assert::IsTrue(glm::vec3(-0.15f, 1, -1) == transform.getWorldTranslation());

      transform.setWorldTranslation(glm::vec3(-1, 0, 1));

      Assert::IsTrue(glm::vec3(-0.5f, -2, 2) == transform.getTranslation());
      Assert::IsTrue(glm::vec3(-1, 0, 1) == transform.getWorldTranslation());
    }

#pragma endregion

#pragma region Get Inverse World Translation Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseWorldTranslation_WithNoParent)
    {
      Transform transform;
      transform.setTranslation(glm::vec3(1, -0.5f, 0));

      Assert::IsNull(transform.getParent());
      Assert::AreEqual(glm::vec3(-1, 0.5f, 0), transform.getInverseWorldTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseWorldTranslation_WithParent)
    {
      Transform transform, parent;
      Transform* parentPtr = &parent;

      parent.setTranslation(glm::vec3(-0.5f, 2, -1));
      transform.setTranslation(glm::vec3(1.5f, -2.5f, 1));
      transform.setParent(&parent);

      Assert::AreEqual(&parent, transform.getParent());
      Assert::AreEqual(glm::vec3(-1, 0.5f, 0), transform.getInverseWorldTranslation());
    }

#pragma endregion

#pragma region Get World Scale Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetWorldScale_WithNoParent)
    {
      Transform transform;
      transform.setScale(glm::vec3(1, -0.5f, 0));

      Assert::IsTrue(glm::vec3(1, -0.5f, 0) == transform.getWorldScale());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetWorldScale_WithParent)
    {
      Transform transform, transform2;
      Transform* txPtr = &transform2;

      transform2.setScale(glm::vec3(0.5f, 2, -1));
      transform.setScale(glm::vec3(2, -0.25f, -1));
      transform.setParent(txPtr);

      Assert::IsTrue(glm::vec3(1, -0.5f, 1) == transform.getWorldScale());
    }

#pragma endregion

#pragma region Set World Scale Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetWorldScale_WithNoParent)
    {
      Transform transform;
      transform.setWorldScale(0, 0);

      Assert::IsTrue(glm::vec3(0, 0, 1) == transform.getScale());
      Assert::IsTrue(glm::vec3(0, 0, 1) == transform.getWorldScale());

      transform.setScale(glm::vec2(2, -1.5f));

      Assert::IsTrue(glm::vec3(2, -1.5f, 1) == transform.getScale());
      Assert::IsTrue(glm::vec3(2, -1.5f, 1) == transform.getWorldScale());

      transform.setScale(-0.15f, 1, -1);

      Assert::IsTrue(glm::vec3(-0.15f, 1, -1) == transform.getScale());
      Assert::IsTrue(glm::vec3(-0.15f, 1, -1) == transform.getWorldScale());

      transform.setScale(glm::vec3(-1, 0, 1));

      Assert::IsTrue(glm::vec3(-1, 0, 1) == transform.getScale()); 
      Assert::IsTrue(glm::vec3(-1, 0, 1) == transform.getWorldScale());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_SetWorldScale_WithParent)
    {
      Transform transform, transform2;
      Transform* txPtr = &transform2;

      transform2.setScale(glm::vec3(0.5f, 2, -1));
      transform.setParent(txPtr);

      transform.setWorldScale(0, 0);

      Assert::IsTrue(glm::vec3(0, 0, -1) == transform.getScale());
      Assert::IsTrue(glm::vec3(0, 0, 1) == transform.getWorldScale());

      transform.setWorldScale(glm::vec2(2, -1.5f));

      Assert::IsTrue(glm::vec3(4, -0.75f, -1) == transform.getScale());
      Assert::IsTrue(glm::vec3(2, -1.5f, 1) == transform.getWorldScale());

      transform.setWorldScale(-0.25f, 1, -1);

      Assert::IsTrue(glm::vec3(-0.5f, 0.5f, 1) == transform.getScale());
      Assert::IsTrue(glm::vec3(-0.25f, 1, -1) == transform.getWorldScale());

      transform.setWorldScale(glm::vec3(-1, 0, 1));

      Assert::IsTrue(glm::vec3(-2, 0, -1) == transform.getScale());
      Assert::IsTrue(glm::vec3(-1, 0, 1) == transform.getWorldScale());
    }

#pragma endregion

#pragma region Get Inverse World Scale Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseWorldScale_WithNoParent)
    {
      Transform transform;
      transform.setScale(glm::vec3(1, -0.5f, 0.1f));

      Assert::IsNull(transform.getParent());
      Assert::AreEqual(glm::vec3(1, -2, 10), transform.getInverseWorldScale());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseWorldScale_WithParent)
    {
      Transform transform, parent;
      Transform* parentPtr = &parent;

      parent.setScale(glm::vec3(0.5f, 2, -1));
      transform.setScale(glm::vec3(2, -0.25f, -1));
      transform.setParent(&parent);

      Assert::AreEqual(glm::vec3(1, -2, 1), transform.getInverseWorldScale());
    }

#pragma endregion

#pragma region Get World Matrix Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetWorldMatrix_WithNoParent)
    {
      Transform transform;
      transform.setRotation(glm::half_pi<float>());
      transform.setTranslation(glm::vec3(2, -1, 1));
      transform.setScale(glm::vec3(0.5f, 0.25f, 1));

      glm::mat4 expected;
      expected[3] = glm::vec4(2, -1, 1, 1);
      expected = glm::rotate(expected, -glm::half_pi<float>(), glm::vec3(0, 0, 1));
      expected = glm::scale(expected, glm::vec3(0.5f, 0.25f, 1));

      Assert::IsTrue(expected == transform.getWorldMatrix());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetWorldMatrix_WithParent)
    {
      Transform transform, transform2;
      Transform* txPtr = &transform2;

      transform2.setRotation(glm::half_pi<float>());
      transform2.setTranslation(glm::vec3(-0.25f, -2, -1));
      transform2.setScale(glm::vec3(5, 1, -1));

      transform.setRotation(glm::half_pi<float>());
      transform.setTranslation(glm::vec3(2, -1, 1));
      transform.setScale(glm::vec3(0.5f, 0.25f, 1));
      transform.setParent(txPtr);

      glm::mat4 expected;
      expected[3] = glm::vec4(1.75f, -3, 0, 1);
      expected = glm::rotate(expected, -glm::pi<float>(), glm::vec3(0, 0, 1));
      expected = glm::scale(expected, glm::vec3(2.5f, 0.25f, -1));

      Assert::IsTrue(expected == transform.getWorldMatrix());
    }

#pragma endregion

#pragma region Get Inverse World Matrix Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseWorldMatrix_WithNoParent)
    {
      Transform transform;
      transform.setRotation(glm::half_pi<float>());
      transform.setTranslation(glm::vec3(2, -1, 1));
      transform.setScale(glm::vec3(0.5f, 0.25f, 1));

      glm::mat4 expected = glm::inverse(transform.getWorldMatrix());

      Assert::IsNull(transform.getParent());
      AssertExt::AreAlmostEqual(expected, transform.getInverseWorldMatrix());
      AssertExt::AreAlmostEqual(glm::mat4(), transform.getInverseWorldMatrix() * transform.getWorldMatrix());
      AssertExt::AreAlmostEqual(glm::mat4(), transform.getWorldMatrix() * transform.getInverseWorldMatrix());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_GetInverseWorldMatrix_WithParent)
    {
      Transform transform, parent;
      Transform* parentPtr = &parent;

      parent.setRotation(glm::half_pi<float>());
      parent.setTranslation(glm::vec3(-0.25f, -2, -1));
      parent.setScale(glm::vec3(5, 1, -1));

      transform.setRotation(glm::half_pi<float>());
      transform.setTranslation(glm::vec3(2, -1, 1));
      transform.setScale(glm::vec3(0.5f, 0.25f, 1));
      transform.setParent(&parent);

      glm::mat4 expected = glm::inverse(transform.getWorldMatrix());

      Assert::AreEqual(&parent, transform.getParent());
      AssertExt::AreAlmostEqual(expected, transform.getInverseWorldMatrix());
      AssertExt::AreAlmostEqual(glm::mat4(), transform.getInverseWorldMatrix() * transform.getWorldMatrix());
      AssertExt::AreAlmostEqual(glm::mat4(), transform.getWorldMatrix() * transform.getInverseWorldMatrix());
    }

#pragma endregion

#pragma region Can Allocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_CanAllocate_ShouldReturnTrue)
    {
      Assert::IsTrue(Transform::canAllocate(0));
      Assert::IsTrue(Transform::canAllocate(1));
      Assert::IsTrue(Transform::canAllocate(10));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_CanAllocate_ShouldReturnFalse)
    {
      Assert::IsFalse(Transform::canAllocate(3010000000));
      Assert::IsFalse(Transform::canAllocate(60000000));
    }

#pragma endregion

#pragma region Allocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Allocate_WithSpaceLeft_ReturnsAllocatedTransformHandle)
    {
      AutoDeallocator<Transform> handle = Transform::allocate(GameObject());

      Assert::IsNotNull(handle.get());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Allocate_WithAllocatedHandle_SetsGameObjectToInput)
    {
      GameObject gameObject;
      AutoDeallocator<Transform> handle = Transform::allocate(gameObject);

      Assert::IsTrue(&gameObject == handle->getGameObject());
    }

#pragma endregion

#pragma region Deallocate Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Deallocate_ResetsAllTransformValues)
    {
      AutoDeallocator<Transform> handle = Transform::allocate(GameObject());
      const Transform* hPtr = handle.get();

      handle->setRotation(2);
      handle->setScale(glm::vec3());
      handle->setTranslation(glm::vec3(1, 1, 1));
      handle->deallocate();

      Assert::AreEqual(0.0f, hPtr->getRotation());
      Assert::IsTrue(glm::vec3() == hPtr->getTranslation());
      Assert::IsTrue(glm::vec3(1, 1, 1) == hPtr->getScale());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Deallocate_WithDeallocatedGameObject_SetsGameObjectToNullptr)
    {
      GameObject gameObject;
      GameObject* gameObjectPtr = &gameObject;

      AutoDeallocator<Transform> handle = Transform::allocate(gameObject);
      gameObject.deallocate();

      Assert::AreEqual(gameObjectPtr, handle->getGameObject());

      handle->deallocate();

      Assert::IsNull(handle->getGameObject());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Deallocate_WithAllocatedGameObject_SetsGameObjectToNullptr)
    {
      GameObject gameObject;
      GameObject* gameObjectPtr = &gameObject;

      AutoDeallocator<Transform> handle = Transform::allocate(gameObject);

      Assert::AreEqual(gameObjectPtr, handle->getGameObject());

      handle->deallocate();

      Assert::IsNull(handle->getGameObject());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Deallocate_WithoutChildren_KeepsChildrenEmpty)
    {
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      const Transform* tPtr = parent.get();

      Assert::AreEqual((size_t)0, parent->getChildCount());

      parent->deallocate();

      Assert::AreEqual((size_t)0, tPtr->getChildCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Deallocate_WithChildren_DeallocatesAllChildren_AndEmptiesChildrenList)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());
      const Transform* tPtr = parent.get();

      Assert::IsNull(transform->getParent());
      Assert::AreEqual((size_t)0, parent->getChildCount());

      transform->setParent(parent.get());

      Assert::AreEqual(parent.get(), transform->getParent());
      Assert::AreEqual((size_t)1, parent->getChildCount());

      parent->deallocate();

      Assert::AreEqual((size_t)0, tPtr->getChildCount());
      Assert::IsNull(tPtr->getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Transform_Deallocate_WithParent_RemovesTransformFromParentChildren)
    {
      AutoDeallocator<Transform> transform = Transform::allocate(GameObject());
      AutoDeallocator<Transform> parent = Transform::allocate(GameObject());

      Assert::IsNull(transform->getParent());
      Assert::AreEqual((size_t)0, parent->getChildCount());

      transform->setParent(parent.get());

      Assert::AreEqual(parent.get(), transform->getParent());
      Assert::AreEqual((size_t)1, parent->getChildCount());

      transform->deallocate();

      Assert::AreEqual((size_t)0, parent->getChildCount());
    }

#pragma endregion

  };
}