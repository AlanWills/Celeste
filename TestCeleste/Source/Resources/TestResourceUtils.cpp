#include "UtilityHeaders/UnitTestHeaders.h"

#include "Resources/ResourceUtils.h"
#include "Game/Game.h"
#include "AssertSpecialization/FileSystem.h"


namespace TestCeleste::Resources
{
  CELESTE_TEST_CLASS(TestResourceUtils)

#pragma region Get Resource Manager Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceUtils_GetResourceManager_ReturnsGameResourceManager)
  {
    Assert::IsTrue(&Celeste::Game::getResourceManager() == &Celeste::Resources::getResourceManager());
  }

#pragma endregion

#pragma region Get Resources Directory Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceUtils_GetResourcesDirectory_ReturnsResourceManagerResourceDirectory)
  {
    Assert::AreEqual(Celeste::Game::getResourceManager().getResourcesDirectory(), Celeste::Resources::getResourcesDirectory());
  }

#pragma endregion

  };
}