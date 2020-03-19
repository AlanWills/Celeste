#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_PREFAB_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, PrefabData, ResourceRelativePath)

  class PrefabLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(PrefabLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(PrefabData, "Prefab Data")

    TEST_PREFAB_DATA(Empty, "Empty.prefab");
    TEST_PREFAB_DATA(NoGameObjectsElement, "NoGameObjectsElement.prefab");
    TEST_PREFAB_DATA(Invalid, "Invalid.prefab");
    TEST_PREFAB_DATA(ValidSingleGameObject, "ValidSingleGameObject.prefab");
    TEST_PREFAB_DATA(ValidMultipleGameObjects, "ValidMultipleGameObjects.prefab");
    TEST_PREFAB_DATA(ValidMultipleChildrenForSingleParent, "ValidMultipleChildrenForSingleParent.prefab");
    TEST_PREFAB_DATA(TwoParentGameObjects, "TwoParentGameObjects.prefab");
  };
}