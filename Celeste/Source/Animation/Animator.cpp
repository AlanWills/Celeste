#include "Animation/Animator.h"
#include "UtilityHeaders/ComponentHeaders.h"

using namespace Celeste::Resources;


namespace Celeste::Animation
{
  REGISTER_UNMANAGED_COMPONENT(Animator, 10)

  //------------------------------------------------------------------------------------------------
  Animator::Animator(GameObject& gameObject) :
    Inherited(gameObject),
    m_spriteSheetDimensions(1),
    m_currentFrame(0),
    m_currentFrameDirty(true),
    m_spriteRenderer(gameObject.findComponent<Rendering::SpriteRenderer>()),
    m_loop(true),
    m_playing(false),
    m_currentSecondsPerFrame(0),
    m_secondsPerFrame(0.1f),
    m_name(0)
  {
    ASSERT_NOT_NULL(m_spriteRenderer);
  }

  //------------------------------------------------------------------------------------------------
  void Animator::setSpriteSheetDimensions(const glm::uvec2& spriteSheetDimensions)
  {
    m_spriteSheetDimensions = spriteSheetDimensions;

    if (m_spriteRenderer != nullptr)
    {
      // Set the scissor rectangle to be the size of one frame
      const glm::vec2& dimensions = m_spriteRenderer->getDimensions();
      float singleFrameWidth = dimensions.x / m_spriteSheetDimensions.x;
      float singleFrameHeight = dimensions.y / m_spriteSheetDimensions.y;

      m_spriteRenderer->getScissorRectangle().setDimensions(singleFrameWidth, singleFrameHeight);
      m_spriteRenderer->getScissorRectangle().setCentre(0, 0);
    }

    setTextureToIndex(m_currentFrame);
  }

  //------------------------------------------------------------------------------------------------
  void Animator::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

#if _DEBUG
    if (m_spriteRenderer == nullptr)
    {
      ASSERT_FAIL();
      return;
    }
#endif

    if (m_playing)
    {
      m_currentSecondsPerFrame += secondsPerUpdate;

      if (m_currentSecondsPerFrame >= m_secondsPerFrame)
      {
        size_t numFrames = getFrameCount();
        ASSERT(numFrames);

        m_currentSecondsPerFrame -= m_secondsPerFrame;

        m_currentFrame++;
        m_currentFrame %= numFrames;

        if (!m_loop && (m_currentFrame == numFrames - 1))
        {
          // If we are not looping and we have reached the end of the animation frames we stop playing the animation
          // This will freeze the sprite renderer on the final frame
          pause();
          m_currentSecondsPerFrame = 0;
        }

        // Tell the animation that it needs to recalculate the texture scissor rect
        m_currentFrameDirty = true;
      }

      if (m_currentFrameDirty)
      {
        // Update texture
        setTextureToIndex(m_currentFrame);

        m_currentFrameDirty = false;
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void Animator::play()
  {
    size_t numFrames = getFrameCount();

    if (m_loop || (0 < numFrames && (m_currentFrame != numFrames - 1)))
    {
      // If we are looping or have not reached the end of a non-looping animation we continue playing
      m_playing = true;
      m_currentFrameDirty = true;
    }
  }

  //------------------------------------------------------------------------------------------------
  void Animator::stop()
  {
    pause();
    restart();
  }

  //------------------------------------------------------------------------------------------------
  void Animator::restart()
  {
    m_currentFrame = 0;
    m_currentSecondsPerFrame = 0;
    m_currentFrameDirty = true;

    setTextureToIndex(0);
  }

  //------------------------------------------------------------------------------------------------
  void Animator::setTextureToIndex(size_t index)
  {
    if (index >= getFrameCount() || m_spriteRenderer == nullptr)
    {
      // Invalid index
      return;
    }

    size_t column = index % m_spriteSheetDimensions.x;
    size_t row = index / m_spriteSheetDimensions.x;

    // Change the origin of the renderer so that the image remains in the same place
    m_spriteRenderer->setOrigin((column + 0.5f) / m_spriteSheetDimensions.x,
      (m_spriteSheetDimensions.y - row - 0.5f) / m_spriteSheetDimensions.y);
  }
}