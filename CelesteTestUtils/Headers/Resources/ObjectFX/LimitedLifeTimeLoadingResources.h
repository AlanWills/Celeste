#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_LIMITEDLIFETIME_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, LimitedLifeTimeData, ResourceRelativePath)

  class LimitedLifeTimeLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(LimitedLifeTimeLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(LimitedLifeTimeData, "LimitedLifeTime Data")

    TEST_LIMITEDLIFETIME_DATA(ValidWithCallbacks, "ValidWithCallbacks.xml");
    TEST_LIMITEDLIFETIME_DATA(ValidNoCallbacks, "ValidNoCallbacks.xml");
    TEST_LIMITEDLIFETIME_DATA(Invalid, "Invalid.xml");
  };
}