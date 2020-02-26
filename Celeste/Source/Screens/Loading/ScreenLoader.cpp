#include "Screens/Loading/ScreenLoader.h"
#include "DataConverters/Screens/ScreenDataConverter.h"
#include "DataConverters/Objects/GameObjectDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Resources/ResourceManager.h"
#include "Screens/Screen.h"
#include "Screens/ScreenUtils.h"

using namespace Celeste::Resources;


namespace Celeste::ScreenLoader
{
  //------------------------------------------------------------------------------------------------
  observer_ptr<Screen> load(const Path& relativePathToLevelFile)
  {
    observer_ptr<Data> data = getResourceManager().load<Data>(relativePathToLevelFile);
    if (data == nullptr)
    {
      ASSERT_FAIL();
      return observer_ptr<Screen>();
    }

    const XMLElement* documentRoot = data->getDocumentRoot();
    if (documentRoot == nullptr)
    {
      ASSERT_FAIL();
      return observer_ptr<Screen>();
    }

    ScreenDataConverter screenData(documentRoot->Name());
    if (!screenData.convertFromXML(documentRoot))
    {
      ASSERT_FAIL();
      return observer_ptr<Screen>();
    }

    observer_ptr<Screen> screen = Screen::allocate();
    screenData.setValues(*screen);

    return screen;
  }
}