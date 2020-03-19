#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_RIGIDBODY2D_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, RigidBody2DData, ResourceRelativePath)

  class RigidBody2DLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(RigidBody2DLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(RigidBody2DData, "RigidBody2D Data")

    TEST_RIGIDBODY2D_DATA(Invalid, "Invalid.xml");
    TEST_RIGIDBODY2D_DATA(Valid, "Valid.xml");
  };
}