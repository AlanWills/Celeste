#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_KEYBOARD_VISIBILITY_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, KeyboardVisibilityData, ResourceRelativePath)

  class KeyboardVisibilityLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(KeyboardVisibilityLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(KeyboardVisibilityData, "KeyboardVisibility Data")

    TEST_KEYBOARD_VISIBILITY_DATA(Invalid, "Invalid.xml");
    TEST_KEYBOARD_VISIBILITY_DATA(Valid, "Valid.xml");
  };
}