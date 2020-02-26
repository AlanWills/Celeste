#include "UtilityHeaders/UnitTestHeaders.h"

#include "Callbacks/TransitionToScreen.h"
#include "Resources/Screens/ScreenLoadingResources.h"
#include "Screens/Screen.h"
#include "Screens/ScreenManager.h"
#include "DataConverters/Screens/ScreenDataConverter.h"
#include "Resources/ResourceManager.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestTransitionToScreen)

#pragma region Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransitionToScreen_Operator_InputtingGameObjectWithNullOwnerScreen_DoesNothing)
  {
    GAMEOBJECT(gameObject);

    Assert::IsNull(gameObject.getScreen());

    TransitionToScreen callback;
    Path path(UPDIR_STRING, ScreenLoadingResources::getEmptyFileRelativePath());
    
    AssertCel::FileExists(Path(TestResources::getDataDirectory().as_string(), path.as_string()));

    // Check does not throw - need relative path from data resources directory
    callback(gameObject, path.as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransitionToScreen_Operator_InputtingEmptyArgument_DoesNothing)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

    Assert::IsTrue(screen.get() == gameObject->getScreen());

    TransitionToScreen callback;

    // Check does not throw
    callback(*gameObject, "");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransitionToScreen_Operator_InputtingArgumentWhichCreatesNonExistentScreenFilePath_DoesNothing)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

    Assert::IsTrue(screen.get() == gameObject->getScreen());

    TransitionToScreen callback;
    Path path("WubbaLubbaDubDub.xml");

    AssertCel::FileDoesNotExist(Path(TestResources::getResourcesDirectory().as_string(), path.as_string()));

    // Check does not throw
    callback(*gameObject, path.as_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TransitionToScreen_Operator_KillsOwnerScreen_AndLoadsNewScreen)
  {
    AutoDeallocator<Screen> screen = Screen::allocate();
    AutoDeallocator<GameObject> gameObject = screen->allocateGameObject();

    Assert::IsTrue(screen.get() == gameObject->getScreen());

    TransitionToScreen callback;
    std::string path = ScreenLoadingResources::getGameObjectsElementRelativePath();
    ScreenDataConverter converter("Screen");

    Assert::IsTrue(converter.convertFromXML(getResourceManager().load<Data>(path)->getDocumentRoot()));
    AssertCel::FileExists(Path(TestResources::getResourcesDirectory().as_string(), path));

    callback(*gameObject, path);

    AssertCel::IsNotAlive(screen.get());

    AutoDeallocator<Screen> createdScreen = getScreenManager().findScreen(converter.getName());

    Assert::IsNotNull(createdScreen.get());
  }

#pragma endregion

  };
}