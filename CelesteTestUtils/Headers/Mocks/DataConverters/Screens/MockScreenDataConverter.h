#include "DataConverters/Screens/ScreenDataConverter.h"


namespace CelesteTestUtils
{
  class MockScreenDataConverter : public Celeste::ScreenDataConverter
  {
    public:
      MockScreenDataConverter(const std::string& elementName) : Celeste::ScreenDataConverter(elementName) { }
  };
}