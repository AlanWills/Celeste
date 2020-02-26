#include "UtilityHeaders/UnitTestHeaders.h"

#include "Debug/Profiling/FPSCounter.h"
#include "Rendering/TextRenderer.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste::Debugging;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestFPSCounter)

#pragma region Update Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FPSCounter_Update_TextRendererNull_DoesNothing)
  {
    FPSCounter fpsCounter;
    
    // This shouldn't throw
    fpsCounter.update(1);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FPSCounter_Update_LessThanHalfASecondPassed_DoesNotChangeTextRenderer)
  {
    GAMEOBJECT(gameObject);
    AutoDeallocator<Celeste::Rendering::TextRenderer> renderer = gameObject.addComponent<Celeste::Rendering::TextRenderer>();
    renderer->addLine("Text");
    AutoDeallocator<FPSCounter> fpsCounter = gameObject.addComponent<FPSCounter>();

    Assert::AreEqual(static_cast<size_t>(1), renderer->getLineCount());
    Assert::AreEqual("Text", renderer->getLine(0).c_str());

    fpsCounter->update(0.25f);

    Assert::AreEqual(static_cast<size_t>(1), renderer->getLineCount());
    Assert::AreEqual("Text", renderer->getLine(0).c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(FPSCounter_Update_AtLeastHalfASecondPassed_UpdatesTextRendererWithCorrectText)
  {
    GAMEOBJECT(gameObject);
    AutoDeallocator<Celeste::Rendering::TextRenderer> renderer = gameObject.addComponent<Celeste::Rendering::TextRenderer>();
    renderer->addLine("Text");
    AutoDeallocator<FPSCounter> fpsCounter = gameObject.addComponent<FPSCounter>();

    Assert::AreEqual(static_cast<size_t>(1), renderer->getLineCount());
    Assert::AreEqual("Text", renderer->getLine(0).c_str());

    fpsCounter->update(0.55f);

    Assert::AreEqual(static_cast<size_t>(1), renderer->getLineCount());
    Assert::AreEqual(std::to_string(static_cast<size_t>(1 / 0.55f)), renderer->getLine(0));
  }

#pragma endregion

  };
}