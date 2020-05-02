#pragma once

#include "UID/StringId.h"


namespace CelesteTestUtils
{
  class KeyboardTextInputtedEventUnsubscriber
  {
    public:
      KeyboardTextInputtedEventUnsubscriber(Celeste::StringId eventId);
      ~KeyboardTextInputtedEventUnsubscriber();

    private:
      Celeste::StringId m_eventHandle;
  };
}