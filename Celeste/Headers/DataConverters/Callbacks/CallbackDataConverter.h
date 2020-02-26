#pragma once

#include "DataConverters/DataConverter.h"
#include "XML/Attributes/DataAttribute.h"


namespace Celeste
{
  class CallbackDataConverter : public DataConverter
  {
    public:
      CelesteDllExport CallbackDataConverter(const std::string& elementName);

      inline const std::string& getName() const { return m_name.getValue(); }
      inline const std::string& getArg() const { return m_arg.getValue(); }

      CelesteDllExport static const char* const NAME_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const ARG_ATTRIBUTE_NAME;

    protected:
      inline bool doConvertFromXML(const XMLElement* callbackElement) { return true; }

    private:
      using Inherited = DataConverter;

      XML::ReferenceAttribute<std::string>& m_name;
      XML::ReferenceAttribute<std::string>& m_arg;
  };
}