#pragma once

#include "CelesteDllExport.h"
#include "Templates/ChooseClass.h"
#include "XML/Elements/DataElement.h"


namespace Celeste::Lua::XML::ElementScriptCommands
{
  template <class T, bool is_reference = false>
  typename choose_class<is_reference, const T&, T>::type as(Celeste::XML::Element& element)
  {
    return reinterpret_cast<typename Celeste::XML::DataElement<T, is_reference ? DataType::kReference : DataType::kValue>&>(element).getValue();
  }

  CelesteDllExport void initialize();
}