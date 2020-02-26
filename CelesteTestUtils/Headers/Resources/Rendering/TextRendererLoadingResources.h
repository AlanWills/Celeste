#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_TEXTRENDERER_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, TextRendererData, ResourceRelativePath)

  class TextRendererLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(TextRendererLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(TextRendererData, "TextRenderer Data")

    TEST_TEXTRENDERER_DATA(Invalid, "Invalid.xml");
    TEST_TEXTRENDERER_DATA(ValidNoLines, "ValidNoLines.xml");
    TEST_TEXTRENDERER_DATA(ValidWithLines, "ValidWithLines.xml");
  };
}