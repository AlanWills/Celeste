#include "DataConverters/Input/KeyboardRigidBody2DControllerDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Input/KeyboardRigidBody2DController.h"


namespace Celeste
{
  REGISTER_COMPONENT_DATA_CONVERTER(KeyboardRigidBody2DControllerDataConverter)

  const char* const KeyboardRigidBody2DControllerDataConverter::DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME("decrease_x_linear_velocity_key");
  const char* const KeyboardRigidBody2DControllerDataConverter::INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME("increase_x_linear_velocity_key");
  const char* const KeyboardRigidBody2DControllerDataConverter::DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME("decrease_y_linear_velocity_key");
  const char* const KeyboardRigidBody2DControllerDataConverter::INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME("increase_y_linear_velocity_key");
  const char* const KeyboardRigidBody2DControllerDataConverter::DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME("decrease_angular_velocity_key");
  const char* const KeyboardRigidBody2DControllerDataConverter::INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME("increase_angular_velocity_key");
  const char* const KeyboardRigidBody2DControllerDataConverter::LINEAR_VELOCITY_DELTA_ATTRIBUTE_NAME("linear_velocity_delta");
  const char* const KeyboardRigidBody2DControllerDataConverter::ANGULAR_VELOCITY_DELTA_ATTRIBUTE_NAME("angular_velocity_delta");
  const char* const KeyboardRigidBody2DControllerDataConverter::SPACE_ATTRIBUTE_NAME("space");
  const char* const KeyboardRigidBody2DControllerDataConverter::INCREMENT_MODE_ATTRIBUTE_NAME("increment_mode");

  //------------------------------------------------------------------------------------------------
  KeyboardRigidBody2DControllerDataConverter::KeyboardRigidBody2DControllerDataConverter() :
    Inherited(Input::KeyboardRigidBody2DController::type_name()),
    m_decreaseXLinearVelocityKey(createValueAttribute<Input::Key>(DECREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME)),
    m_increaseXLinearVelocityKey(createValueAttribute<Input::Key>(INCREASE_X_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME)),
    m_decreaseYLinearVelocityKey(createValueAttribute<Input::Key>(DECREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME)),
    m_increaseYLinearVelocityKey(createValueAttribute<Input::Key>(INCREASE_Y_LINEAR_VELOCITY_KEY_ATTRIBUTE_NAME)),
    m_decreaseAngularVelocityKey(createValueAttribute<Input::Key>(DECREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME)),
    m_increaseAngularVelocityKey(createValueAttribute<Input::Key>(INCREASE_ANGULAR_VELOCITY_KEY_ATTRIBUTE_NAME)),
    m_linearVelocityDelta(createReferenceAttribute<glm::vec2>(LINEAR_VELOCITY_DELTA_ATTRIBUTE_NAME)),
    m_angularVelocityDelta(createValueAttribute<float>(ANGULAR_VELOCITY_DELTA_ATTRIBUTE_NAME)),
    m_space(createValueAttribute<Maths::Space>(SPACE_ATTRIBUTE_NAME, Maths::Space::kLocal)),
    m_incrementMode(createValueAttribute<Input::IncrementMode>(INCREMENT_MODE_ATTRIBUTE_NAME, Input::IncrementMode::kContinuous))
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardRigidBody2DControllerDataConverter::doSetValues(Input::KeyboardRigidBody2DController& controller) const
  {
    controller.setDecreaseXLinearVelocityKey(getDecreaseXLinearVelocityKey());
    controller.setIncreaseXLinearVelocityKey(getIncreaseXLinearVelocityKey());
    controller.setDecreaseYLinearVelocityKey(getDecreaseYLinearVelocityKey());
    controller.setIncreaseYLinearVelocityKey(getIncreaseYLinearVelocityKey());
    controller.setDecreaseAngularVelocityKey(getDecreaseAngularVelocityKey());
    controller.setIncreaseAngularVelocityKey(getIncreaseAngularVelocityKey());
    controller.setLinearVelocityDelta(getLinearVelocityDelta());
    controller.setAngularVelocityDelta(getAngularVelocityDelta());
    controller.setSpace(getSpace());
    controller.setIncrementMode(getIncrementMode());
  }
}