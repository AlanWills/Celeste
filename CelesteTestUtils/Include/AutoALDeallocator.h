#pragma once

#include "AL/al.h"


namespace CelesteTestUtils
{

class AutoALDeallocator
{
  public:
    AutoALDeallocator(ALuint handle) :
      m_handle(handle)
    {
    }

    ~AutoALDeallocator()
    {
      if (m_handle != AL_NONE && alIsBuffer(m_handle))
      {
        alDeleteBuffers(1, &m_handle);
      }

      if (m_handle != AL_NONE && alIsSource(m_handle))
      {
        alDeleteSources(1, &m_handle);
      }

      m_handle = 0;
    }

  private:
    ALuint m_handle;
};

}