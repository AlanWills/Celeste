#include "Resources/Audio/Sound.h"
#include "FileSystem/File.h"
#include "Debug/Log.h"


namespace Celeste::Resources
{
  //------------------------------------------------------------------------------------------------
  Sound::Sound() :
    m_audioHandle(AL_NONE)
  {
  }

  //------------------------------------------------------------------------------------------------
  Sound::~Sound()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool Sound::doLoadFromFile(const Path& soundFilePath)
  {
    m_audioHandle = alutCreateBufferFromFile(soundFilePath.c_str());
    if (m_audioHandle == AL_NONE)
    {
      const char* error = alutGetErrorString(alutGetError());
      LOG_ERROR(error);
      ASSERT_FAIL_MSG(error);
    }

    return m_audioHandle != AL_NONE;
  }

  //------------------------------------------------------------------------------------------------
  void Sound::doUnload()
  {
    if (m_audioHandle > 0 && alIsBuffer(m_audioHandle))
    {
      alDeleteBuffers(1, &m_audioHandle);
    }

    m_audioHandle = AL_NONE;
  }
}