#include "DataConverters/Callbacks/CallbackDataConverter.h"


namespace Celeste
{
  const char* const CallbackDataConverter::NAME_ATTRIBUTE_NAME("name");
  const char* const CallbackDataConverter::ARG_ATTRIBUTE_NAME("arg");

  //------------------------------------------------------------------------------------------------
  CallbackDataConverter::CallbackDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_name(createReferenceAttribute<std::string>(NAME_ATTRIBUTE_NAME, "", DeserializationRequirement::kRequired)),
    m_arg(createReferenceAttribute<std::string>(ARG_ATTRIBUTE_NAME, ""))
  {
  }
}