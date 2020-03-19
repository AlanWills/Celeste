#include "UtilityHeaders/UnitTestHeaders.h"

#include "Debug/Profiling/Profiler.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"
#include "Utils/StringUtils.h"

#include "FileAssert.h"
#include "AssertExt.h"

#include <chrono>
#include <thread>

using namespace Celeste;


namespace TestCeleste
{
  static Path resultsFilePath(Directory::getExecutingAppDirectory(), "Profiling.txt");

  CELESTE_TEST_CLASS(TestProfiler)

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_ConstructorWithString)
    {
      Profiler profiler(resultsFilePath.as_string());
      FileAssert::FileExists(resultsFilePath.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_ConstructorWithPath)
    {
      Profiler profiler(resultsFilePath);
      FileAssert::FileExists(resultsFilePath.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_GetProfilingBlock_WithExistentBlock_ReturnsBlockSuccessfully)
    {
      Profiler profiler(resultsFilePath);
      profiler.beginProfilingBlock("Test Get Profiling Block");

      Assert::IsNotNull(profiler.getProfilingBlock("Test Get Profiling Block"));

      profiler.endProfilingBlock("Test Get Profiling Block");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_GetProfilingBlock_WithNonExistentBlock_ReturnsNullptr)
    {
      Profiler profiler(resultsFilePath);
      Assert::IsNull(profiler.getProfilingBlock("Test Block That Shouldnt Exist"));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_BeginProfilingBlock_OpensBlock)
    {
      Profiler profiler(resultsFilePath);
      profiler.beginProfilingBlock("Test Opening");

      Assert::IsFalse(profiler.getProfilingBlock("Test Opening")->isClosed());

      profiler.endProfilingBlock("Test Opening");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_EndProfilingBlock_ClosesBlock)
    {
      Profiler profiler(resultsFilePath);
      profiler.beginProfilingBlock("Test Opening");

      // To prove it is actually changed
      Assert::IsFalse(profiler.getProfilingBlock("Test Opening")->isClosed());

      profiler.endProfilingBlock("Test Opening");

      Assert::IsTrue(profiler.getProfilingBlock("Test Opening")->isClosed());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_GetCurrentProfilingBlockName_SingleBlock)
    {
      Profiler profiler(resultsFilePath);
      profiler.beginProfilingBlock("Test Get Name");

      Assert::AreEqual("Test Get Name", profiler.getCurrentProfilingBlockName().c_str());

      profiler.endProfilingBlock("Test Get Name");

      Assert::AreEqual("Test Get Name", profiler.getCurrentProfilingBlockName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_GetCurrentProfilingBlockName_NestedBlocks)
    {
      Profiler profiler(resultsFilePath);
      profiler.beginProfilingBlock("Root");

      Assert::AreEqual("Root", profiler.getCurrentProfilingBlockName().c_str());
      {
        profiler.beginProfilingBlock("Nested");

        Assert::AreEqual("Nested", profiler.getCurrentProfilingBlockName().c_str());

        profiler.endProfilingBlock("Nested");

        Assert::AreEqual("Nested", profiler.getCurrentProfilingBlockName().c_str());
      }
      profiler.endProfilingBlock("Root");

      Assert::AreEqual("Nested", profiler.getCurrentProfilingBlockName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_ProfileCodeBlock)
    {
      Profiler profiler(resultsFilePath);
      long long expectedTime = 1;

      profiler.beginProfilingBlock("Profile Code Block");

      // Simulate some work
      std::this_thread::sleep_for(std::chrono::seconds(expectedTime));

      profiler.endProfilingBlock("Profile Code Block");

      const ProfilingBlock* profilingBlock = profiler.getProfilingBlock("Profile Code Block");

      Assert::IsNotNull(profilingBlock);
      Assert::AreEqual("Profile Code Block", profilingBlock->getName().c_str());
      Assert::AreEqual(1, profilingBlock->getNumCalls());
      AssertExt::AreAlmostEqual(expectedTime * 1000.0f, static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(profilingBlock->getAverageTimeTaken()).count()), 100);
      AssertExt::AreAlmostEqual(expectedTime * 1000.0f, static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(profilingBlock->getLastCallTimeTaken()).count()), 100);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_ProfileFunction)
    {
      Profiler profiler(resultsFilePath);
      int numCalls = 10;

      for (int i = 0; i < numCalls; ++i)
      {
        profiler.beginProfilingBlock("Profile Function Block");

        testFunction();

        profiler.endProfilingBlock("Profile Function Block");
      }

      const ProfilingBlock* profilingBlock = profiler.getProfilingBlock("Profile Function Block");

      Assert::IsNotNull(profilingBlock);
      Assert::AreEqual("Profile Function Block", profilingBlock->getName().c_str());
      Assert::AreEqual(numCalls, profilingBlock->getNumCalls());
      AssertExt::AreAlmostEqual(100.0f, static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(profilingBlock->getAverageTimeTaken()).count()), 100);
      AssertExt::AreAlmostEqual(100.0f, static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(profilingBlock->getLastCallTimeTaken()).count()), 100);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_ProfileCodeBlock_FileResults)
    {
      int numCalls = 0;
      ProfilingBlock::Seconds averageTimeTaken(0);
      ProfilingBlock::Seconds lastCallTimeTaken(0);

      // Scope the profiler so that it is destroyed in this test and writes to the file
      {
        Profiler profiler(resultsFilePath);
        int expectedTime = 1;

        profiler.beginProfilingBlock("Profile Code Block");

        // Simulate some work
        std::this_thread::sleep_for(std::chrono::seconds(expectedTime));

        profiler.endProfilingBlock("Profile Code Block");

        const ProfilingBlock* profilingBlock = profiler.getProfilingBlock("Profile Code Block");
        Assert::IsNotNull(profilingBlock);

        numCalls = profilingBlock->getNumCalls();
        averageTimeTaken = profilingBlock->getAverageTimeTaken();
        lastCallTimeTaken = profilingBlock->getLastCallTimeTaken();
      }

      checkResultsFileContents("Profile Code Block", numCalls, averageTimeTaken, lastCallTimeTaken);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_ProfileFunction_FileResults)
    {
      int numCalls = 10;
      ProfilingBlock::Seconds averageTimeTaken(0);
      ProfilingBlock::Seconds lastCallTimeTaken(0);

      // Scope the profiler so that it is destroyed in this test and writes to the file
      {
        Profiler profiler(resultsFilePath);

        for (int i = 0; i < numCalls; ++i)
        {
          profiler.beginProfilingBlock("Profile Function Block");

          testFunction();

          profiler.endProfilingBlock("Profile Function Block");
        }

        const ProfilingBlock* profilingBlock = profiler.getProfilingBlock("Profile Function Block");
        Assert::IsNotNull(profilingBlock);

        averageTimeTaken = profilingBlock->getAverageTimeTaken();
        lastCallTimeTaken = profilingBlock->getLastCallTimeTaken();
      }

      checkResultsFileContents("Profile Function Block", numCalls, averageTimeTaken, lastCallTimeTaken);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Profiler_DestructorClosesAllBlocks_AndLogsDataToFile)
    {
      // Scope the profiler so it is destroyed within the test rather than at the end of the test function
      {
        Profiler profiler(resultsFilePath);
        profiler.beginProfilingBlock("Test Destructor");
      }

      // Currently can't think of a way of testing closure, because the profiler has ownership of the blocks
      FileAssert::FileExists(resultsFilePath.as_string());
    }

    //------------------------------------------------------------------------------------------------
    void checkResultsFileContents(
      const std::string& blockName, 
      int numCalls, 
      ProfilingBlock::Seconds averageTime, 
      ProfilingBlock::Seconds lastTime)
    {
      std::string expectedFileContents;
      expectedFileContents.append("Profiling Block: ");
      expectedFileContents.append(blockName);
      expectedFileContents.append("\n");

      expectedFileContents.append("Number of calls: ");
      numericToStringAppend(numCalls, expectedFileContents);
      expectedFileContents.append("\n");

      expectedFileContents.append("Average time (s): ");
      numericToStringAppend(std::chrono::duration_cast<std::chrono::milliseconds>(averageTime).count() / 1000.0f, expectedFileContents);
      expectedFileContents.append("\n");

      expectedFileContents.append("Last call time (s): ");
      numericToStringAppend(std::chrono::duration_cast<std::chrono::milliseconds>(lastTime).count() / 1000.0f, expectedFileContents);

      FileAssert::FileContentsEqual(resultsFilePath.as_string(), expectedFileContents);
    }

    //------------------------------------------------------------------------------------------------
    void testFunction()
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  };
}