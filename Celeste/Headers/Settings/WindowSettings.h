#pragma once

#include "CelesteDllExport.h"
#include "Objects/ScriptableObject.h"
#include "Resources/2D/Texture2D.h"
#include "Serialization/MathsSerializers.h"

#include <string>


namespace Celeste
{
  namespace Settings
  {
    class WindowSettings : public ScriptableObject
    {
      DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(WindowSettings, CelesteDllExport)

      public:
        const std::string& getWindowTitle() const { return m_windowTitle.getValue(); }
        void setWindowTitle(const std::string& windowTitle) { m_windowTitle.setValue(windowTitle); }

        const std::string& getWindowIcon() const { return m_windowIcon.getValue(); }
        
        const glm::vec2& getResolution() const { return m_resolution.getValue(); }
        void setResolution(const glm::vec2& resolution) { m_resolution.setValue(resolution); }

        bool isWindowed() const { return m_windowed.getValue(); }
        void setWindowed(bool windowed) { m_windowed.setValue(windowed); }

        CelesteDllExport void apply() const;

      private:
        using Inherited = ScriptableObject;

        ReferenceField<std::string>& m_windowTitle;
        ReferenceField<std::string>& m_windowIcon;
        ReferenceField<glm::vec2>& m_resolution;
        ValueField<bool>& m_windowed;
    };
  }
}