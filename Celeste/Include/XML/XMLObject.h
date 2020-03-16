#pragma once

#include "tinyxml2.h"
#include "DataConverters/Enums/ConverterEnums.h"


namespace Celeste
{
  namespace XML
  {
    class XMLObject
    {
      public:
        XMLObject(DeserializationRequirement required = DeserializationRequirement::kNotRequired) : m_deserializationRequirement(required) { }
        virtual ~XMLObject() { }

        bool isRequired() const { return m_deserializationRequirement == DeserializationRequirement::kRequired; }

      private:
        DeserializationRequirement m_deserializationRequirement;
    };
  }
}