#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Time/Clock.h"

#include <chrono>
#include <thread>

#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestClock)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_Constructor)
    {
      Clock clock(10, 20);

      Assert::AreEqual(10, clock.getTargetFramesPerSecond());
      Assert::AreEqual((uint64_t)(20 * CLOCKS_PER_SEC), clock.getElapsedCycles());
      Assert::IsFalse(clock.getPaused());
      Assert::AreEqual(1.0f, clock.getTimeScale());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_CyclesToSeconds)
    {
      Assert::AreEqual(10.0f, Clock::cyclesToSeconds(static_cast<uint64_t>(10) * CLOCKS_PER_SEC));
      Assert::AreEqual(0.0f, Clock::cyclesToSeconds(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_SecondsToCycles)
    {
      Assert::AreEqual((uint64_t)20 * CLOCKS_PER_SEC, Clock::secondsToCycles(20));
      Assert::AreEqual((uint64_t)0, Clock::secondsToCycles(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_SystemSeconds)
    {
      Assert::AreEqual(20.0f, Clock::systemSeconds(std::chrono::seconds(20)));
      Assert::AreEqual(0.0f, Clock::systemSeconds(std::chrono::seconds(0)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_Update)
    {
      Clock clock;

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.update(0.24f);

      AssertExt::AreAlmostEqual(0.24f, clock.getElapsedDeltaTime());

      clock.update(0.13f);

      AssertExt::AreAlmostEqual(0.13f, clock.getElapsedDeltaTime());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_UpdateSlowerThanNormalTimeScale)
    {
      Clock clock;
      clock.setTimeScale(0.5f);

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.update(0.24f);

      AssertExt::AreAlmostEqual(0.12f, clock.getElapsedDeltaTime());

      clock.update(0.06f);

      AssertExt::AreAlmostEqual(0.03f, clock.getElapsedDeltaTime());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_UpdateFasterThanNormalTimeScale)
    {
      Clock clock;
      clock.setTimeScale(2.0f);

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.update(0.24f);

      AssertExt::AreAlmostEqual(0.48f, clock.getElapsedDeltaTime());

      clock.update(0.13f);

      AssertExt::AreAlmostEqual(0.26f, clock.getElapsedDeltaTime());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_NoUpdateWhenPaused)
    {
      Clock clock;
      clock.setPaused(true);

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.update(0.24f);

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.update(0.13f);

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_SingleStep)
    {
      Clock clock(1);
      clock.setTargetFramesPerSecond(10);

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.singleStep();

      Assert::AreEqual(0.1f, clock.getElapsedDeltaTime());

      clock.singleStep();

      Assert::AreEqual(0.1f, clock.getElapsedDeltaTime());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_SingleStepSlowerThanNormalTimeScale)
    {
      // Bump up the cpu cycles a little for this test (it will be reset)
      Clock clock(4);
      clock.setTimeScale(0.5f);
      clock.setTargetFramesPerSecond(5);

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.singleStep();

      AssertExt::AreAlmostEqual(0.1f, clock.getElapsedDeltaTime());

      clock.singleStep();

      AssertExt::AreAlmostEqual(0.1f, clock.getElapsedDeltaTime());

      clock.singleStep();

      AssertExt::AreAlmostEqual(0.1f, clock.getElapsedDeltaTime());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_SingleStepFasterThanNormalTimeScale)
    {
      Clock clock(4);
      clock.setTimeScale(2.0f);
      clock.setTargetFramesPerSecond(2);

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.singleStep();

      Assert::AreEqual(1.0f, clock.getElapsedDeltaTime());

      clock.singleStep();

      Assert::AreEqual(1.0f, clock.getElapsedDeltaTime());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_NoSingleStepWhenPaused)
    {
      Clock clock(4);
      clock.setPaused(true);
      clock.setTargetFramesPerSecond(60);

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.singleStep();

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());

      clock.singleStep();

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Clock_Reset)
    {
      Clock clock;
      clock.update(12.1f);

      Assert::AreEqual(12.1f, clock.getElapsedDeltaTime());

      clock.reset();

      Assert::AreEqual(0.0f, clock.getElapsedDeltaTime());
    }
  };
}