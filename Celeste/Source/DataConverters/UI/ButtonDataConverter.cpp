#include "DataConverters/UI/ButtonDataConverter.h"
#include "Resources/Data/Data.h"
#include "Registries/CallbackRegistry.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "UI/Button.h"


namespace Celeste
{
  REGISTER_COMPONENT_DATA_CONVERTER(ButtonDataConverter)

  const char* const ButtonDataConverter::DEFAULT_TEXTURE_ATTRIBUTE_NAME("default_texture");
  const char* const ButtonDataConverter::HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME("highlighted_texture");
  const char* const ButtonDataConverter::CLICKED_TEXTURE_ATTRIBUTE_NAME("clicked_texture");
  const char* const ButtonDataConverter::HIGHLIGHTED_SOUND_ATTRIBUTE_NAME("highlighted_sound");
  const char* const ButtonDataConverter::CLICKED_SOUND_ATTRIBUTE_NAME("clicked_sound");
  const char* const ButtonDataConverter::LEFT_CLICK_CALLBACKS_ELEMENT_NAME("LeftClickCallbacks");
  const char* const ButtonDataConverter::CALLBACK_ELEMENT_NAME("Callback");
  
  Path ButtonDataConverter::m_defaultTextureDefaultPath = Path("Textures", "UI", "ButtonDefault.png");
  Path ButtonDataConverter::m_highlightedTextureDefaultPath = Path("Textures", "UI", "ButtonHighlighted.png");
  Path ButtonDataConverter::m_clickedTextureDefaultPath = Path("Textures", "UI", "ButtonClicked.png");
  Path ButtonDataConverter::m_highlightedSoundDefaultPath = Path("Audio", "SFX", "ButtonHover.wav");
  Path ButtonDataConverter::m_clickedSoundDefaultPath = Path("Audio", "SFX", "ButtonClicked.wav");

  //------------------------------------------------------------------------------------------------
  ButtonDataConverter::ButtonDataConverter() :
    Inherited(UI::Button::type_name()),
    m_defaultTexturePath(createReferenceAttribute<Path>(DEFAULT_TEXTURE_ATTRIBUTE_NAME, m_defaultTextureDefaultPath)),
    m_highlightedTexturePath(createReferenceAttribute<Path>(HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME, m_highlightedTextureDefaultPath)),
    m_clickedTexturePath(createReferenceAttribute<Path>(CLICKED_TEXTURE_ATTRIBUTE_NAME, m_clickedTextureDefaultPath)),
    m_highlightedSoundPath(createReferenceAttribute<Path>(HIGHLIGHTED_SOUND_ATTRIBUTE_NAME, m_highlightedSoundDefaultPath)),
    m_clickedSoundPath(createReferenceAttribute<Path>(CLICKED_SOUND_ATTRIBUTE_NAME, m_clickedSoundDefaultPath)),
    m_leftClickCallbacks(createDataConverterListElement<CallbackDataConverter>(LEFT_CLICK_CALLBACKS_ELEMENT_NAME, XML::ChildElementName(CALLBACK_ELEMENT_NAME)))
  {
  }

  //------------------------------------------------------------------------------------------------
  void ButtonDataConverter::doSetValues(UI::Button& button) const
  {
    button.setDefaultTexture(getDefaultTexturePath());
    button.setHighlightedTexture(getHighlightedTexturePath());
    button.setClickedTexture(getClickedTexturePath());
    button.setHighlightedSound(getHighlightedSoundPath());
    button.setClickedSound(getClickedSoundPath());

    // Turn this into a utility function?
    for (CallbackDataConverter* callbackInfo : m_leftClickCallbacks)
    {
      const std::string& name = callbackInfo->getName();
      const std::string& arg = callbackInfo->getArg();

      // Check if callback exists in registry
      if (!CallbackRegistry::hasCallback(name))
      {
        ASSERT_FAIL();
        continue;
      }

      // Think we want to pass function arguments by value so we don't have to rely on this converter existing at invocation time
      button.subscribeLeftClickCallback([name, arg](GameObject& gameObject) -> void
      {
        CallbackRegistry::invokeCallback(name, gameObject, arg);
      });
    }
  }
}