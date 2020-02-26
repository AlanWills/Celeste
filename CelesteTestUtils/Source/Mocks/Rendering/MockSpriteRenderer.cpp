#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_SCRIPT(MockSpriteRenderer, 10);

  //------------------------------------------------------------------------------------------------
  MockSpriteRenderer::MockSpriteRenderer() :
    m_renderCalled(false)
  {
  }
}