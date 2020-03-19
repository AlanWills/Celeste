#pragma once

#include "DataConverters/Objects/ObjectDataConverter.h"
#include "Mocks/Objects/MockObject.h"


namespace CelesteMocks
{
  class MockObjectDataConverter : public Celeste::ObjectDataConverter<MockObject>
  {
    public:
      MockObjectDataConverter(const std::string& elementName) : 
        Celeste::ObjectDataConverter<MockObject>(elementName),
        m_doConvertFromXMLCalled(false), 
        m_doSetValuesCalled(false) 
      { 
      }

      bool isDoConvertFromXMLCalled() const { return m_doConvertFromXMLCalled; }
      bool isDoSetValuesCalled() const { return m_doSetValuesCalled; }

    protected:
      bool doConvertFromXML(const XMLElement* /*element*/) override { m_doConvertFromXMLCalled = true; return true; }
      void doSetValues(MockObject& object) const override { Inherited::doSetValues(object); m_doSetValuesCalled = true; }

    private:
      using Inherited = Celeste::ObjectDataConverter<MockObject>;

      bool m_doConvertFromXMLCalled;
      mutable bool m_doSetValuesCalled;
  };
}