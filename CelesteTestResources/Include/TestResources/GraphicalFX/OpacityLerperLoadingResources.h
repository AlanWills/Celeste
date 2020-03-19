#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_OPACITYLERPER_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, OpacityLerperData, ResourceRelativePath)

  class OpacityLerperLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(OpacityLerperLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(OpacityLerperData, "OpacityLerper Data")

    TEST_OPACITYLERPER_DATA(Invalid, "Invalid.xml");
    TEST_OPACITYLERPER_DATA(Valid, "Valid.xml");
  };
}