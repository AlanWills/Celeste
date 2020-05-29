#pragma once

#include "Objects/Component.h"
#include "Resources/2D/Texture2D.h"
#include "Resources/ResourceManager.h"
#include "Rendering/SpriteRenderer.h"
#include "AnimationEnums.h"


namespace Celeste::Animation
{
  class Animator : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(Animator, CelesteDllExport)

    public:
      inline const glm::uvec2 getSpriteSheetDimensions() { return m_spriteSheetDimensions; }
      CelesteDllExport void setSpriteSheetDimensions(const glm::uvec2& spriteSheetDimensions);

      inline float getSecondsPerFrame() const { return m_secondsPerFrame; }
      inline void setSecondsPerFrame(float secondsPerFrame) { m_secondsPerFrame = secondsPerFrame; }

      inline void setLooping(LoopMode shouldLoop) { m_loop = shouldLoop == LoopMode::kLooping; }
      inline bool isLooping() const { return m_loop; }

      inline StringId getName() const { return m_name; }
      inline void setName(StringId name) { m_name = name; }
      inline void setName(const std::string& name) { m_name = internString(name); }

      inline size_t getFrameCount() const
      {
        return static_cast<size_t>(m_spriteSheetDimensions.x)* static_cast<size_t>(m_spriteSheetDimensions.y);
      }

      /// Start from the first frame or continue the animation at the current frame it was on
      /// With the current time left until the next frame.  Also begins rendering the animation texture.
      /// If we play a non-looping animation that reached it's end, nothing will happen
      CelesteDllExport void play();

      /// Will stop the animation at the current frame it was on
      /// With the current time left until the next frame
      /// If we pause a non-looping animation that reached it's end, nothing will happen
      inline void pause() { m_playing = false; }

      /// Will set the animation to the first frame and reset the current timer
      /// Whether the animation is playing or not will not be affected
      CelesteDllExport void restart();

      /// Will stop the animation from playing and stop rendering the animation texture
      CelesteDllExport void stop();

      /// Will return true if this animation is playing
      inline bool isPlaying() const { return m_playing; }

      CelesteDllExport void update() override;

    protected:
      inline size_t getCurrentFrame() const { return m_currentFrame; }
      inline void setCurrentFrame(size_t newFrame) { m_currentFrame = newFrame; }

      inline void setPlaying(bool isPlaying) { m_playing = isPlaying; }

      inline float getCurrentSecondsPerFrame() const { return m_currentSecondsPerFrame; }
      inline void setCurrentSecondsPerFrame(float currentScondsPerFrame) { m_currentSecondsPerFrame = currentScondsPerFrame; }

    private:
      using Inherited = Component;

      void setTextureToIndex(size_t index);

      glm::uvec2 m_spriteSheetDimensions;
      size_t m_currentFrame;
      bool m_currentFrameDirty;

      observer_ptr<Rendering::SpriteRenderer> m_spriteRenderer;

      bool m_playing;
      bool m_loop;

      float m_currentSecondsPerFrame;
      float m_secondsPerFrame;

      StringId m_name;
  };
}