#pragma once

#include "tinyxml2.h"

#include <string>


namespace CelesteTestUtils
{
  tinyxml2::XMLElement* createScreenElement(
    tinyxml2::XMLDocument& document);

  tinyxml2::XMLElement* createScreenElement(
    tinyxml2::XMLDocument& document,
    const std::string& name);
}