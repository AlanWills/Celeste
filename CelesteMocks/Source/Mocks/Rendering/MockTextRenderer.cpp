#include "Mocks/Rendering/MockTextRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteMocks
{
  REGISTER_UNMANAGED_COMPONENT(MockTextRenderer, 10);

  MockTextRenderer::MockTextRenderer(GameObject& gameObject) :
    Inherited(gameObject)
  {
  }
}