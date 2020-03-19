#pragma once

#include "DataConverters/Input/KeyboardRigidBody2DControllerDataConverter.h"


namespace CelesteMocks
{
  class MockKeyboardRigidBody2DControllerDataConverter : public Celeste::KeyboardRigidBody2DControllerDataConverter
  {
    public:
      MockKeyboardRigidBody2DControllerDataConverter() = default;
  };
}