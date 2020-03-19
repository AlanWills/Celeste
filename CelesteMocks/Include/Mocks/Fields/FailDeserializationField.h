#pragma once

#include "Mocks/Fields/MockField.h"


namespace CelesteTestUtils
{

class FailDeserializationField : public MockField
{
  public:
    FailDeserializationField(const std::string& name) : MockField(name) { }
    
    bool doDeserialize(const tinyxml2::XMLElement* element) override { return false; }

    void doSerialize(tinyxml2::XMLElement* element) const { }
};

}