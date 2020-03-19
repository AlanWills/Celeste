#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
#define TEST_WINDOW_SETTINGS_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, WindowSettingsData, ResourceRelativePath)

  class WindowSettingsLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(WindowSettingsLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(WindowSettingsData, "WindowSettings Data")

    TEST_WINDOW_SETTINGS_DATA(Valid, "Valid.asset");
    TEST_WINDOW_SETTINGS_DATA(Invalid, "Invalid.asset");
  };
}