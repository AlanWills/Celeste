#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_RECTANGLECOLLIDER_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, RectangleColliderData, ResourceRelativePath)

  class RectangleColliderLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(RectangleColliderLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(RectangleColliderData, "RectangleCollider Data")

    TEST_RECTANGLECOLLIDER_DATA(Invalid, "Invalid.xml");
    TEST_RECTANGLECOLLIDER_DATA(Valid, "Valid.xml");
  };
}