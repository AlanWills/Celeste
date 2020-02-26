#pragma once

#include "CelesteTestUtilsDllExport.h"
#include "Physics/EllipseCollider.h"
#include "Objects/Script.h"


namespace CelesteTestUtils
{
  class MockEllipseCollider : public Celeste::Physics::EllipseCollider
  {
    DECLARE_SCRIPT(MockEllipseCollider, CelesteTestUtilsDllExport)
  };
}