#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_SLIDER_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, SliderData, ResourceRelativePath)

  class SliderLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(SliderLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(SliderData, "Slider Data")

    TEST_SLIDER_DATA(ValidWithCallbacks, "ValidWithCallbacks.xml");
    TEST_SLIDER_DATA(ValidNoCallbacks, "ValidNoCallbacks.xml");
    TEST_SLIDER_DATA(Invalid, "Invalid.xml");
  };
}