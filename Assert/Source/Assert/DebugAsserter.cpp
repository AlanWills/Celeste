#include "Assert/DebugAsserter.h"

#include <assert.h>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  void DebugAsserter::check(bool condition) const
  {
    if (!condition)
    {
      __debugbreak();
    }
  }
}