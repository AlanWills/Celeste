#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "XML/Attributes/DataAttribute.h"
#include "Deserialization/MathsDeserializers.h"


namespace Celeste::Physics
{
  class RigidBody2D;
}

namespace Celeste
{
  class RigidBody2DDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(RigidBody2DDataConverter, Physics::RigidBody2D, CelesteDllExport)

    public:
      inline const glm::vec2& getLinearVelocity() const { return m_linearVelocity.getValue(); }
      inline const glm::vec2& getMinLinearVelocity() const { return m_minLinearVelocity.getValue(); }
      inline const glm::vec2& getMaxLinearVelocity() const { return m_maxLinearVelocity.getValue(); }
      inline float getAngularVelocity() const { return m_angularVelocity.getValue(); }
      inline float getMinAngularVelocity() const { return m_minAngularVelocity.getValue(); }
      inline float getMaxAngularVelocity() const { return m_maxAngularVelocity.getValue(); }

      CelesteDllExport static const char* const LINEAR_VELOCITY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const MIN_LINEAR_VELOCITY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const MAX_LINEAR_VELOCITY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const ANGULAR_VELOCITY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const MIN_ANGULAR_VELOCITY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const MAX_ANGULAR_VELOCITY_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ReferenceAttribute<glm::vec2>& m_linearVelocity;
      XML::ReferenceAttribute<glm::vec2>& m_minLinearVelocity;
      XML::ReferenceAttribute<glm::vec2>& m_maxLinearVelocity;
      XML::ValueAttribute<float>& m_angularVelocity;
      XML::ValueAttribute<float>& m_minAngularVelocity;
      XML::ValueAttribute<float>& m_maxAngularVelocity;
  };
}