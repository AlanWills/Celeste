#include "Time/TimeNotifierSystem.h"


namespace Celeste::Time
{
  //------------------------------------------------------------------------------------------------
  void TimeNotifierSystem::update(float elapsedGameTime)
  {
    m_timeNotifierEvent.invoke(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  StringId TimeNotifierSystem::subscribe(TimeNotifierSystem::TimeNotifierEvent::Function&& callback)
  {
    return m_timeNotifierEvent.subscribe(std::move(callback));
  }

  //------------------------------------------------------------------------------------------------
  void TimeNotifierSystem::unsubscribe(StringId eventHandle)
  {
    m_timeNotifierEvent.unsubscribe(eventHandle);
  }
}