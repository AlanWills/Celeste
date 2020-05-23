#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "XML/Attributes/DataAttribute.h"
#include "XML/Elements/ListElement.h"
#include "Deserialization/MathsDeserializers.h"
#include "Deserialization/UIDeserializers.h"
#include "Bindings/MathsDataBindingGenerators.h"
#include "Bindings/UIDataBindingGenerators.h"


namespace Celeste::Rendering
{
  class TextRenderer;
}

namespace Celeste
{
  class TextRendererDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(TextRendererDataConverter, Rendering::TextRenderer, CelesteDllExport)

    public:
      inline const Path& getFont() const { return m_font.getValue(); }
      inline float getFontHeight() const { return m_fontHeight.getValue(); }
      inline float getMaxWidth() const { return m_maxWidth.getValue(); }
      inline UI::HorizontalWrapMode getHorizontalWrapMode() const { return m_horizontalWrapMode.getValue(); }
      inline UI::HorizontalAlignment getHorizontalAlignment() const { return m_horizontalAlignment.getValue(); }
      inline UI::VerticalAlignment getVerticalAlignment() const { return m_verticalAlignment.getValue(); }
      inline const glm::vec3& getColour() const { return m_colour.getValue(); }
      inline float getOpacity() const { return m_opacity.getValue(); }
      inline const std::string& getRawText() const { return m_text.getValue(); }
      
      CelesteDllExport std::string getParsedText() const;

      CelesteDllExport static const char* const FONT_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const FONT_HEIGHT_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const MAX_WIDTH_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const HORIZONTAL_WRAP_MODE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const VERTICAL_ALIGNMENT_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const COLOUR_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const OPACITY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const TEXT_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ReferenceAttribute<Path>& m_font;
      XML::ValueAttribute<float>& m_fontHeight;
      XML::ValueAttribute<float>& m_maxWidth;
      XML::ValueAttribute<UI::HorizontalWrapMode>& m_horizontalWrapMode;
      XML::ValueAttribute<UI::HorizontalAlignment>& m_horizontalAlignment;
      XML::ValueAttribute<UI::VerticalAlignment>& m_verticalAlignment;
      XML::ReferenceAttribute<glm::vec3>& m_colour;
      XML::ValueAttribute<float>& m_opacity;
      XML::ReferenceAttribute<std::string>& m_text;
  };
}