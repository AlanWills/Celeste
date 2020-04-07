#include "Maths/MathsEnums.h"
#include "Assert/Assert.h"

#include <string>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <>
  std::string to_string(Maths::Space space)
  {
    if (space == Maths::Space::kLocal)
    {
      return "Local";
    }
    else if (space == Maths::Space::kWorld)
    {
      return "World";
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }
}