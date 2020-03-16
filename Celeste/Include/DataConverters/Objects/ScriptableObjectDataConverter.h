#pragma once

#include "DataConverters/DataConverter.h"


namespace Celeste
{
  class ScriptableObject;

  class ScriptableObjectDataConverter : public Celeste::DataConverter
  {
    public:
      CelesteDllExport ScriptableObjectDataConverter(const std::string& elementName);

      const std::string& getPath() const { return m_path.getValue(); }

      template <typename T>
      std::unique_ptr<T> instantiate() const;

      CelesteDllExport static const char* const PATH_ATTRIBUTE_NAME;

    private:
      using Inherited = Celeste::DataConverter;

      Celeste::XML::ReferenceAttribute<std::string>& m_path;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  std::unique_ptr<T> ScriptableObjectDataConverter::instantiate() const
  {
    auto scriptableObject = Celeste::ScriptableObject::load(getPath());
    return std::unique_ptr<T>(static_cast<T*>(scriptableObject.release()));
  }
}