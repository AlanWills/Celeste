#pragma once

#include "tinyxml2.h"

#include <string>


namespace CelesteTestUtils
{
  tinyxml2::XMLElement* createElement(
    tinyxml2::XMLDocument& document,
    const std::string& elementName);

  tinyxml2::XMLElement* createElement(
    tinyxml2::XMLDocument& document,
    const std::string& elementName,
    tinyxml2::XMLElement* parent);
}