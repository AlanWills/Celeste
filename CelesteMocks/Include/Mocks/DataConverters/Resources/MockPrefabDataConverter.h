#pragma once

#include "DataConverters/Resources/PrefabDataConverter.h"


namespace CelesteMocks
{
  class MockPrefabDataConverter : public Celeste::PrefabDataConverter
  {
    public:
      MockPrefabDataConverter(const std::string& elementName) : Celeste::PrefabDataConverter(elementName) { }
  };
}