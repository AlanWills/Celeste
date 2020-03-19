#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_KEYBOARD_TRANSFORMER_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, KeyboardTransformerData, ResourceRelativePath)

  class KeyboardTransformerLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(KeyboardTransformerLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(KeyboardTransformerData, "KeyboardTransformer Data")

    TEST_KEYBOARD_TRANSFORMER_DATA(Invalid, "Invalid.xml");
    TEST_KEYBOARD_TRANSFORMER_DATA(Valid, "Valid.xml");
  };
}