#pragma once

#include "CelesteDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Resources/2D/Texture2D.h"

#include <string>


namespace Celeste::Settings
{
  class StartupSettings : public ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(StartupSettings, CelesteDllExport)

    public:
      const std::string& getWindowTitle() const { return m_windowTitle.getValue(); }
      void setWindowTitle(const std::string& windowTitle) { m_windowTitle.setValue(windowTitle); }

      const std::string& getWindowIcon() const { return m_windowIcon.getValue(); }
      const std::string& getCursor() const { return m_cursor.getValue(); }

      CelesteDllExport void apply() const;

      static const Path SETTINGS_RELATIVE_PATH;

    private:
      using Inherited = ScriptableObject;

      ReferenceField<std::string>& m_windowTitle;
      ReferenceField<std::string>& m_windowIcon;
      ReferenceField<std::string>& m_cursor;
  };
}