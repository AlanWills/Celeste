#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_GAMEOBJECT_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, GameObjectData, ResourceRelativePath)

  class GameObjectLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(GameObjectLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(GameObjectData, "GameObject Data")

    TEST_GAMEOBJECT_DATA(Invalid, "Invalid.xml");
    TEST_GAMEOBJECT_DATA(Valid, "Valid.xml");
  };
}