#pragma once

#include "DataConverters/Rendering/TextRendererDataConverter.h"


namespace CelesteTestUtils
{
  class MockTextRendererDataConverter : public Celeste::TextRendererDataConverter
  {
    public:
      MockTextRendererDataConverter() = default;

      void setRawText(const std::string& rawText)
      {
        const_cast<std::string&>(getRawText()).assign(rawText);
      }
  };
}