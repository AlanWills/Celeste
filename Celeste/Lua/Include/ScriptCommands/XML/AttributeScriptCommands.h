#pragma once

#include "Templates/ChooseClass.h"
#include "XML/Attributes/DataAttribute.h"


namespace sol
{
  class state;
}

namespace Celeste::Lua::XML::AttributeScriptCommands
{
  template <class T>
  bool is(Celeste::XML::Attribute& attribute)
  {
    return dynamic_cast<Celeste::XML::ValueAttribute<T>*>(&attribute) != nullptr ||
      dynamic_cast<Celeste::XML::ReferenceAttribute<T>*>(&attribute) != nullptr;
  }

  template <class T, bool is_reference = false>
  typename choose_class<is_reference, const T&, T>::type as(Celeste::XML::Attribute& attribute)
  {
    return reinterpret_cast<typename Celeste::XML::DataAttribute<T, is_reference>&>(attribute).getValue();
  }

  void initialize(sol::state& state);
}