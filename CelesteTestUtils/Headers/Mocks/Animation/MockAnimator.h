#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Animation/Animator.h"


namespace CelesteTestUtils
{
  class MockAnimator : public Celeste::Animation::Animator
  {
    DECLARE_SCRIPT(MockAnimator, CelesteTestUtilsDllExport)

    public:      
      size_t getCurrentFrame_Public() const { return getCurrentFrame(); }
      void setCurrentFrame_Public(size_t newFrame) { setCurrentFrame(newFrame); }

      void setPlaying_Public(bool isPlaying) { setPlaying(isPlaying); }

      float getCurrentSecondsPerFrame_Public() const { return getCurrentSecondsPerFrame(); }
      void setCurrentSecondsPerFrame_Public(float currentScondsPerFrame) { setCurrentSecondsPerFrame(currentScondsPerFrame); }
  };
}