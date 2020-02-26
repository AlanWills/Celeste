#include "Utils/XMLUtils.h"
#include "Utils/ScreenXMLUtils.h"
#include "DataConverters/Screens/ScreenDataConverter.h"
#include "Screens/Screen.h"


namespace CelesteTestUtils
{
  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createScreenElement(tinyxml2::XMLDocument& document)
  {
    return createElement(document, Celeste::ScreenDataConverter::SCREEN_ELEMENT_NAME);
  }

  //------------------------------------------------------------------------------------------------
  tinyxml2::XMLElement* createScreenElement(tinyxml2::XMLDocument& document, const std::string& name)
  {
    tinyxml2::XMLElement* screenElement = createScreenElement(document);
    screenElement->SetAttribute(Celeste::ScreenDataConverter::NAME_ATTRIBUTE_NAME, name.c_str());

    return screenElement;
  }
}