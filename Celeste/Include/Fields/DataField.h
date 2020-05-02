#pragma once

#include "Fields/Field.h"
#include "Deserialization/Deserializers.h"
#include "Serialization/Serializers.h"
#include "Templates/ChooseClass.h"
#include "Bindings/DataBindingGenerators.h"


namespace Celeste
{
  template <typename T, bool is_reference>
  class DataField : public Field
  {
    public:
      ~DataField() = default;

      using field_type = typename choose_class<is_reference, const T&, T>::type;

      typename field_type getValue() const { return m_value; }
      void setValue(typename field_type value) { m_value = value; }

    protected:
      DataField(const std::string& fieldName, field_type defaultValue = T()) :
        Field(fieldName),
        m_value(defaultValue)
      {
      }
      DataField(const DataField<T, is_reference>&) = default;
      DataField<T, is_reference>& operator=(const DataField<T, is_reference>&) = default;

      bool doDeserialize(const tinyxml2::XMLElement* element) override;
      void doSerialize(tinyxml2::XMLElement* element) const override;

  #if _DEBUG
      void generateBinding(std::string& output) const override;
  #endif

    private:
      T m_value;

      friend class ScriptableObject;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T, bool is_reference>
  bool DataField<T, is_reference>::doDeserialize(const tinyxml2::XMLElement* element)
  {
    const tinyxml2::XMLAttribute* attribute = element->FindAttribute(getName().c_str());
    if (attribute == nullptr)
    {
      ASSERT_FAIL();
      return false;
    }

    return Celeste::deserialize<T>(attribute->Value(), m_value);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, bool is_reference>
  void DataField<T, is_reference>::doSerialize(tinyxml2::XMLElement* element) const
  {
    std::string output;
    Celeste::serialize<typename choose_class<is_reference, const T&, T>::type>(m_value, output);
    element->SetAttribute(getName().c_str(), output.c_str());
  }

  #if _DEBUG
  //------------------------------------------------------------------------------------------------
  template <typename T, bool is_reference>
  void DataField<T, is_reference>::generateBinding(std::string& output) const
  {
    Bindings::DataBindingGenerator<T, is_reference>::generateBinding(getName(), getValue(), output);
  }
  #endif

  //------------------------------------------------------------------------------------------------
  // Alias templates for shorthand
  //------------------------------------------------------------------------------------------------
  template <typename T>
  using ValueField = DataField<T, false>;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  using ReferenceField = DataField<T, true>;
}