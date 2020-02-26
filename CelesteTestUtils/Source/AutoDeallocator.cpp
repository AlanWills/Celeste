#include "AutoDeallocator.h"
#include "Objects/Component.h"
#include "Objects/GameObject.h"


namespace CelesteTestUtils
{
  //------------------------------------------------------------------------------------------------
  AutoDeallocator<Celeste::Component>::~AutoDeallocator()
  {
    if (m_object != nullptr)
    {
      m_object->deallocate();
    }
  }

  //------------------------------------------------------------------------------------------------
  AutoDeallocator<Celeste::GameObject>::~AutoDeallocator()
  {
    if (m_object != nullptr)
    {
      m_object->deallocate();
    }
  }
}