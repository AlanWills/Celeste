#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "XML/Attributes/DataAttribute.h"
#include "Deserialization/MathsDeserializers.h"


namespace Celeste::Physics
{
  class RectangleCollider;
}

namespace Celeste
{
  class RectangleColliderDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(RectangleColliderDataConverter, Physics::RectangleCollider, CelesteDllExport)

    public:
      inline bool getIsTrigger() const { return m_isTrigger.getValue(); }
      inline const glm::vec2& getDimensions() const { return m_dimensions.getValue(); }
      inline const glm::vec2& getOffset() const { return m_offset.getValue(); }

      CelesteDllExport static const char* const IS_TRIGGER_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const DIMENSIONS_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const OFFSET_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ValueAttribute<bool>& m_isTrigger;
      XML::ReferenceAttribute<glm::vec2>& m_dimensions;
      XML::ReferenceAttribute<glm::vec2>& m_offset;
  };
}