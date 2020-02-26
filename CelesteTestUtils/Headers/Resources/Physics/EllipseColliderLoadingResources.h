#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_ELLIPSE_COLLIDER_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, EllipseColliderData, ResourceRelativePath)

  class EllipseColliderLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(EllipseColliderLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(EllipseColliderData, "EllipseCollider Data")

    TEST_ELLIPSE_COLLIDER_DATA(Invalid, "Invalid.xml");
    TEST_ELLIPSE_COLLIDER_DATA(Valid, "Valid.xml");
  };
}