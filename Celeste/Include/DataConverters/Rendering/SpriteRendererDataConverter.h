#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "Deserialization/MathsDeserializers.h"


namespace Celeste::Rendering
{
  class SpriteRenderer;
}

namespace Celeste
{
  class SpriteRendererDataConverter : public ComponentDataConverter
  {
    DECLARE_MANAGED_COMPONENT_DATA_CONVERTER(SpriteRendererDataConverter, Rendering::SpriteRenderer, CelesteDllExport)

    public:
      inline const Path& getSprite() const { return m_sprite.getValue(); }
      inline const glm::vec2& getSize() const { return m_size.getValue(); }
      inline const glm::vec3& getColour() const { return m_colour.getValue(); }
      inline float getOpacity() const { return m_opacity.getValue(); }
      inline bool getPreserveAspectRatio() const { return m_preserveAspectRatio.getValue(); }
      inline const glm::vec2& getScissorRectangleDimensions() const { return m_scissorRectangleDimensions.getValue(); }
      inline const glm::vec2& getScissorRectangleCentre() const { return m_scissorRectangleCentre.getValue(); }

      CelesteDllExport static const char* const SPRITE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const SIZE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const COLOUR_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const OPACITY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const PRESERVE_ASPECT_RATIO_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const SCISSOR_RECTANGLE_DIMENSIONS_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const SCISSOR_RECTANGLE_CENTRE_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ReferenceAttribute<Path>& m_sprite;
      XML::ReferenceAttribute<glm::vec2>& m_size;
      XML::ReferenceAttribute<glm::vec3>& m_colour;
      XML::ValueAttribute<float>& m_opacity;
      XML::ValueAttribute<bool>& m_preserveAspectRatio;
      XML::ReferenceAttribute<glm::vec2>& m_scissorRectangleDimensions;
      XML::ReferenceAttribute<glm::vec2>& m_scissorRectangleCentre;
  };
}