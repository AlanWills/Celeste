#include "ALUnitTest.h"
#include "UtilityHeaders/ALHeaders.h"
#include "OpenAL/OpenALState.h"


namespace CelesteTestUtils
{
  //------------------------------------------------------------------------------------------------
  void ALUnitTest::testInitialize()
  {
    CelesteUnitTest::testInitialize();

    Celeste::OpenALState::terminate();
    Celeste::OpenALState::initialize();
  }

  //------------------------------------------------------------------------------------------------
  void ALUnitTest::testCleanup()
  {
    CelesteUnitTest::testCleanup();

    Celeste::OpenALState::terminate();
    Celeste::OpenALState::initialize();
  }
}