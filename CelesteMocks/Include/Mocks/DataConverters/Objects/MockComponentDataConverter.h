#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "Mocks/Objects/MockComponent.h"
#include "StaticLibExport.h"


namespace CelesteMocks
{
  class MockComponentDataConverter : public Celeste::ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(MockComponentDataConverter, MockComponent, StaticLibExport)

    public:
      bool isDoConvertFromXMLCalled() const { return m_doConvertFromXMLCalled; }
      bool isDoSetValuesCalled() const { return m_doSetValuesCalled; }

    protected:
      bool doConvertFromXML(const XMLElement* /*element*/) override { m_doConvertFromXMLCalled = true; return true; }

    private:
      bool m_doConvertFromXMLCalled;
      mutable bool m_doSetValuesCalled;
  };
}