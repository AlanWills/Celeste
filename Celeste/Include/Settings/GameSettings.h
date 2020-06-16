#pragma once

#include "CelesteDllExport.h"
#include "Objects/ScriptableObject.h"


namespace Celeste::Settings
{
  class GameSettings : public ScriptableObject
  {
    DECLARE_SCRIPTABLE_OBJECT(GameSettings, CelesteDllExport)

    public:
      inline float getMasterVolume() const { return m_masterVolume.getValue(); }
      inline void setMasterVolume(float masterVolume) { m_masterVolume.setValue(masterVolume); }

      inline float getMusicVolume() const { return m_musicVolume.getValue(); }
      inline void setMusicVolume(float musicVolume) { m_musicVolume.setValue(musicVolume); }

      inline float getSFXVolume() const { return m_sfxVolume.getValue(); }
      inline void setSFXVolume(float sfxVolume) { m_sfxVolume.setValue(sfxVolume); }

      inline bool isVsyncEnabled() const { return m_vsyncEnabled.getValue(); }
      inline void setVsyncEnabled(bool vsyncEnabled) { m_vsyncEnabled.setValue(vsyncEnabled); }

      CelesteDllExport void apply() const;

    private:
      using Inherited = ScriptableObject;

      ValueField<float>& m_masterVolume;
      ValueField<float>& m_musicVolume;
      ValueField<float>& m_sfxVolume;
      ValueField<bool>& m_vsyncEnabled;
  };
}