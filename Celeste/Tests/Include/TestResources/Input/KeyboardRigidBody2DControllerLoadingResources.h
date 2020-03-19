#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_KEYBOARD_RIGIDBODY2D_CONTROLLER_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, KeyboardRigidBody2DControllerData, ResourceRelativePath)

  class KeyboardRigidBody2DControllerLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(KeyboardRigidBody2DControllerLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(KeyboardRigidBody2DControllerData, "KeyboardRigidBody2DController Data")

    TEST_KEYBOARD_RIGIDBODY2D_CONTROLLER_DATA(Invalid, "Invalid.xml");
    TEST_KEYBOARD_RIGIDBODY2D_CONTROLLER_DATA(Valid, "Valid.xml");
  };
}