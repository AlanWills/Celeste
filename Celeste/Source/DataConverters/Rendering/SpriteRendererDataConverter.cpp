#include "DataConverters/Rendering/SpriteRendererDataConverter.h"
#include "Resources/ResourceManager.h"
#include "Screens/ScreenUtils.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Rendering/SpriteRenderer.h"

using namespace Celeste::Rendering;


namespace Celeste
{
  REGISTER_MANAGED_COMPONENT_DATA_CONVERTER(SpriteRendererDataConverter)

  const char* const SpriteRendererDataConverter::SPRITE_ATTRIBUTE_NAME("sprite");
  const char* const SpriteRendererDataConverter::SIZE_ATTRIBUTE_NAME("size");
  const char* const SpriteRendererDataConverter::COLOUR_ATTRIBUTE_NAME("colour");
  const char* const SpriteRendererDataConverter::OPACITY_ATTRIBUTE_NAME("opacity");
  const char* const SpriteRendererDataConverter::PRESERVE_ASPECT_RATIO_ATTRIBUTE_NAME("preserve_aspect_ratio");
  const char* const SpriteRendererDataConverter::SCISSOR_RECTANGLE_DIMENSIONS_ATTRIBUTE_NAME("scissor_rectangle_dimensions");
  const char* const SpriteRendererDataConverter::SCISSOR_RECTANGLE_CENTRE_ATTRIBUTE_NAME("scissor_rectangle_centre");

  //------------------------------------------------------------------------------------------------
  SpriteRendererDataConverter::SpriteRendererDataConverter() :
    Inherited(Rendering::SpriteRenderer::type_name()),
    m_sprite(createReferenceAttribute<Path>(SPRITE_ATTRIBUTE_NAME, "")),
    m_size(createReferenceAttribute<glm::vec2>(SIZE_ATTRIBUTE_NAME)),
    m_colour(createReferenceAttribute(COLOUR_ATTRIBUTE_NAME, glm::vec3(1))),
    m_opacity(createValueAttribute(OPACITY_ATTRIBUTE_NAME, 1.0f)),
    m_preserveAspectRatio(createValueAttribute(PRESERVE_ASPECT_RATIO_ATTRIBUTE_NAME, false)),
    m_scissorRectangleDimensions(createReferenceAttribute<glm::vec2>(SCISSOR_RECTANGLE_DIMENSIONS_ATTRIBUTE_NAME)),
    m_scissorRectangleCentre(createReferenceAttribute<glm::vec2>(SCISSOR_RECTANGLE_CENTRE_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRendererDataConverter::doSetValues(SpriteRenderer& spriteRenderer) const
  {
    spriteRenderer.shouldPreserveAspectRatio(getPreserveAspectRatio() ? RatioMode::kPreserveAspectRatio : RatioMode::kDontPreserveAspectRatio);
    spriteRenderer.setColour(getColour());
    spriteRenderer.setOpacity(getOpacity());
    spriteRenderer.getScissorRectangle().setDimensions(getScissorRectangleDimensions());
    spriteRenderer.getScissorRectangle().setCentre(getScissorRectangleCentre());
    
    if (!getSprite().as_string().empty())
    {
      // Sprite isn't required - this is because we can set it from a scriptable object
      spriteRenderer.setTexture(getSprite());
    }
    
    if (!findAttribute(SIZE_ATTRIBUTE_NAME)->isUsingDefaultValue())
    {
      // If we have specified a value we should set the dimensions
      // Otherwise, let the standard sprite renderer behaviour take over - it will set the dimensions to those of the texture
      spriteRenderer.setDimensions(getSize());
    }
  }
}