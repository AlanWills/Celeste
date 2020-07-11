#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "XML/Attributes/DataAttribute.h"
#include "Input/Key.h"
#include "Deserialization/InputDeserializers.h"
#include "Deserialization/MathsDeserializers.h"


namespace Celeste::Input
{
  class KeyboardRigidBody2DController;
}

namespace Celeste
{
  class KeyboardRigidBody2DControllerDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(KeyboardRigidBody2DControllerDataConverter, Input::KeyboardRigidBody2DController, CelesteDllExport)

    public:
      inline int getDecreaseXLinearVelocityKey() const { return m_decreaseXLinearVelocityKey.getValue().m_key; }
      inline int getIncreaseXLinearVelocityKey() const { return m_increaseXLinearVelocityKey.getValue().m_key; }
      inline int getDecreaseYLinearVelocityKey() const { return m_decreaseYLinearVelocityKey.getValue().m_key; }
      inline int getIncreaseYLinearVelocityKey() const { return m_increaseYLinearVelocityKey.getValue().m_key; }
      inline int getDecreaseAngularVelocityKey() const { return m_decreaseAngularVelocityKey.getValue().m_key; }
      inline int getIncreaseAngularVelocityKey() const { return m_increaseAngularVelocityKey.getValue().m_key; }
      inline const glm::vec2& getLinearVelocityDelta() const { return m_linearVelocityDelta.getValue(); }
      inline float getAngularVelocityDelta() const { return m_angularVelocityDelta.getValue(); }
      inline Maths::Space getSpace() const { return m_space.getValue(); }
      inline Input::IncrementMode getIncrementMode() const { return m_incrementMode.getValue(); }

      CelesteDllExport static const char* const DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const LINEAR_VELOCITY_DELTA_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const ANGULAR_VELOCITY_DELTA_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const SPACE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const INCREMENT_MODE_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ValueAttribute<Input::Key>& m_decreaseXLinearVelocityKey;
      XML::ValueAttribute<Input::Key>& m_increaseXLinearVelocityKey;
      XML::ValueAttribute<Input::Key>& m_decreaseYLinearVelocityKey;
      XML::ValueAttribute<Input::Key>& m_increaseYLinearVelocityKey;
      XML::ValueAttribute<Input::Key>& m_decreaseAngularVelocityKey;
      XML::ValueAttribute<Input::Key>& m_increaseAngularVelocityKey;

      XML::ReferenceAttribute<glm::vec2>& m_linearVelocityDelta;
      XML::ValueAttribute<float>& m_angularVelocityDelta;

      XML::ValueAttribute<Maths::Space>& m_space;
      XML::ValueAttribute<Input::IncrementMode>& m_incrementMode;
  };
}