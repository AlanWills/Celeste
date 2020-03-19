#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteTestUtils
{
  REGISTER_UNMANAGED_COMPONENT(MockSpriteRenderer, 10);

  //------------------------------------------------------------------------------------------------
  MockSpriteRenderer::MockSpriteRenderer(GameObject& gameObject) :
    Inherited(gameObject),
    m_renderCalled(false)
  {
  }
}