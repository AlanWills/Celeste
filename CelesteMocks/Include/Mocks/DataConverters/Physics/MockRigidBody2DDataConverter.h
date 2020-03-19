#pragma once

#include "DataConverters/Physics/RigidBody2DDataConverter.h"


namespace CelesteTestUtils
{
  class MockRigidBody2DDataConverter : public Celeste::RigidBody2DDataConverter
  {
    public:
      MockRigidBody2DDataConverter() = default;
  };
}