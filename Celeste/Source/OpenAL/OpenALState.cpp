#include "OpenAL/OpenALState.h"
#include "UtilityHeaders/ALHeaders.h"


namespace Celeste
{
  /// Initialize static variables
  bool OpenALState::m_initialized = false;

  //------------------------------------------------------------------------------------------------
  bool OpenALState::initialize()
  {
    bool result = true;

    if (!m_initialized)
    {
      // Initialize alut state here
      result = (alutInit(nullptr, nullptr) == AL_TRUE);

      // Mark the state as now initialized
      m_initialized = true;
    }

    return result;
  }

  //------------------------------------------------------------------------------------------------
  bool OpenALState::terminate()
  {
    bool result = true;

    if (m_initialized)
    {
      alutGetError();

      // Terminate the alut state
      result = (alutExit() == AL_TRUE);

      // Mark the state as now terminated
      m_initialized = false;
    }

    return result;
  }
}