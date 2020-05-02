#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Resources/ResourceManager.h"
#include "Resources/ResourceUtils.h"
#include "Game/Game.h"
#include "TestUtils/AssertSpecialization/FileSystem.h"

using namespace Celeste;
using ResourceManager = Celeste::Resources::ResourceManager;


namespace TestCeleste::Resources
{
  CELESTE_TEST_CLASS(TestResourceUtils)

#pragma region Get Resource Manager Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceUtils_GetResourceManager_ReturnsGameResourceManager)
  {
    Assert::IsTrue(&Game::current().getResourceManager() == &Celeste::Resources::getResourceManager());
  }

#pragma endregion

#pragma region Get Resources Directory Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ResourceUtils_GetResourcesDirectory_ReturnsResourceManagerResourceDirectory)
  {
    Assert::AreEqual(Game::current().getResourceManager().getResourcesDirectory(), Celeste::Resources::getResourcesDirectory());
  }

#pragma endregion

  };
}