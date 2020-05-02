#include "TestUtils/Utils/XMLUtils.h"


namespace CelesteTestUtils
{
  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createElement(tinyxml2::XMLDocument& document, const std::string& elementName)
  {
    tinyxml2::XMLElement* element = document.NewElement(elementName.c_str());
    document.InsertEndChild(element);

    return element;
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createElement(
    tinyxml2::XMLDocument& document,
    const std::string& elementName,
    tinyxml2::XMLElement* parent)
  {
    tinyxml2::XMLElement* element = document.NewElement(elementName.c_str());
    parent->InsertEndChild(element);

    return element;
  }
}