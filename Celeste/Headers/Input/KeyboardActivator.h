#pragma once

#include "Objects/Component.h"
#include "UID/StringId.h"
#include "InputEnums.h"
#include "Key.h"


namespace Celeste::Input
{
  class KeyboardActivator : public Component
  {
    DECLARE_MANAGED_COMPONENT(KeyboardActivator, InputManager, CelesteDllExport)

    public:
      inline int getActivationKey() const { return m_activationKey; }
      inline void setActivationKey(int activationKey) { m_activationKey = activationKey; }

      inline int getDeactivationKey() const { return m_deactivationKey; }
      inline void setDeactivationKey(int deactivationKey) { m_deactivationKey = deactivationKey; }

      inline InputMode getInputMode() const { return m_inputMode; }
      inline void setInputMode(InputMode inputMode) { m_inputMode = inputMode; }

      CelesteDllExport void handleInput() override;

    private:
      using Inherited = Component;

      int m_activationKey;
      int m_deactivationKey;
      InputMode m_inputMode;
  };
}