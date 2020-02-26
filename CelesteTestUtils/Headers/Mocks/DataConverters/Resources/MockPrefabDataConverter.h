#pragma once

#include "DataConverters/Resources/PrefabDataConverter.h"


namespace CelesteTestUtils
{
  class MockPrefabDataConverter : public Celeste::PrefabDataConverter
  {
    public:
      MockPrefabDataConverter(const std::string& elementName) : Celeste::PrefabDataConverter(elementName) { }
  };
}