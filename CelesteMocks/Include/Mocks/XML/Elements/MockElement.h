#pragma once

#include "XML/Elements/Element.h"


namespace CelesteMocks
{
  class MockElement : public Celeste::XML::Element
  {
    public:
      MockElement(const std::string& elementName, Celeste::DeserializationRequirement required = Celeste::DeserializationRequirement::kNotRequired) :
        Celeste::XML::Element(elementName, required), 
        m_isDoConvertFromXMLCalled(false),
        m_doConvertResult(false)
      {
      }

      typedef void* type;

      Element* clone() const override { ASSERT_FAIL(); return nullptr; };

      bool isDoConvertFromXMLCalled() const { return m_isDoConvertFromXMLCalled; }
      void setDoConvertResult(bool value) { m_doConvertResult = value; }

    protected:
      bool doConvertFromXML(const tinyxml2::XMLElement* /*childElement*/) override
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