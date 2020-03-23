#include "UI/Button.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"
#include "Input/MouseInteractionHandler.h"
#include "DataConverters/UI/ButtonDataConverter.h"
#include "Rendering/SpriteRenderer.h"
#include "Audio/AudioSource.h"
#include "FileSystem/Path.h"


namespace Celeste
{
  using namespace Resources;
  using namespace Audio;
  using namespace Rendering;
  using namespace Input;

  namespace UI
  {
    REGISTER_COMPONENT(Button, 10)

    //------------------------------------------------------------------------------------------------
    Button::Button(GameObject& gameObject) :
      Inherited(gameObject),
      m_spriteRenderer(gameObject.findComponent<Rendering::SpriteRenderer>()),
      m_mouseInteraction(gameObject.findComponent<MouseInteractionHandler>()),
      m_audio(gameObject.findComponent<Audio::AudioSource>())
    {
      setDefaultTexture(ButtonDataConverter::getDefaultTextureDefaultPath());
      ASSERT_NOT_NULL(m_defaultTexture);

      setHighlightedTexture(ButtonDataConverter::getHighlightedTextureDefaultPath());
      ASSERT_NOT_NULL(m_highlightedTexture);

      setClickedTexture(ButtonDataConverter::getClickedTextureDefaultPath());
      ASSERT_NOT_NULL(m_clickedTexture);

      setHighlightedSound(ButtonDataConverter::getHighlightedSoundDefaultPath());
      ASSERT_NOT_NULL(m_highlightedSound);

      setClickedSound(ButtonDataConverter::getClickedSoundDefaultPath());
      ASSERT_NOT_NULL(m_clickedSound);

      // Set the default texture on the sprite renderer for this button
      ASSERT_NOT_NULL(m_spriteRenderer);
      m_spriteRenderer->setTexture(m_defaultTexture);

      // Set up the events for mouse interaction
      ASSERT_NOT_NULL(m_mouseInteraction);
      m_mouseInteraction->getOnEnterEvent().subscribe([this](GameObject&) -> void { onEnter(); });
      m_mouseInteraction->getOnLeaveEvent().subscribe([this](GameObject&) -> void { onLeave(); });
      m_mouseInteraction->getOnLeftButtonDownEvent().subscribe([this](GameObject&) -> void { onLeftMouseButtonDown(); });
      m_mouseInteraction->getOnLeftButtonUpEvent().subscribe([this](GameObject&) -> void { onLeftMouseButtonUp(); });

      // Set up the audio source for this button
      if (m_audio != nullptr)
      {
        m_audio->setAudioType(AudioType::kSFX);
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::update(float secondsPerUpdate)
    {
      Inherited::update(secondsPerUpdate);

      m_clickTimer += secondsPerUpdate;
    }

    //------------------------------------------------------------------------------------------------
    void Button::onEnter()
    {
      m_spriteRenderer->setTexture(m_highlightedTexture);

      if (m_audio != nullptr)
      {
        m_audio->setSound(m_highlightedSound);
        m_audio->play();
      }

      m_state = ButtonState::kHighlighted;
    }

    //------------------------------------------------------------------------------------------------
    void Button::onLeave()
    {
      m_spriteRenderer->setTexture(m_defaultTexture);
      m_state = ButtonState::kIdle;
    }

    //------------------------------------------------------------------------------------------------
    void Button::onLeftMouseButtonDown()
    {
      if (m_state != ButtonState::kClicked)
      {
        m_spriteRenderer->setTexture(m_clickedTexture);

        if (m_audio != nullptr)
        {
          m_audio->setSound(m_clickedSound);
          m_audio->play();
        }

        m_state = ButtonState::kClicked;
        m_clickTimer = 0;
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::onLeftMouseButtonUp()
    {
      if (m_state == ButtonState::kClicked)
      {
        // Update loop will sort out proper texture
        m_state = ButtonState::kIdle;
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::subscribeLeftClickCallback(const GameObjectClickCallback& callback)
    {
#if _DEBUG
      if (m_mouseInteraction == nullptr)
      {
        ASSERT_FAIL();
        return;
      }
#endif

      m_mouseInteraction->getOnLeftButtonUpEvent().subscribe(callback);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setDefaultTexture(const Path& path)
    {
      m_defaultTexture = getResourceManager().load<Texture2D>(path);
      ASSERT_NOT_NULL(m_defaultTexture);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setHighlightedTexture(const Path& path)
    {
      m_highlightedTexture = getResourceManager().load<Texture2D>(path);
      ASSERT_NOT_NULL(m_highlightedTexture);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setClickedTexture(const Path& path)
    {
      m_clickedTexture = getResourceManager().load<Texture2D>(path);
      ASSERT_NOT_NULL(m_clickedTexture);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setHighlightedSound(const Path& path)
    {
      m_highlightedSound = getResourceManager().load<Sound>(path);
      ASSERT_NOT_NULL(m_highlightedSound);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setClickedSound(const Path& path)
    {
      m_clickedSound = getResourceManager().load<Sound>(path);
      ASSERT_NOT_NULL(m_clickedSound);
    }
  }
}