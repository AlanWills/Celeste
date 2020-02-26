#pragma once

#include "Mocks/Objects/MockGameObject.h"
#include "AutoKiller.h"
#include "AutoDeallocator.h"


namespace CelesteTestUtils
{
  #define GAMEOBJECT(Name) \
      Celeste::GameObject Name; \
      CelesteTestUtils::AutoKiller<Celeste::GameObject> Name##AutoKiller = \
        CelesteTestUtils::AutoKiller<Celeste::GameObject>(&Name);
}