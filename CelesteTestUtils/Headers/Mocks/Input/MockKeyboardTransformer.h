#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Input/KeyboardTransformer.h"


namespace CelesteTestUtils
{
  class MockKeyboardTransformer : public Celeste::Input::KeyboardTransformer
  {
    DECLARE_UNMANAGED_COMPONENT(MockKeyboardTransformer, CelesteTestUtilsDllExport)

    public:
      const glm::vec2& getDirectionVector_Public() const { return getDirectionVector(); }
      void setDirectionVector_Public(const glm::vec2& direction) { setDirectionVector(direction); }

      const float getRotationDelta_Public() const { return getRotationDelta(); }
      void setRotationDelta_Public(float delta) { setRotationDelta(delta); }
  };
}