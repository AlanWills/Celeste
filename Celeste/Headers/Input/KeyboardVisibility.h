#pragma once

#include "Objects/Script.h"
#include "InputEnums.h"
#include "UID/StringId.h"

#include <string>


namespace Celeste::Input
{
  class KeyboardVisibility : public Script
  {
    DECLARE_SCRIPT(KeyboardVisibility, CelesteDllExport)

    public:
      inline int getVisibilityKey() const { return m_visibilityKey; }
      inline void setVisibilityKey(int visibilityKey) { m_visibilityKey = visibilityKey; }

      inline int getInvisibilityKey() const { return m_invisibilityKey; }
      inline void setInvisibilityKey(int invisibilityKey) { m_invisibilityKey = invisibilityKey; }

      inline InputMode getInputMode() const { return m_inputMode; }
      inline void setInputMode(InputMode inputMode) { m_inputMode = inputMode; }

      inline observer_ptr<GameObject> getTarget() const { return m_target; }
      inline void setTarget(observer_ptr<GameObject> target) { m_target = target; }
      void setTarget(const std::string& targetName) { setTarget(internString(targetName)); }
      CelesteDllExport void setTarget(StringId targetName);

      CelesteDllExport void handleInput() override;

    private:
      using Inherited = Script;

      int m_visibilityKey;
      int m_invisibilityKey;
      InputMode m_inputMode;
      observer_ptr<GameObject> m_target;
  };
}