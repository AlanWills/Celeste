#include "DataConverters/Physics/RectangleColliderDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Physics/RectangleCollider.h"


namespace Celeste
{
  REGISTER_COMPONENT_DATA_CONVERTER(RectangleColliderDataConverter)

  const char* const RectangleColliderDataConverter::IS_TRIGGER_ATTRIBUTE_NAME("trigger");
  const char* const RectangleColliderDataConverter::DIMENSIONS_ATTRIBUTE_NAME("dimensions");
  const char* const RectangleColliderDataConverter::OFFSET_ATTRIBUTE_NAME("offset");

  //------------------------------------------------------------------------------------------------
  RectangleColliderDataConverter::RectangleColliderDataConverter() :
    Inherited(Physics::RectangleCollider::type_name()),
    m_isTrigger(createValueAttribute<bool>(IS_TRIGGER_ATTRIBUTE_NAME)),
    m_dimensions(createReferenceAttribute(DIMENSIONS_ATTRIBUTE_NAME, glm::vec2())),
    m_offset(createReferenceAttribute<glm::vec2>(OFFSET_ATTRIBUTE_NAME))
  {
  }

  //------------------------------------------------------------------------------------------------
  void RectangleColliderDataConverter::doSetValues(Physics::RectangleCollider& collider) const
  {
    collider.setColliderType(getIsTrigger() ? Physics::ColliderType::kTrigger : Physics::ColliderType::kCollider);
    collider.setDimensions(getDimensions());
    collider.setOffset(getOffset());
  }
}