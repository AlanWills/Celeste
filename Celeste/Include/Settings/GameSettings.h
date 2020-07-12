#pragma once

#include "CelesteDllExport.h"
#include "Objects/ScriptableObject.h"


namespace Celeste::Settings
{
  class GameSettings : public ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(GameSettings, CelesteDllExport)

    public:
      const glm::vec2& getResolution() const { return m_resolution.getValue(); }
      void setResolution(const glm::vec2& resolution) { m_resolution.setValue(resolution); }

      bool isWindowed() const { return m_windowed.getValue(); }
      void setWindowed(bool windowed) { m_windowed.setValue(windowed); }

      bool isVsyncEnabled() const { return m_vsyncEnabled.getValue(); }
      void setVsyncEnabled(bool vsyncEnabled) { m_vsyncEnabled.setValue(vsyncEnabled); }

      inline float getMasterVolume() const { return m_masterVolume.getValue(); }
      inline void setMasterVolume(float masterVolume) { m_masterVolume.setValue(masterVolume); }

      inline float getMusicVolume() const { return m_musicVolume.getValue(); }
      inline void setMusicVolume(float musicVolume) { m_musicVolume.setValue(musicVolume); }

      inline float getSFXVolume() const { return m_sfxVolume.getValue(); }
      inline void setSFXVolume(float sfxVolume) { m_sfxVolume.setValue(sfxVolume); }

      CelesteDllExport void apply() const;

      static const Path SETTINGS_RELATIVE_PATH;

    private:
      using Inherited = ScriptableObject;

      ReferenceField<glm::vec2>& m_resolution;
      ValueField<bool>& m_windowed;
      ValueField<bool>& m_vsyncEnabled;
      ValueField<float>& m_masterVolume;
      ValueField<float>& m_musicVolume;
      ValueField<float>& m_sfxVolume;
  };
}