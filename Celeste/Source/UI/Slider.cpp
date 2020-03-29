#include "UI/Slider.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Rendering/SpriteRenderer.h"
#include "Input/InputManager.h"
#include "Input/MouseInteractionHandler.h"

using namespace Celeste::Rendering;
using namespace Celeste::Input;


namespace Celeste::UI
{
  REGISTER_COMPONENT(Slider, 4)

  //------------------------------------------------------------------------------------------------
  Slider::Slider(GameObject& gameObject) :
    Inherited(gameObject),
    m_sliderClicked(false),
    m_min(0),
    m_max(1),
    m_currentValue(0),
    m_valueChanged()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Slider::handleInput()
  {
    Inherited::handleInput();

#if _DEBUG
    if (getGameObject() == nullptr || !getGameObject()->hasComponent<MouseInteractionHandler>())
    {
      ASSERT_FAIL();
      return;
    }
#endif

    if (m_sliderClicked)
    {
      // Calculate based on mouse position relative to this game object
      // In the range [-0.5, 0.5]
      float diff = (getMouse().getTransform().getWorldTranslation().x - getTransform()->getWorldTranslation().x);

      observer_ptr<SpriteRenderer> spriteRenderer = getGameObject()->findComponent<SpriteRenderer>();
      setCurrentValue((diff / (spriteRenderer->getDimensions().x - spriteRenderer->getScissorRectangle().getDimensions().x)) + 0.5f);
      m_sliderClicked = getMouse().isButtonPressed(MouseButton::kLeft);
    }
    else
    {
      m_sliderClicked = getMouse().isButtonClicked(MouseButton::kLeft) && getGameObject()->findComponent<MouseInteractionHandler>()->isMouseOver();
    }
  }

  //------------------------------------------------------------------------------------------------
  void Slider::setCurrentValue(float value)
  {
    // Update value but keep it in valid range
    m_currentValue = glm::clamp<float>(value, m_min, m_max);

    if (getTransform() != nullptr)
    {
      // Update slider position
      float offset = (m_currentValue - (m_max + m_min) * 0.5f) / (m_max - m_min);

      observer_ptr<SpriteRenderer> spriteRenderer = getGameObject()->findComponent<SpriteRenderer>();
      Maths::Rectangle& scissorRectangle = spriteRenderer->getScissorRectangle();
      spriteRenderer->getScissorRectangle().setCentreX((spriteRenderer->getDimensions().x - scissorRectangle.getDimensions().x) * offset);
    }

    // Trigger event
    m_valueChanged.invoke(*getGameObject(), m_currentValue);
  }
}