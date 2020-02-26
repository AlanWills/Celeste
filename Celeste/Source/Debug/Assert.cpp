#include "Debug/Assert.h"
#include "Debug/Asserting/DebugAsserter.h"


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
  void Assertion::setAsserter(IAsserter* asserter) 
  { 
    m_asserter.reset(asserter); 
  }

  //------------------------------------------------------------------------------------------------
  IAsserter* Assertion::getAsserter() 
  { 
    return m_asserter.get(); 
  }
}