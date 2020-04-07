#include "Assert/Assert.h"
#include "Assert/DebugAsserter.h"


namespace Celeste
{
  std::unique_ptr<IAsserter> Assertion::m_asserter(new DebugAsserter());

  //------------------------------------------------------------------------------------------------
  Assertion& Assertion::instance()
  {
    static Assertion instance;
    return instance;
  }

  //------------------------------------------------------------------------------------------------
  void Assertion::setAsserter(std::unique_ptr<IAsserter>&& asserter) 
  { 
    m_asserter = std::move(asserter); 
  }

  //------------------------------------------------------------------------------------------------
  IAsserter& Assertion::getAsserter() 
  { 
    return *m_asserter; 
  }
}