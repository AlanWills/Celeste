#include "Lua/ScriptCommands/Maths/VectorScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"


namespace Celeste::Lua::Maths::VectorScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = Lua::LuaState::instance();

    // uvec2
    state.new_usertype<glm::uvec2>(
      "uvec2",
      sol::constructors<
      glm::uvec2(),
      glm::uvec2(glm::uint),
      glm::uvec2(glm::uint, glm::uint),
      glm::uvec2(glm::uvec2),
      glm::uvec2(const glm::uvec2&)>(),
      "x", sol::property(&glm::uvec2::x, &glm::uvec2::x),
      "y", sol::property(&glm::uvec2::y, &glm::uvec2::y),
      sol::meta_function::addition, &addition<glm::uvec2, true>,
      sol::meta_function::subtraction, &subtraction<glm::uvec2, true>,
      sol::meta_function::multiplication, &multiplication<glm::uvec2, true>,
      sol::meta_function::division, &division<glm::uvec2, true>);

    // vec2
    state.new_usertype<glm::vec2>(
      "vec2",
      sol::constructors<
      glm::vec2(),
      glm::vec2(float),
      glm::vec2(float, float),
      glm::vec2(glm::vec2),
      glm::vec2(const glm::vec2&)>(),
      "x", sol::property(&glm::vec2::x, &glm::vec2::x),
      "y", sol::property(&glm::vec2::y, &glm::vec2::y),
      sol::meta_function::addition, &addition<glm::vec2, true>,
      sol::meta_function::subtraction, &subtraction<glm::vec2, true>,
      sol::meta_function::multiplication, &multiplication<glm::vec2, true>,
      sol::meta_function::division, &division<glm::vec2, true>);
  }
}