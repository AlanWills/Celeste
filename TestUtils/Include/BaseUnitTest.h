#pragma once


namespace TestUtils
{
  class BaseUnitTest
  {
    public:
      BaseUnitTest() { }
      virtual ~BaseUnitTest() noexcept(false) { }

      void testInitializeCaller() 
      { 
        testInitialize(); 
      }

      void testCleanupCaller()
      {
        testCleanup();
      }

    protected:
      static void testClassInitialize() { }
      static void testClassCleanup() { }

      virtual void testInitialize() { }
      virtual void testCleanup() { }
  };
}