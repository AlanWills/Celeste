#pragma once

#include "CelesteUnitTest.h"


namespace CelesteTestUtils
{
  class ALUnitTest : public CelesteUnitTest
  {
    protected:
      void testInitialize() override;
      void testCleanup() override;
  };
};