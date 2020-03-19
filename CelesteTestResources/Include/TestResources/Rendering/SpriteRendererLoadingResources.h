#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_SPRITERENDERER_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, SpriteRendererData, ResourceRelativePath)

  class SpriteRendererLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(SpriteRendererLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(SpriteRendererData, "SpriteRenderer Data")

    TEST_SPRITERENDERER_DATA(Invalid, "Invalid.xml");
    TEST_SPRITERENDERER_DATA(Valid, "Valid.xml");
  };
}