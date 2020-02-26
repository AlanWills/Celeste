#include "UtilityHeaders/UnitTestHeaders.h"

#include "SOIL/SOIL.h"
#include "Resources/2D/RawImageLoader.h"
#include "Resources/TestResources.h"

using namespace Celeste::Resources;


namespace TestCeleste
{
  namespace Resources
  {
    CELESTE_TEST_CLASS(TestRawImageLoader)

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Constructor_WithNonExistentFilePath_DoesNothing)
    {
      RawImageLoader loader(Path("ThisPathShouldn'tExist.png"));

      Assert::IsNull(loader.getData());
      Assert::AreEqual(0, loader.getWidth());
      Assert::AreEqual(0, loader.getHeight());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Constructor_WithExistentFilePath_SuccessfullyLoadsImage)
    {
      int width = 0, height = 0;
      unsigned char* data = SOIL_load_image(TestResources::getBlockPngFullPath().c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
      SOIL_free_image_data(data);

      RawImageLoader loader(TestResources::getBlockPngFullPath());

      Assert::IsNotNull(loader.getData());
      Assert::AreEqual(width, loader.getWidth());
      Assert::AreEqual(height, loader.getHeight());
    }

    // No way of testing destructor works - we cannot tell that memory is freed
    };
  }
}