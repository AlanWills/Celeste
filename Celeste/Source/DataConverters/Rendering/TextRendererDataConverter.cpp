#include "DataConverters/Rendering/TextRendererDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Rendering/TextRenderer.h"


namespace Celeste
{
  using namespace Rendering;

  REGISTER_MANAGED_COMPONENT_DATA_CONVERTER(TextRendererDataConverter)

  //------------------------------------------------------------------------------------------------
  const char* const TextRendererDataConverter::FONT_ATTRIBUTE_NAME("font");
  const char* const TextRendererDataConverter::FONT_HEIGHT_ATTRIBUTE_NAME("font_height");
  const char* const TextRendererDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME("horizontal_alignment");
  const char* const TextRendererDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME("vertical_alignment");
  const char* const TextRendererDataConverter::COLOUR_ATTRIBUTE_NAME("colour");
  const char* const TextRendererDataConverter::OPACITY_ATTRIBUTE_NAME("opacity");
  const char* const TextRendererDataConverter::TEXT_ATTRIBUTE_NAME("text");

  //------------------------------------------------------------------------------------------------
  TextRendererDataConverter::TextRendererDataConverter() :
    Inherited(Rendering::TextRenderer::type_name()),
    m_font(createReferenceAttribute<Path>(FONT_ATTRIBUTE_NAME, Path("Fonts", "Arial.ttf"))),
    m_fontHeight(createValueAttribute(FONT_HEIGHT_ATTRIBUTE_NAME, 12.0f)),
    m_horizontalAlignment(createValueAttribute(HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME, UI::HorizontalAlignment::kCentre)),
    m_verticalAlignment(createValueAttribute(VERTICAL_ALIGNMENT_ATTRIBUTE_NAME, UI::VerticalAlignment::kCentre)),
    m_colour(createReferenceAttribute(COLOUR_ATTRIBUTE_NAME, glm::vec3(1))),
    m_opacity(createValueAttribute(OPACITY_ATTRIBUTE_NAME, 1.0f)),
    m_text(createReferenceAttribute<std::string>(TEXT_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void TextRendererDataConverter::doSetValues(TextRenderer& textRenderer) const
  {
    textRenderer.setFont(getFont());
    textRenderer.setFontHeight(getFontHeight());
    textRenderer.setHorizontalAlignment(getHorizontalAlignment());
    textRenderer.setVerticalAlignment(getVerticalAlignment());
    textRenderer.setColour(getColour());
    textRenderer.setOpacity(getOpacity());
    textRenderer.setText(getParsedText());
  }

  //------------------------------------------------------------------------------------------------
  std::string TextRendererDataConverter::getParsedText() const
  {
    std::string result;

    const std::string& rawText = getRawText();
    for (size_t i = 0, n = rawText.size(); i < n; ++i)
    {
      char c = rawText[i];
      if (c != '\\' ||
          i == (n - 1) ||
          rawText[i + 1] != 'n')
      {
        // Ignore all escape backslashes for newline symbols ONLY
        result.push_back(c);
      }
      else
      {
        // Push back the newline and advance past it now
        result.push_back('\n');
        ++i;
      }
    }

    return result;
  }
}