#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "XML/Attributes/DataAttribute.h"
#include "XML/Elements/ListElement.h"
#include "Deserialization/UIDeserializers.h"
#include "Bindings/UIDataBindingGenerators.h"


namespace Celeste::UI
{
  class StackPanel;
}

namespace Celeste
{
  class StackPanelDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(StackPanelDataConverter, UI::StackPanel, CelesteDllExport)

    public:
      inline UI::Orientation getOrientation() const { return m_orientation.getValue(); }
      inline UI::HorizontalAlignment getHorizontalAlignment() const { return m_horizontalAlignment.getValue(); }
      inline UI::VerticalAlignment getVerticalAlignment() const { return m_verticalAlignment.getValue(); }
      inline float getPadding() const { return m_padding.getValue(); }

      CelesteDllExport static const char* const ORIENTATION_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const HORIZONTAL_ALIGNMENT_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const VERTICAL_ALIGNMENT_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const PADDING_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ValueAttribute<UI::Orientation>& m_orientation;
      XML::ValueAttribute<UI::HorizontalAlignment>& m_horizontalAlignment;
      XML::ValueAttribute<UI::VerticalAlignment>& m_verticalAlignment;
      XML::ValueAttribute<float>& m_padding;
  };
}