#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_KEYBOARD_ACTIVATOR_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, KeyboardActivatorData, ResourceRelativePath)

  class KeyboardActivatorLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(KeyboardActivatorLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(KeyboardActivatorData, "KeyboardActivator Data")

    TEST_KEYBOARD_ACTIVATOR_DATA(Invalid, "Invalid.xml");
    TEST_KEYBOARD_ACTIVATOR_DATA(Valid, "Valid.xml");
  };
}