#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Physics/RigidBody2D.h"
#include "Objects/Script.h"


namespace CelesteTestUtils
{
  class MockRigidBody2D : public Celeste::Physics::RigidBody2D
  {
    DECLARE_UNMANAGED_COMPONENT(MockRigidBody2D, CelesteTestUtilsDllExport)
  };
}