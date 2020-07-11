#pragma once

#include "Fields/Field.h"


namespace CelesteMocks
{
  class MockField : public Celeste::Field
  {
    public :
      MockField(const std::string& name) : 
        Field(name), 
        m_doDeserializeCalled(false),
        m_doSerializeCalled(false),
        m_doDeserializeResult(true)
      { 
      }

      bool doDeserialize(const tinyxml2::XMLElement* /*element*/) override
      { 
        m_doDeserializeCalled = true;
        return m_doDeserializeResult; 
      }

      void doSerialize(tinyxml2::XMLElement* /*element*/) const 
      { 
        const_cast<MockField*>(this)->m_doSerializeCalled = true;
      };

      bool isDoDeserializeCalled() const { return m_doDeserializeCalled; }
      bool isDoSerializeCalled() const { return m_doSerializeCalled; }

      bool getDoDeserializeResult() const { return m_doDeserializeResult; }
      void setDoDeserializeResult(bool doDeserializeResult) { m_doDeserializeResult = doDeserializeResult; }

    private:
      bool m_doDeserializeCalled;
      bool m_doSerializeCalled;
      bool m_doDeserializeResult;
  };
}