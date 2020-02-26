#include "Mocks/Rendering/MockRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_SCRIPT(MockRenderer, 10);

  //------------------------------------------------------------------------------------------------
  MockRenderer::MockRenderer() :
    m_renderCalled(false)
  {
  }
}