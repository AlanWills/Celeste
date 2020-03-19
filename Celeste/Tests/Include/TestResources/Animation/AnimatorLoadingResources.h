#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_ANIMATOR_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, AnimatorData, ResourceRelativePath)

  class AnimatorLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(AnimatorLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(AnimatorData, "Animator Data")

    TEST_ANIMATOR_DATA(Invalid, "Invalid.xml");
    TEST_ANIMATOR_DATA(Valid, "Valid.xml");
  };
}