#include "TestUtils/TestUtils.h"
#include "Assert/Assert.h"
#include "Assert/NullAsserter.h"


namespace TestSystemLua
{
  //------------------------------------------------------------------------------------------------
  TEST_MODULE_INITIALIZE(TestSystemLua_Initialize)
  {
    Celeste::Assertion::setAsserter(std::make_unique<Celeste::NullAsserter>());
  }
}