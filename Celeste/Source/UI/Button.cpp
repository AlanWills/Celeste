#include "UI/Button.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"
#include "Input/MouseInteractionHandler.h"
#include "DataConverters/UI/ButtonDataConverter.h"
#include "Rendering/SpriteRenderer.h"
#include "Audio/AudioSource.h"
#include "FileSystem/Path.h"
#include "Time/TimeUtils.h"


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
      m_spriteRenderer->setTexture(m_idleTexture);
      m_state = ButtonState::kIdle;
    }

    //------------------------------------------------------------------------------------------------
    void Button::onLeftMouseButtonDown()
    {
      if (m_state != ButtonState::kClicked)
      {
        m_spriteRenderer->setTexture(m_clickedTexture);
        m_state = ButtonState::kClicked;
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::onLeftMouseButtonUp()
    {
      if (m_state == ButtonState::kClicked)
      {
        if (m_audio != nullptr)
        {
          m_audio->setSound(m_clickedSound);
          m_audio->play();
        }

        m_spriteRenderer->setTexture(m_idleTexture);
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
    void Button::setIdleTexture(const Path& path)
    {
      m_idleTexture = getResourceManager().load<Texture2D>(path);

      if (m_state == ButtonState::kIdle)
      {
        m_spriteRenderer->setTexture(m_idleTexture);
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::setHighlightedTexture(const Path& path)
    {
      m_highlightedTexture = getResourceManager().load<Texture2D>(path);

      if (m_state == ButtonState::kHighlighted)
      {
        m_spriteRenderer->setTexture(m_highlightedTexture);
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::setClickedTexture(const Path& path)
    {
      m_clickedTexture = getResourceManager().load<Texture2D>(path);

      if (m_state == ButtonState::kClicked)
      {
        m_spriteRenderer->setTexture(m_clickedTexture);
      }
    }

    //------------------------------------------------------------------------------------------------
    void Button::setHighlightedSound(const Path& path)
    {
      m_highlightedSound = getResourceManager().load<Sound>(path);
    }

    //------------------------------------------------------------------------------------------------
    void Button::setClickedSound(const Path& path)
    {
      m_clickedSound = getResourceManager().load<Sound>(path);
    }
  }
}