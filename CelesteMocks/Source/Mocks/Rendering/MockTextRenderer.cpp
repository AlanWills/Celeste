#include "Mocks/Rendering/MockTextRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"


namespace CelesteMocks
{
  REGISTER_COMPONENT(MockTextRenderer, 10);

  MockTextRenderer::MockTextRenderer(GameObject& gameObject) :
    Inherited(gameObject)
  {
  }
}