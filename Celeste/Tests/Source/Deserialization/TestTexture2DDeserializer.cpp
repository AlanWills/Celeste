#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/Deserializers.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"

#include "CelesteTestUtils/Assert/AssertCel.h"
#include "TestUtils/Assert/FileAssert.h"

using namespace Celeste::Resources;


namespace TestCeleste::Deserialization
{
  CELESTE_TEST_CLASS(TestTexture2DDeserializer)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DDeserializer_Deserialize_InputtingEmptyString_SetsOutputToNullptr)
  {
    Texture2D texture;
    Texture2D* texturePtr = &texture;

    Assert::IsNotNull(texturePtr);

    deserialize("", texturePtr);

    Assert::IsNull(texturePtr);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DDeserializer_Deserialize_InputtingNonEmptyString_FileDoesNotExist_SetsOutputToNullptr)
  {
    Texture2D texture;
    Texture2D* texturePtr = &texture;

    Assert::IsNotNull(texturePtr);
    FileAssert::FileDoesNotExist("WubbaLubbaDubDub.txt");

    deserialize("WubbaLubbaDubDub.txt", texturePtr);

    Assert::IsNull(texturePtr);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DDeserializer_Deserialize_InputtingNonEmptyString_FileExists_IsNotTexture_SetsOutputToNullptr)
  {
    Texture2D texture;
    Texture2D* texturePtr = &texture;

    Assert::IsNotNull(texturePtr);
    FileAssert::FileExists(TestResources::getButtonHoverWavFullPath().as_string());

    deserialize(TestResources::getButtonHoverWavFullPath().as_string(), texturePtr);

    Assert::IsNull(texturePtr);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DDeserializer_Deserialize_InputtingNonEmptyString_FileExists_IsTexture_SetsOutputToCorrectTexture)
  {
    Texture2D texture;
    Texture2D* texturePtr = &texture;

    Assert::IsNotNull(texturePtr);
    FileAssert::FileExists(TestResources::getBlockPngFullPath().as_string());

    deserialize(TestResources::getBlockPngFullPath().as_string(), texturePtr);

    Assert::AreNotEqual(&texture, texturePtr);
    Assert::AreEqual(getResourceManager().load<Texture2D>(TestResources::getBlockPngFullPath()), texturePtr);

    texturePtr = nullptr;

    Assert::IsNull(texturePtr);
    FileAssert::FileExists(Path(TestResources::getResourcesDirectory(), TestResources::getBlockPngRelativePath()).as_string());

    deserialize(TestResources::getBlockPngRelativePath(), texturePtr);

    Assert::IsNotNull(texturePtr);
    Assert::AreEqual(getResourceManager().load<Texture2D>(TestResources::getBlockPngRelativePath()), texturePtr);
  }

#pragma endregion

  };
}