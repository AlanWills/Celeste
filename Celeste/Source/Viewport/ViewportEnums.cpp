#include "Viewport/ViewportEnums.h"
#include "Debug/Assert.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  std::string to_string(ProjectionMode projectionMode)
  {
    if (projectionMode == ProjectionMode::kOrthographic)
    {
      return "Orthographic";
    }
    else if (projectionMode == ProjectionMode::kPerspective)
    {
      return "Perspective";
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }
}