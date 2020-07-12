#include "DataConverters/UI/ButtonDataConverter.h"
#include "Resources/Data/Data.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "UI/Button.h"


namespace Celeste
{
  REGISTER_COMPONENT_DATA_CONVERTER(ButtonDataConverter)

  const char* const ButtonDataConverter::IDLE_TEXTURE_ATTRIBUTE_NAME("idle_texture");
  const char* const ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME("highlighted_texture");
  const char* const ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME("clicked_texture");
  const char* const ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME("highlighted_sound");
  const char* const ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME("clicked_sound");
  
  //------------------------------------------------------------------------------------------------
  ButtonDataConverter::ButtonDataConverter() :
    Inherited(UI::Button::type_name()),
    m_idleTexturePath(createReferenceAttribute<Path>(IDLE_TEXTURE_ATTRIBUTE_NAME)),
    m_highlightedTexturePath(createReferenceAttribute<Path>(HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME)),
    m_clickedTexturePath(createReferenceAttribute<Path>(CLICKED_TEXTURE_ATTRIBUTE_NAME)),
    m_highlightedSoundPath(createReferenceAttribute<Path>(HIGHLIGHTED_SOUND_ATTRIBUTE_NAME)),
    m_clickedSoundPath(createReferenceAttribute<Path>(CLICKED_SOUND_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ButtonDataConverter::doSetValues(UI::Button& button) const
  {
    button.setIdleTexture(getIdleTexturePath());
    button.setHighlightedTexture(getHighlightedTexturePath());
    button.setClickedTexture(getClickedTexturePath());
    button.setHighlightedSound(getHighlightedSoundPath());
    button.setClickedSound(getClickedSoundPath());
  }
}