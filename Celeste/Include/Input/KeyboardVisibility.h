#pragma once

#include "Objects/Component.h"
#include "InputEnums.h"
#include "UID/StringId.h"

#include <string>


namespace Celeste::Input
{
  class KeyboardVisibility : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(KeyboardVisibility, CelesteDllExport)

    public:
      inline int getVisibilityKey() const { return m_visibilityKey; }
      inline void setVisibilityKey(int visibilityKey) { m_visibilityKey = visibilityKey; }

      inline int getInvisibilityKey() const { return m_invisibilityKey; }
      inline void setInvisibilityKey(int invisibilityKey) { m_invisibilityKey = invisibilityKey; }

      inline InputMode getInputMode() const { return m_inputMode; }
      inline void setInputMode(InputMode inputMode) { m_inputMode = inputMode; }

      CelesteDllExport void update() override;

    private:
      using Inherited = Component;

      int m_visibilityKey;
      int m_invisibilityKey;
      InputMode m_inputMode;
  };
}