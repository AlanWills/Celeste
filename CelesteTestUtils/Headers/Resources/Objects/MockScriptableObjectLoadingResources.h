#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_MOCK_SCRIPTABLE_OBJECT_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, MockScriptableObjectData, ResourceRelativePath)

  class MockScriptableObjectLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(MockScriptableObjectLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(MockScriptableObjectData, "MockScriptableObject Data")

    TEST_MOCK_SCRIPTABLE_OBJECT_DATA(Invalid, "Invalid.xml");
    TEST_MOCK_SCRIPTABLE_OBJECT_DATA(Valid, "Valid.xml");
  };
}