#pragma once

#include "DataConverters/Objects/EntityDataConverter.h"
#include "Mocks/Objects/MockEntity.h"


namespace CelesteMocks
{
  class MockEntityDataConverter : public Celeste::EntityDataConverter<MockEntity>
  {
    public:
      MockEntityDataConverter(const std::string& elementName) :
        Celeste::EntityDataConverter<MockEntity>(elementName),
        m_doConvertFromXMLCalled(false),
        m_doSetValuesCalled(false)
      {
      }

      bool isDoConvertFromXMLCalled() const { return m_doConvertFromXMLCalled; }
      bool isDoSetValuesCalled() const { return m_doSetValuesCalled; }

    protected:
      bool doConvertFromXML(const XMLElement* /*element*/) override { m_doConvertFromXMLCalled = true; return true; }
      void doSetValues(MockEntity& entity) const override { Inherited::doSetValues(entity); m_doSetValuesCalled = true; }

    private:
      using Inherited = Celeste::EntityDataConverter<MockEntity>;

      bool m_doConvertFromXMLCalled;
      mutable bool m_doSetValuesCalled;
  };
}