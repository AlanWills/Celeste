#pragma once

#include "StaticLibExport.h"
#include "Objects/ScriptableObject.h"


namespace CelesteMocks
{
  class MockScriptableObject : public Celeste::ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(MockScriptableObject, StaticLibExport)

    public:
      template <typename T>
      Celeste::ValueField<T>& createValueField_Public(const std::string& fieldName, T defaultValue = T()) { return createValueField(fieldName, defaultValue); }

      template <typename T>
      Celeste::ReferenceField<T>& createReferenceField_Public(const std::string& fieldName, const T& defaultValue = T()) { return createReferenceField(fieldName, defaultValue); }

      template <typename T>
      T& createScriptableObject_Public(const std::string& name) { return createScriptableObject<T>(name); }

      size_t getFieldsSize_Public() const { return getFieldsSize(); }
      size_t getScriptableObjectsSize_Public() const { return getScriptableObjectsSize(); }
  };
}