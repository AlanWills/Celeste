#include "DataConverters/UI/StackPanelDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "UI/StackPanel.h"
#include "Objects/GameObject.h"


namespace Celeste
{
  REGISTER_MANAGED_COMPONENT_DATA_CONVERTER(StackPanelDataConverter)

  const char* const StackPanelDataConverter::ORIENTATION_ATTRIBUTE_NAME("orientation");
  const char* const StackPanelDataConverter::HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME("horizontal_alignment");
  const char* const StackPanelDataConverter::VERTICAL_ALIGNMENT_ATTRIBUTE_NAME("vertical_alignment");
  const char* const StackPanelDataConverter::PADDING_ATTRIBUTE_NAME("padding");

  //------------------------------------------------------------------------------------------------
  StackPanelDataConverter::StackPanelDataConverter() :
    Inherited(UI::StackPanel::type_name()),
    m_orientation(createValueAttribute(ORIENTATION_ATTRIBUTE_NAME, UI::Orientation::kVertical)),
    m_horizontalAlignment(createValueAttribute(HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME, UI::HorizontalAlignment::kCentre)),
    m_verticalAlignment(createValueAttribute(VERTICAL_ALIGNMENT_ATTRIBUTE_NAME, UI::VerticalAlignment::kCentre)),
    m_padding(createValueAttribute(PADDING_ATTRIBUTE_NAME, 0.0f))
  {
  }

  //------------------------------------------------------------------------------------------------
  void StackPanelDataConverter::doSetValues(UI::StackPanel& stackPanel) const
  {
    stackPanel.setOrientation(getOrientation());
    stackPanel.setVerticalAlignment(getVerticalAlignment());
    stackPanel.setHorizontalAlignment(getHorizontalAlignment());
    stackPanel.setPadding(getPadding());

    for (observer_ptr<GameObject> gameObject : *stackPanel.getGameObject())
    {
      stackPanel.addChildren(*gameObject);
    }
  }
}