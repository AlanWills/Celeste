#pragma once

#include "CelesteDllExport.h"
#include "Fields/DataField.h"
#include "tinyxml2.h"
#include "UID/Guid.hpp"
#include "Resources/ResourceUtils.h"
#include "Resources/ResourceManager.h"
#include "Reflection/Type.h"
#include "Bindings/BindingUtils.h"
#include "XML/ChildXMLElementWalker.h"
#include "UtilityMacros/ScriptableObjectMacros.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>


namespace Celeste
{
  namespace Bindings
  {
    class BindingsGenerator;
  }

  class ScriptableObject
  {
    public:
      virtual ~ScriptableObject() = default;
      ScriptableObject(const ScriptableObject&) = delete;
      ScriptableObject& operator=(const ScriptableObject&) = delete;

      void setName(const std::string& name) { m_name = name; }
      const std::string& getName() const { return m_name; }

      const Celeste::Guid& getGuid() const { return m_guid; }

      template <typename T>
      static std::unique_ptr<T> create(const std::string& name);
      CelesteDllExport static std::unique_ptr<ScriptableObject> create(const std::string& typeName, const std::string& name);

      /// Attempts to load an instance of the inputted scriptable object from a file.
      /// This will return null if the scriptable object could not be deserialized
      template <typename T>
      static std::unique_ptr<T> load(const Path& pathToFile);
      CelesteDllExport static std::unique_ptr<ScriptableObject> load(const Path& pathToFile);
    
      CelesteDllExport void save(const Path& pathToFile) const;

    protected:
      CelesteDllExport ScriptableObject();

      virtual bool doDeserialize(const tinyxml2::XMLElement* element) { return true; }
      virtual void doSerialize(tinyxml2::XMLElement* element) const { }

      template <typename T>
      T& createField(const std::string& fieldName);

      template <typename T>
      ValueField<T>& createValueField(const std::string& fieldName, T defaultValue = T()) { return createDataFieldImpl<T, false>(fieldName, defaultValue); }

      template <typename T>
      ReferenceField<T>& createReferenceField(const std::string& fieldName, const T& defaultValue = T()) { return createDataFieldImpl<T, true>(fieldName, defaultValue); }

      template <typename T>
      T& createScriptableObject(const std::string& name);

      size_t getFieldsSize() const { return m_fields.size(); }
      size_t getScriptableObjectsSize() const { return m_scriptableObjects.size(); }

  #if _DEBUG
      virtual void generateBinding(std::string& output) const = 0;
  #endif

  #if _DEBUG
      /// DEBUG ONLY!  Do not use in release code - should be for tool code only
      virtual void type_info_i(std::unique_ptr<Reflection::ITypeInfo>& output) const = 0;
  #endif

    private:
      using ElementInformation = std::string;
      using ElementLookup = std::unordered_map<ElementInformation, const tinyxml2::XMLElement*>;

      CelesteDllExport bool deserialize(const tinyxml2::XMLElement* element);
      void serialize(tinyxml2::XMLElement* element) const;

      template <typename T, bool is_reference>
      DataField<T, is_reference>& createDataFieldImpl(const std::string& fieldName, typename DataField<T, is_reference>::field_type defaultValue);

      std::vector<std::unique_ptr<Field>> m_fields;
      std::vector<std::unique_ptr<ScriptableObject>> m_scriptableObjects;

      std::string m_name;
      Celeste::Guid m_guid;

      // Need this to allow bindings generator to access all members
      friend class Bindings::BindingsGenerator;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  std::unique_ptr<T> ScriptableObject::create(const std::string& name)
  {
    std::unique_ptr<T> object = std::unique_ptr<T>(new T());
    object->setName(name);
    return std::move(object);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  std::unique_ptr<T> ScriptableObject::load(const Path& pathToFile)
  {
    observer_ptr<Resources::Data> data = Resources::getResourceManager().load<Resources::Data>(pathToFile);
    if (data == nullptr)
    {
      return std::unique_ptr<T>();
    }

    // Interestingly, this will return false if a value for the scriptable object was specified but no matching data element could be found,
    // but will not if it wasn't.  It's possible we may want to review this behaviour, but to me at the moment
    // it sort of makes sense.  No value = default, value but no data = error.  We may want to change it so that it doesn't error if no data could be found
    // and just fall back on the default value, but I'm not sure.
    std::unique_ptr<T> t(new T());
    if (!t->deserialize(data->getDocumentRoot()))
    {
      ASSERT_FAIL();
      return std::unique_ptr<T>();
    }

    return std::move(t);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T& ScriptableObject::createField(const std::string& name)
  {
    m_fields.emplace_back(new T(name));
    return static_cast<T&>(*(m_fields.back()));
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, bool is_reference>
  DataField<T, is_reference>& ScriptableObject::createDataFieldImpl(const std::string& fieldName, typename DataField<T, is_reference>::field_type defaultValue)
  {
    m_fields.emplace_back(new DataField<T, is_reference>(fieldName, defaultValue));
    return static_cast<DataField<T, is_reference>&>(*(m_fields.back()));
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T& ScriptableObject::createScriptableObject(const std::string& name)
  {
    m_scriptableObjects.emplace_back(ScriptableObject::create<T>(name));
    return static_cast<T&>(*(m_scriptableObjects.back()));
  }
}

//------------------------------------------------------------------------------------------------
namespace std
{
  template <> struct hash<std::pair<std::string, std::string>>
  {
    size_t operator()(const std::pair<std::string, std::string>& x) const
    {
      std::hash<std::string> hash_fn;
      return hash_fn(x.first) + hash_fn(x.second);
    }
  };
}
