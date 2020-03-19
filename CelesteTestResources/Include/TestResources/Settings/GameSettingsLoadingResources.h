#pragma once

#include "TestResources/TestResources.h"


namespace CelesteTestResources
{
  #define TEST_GAME_SETTINGS_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, GameSettingsData, ResourceRelativePath)

  class GameSettingsLoadingResources
  {
    DECLARE_TEST_RESOURCE_CLASS(GameSettingsLoadingResources)
    DECLARE_TEST_RESOURCE_DIRECTORY(GameSettingsData, "GameSettings Data")

    TEST_GAME_SETTINGS_DATA(Valid, "Valid.asset");
    TEST_GAME_SETTINGS_DATA(Invalid, "Invalid.asset");
  };
}