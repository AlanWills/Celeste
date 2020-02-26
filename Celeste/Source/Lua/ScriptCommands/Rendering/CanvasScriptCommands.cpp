#include "Lua/ScriptCommands/Rendering/CanvasScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"
#include "Rendering/Canvas.h"

#include "Deserialization/ViewportDeserializers.h"

using ProjectionMode = Celeste::ProjectionMode;


namespace Celeste::Lua::Rendering::CanvasScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::string getProjectionMode(Celeste::Rendering::Canvas& renderer)
    {
      std::string output;
      serialize<ProjectionMode>(renderer.getProjectionMode(), output);

      return std::move(output);
    }

    //------------------------------------------------------------------------------------------------
    void setProjectionMode(Celeste::Rendering::Canvas& renderer, const std::string& text)
    {
      ProjectionMode projectionMode;
      if (!deserialize<ProjectionMode>(text, projectionMode))
      {
        ASSERT_FAIL();
        return;
      }

      renderer.setProjectionMode(projectionMode);
    }

    //------------------------------------------------------------------------------------------------
    void setDimensions_SingleVec2(Celeste::Rendering::Canvas& renderer, const glm::vec2& dimensions)
    {
      renderer.setDimensions(dimensions);
    }

    //------------------------------------------------------------------------------------------------
    void setDimensions_TwoFloats(Celeste::Rendering::Canvas& renderer, float xDimensions, float yDimensions)
    {
      renderer.setDimensions(xDimensions, yDimensions);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using Canvas = Celeste::Rendering::Canvas;

    registerUserType<Canvas>(
      "Canvas",
      sol::base_classes, sol::bases<Component, Entity, Object>(),
      "allocate", sol::factories(&Canvas::allocate),
      "getProjectionMode", &Internals::getProjectionMode,
      "setProjectionMode", &Internals::setProjectionMode,
      "getDimensions", &Canvas::getDimensions,
      "setDimensions", sol::overload(&Internals::setDimensions_SingleVec2, &Internals::setDimensions_TwoFloats));
  }
}