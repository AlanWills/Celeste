#include "DataConverters/Objects/ScriptableObjectDataConverter.h"
#include "Registries/ScriptableObjectRegistry.h"


namespace Celeste
{
  const char* const ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME = "path";

  //------------------------------------------------------------------------------------------------
  ScriptableObjectDataConverter::ScriptableObjectDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_path(createReferenceAttribute<std::string>(PATH_ATTRIBUTE_NAME, "", DeserializationRequirement::kRequired))
  {
  }
}