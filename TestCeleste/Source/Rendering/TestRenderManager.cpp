#include "UtilityHeaders/UnitTestHeaders.h"

#include "Rendering/RenderManager.h"
#include "Rendering/Canvas.h"
#include "Rendering/RenderUtils.h"

#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste::Rendering;


namespace TestCeleste::Rendering
{
  CELESTE_TEST_CLASS(TestRenderManager)

#pragma region Die Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderManager_Die_CallsDieOnAllAliveCanvasses)
  {
    GAMEOBJECT(gameObject);
    RenderManager manager;

    AutoDeallocator<Canvas> canvas = gameObject.addComponent<Canvas>();
    canvas->setActive(false);

    AssertCel::IsAlive(canvas.get());
    AssertCel::IsNotActive(canvas.get());

    manager.die();

    AssertCel::IsNotAlive(canvas.get());
    AssertCel::IsNotActive(canvas.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(RenderManager_Die_CallsDieOnAllActiveCanvasses)
  {
    GAMEOBJECT(gameObject);
    RenderManager manager;

    AutoDeallocator<Canvas> canvasses = gameObject.addComponent<Canvas>();
    canvasses->setActive(true);

    AssertCel::IsAlive(canvasses.get());
    AssertCel::IsActive(canvasses.get());

    manager.die();

    AssertCel::IsNotAlive(canvasses.get());
    AssertCel::IsNotActive(canvasses.get());
  }

#pragma endregion

  };
}