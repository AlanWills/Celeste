#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Debug/Profile.h"
#include "Debug/Profiling/ProfilingBlock.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"
#include "TestUtils/Assert/AssertExt.h"

#include <chrono>
#include <thread>

using namespace Celeste;


namespace TestCeleste
{
  static Path resultsFilePath(Directory::getExecutingAppDirectory(), "Profiling.txt");

  CELESTE_TEST_CLASS(TestProfile)

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Debug_PROFILING_BLOCK_Macros)
  {
    float expectedTime = 1;
  
    BEGIN_PROFILING_BLOCK("Profile Code Block");
  
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds((int)expectedTime));
  
    END_PROFILING_BLOCK("Profile Code Block");
  
    const ProfilingBlock* profilingBlock = Profile::getProfiler()->getProfilingBlock("Profile Code Block");
  
    Assert::IsNotNull(profilingBlock);
    Assert::AreEqual(1, profilingBlock->getNumCalls());
    AssertExt::AreAlmostEqual(expectedTime * 1000, static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(profilingBlock->getAverageTimeTaken()).count()), 100);
    AssertExt::AreAlmostEqual(expectedTime * 1000, static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(profilingBlock->getLastCallTimeTaken()).count()), 100);
  }

  };
}