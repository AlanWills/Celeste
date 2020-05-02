#if _DEBUG

#include "Settings/DolceSettings.h"
#include "UtilityHeaders/ScriptableObjectHeaders.h"
#include "Dolce/Dolce.h"
#include "Dolce/DolceWindow.h"
#include "XML/tinyxml2_ext.h"

using namespace Celeste::XML;


namespace Celeste::Settings
{
  REGISTER_SCRIPTABLE_OBJECT(DolceSettings)

  const char* const DolceSettings::ENABLED_ATTRIBUTE_NAME = "enabled";
  const char* const DolceSettings::OPEN_WINDOWS_ELEMENT_NAME = "OpenWindows";
  const char* const DolceSettings::OPEN_WINDOW_ELEMENT_NAME = "OpenWindow";

  //------------------------------------------------------------------------------------------------
  DolceSettings::DolceSettings() :
    Inherited(),
    m_enabled(createValueField<bool>(ENABLED_ATTRIBUTE_NAME, false)),
    m_openWindows()
  {
  }

  //------------------------------------------------------------------------------------------------
  void DolceSettings::applyTo(Dolce::Dolce& dolce) const
  {
    dolce.setEnabled(getEnabled());

    for (const std::string& openWindow : getOpenWindows())
    {
      observer_ptr<Dolce::DolceWindow> window = dolce.findWindow(openWindow);
      if (window != nullptr)
      {
        window->open();
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void DolceSettings::applyFrom(Dolce::Dolce& dolce)
  {
    m_enabled.setValue(dolce.isEnabled());
    m_openWindows = std::move(dolce.getOpenWindows());
  }

  //------------------------------------------------------------------------------------------------
  bool DolceSettings::doDeserialize(const tinyxml2::XMLElement* element)
  {
    XMLValueError result = getChildElementDataAsVector(element, OPEN_WINDOWS_ELEMENT_NAME, OPEN_WINDOW_ELEMENT_NAME, m_openWindows, false);
    return result != XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  void DolceSettings::doSerialize(tinyxml2::XMLElement* element) const
  {
    tinyxml2::XMLElement* openWindowsElement = element->GetDocument()->NewElement(OPEN_WINDOWS_ELEMENT_NAME);
    element->InsertFirstChild(openWindowsElement);

    for (const auto& openWindow : m_openWindows)
    {
      tinyxml2::XMLElement* openWindowElement = openWindowsElement->GetDocument()->NewElement(OPEN_WINDOW_ELEMENT_NAME);
      openWindowElement->SetText(openWindow.c_str());
      openWindowsElement->InsertFirstChild(openWindowElement);

    }
  }
}

#endif