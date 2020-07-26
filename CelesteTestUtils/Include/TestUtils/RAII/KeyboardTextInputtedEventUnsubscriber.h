#pragma once

#include "Events/EventHandle.h"


namespace CelesteTestUtils
{
  class KeyboardTextInputtedEventUnsubscriber
  {
    public:
      KeyboardTextInputtedEventUnsubscriber(Celeste::EventHandle eventHandle);
      ~KeyboardTextInputtedEventUnsubscriber();

    private:
      Celeste::EventHandle m_eventHandle;
  };
}