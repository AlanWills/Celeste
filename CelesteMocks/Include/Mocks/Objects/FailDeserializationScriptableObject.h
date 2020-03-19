#pragma once

#include "Mocks/Objects/MockScriptableObject.h"


namespace CelesteMocks
{

class FailDeserializationScriptableObject : public MockScriptableObject
{
  public:
    static std::string type_name() { return "FailDeserializationScriptableObject"; }

    bool doDeserialize(const tinyxml2::XMLElement* /*element*/) override { return false; }
};

}