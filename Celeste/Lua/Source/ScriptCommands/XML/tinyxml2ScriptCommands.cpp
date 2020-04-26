#include "ScriptCommands/XML/tinyxml2ScriptCommands.h"
#include "sol/sol.hpp"
#include "tinyxml2.h"

#include <memory>


namespace Celeste::Lua::XML::tinyxml2ScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::unique_ptr<tinyxml2::XMLDocument> createDocument()
    {
      return std::unique_ptr<tinyxml2::XMLDocument>(new tinyxml2::XMLDocument());
    }

    //------------------------------------------------------------------------------------------------
    bool saveFile(tinyxml2::XMLDocument& document, const std::string& path)
    {
      return document.SaveFile(path.c_str()) == tinyxml2::XMLError::XML_SUCCESS;
    }

    //------------------------------------------------------------------------------------------------
    const tinyxml2::XMLAttribute* findAttribute(tinyxml2::XMLElement& element, const std::string& attributeName)
    {
      return element.FindAttribute(attributeName.c_str());
    }

    //------------------------------------------------------------------------------------------------
    void setAttributeString(tinyxml2::XMLElement& element, const std::string& attributeName, const std::string& value)
    {
      return element.SetAttribute(attributeName.c_str(), value.c_str());
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    using namespace tinyxml2;

    state.new_usertype<XMLDocument>(
      "XMLDocument",
      "new", sol::factories(&Internals::createDocument),
      "insertFirstChild", &XMLDocument::InsertFirstChild,
      "newElement", &XMLDocument::NewElement,
      "saveFile", &Internals::saveFile);

    state.new_usertype<XMLNode>("XMLNode");

    state.new_usertype<XMLElement>(
      "XMLElement",
      sol::base_classes, sol::bases<XMLNode>(),
      "findAttribute", &Internals::findAttribute,
      "setAttribute", sol::overload(&Internals::setAttributeString));

    state.new_usertype<XMLAttribute>(
      "XMLAttribute",
      "asString", &XMLAttribute::Value,
      "asFloat", &XMLAttribute::FloatValue);
  }
}