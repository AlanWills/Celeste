#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_SCRIPT(FileName, ResourceRelativePath) \
    TEST_RESOURCE(FileName, LuaScripts, ResourceRelativePath) \
    \
    static std::string get##FileName##Name() { return #FileName; }

  class LuaScriptResources
  {
    DECLARE_TEST_RESOURCE_CLASS(LuaScriptResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(LuaScripts, "Scripts")

    TEST_SCRIPT(EmptyModule, "EmptyModule");
  };
}