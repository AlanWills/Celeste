#include "Mocks/DataConverters/Objects/MockComponentDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"


namespace CelesteTestUtils
{
  REGISTER_MANAGED_COMPONENT_DATA_CONVERTER(MockComponentDataConverter)

  //------------------------------------------------------------------------------------------------
  MockComponentDataConverter::MockComponentDataConverter() :
    Celeste::ComponentDataConverter(MockComponent::type_name()),
    m_doConvertFromXMLCalled(false),
    m_doSetValuesCalled(false)
  {

  }

  //------------------------------------------------------------------------------------------------
  void MockComponentDataConverter::doSetValues(MockComponent& component) const
  { 
    m_doSetValuesCalled = true; 
  }
}