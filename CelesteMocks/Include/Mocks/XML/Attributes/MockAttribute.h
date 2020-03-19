#pragma once

#include "XML/Attributes/Attribute.h"


namespace CelesteMocks
{
  class MockAttribute : public Celeste::XML::Attribute
  {
    public:
      MockAttribute(const std::string& attributeName, Celeste::DeserializationRequirement required = Celeste::DeserializationRequirement::kNotRequired) :
        Attribute(attributeName, required), 
        m_isDoConvertFromXMLCalled(false),
        m_doConvertResult(true)
      {
      }

      Attribute* clone() const override { ASSERT_FAIL(); return nullptr; };

      bool isDoConvertFromXMLCalled() const { return m_isDoConvertFromXMLCalled; }
      void setDoConvertResult(bool value) { m_doConvertResult = value; }

    protected:
      bool doConvertFromXML(const std::string& /*attributeText*/) override
      {
        m_isDoConvertFromXMLCalled = true;
        return m_doConvertResult;
      }

  #if _DEBUG
      void generateBinding(std::string& /*output*/) const override { }
  #endif

    private:
      bool m_isDoConvertFromXMLCalled;
      bool m_doConvertResult;
  };
}