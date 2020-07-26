#pragma once

#include "Resources/Fonts/FontInstance.h"
#include "Renderer.h"
#include "UI/LayoutEnums.h"
#include "FileSystem/Path.h"


namespace Celeste::Rendering
{
  // A class which is responsible for rendering text in a specific font
  class TextRenderer : public Renderer
  {
    DECLARE_UNMANAGED_COMPONENT(TextRenderer, CelesteDllExport)

    public:
      CelesteDllExport void render(const Resources::Program& shaderProgram, const glm::mat4& viewModelMatrix) const override;

      /// Loads a font from the resource manager and sets it to be the font this renderer uses
      CelesteDllExport void setFont(const std::string& relativePathToFont, float height = 12);
      void setFont(const char* relativePathToFont, float height = 12) { setFont(std::string(relativePathToFont), height); }
      void setFont(const Path& relativePathToFont, float height = 12) { setFont(relativePathToFont.as_string(), height); }

      inline const Resources::FontInstance* getFontInstance() const { return m_fontInstance.get(); }

      CelesteDllExport void setFontHeight(float height);
      inline float getFontHeight() const { return m_fontInstance->getHeight(); }

      inline glm::vec2 getDimensions() const override { return m_dimensions; }

      const std::string& getText() const { return m_text; }
      CelesteDllExport void setText(const std::string& text);

      CelesteDllExport void setHorizontalWrapMode(UI::HorizontalWrapMode horizontalWrapMode);
      inline UI::HorizontalWrapMode getHorizontalWrapMode() const { return m_horizontalWrapMode; }

      inline void setHorizontalAlignment(UI::HorizontalAlignment horizontalAlignment) { m_horizontalAlignment = horizontalAlignment; }
      inline UI::HorizontalAlignment getHorizontalAlignment() const { return m_horizontalAlignment; }

      inline void setVerticalAlignment(UI::VerticalAlignment verticalAlignment) { m_verticalAlignment = verticalAlignment; }
      inline UI::VerticalAlignment getVerticalAlignment() const { return m_verticalAlignment; }

      CelesteDllExport void setMaxWidth(float maxWidth);
      inline float getMaxWidth() const { return m_maxWidth; }

    protected:
      inline float getXPosition(float halfLineWidth) const { return -static_cast<int>(m_horizontalAlignment)* halfLineWidth; }
      inline float getYPosition(float halfMaxHeight) const { return (2 - static_cast<int>(m_verticalAlignment))* halfMaxHeight; }

    private:
      using Inherited = Renderer;

      void layoutText();
      void recalculateDimensions();

      std::unique_ptr<Resources::FontInstance> m_fontInstance;

      UI::HorizontalWrapMode m_horizontalWrapMode = UI::HorizontalWrapMode::kOverflow;
      UI::HorizontalAlignment m_horizontalAlignment = UI::HorizontalAlignment::kCentre;
      UI::VerticalAlignment m_verticalAlignment = UI::VerticalAlignment::kCentre;

      float m_maxWidth = 0;
      glm::vec2 m_dimensions;
      std::string m_text;
  };
}