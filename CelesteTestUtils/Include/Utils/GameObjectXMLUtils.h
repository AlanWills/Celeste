#pragma once

#include "tinyxml2.h"

#include <string>


namespace CelesteTestUtils
{
  tinyxml2::XMLElement* createGameObjectsElement(
    tinyxml2::XMLDocument& document);

  tinyxml2::XMLElement* createGameObjectsElement(
    tinyxml2::XMLDocument& document,
    tinyxml2::XMLElement* parent);

  tinyxml2::XMLElement* createGameObjectElement(
    tinyxml2::XMLDocument& document);

  tinyxml2::XMLElement* createGameObjectElement(
    tinyxml2::XMLDocument& document, 
    const std::string& name);

  tinyxml2::XMLElement* createGameObjectElement(
    tinyxml2::XMLDocument& document, 
    tinyxml2::XMLElement* parent);

  tinyxml2::XMLElement* createGameObjectElement(
    tinyxml2::XMLDocument& document,
    const std::string& name,
    tinyxml2::XMLElement* parent);

  tinyxml2::XMLElement* createPrefabElement(
    tinyxml2::XMLDocument& document);

  tinyxml2::XMLElement* createPrefabElement(
    tinyxml2::XMLDocument& document,
    const std::string& name);

  tinyxml2::XMLElement* createPrefabElement(
    tinyxml2::XMLDocument& document,
    tinyxml2::XMLElement* parent);

  tinyxml2::XMLElement* createPrefabElement(
    tinyxml2::XMLDocument& document,
    const std::string& name,
    tinyxml2::XMLElement* parent);
}