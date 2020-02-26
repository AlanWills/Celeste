#pragma once

#include "Resources/TestResources.h"


namespace CelesteEngineTestUtils
{
  #define TEST_SCRIPT(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, LuaScripts, ResourceRelativePath)

  class CETestUtilsDllExport LuaScriptResources
  {
    DECLARE_TEST_RESOURCE_CLASS(LuaScriptResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(LuaScripts, "KeyboardActivator Data")

    TEST_KEYBOARD_ACTIVATOR_DATA(Invalid, "Invalid.xml");
    TEST_KEYBOARD_ACTIVATOR_DATA(Valid, "Valid.xml");
  };
}