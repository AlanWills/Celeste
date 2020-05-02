#include "TestUtils/RAII/KeyboardTextInputtedEventUnsubscriber.h"
#include "Input/InputUtils.h"
#include "Input/Keyboard.h"


namespace CelesteTestUtils
{
  //------------------------------------------------------------------------------------------------
  KeyboardTextInputtedEventUnsubscriber::KeyboardTextInputtedEventUnsubscriber(Celeste::StringId eventId) :
    m_eventHandle(eventId) 
  { 
  }

  //------------------------------------------------------------------------------------------------
  KeyboardTextInputtedEventUnsubscriber::~KeyboardTextInputtedEventUnsubscriber()
  {
    Celeste::Input::getKeyboard().getTextInputtedEvent().unsubscribe(m_eventHandle);
  }
}