#include "Deserialization/ViewportDeserializers.h"
#include "Assert/Assert.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template<>
  bool deserialize<ProjectionMode>(const std::string& text, ProjectionMode& output)
  {
    if (text == "Orthographic")
    {
      output = ProjectionMode::kOrthographic;
      return true;
    }
    else if (text == "Perspective")
    {
      output = ProjectionMode::kPerspective;
      return true;
    }

    ASSERT_FAIL();
    return false;
  }
}