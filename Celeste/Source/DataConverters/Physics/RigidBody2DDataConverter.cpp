#include "DataConverters/Physics/RigidBody2DDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Physics/RigidBody2D.h"
#include "glm/glm.hpp"

#include <limits>


namespace Celeste
{
  REGISTER_COMPONENT_DATA_CONVERTER(RigidBody2DDataConverter)

  const char* const RigidBody2DDataConverter::LINEAR_VELOCITY_ATTRIBUTE_NAME("linear_velocity");
  const char* const RigidBody2DDataConverter::MIN_LINEAR_VELOCITY_ATTRIBUTE_NAME("min_linear_velocity");
  const char* const RigidBody2DDataConverter::MAX_LINEAR_VELOCITY_ATTRIBUTE_NAME("max_linear_velocity");
  const char* const RigidBody2DDataConverter::ANGULAR_VELOCITY_ATTRIBUTE_NAME("angular_velocity");
  const char* const RigidBody2DDataConverter::MIN_ANGULAR_VELOCITY_ATTRIBUTE_NAME("min_angular_velocity");
  const char* const RigidBody2DDataConverter::MAX_ANGULAR_VELOCITY_ATTRIBUTE_NAME("max_angular_velocity");

  //------------------------------------------------------------------------------------------------
  RigidBody2DDataConverter::RigidBody2DDataConverter() :
    Inherited(Physics::RigidBody2D::type_name()),
    m_linearVelocity(createReferenceAttribute<glm::vec2>(LINEAR_VELOCITY_ATTRIBUTE_NAME)),
    m_minLinearVelocity(createReferenceAttribute(MIN_LINEAR_VELOCITY_ATTRIBUTE_NAME, glm::vec2(-(std::numeric_limits<float>::max)(), -(std::numeric_limits<float>::max)()))),
    m_maxLinearVelocity(createReferenceAttribute(MAX_LINEAR_VELOCITY_ATTRIBUTE_NAME, glm::vec2((std::numeric_limits<float>::max)(), (std::numeric_limits<float>::max)()))),
    m_angularVelocity(createValueAttribute<float>(ANGULAR_VELOCITY_ATTRIBUTE_NAME)),
    m_minAngularVelocity(createValueAttribute(MIN_ANGULAR_VELOCITY_ATTRIBUTE_NAME, -(std::numeric_limits<float>::max)())),
    m_maxAngularVelocity(createValueAttribute(MAX_ANGULAR_VELOCITY_ATTRIBUTE_NAME, (std::numeric_limits<float>::max)()))
  {
  }

  //------------------------------------------------------------------------------------------------
  void RigidBody2DDataConverter::doSetValues(Physics::RigidBody2D& rigidBody) const
  {
    rigidBody.setLinearVelocity(getLinearVelocity());
    rigidBody.setMinLinearVelocity(getMinLinearVelocity());
    rigidBody.setMaxLinearVelocity(getMaxLinearVelocity());
    rigidBody.setAngularVelocity(getAngularVelocity());
    rigidBody.setMinAngularVelocity(getMinAngularVelocity());
    rigidBody.setMaxAngularVelocity(getMaxAngularVelocity());
  }
}