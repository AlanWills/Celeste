#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Debug/Profiling/FPSCounter.h"
#include "Rendering/TextRenderer.h"
#include "Objects/GameObject.h"
#include "CelesteTestUtils/Assert/AssertCel.h"
#include "Time/TimeUtils.h"
#include "Time/Clock.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste;
using namespace Celeste::Debugging;
using namespace Celeste::Time;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestFPSCounter)

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FPSCounter_Update_TextRendererNull_DoesNothing)
  {
    GameObject gameObject;
    FPSCounter fpsCounter(gameObject);

    getClock().update(1);

    Assert::AreEqual(1.0f, getElapsedDeltaTime());

    // This shouldn't throw
    fpsCounter.update();
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FPSCounter_Update_LessThanHalfASecondPassed_DoesNotChangeTextRenderer)
  {
    GameObject gameObject;
    observer_ptr<Celeste::Rendering::TextRenderer> renderer = gameObject.addComponent<Celeste::Rendering::TextRenderer>();
    renderer->setText("Text");
    observer_ptr<FPSCounter> fpsCounter = gameObject.addComponent<FPSCounter>();

    Assert::AreEqual("Text", renderer->getText().c_str());

    getClock().update(0.25f);

    Assert::AreEqual(0.25f, getElapsedDeltaTime());

    fpsCounter->update();

    Assert::AreEqual("Text", renderer->getText().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FPSCounter_Update_AtLeastHalfASecondPassed_UpdatesTextRendererWithCorrectText)
  {
    GameObject gameObject;
    observer_ptr<Celeste::Rendering::TextRenderer> renderer = gameObject.addComponent<Celeste::Rendering::TextRenderer>();
    renderer->setText("Text");
    observer_ptr<FPSCounter> fpsCounter = gameObject.addComponent<FPSCounter>();

    Assert::AreEqual("Text", renderer->getText().c_str());

    getClock().update(0.55f);

    AssertExt::AreAlmostEqual(0.55f, getElapsedDeltaTime());

    fpsCounter->update();

    Assert::AreEqual(std::to_string(static_cast<size_t>(1 / 0.55f)), renderer->getText());
  }

#pragma endregion

  };
}