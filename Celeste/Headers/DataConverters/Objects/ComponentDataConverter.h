#pragma once

#include "DataConverters/Objects/EntityDataConverter.h"
#include "UtilityMacros/ComponentDataConverterMacros.h"
#include "Objects/Component.h"


namespace Celeste
{
  class ComponentDataConverter : public EntityDataConverter<Component>
  {
    private:
      using Inherited = EntityDataConverter<Component>;

    public:
      ComponentDataConverter(const std::string& elementName) : Inherited(elementName) { }
      ComponentDataConverter(const ComponentDataConverter& rhs) : Inherited(rhs) { }
      ComponentDataConverter(ComponentDataConverter&& rhs) noexcept : Inherited(std::move(rhs)) { }
      ComponentDataConverter& operator=(const ComponentDataConverter& rhs) 
      { 
        Inherited::operator=(rhs);
        return *this;
      }

      virtual void instantiate(std::unique_ptr<ComponentDataConverter>& output) 
      { 
        output.reset(new ComponentDataConverter(getElementName()));
      }
  };
}