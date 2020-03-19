#include "Mocks/Rendering/MockRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_UNMANAGED_COMPONENT(MockRenderer, 10);

  //------------------------------------------------------------------------------------------------
  MockRenderer::MockRenderer(GameObject& gameObject) :
    Inherited(gameObject),
    m_renderCalled(false)
  {
  }
}