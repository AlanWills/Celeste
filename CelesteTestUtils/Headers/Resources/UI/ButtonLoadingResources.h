#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_BUTTON_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, ButtonData, ResourceRelativePath)

  class ButtonLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(ButtonLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(ButtonData, "Button Data")

    TEST_BUTTON_DATA(ValidWithCallbacks, "ValidWithCallbacks.xml");
    TEST_BUTTON_DATA(ValidNoCallbacks, "ValidNoCallbacks.xml");
    TEST_BUTTON_DATA(Invalid, "Invalid.xml");
  };
}