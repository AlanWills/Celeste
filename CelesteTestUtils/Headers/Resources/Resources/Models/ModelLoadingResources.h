#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_MODEL_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, Models, ResourceRelativePath)

  class ModelLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(ModelLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(Models, "Models")

    TEST_MODEL_DATA(Box, "Box\\Crate1.obj");
  };
}