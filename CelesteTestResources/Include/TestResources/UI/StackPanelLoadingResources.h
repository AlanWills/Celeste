#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_STACKPANEL_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, StackPanelData, ResourceRelativePath)

  class StackPanelLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(StackPanelLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(StackPanelData, "StackPanel Data")

    TEST_STACKPANEL_DATA(Valid, "Valid.xml");
    TEST_STACKPANEL_DATA(Invalid, "Invalid.xml");
  };
}