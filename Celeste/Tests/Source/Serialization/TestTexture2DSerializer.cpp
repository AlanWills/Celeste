#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Serialization/Serializers.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste::Serialization
{
  CELESTE_TEST_CLASS(TestTexture2DSerializer)

#pragma region Serialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DSerializer_Serialize_InputtingTexture2D_WithNoResourceIdSet_SetsOutputToEmptyString)
  {
    Texture2D texture;

    Assert::AreEqual(static_cast<StringId>(0), texture.getResourceId());

    std::string output;
    serialize<const Texture2D&>(texture, output);

    Assert::IsTrue(output.empty());

    output.append("Wubba");
    serialize<const Texture2D&>(texture, output);

    Assert::IsTrue(output.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DSerializer_Serialize_InputtingLoadedTexture2D_SetsOutputToFilePath)
  {
    observer_ptr<Texture2D> texture = getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath());

    Assert::AreEqual(internString(TestResources::getBlockPngFullPath().as_string()), texture->getResourceId());

    std::string output;
    serialize<const Texture2D&>(*texture, output);

    Assert::AreEqual(TestResources::getBlockPngFullPath().as_string(), output);

    output.append("Wubba");
    serialize<const Texture2D&>(*texture, output);

    Assert::AreEqual(TestResources::getBlockPngFullPath().as_string(), output);
  }

#pragma endregion

  };
}