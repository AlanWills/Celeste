#pragma once

#include "DataConverters/Callbacks/CallbackDataConverter.h"


namespace CelesteTestUtils
{

class MockCallbackDataConverter : public Celeste::CallbackDataConverter
{
  public:
    MockCallbackDataConverter(const std::string& elementName) : Celeste::CallbackDataConverter(elementName) { }
};

}