#include "Lua/ScriptCommands/XML/AttributeScriptCommands.h"
#include "Lua/LuaState.h"

// DON'T delete these
#include "Deserialization/MathsDeserializers.h"
#include "Bindings/MathsDataBindingGenerators.h"


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::XML::Attribute> : std::false_type {};
}

namespace Celeste::Lua::XML::AttributeScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    sol::state& state = Lua::LuaState::instance();

    using Attribute = Celeste::XML::Attribute;

    state.new_usertype<Attribute>(
      "Attribute",
      sol::base_classes, sol::bases<Celeste::XML::XMLObject>(),
      "isBool", &is<bool>,
      "asBool", &as<bool>,
      "isFloat", &is<float>,
      "asFloat", &as<float>,
      "isString", &is<std::string>,
      "asString", &as<std::string>,
      "isVec2", &is<glm::vec2>,
      "asVec2", &as<glm::vec2, true>,
      "isUVec2", &is<glm::uvec2>,
      "asUVec2", &as<glm::uvec2, true>);
  }
}