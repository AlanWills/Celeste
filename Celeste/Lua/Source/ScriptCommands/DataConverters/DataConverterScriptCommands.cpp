#include "ScriptCommands/DataConverters/DataConverterScriptCommands.h"
#include "ScriptCommands/DataConverters/Objects/ComponentDataConverterScriptCommands.h"
#include "ScriptCommands/DataConverters/LuaComponentDataConverterScriptCommands.h"

#include "DataConverters/DataConverter.h"
#include "Lua/LuaState.h"

using DataConverter = Celeste::DataConverter;


namespace sol
{
  template <>
  struct is_to_stringable<Celeste::DataConverter> : std::false_type {};
}

namespace Celeste::Lua::DataConverters::ScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    observer_ptr<const XML::Attribute> findAttribute(const DataConverter& dataConverter, const std::string& name)
    {
      return dataConverter.findAttribute(name);
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<const XML::Element> findElement(const DataConverter& dataConverter, const std::string& name)
    {
      return dataConverter.findElement(name);
    }

    //------------------------------------------------------------------------------------------------
    bool convertFromXML_StringOverload(DataConverter& dataConverter, const std::string& fullFilePath)
    {
      return dataConverter.convertFromXML(fullFilePath);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    state.new_usertype<DataConverter>(
      "DataConverter",
      "findAttribute", &Internals::findAttribute,
      "findElement", &Internals::findElement,
      "convertFromXML", sol::overload(&Internals::convertFromXML_StringOverload));

    Objects::ComponentDataConverterScriptCommands::initialize(state);
    LuaComponentDataConverterScriptCommands::initialize(state);

    // Initialize the lua data converter scripts
    LuaState::requireModule("DataConverters.DataConverters");
  }
}