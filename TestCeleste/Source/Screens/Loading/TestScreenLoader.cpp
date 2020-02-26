#include "UtilityHeaders/UnitTestHeaders.h"

#include "Screens/Loading/ScreenLoader.h"
#include "Screens/Screen.h"
#include "Resources/Screens/ScreenLoadingResources.h"
#include "tinyxml2.h"

#include "AutoDeallocator.h"
#include "AssertCel.h"
#include "FileAssert.h"

using namespace tinyxml2;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestScreenLoader)

#pragma region Load Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingNonExistentFilePath_ReturnsNullHandle)
  {
    AutoDeallocator<Screen> deallocator = ScreenLoader::load("WubbaLubba");

    Assert::IsNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentFullFilePath_ToInvalidXMLFile_ReturnsNullHandle)
  {
    Path path(TestResources::getTempDirectory(), "Test.xml");
    File file(path);
    file.append("");

    FileAssert::FileExists(path.as_string());

    AutoDeallocator<Screen> deallocator = ScreenLoader::load(path);

    Assert::IsNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentRelativeFilePath_ToInvalidXMLFile_ReturnsNullHandle)
  {
    Path path(TestResources::getTempDirectory(), "Test.xml");
    File file(path);
    file.append("");

    FileAssert::FileExists(path.as_string());

    AutoDeallocator<Screen> deallocator = ScreenLoader::load(Path("Temp", "Text.xml"));

    Assert::IsNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentFullFilePath_NoDocumentRoot_ReturnsNullHandle)
  {
    Path path(TestResources::getTempDirectory(), "Test.xml");
    XMLDocument document;
    document.SaveFile(path.c_str());

    FileAssert::FileExists(path.as_string());

    AutoDeallocator<Screen> deallocator = ScreenLoader::load(path);

    Assert::IsNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentRelativeFilePath_NoDocumentRoot_ReturnsNullHandle)
  {
    Path path(TestResources::getTempDirectory(), "Test.xml");
    XMLDocument document;
    document.SaveFile(path.c_str());

    FileAssert::FileExists(path.as_string());

    AutoDeallocator<Screen> deallocator = ScreenLoader::load(Path("Temp", "Text.xml"));

    Assert::IsNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentFullFilePath_DocumentRootHasNoChildElement_ReturnsNullHandle)
  {
    Path path(TestResources::getTempDirectory(), "Test.xml");
    XMLDocument document;
    document.NewElement("Root");
    document.SaveFile(path.c_str());

    FileAssert::FileExists(path.as_string());

    AutoDeallocator<Screen> deallocator = ScreenLoader::load(path);

    Assert::IsNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentRelativeFilePath_DocumentRootHasNoChildElement_ReturnsNullHandle)
  {
    Path path(TestResources::getTempDirectory(), "Test.xml");
    XMLDocument document;
    document.NewElement("Root");
    document.SaveFile(path.c_str());

    FileAssert::FileExists(path.as_string());

    AutoDeallocator<Screen> deallocator = ScreenLoader::load(Path("Temp", "Text.xml"));

    Assert::IsNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentFullFilePath_InvalidScreenData_ReturnsNullHandle)
  {
    AutoDeallocator<Screen> deallocator = ScreenLoader::load(ScreenLoadingResources::getEmptyFileFullPath());

    Assert::IsNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentRelativeFilePath_InvalidScreenData_ReturnsNullHandle)
  {
    AutoDeallocator<Screen> deallocator = ScreenLoader::load(ScreenLoadingResources::getEmptyFileRelativePath());

    Assert::IsNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentFullFilePath_ValidScreenData_ReturnsNewlyAllocatedScreen)
  {
    AutoDeallocator<Screen> deallocator = ScreenLoader::load(ScreenLoadingResources::getDataElementFullPath());

    Assert::IsNotNull(deallocator.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScreenLoader_Load_InputtingExistentRelativeFilePath_ValidScreenData_ReturnsNewlyAllocatedScreen)
  {
    AutoDeallocator<Screen> deallocator = ScreenLoader::load(ScreenLoadingResources::getDataElementRelativePath());

    Assert::IsNotNull(deallocator.get());
  }

#pragma endregion

  };
}