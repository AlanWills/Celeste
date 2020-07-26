#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Rendering/RenderManager.h"
#include "Rendering/RenderUtils.h"
#include "Game/Game.h"

using namespace Celeste::Rendering;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestRenderUtils)

#pragma region Get Render Manager Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderUtils_GetRenderManager_EqualsGameRenderManager)
  {
    Assert::IsTrue(&getRenderManager() == Celeste::Game::current().getSystem<RenderManager>());
  }

#pragma endregion

  };
}