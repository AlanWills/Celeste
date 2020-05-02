#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/Data/MockData.h"
#include "TestResources/TestResources.h"
#include "TestUtils/Assert/FileAssert.h"


namespace TestCeleste
{
  namespace Resources
  {
    CELESTE_TEST_CLASS(TestData)

#pragma region Load From File Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_LoadFromFile_WithExistentNonXMLFilePath_ReturnsFalse)
    {
      MockData data;

      Assert::IsFalse(data.loadFromFile(TestResources::getArialTtfFullPath()));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_LoadFromFile_WithExistentXMLFilePath_ReturnsTrue)
    {
      MockData data;

      Assert::IsTrue(data.loadFromFile(TestResources::getDataXmlFullPath()));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_LoadFromFile_WithExistentXMLFilePath_LoadsXmlDocument)
    {
      MockData data;
      data.loadFromFile(TestResources::getDataXmlFullPath());

      Assert::IsNotNull(data.getDocumentRoot());
    }

#pragma endregion

#pragma region Unload Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_UnloadFromFile_WithNonLoadedData_SetsResourceIdToZero)
    {
      MockData data;
      data.loadFromFile(Path("ThisFileShouldntExist.xml"));

      Assert::AreEqual(static_cast<StringId>(0), data.getResourceId());

      data.unload();

      Assert::AreEqual(static_cast<StringId>(0), data.getResourceId());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_UnloadFromFile_WithLoadedData_SetsResourceIdToZero)
    {
      MockData data;
      data.loadFromFile(TestResources::getDataXmlFullPath());

      Assert::AreNotEqual(static_cast<StringId>(0), data.getResourceId());

      data.unload();

      Assert::AreEqual(static_cast<StringId>(0), data.getResourceId());
    }

#pragma endregion

#pragma region Save To File Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_SaveToFile_InputtingInvalidPath_ReturnsTrue)
    {
      MockData data;

      // Can't make this return false if path invalid  - don't know why tinyxml2 is set up like this
      Assert::IsTrue(data.saveToFile(Path("ThisFileShouldBeInvalid")));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_SaveToFile_InputtingValidPath_ReturnsTrue)
    {
      MockData data;

      Assert::IsTrue(data.saveToFile(Path(TempDirectory::getFullPath(), "TestData.xml")));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_SaveToFile_InputtingValidPath_FileDoesNotExist_CreatesCorrectXmlDocument)
    {
      MockData data;
      XMLDocument& document = data.getDocument();
      XMLElement* root = document.NewElement("Root");
      document.InsertFirstChild(root);
      XMLElement* firstChild = document.NewElement("Child1");
      root->InsertFirstChild(firstChild);
      XMLElement* secondChild = document.NewElement("Child2");
      root->InsertEndChild(secondChild);

      Path path(TempDirectory::getFullPath(), "TestData.xml");

      FileAssert::FileDoesNotExist(path);

      data.saveToFile(path);

      FileAssert::FileExists(path);

      XMLDocument loadedDocument;
      loadedDocument.LoadFile(path.as_string().c_str());

      // Check root
      Assert::AreEqual("Root", loadedDocument.RootElement()->Name());
      Assert::AreEqual("Child1", loadedDocument.RootElement()->FirstChildElement()->Name());
      Assert::AreEqual("Child2", loadedDocument.RootElement()->LastChildElement()->Name());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_SaveToFile_InputtingValidPath_FileExists_OverwritesPreviousDocument)
    {
      MockData data;
      XMLDocument& document = data.getDocument();
      XMLElement* root = document.NewElement("Root");
      document.InsertFirstChild(root);

      Path path(TempDirectory::getFullPath(), "TestData.xml");

      FileAssert::FileDoesNotExist(path);

      data.saveToFile(path);

      FileAssert::FileExists(path);

      XMLDocument loadedDocument;
      loadedDocument.LoadFile(path.as_string().c_str());

      // Check root
      Assert::AreEqual("Root", loadedDocument.RootElement()->Name());

      data.getDocumentRoot()->SetName("NewRoot");

      FileAssert::FileExists(path);

      data.saveToFile(path);
      loadedDocument.LoadFile(path.as_string().c_str());

      // Check root
      Assert::AreEqual("NewRoot", loadedDocument.RootElement()->Name());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_SaveToFile_InputtingInvalidPathString_ReturnsTrue)
    {
      MockData data;

      // Can't make this return false if path invalid - bug with tinyxml2
      Assert::IsTrue(data.saveToFile("ThisFileShouldBeInvalid"));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_SaveToFile_InputtingValidPathString_ReturnsTrue)
    {
      MockData data;
      Path path(TempDirectory::getFullPath(), "TestData.xml");
      const std::string& str = path.as_string();

      Assert::IsTrue(data.saveToFile(str));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_SaveToFile_InputtingValidPathString_FileDoesNotExist_CreatesCorrectXmlDocument)
    {
      MockData data;
      XMLDocument& document = data.getDocument();
      XMLElement* root = document.NewElement("Root");
      document.InsertFirstChild(root);
      XMLElement* firstChild = document.NewElement("Child1");
      root->InsertFirstChild(firstChild);
      XMLElement* secondChild = document.NewElement("Child2");
      root->InsertEndChild(secondChild);

      Path path(TempDirectory::getFullPath(), "TestData.xml");

      FileAssert::FileDoesNotExist(path);

      data.saveToFile(path.as_string());

      FileAssert::FileExists(path);

      XMLDocument loadedDocument;
      loadedDocument.LoadFile(path.as_string().c_str());

      // Check root
      Assert::AreEqual("Root", loadedDocument.RootElement()->Name());
      Assert::AreEqual("Child1", loadedDocument.RootElement()->FirstChildElement()->Name());
      Assert::AreEqual("Child2", loadedDocument.RootElement()->LastChildElement()->Name());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_SaveToFile_InputtingValidPathString_FileExists_OverwritesPreviousDocument)
    {
      MockData data;
      XMLDocument& document = data.getDocument();
      XMLElement* root = document.NewElement("Root");
      document.InsertFirstChild(root);

      Path path(TempDirectory::getFullPath(), "TestData.xml");

      FileAssert::FileDoesNotExist(path);

      data.saveToFile(path.as_string());

      FileAssert::FileExists(path);

      XMLDocument loadedDocument;
      loadedDocument.LoadFile(path.as_string().c_str());

      // Check root
      Assert::AreEqual("Root", loadedDocument.RootElement()->Name());

      data.getDocumentRoot()->SetName("NewRoot");

      FileAssert::FileExists(path);

      data.saveToFile(path.as_string());
      loadedDocument.LoadFile(path.as_string().c_str());

      // Check root
      Assert::AreEqual("NewRoot", loadedDocument.RootElement()->Name());
    }

#pragma endregion

#pragma region Overwrite File Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_OverwriteFile_DataNotLoadedFromFile_ReturnsTrueFalse)
    {
      MockData data;

      Assert::AreEqual((StringId)0, data.getResourceId());
      Assert::IsFalse(data.overwriteFile());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_OverwriteFile_DataLoadedFromFile_FileDoesNotExist_CreatesCorrectXmlDocument)
    {
      MockData data;

      File dataFile(Path(TempDirectory::getFullPath(), "Data.xml"));
      File(TestResources::getDataXmlFullPath()).copy(dataFile.getFilePath());

      Assert::IsTrue(dataFile.exists());

      data.loadFromFile(dataFile.getFilePath());
      dataFile.remove();

      Assert::IsFalse(dataFile.exists());

      data.overwriteFile();

      Assert::IsTrue(dataFile.exists());

      std::string expectedXML, actualXML;
      File(TestResources::getDataXmlFullPath()).read(expectedXML);
      dataFile.read(actualXML);

      // Remove white space because it causes problems where there are none
      expectedXML.erase(std::remove_if(expectedXML.begin(), expectedXML.end(), [](char c)-> bool { return std::isspace(c); }), expectedXML.end());
      actualXML.erase(std::remove_if(actualXML.begin(), actualXML.end(), [](char c)-> bool { return std::isspace(c); }), actualXML.end());

      Assert::AreEqual(expectedXML, actualXML);
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_OverwriteFile_DataLoadedFromFile_FileExists_OverwritesPreviousDocument)
    {
      MockData data;

      File dataFile(Path(TempDirectory::getFullPath(), "Data.xml"));
      File(TestResources::getDataXmlFullPath()).copy(dataFile.getFilePath());

      Assert::IsTrue(dataFile.exists());

      data.loadFromFile(dataFile.getFilePath());
      data.getDocumentRoot()->DeleteChildren();
      data.overwriteFile();

      Assert::IsTrue(dataFile.exists());

      std::string expectedXML = "<Root/>", actualXML;
      dataFile.read(actualXML);

      // Remove white space because it causes problems where there are none
      expectedXML.erase(std::remove_if(expectedXML.begin(), expectedXML.end(), [](char c)-> bool { return std::isspace(c); }), expectedXML.end());
      actualXML.erase(std::remove_if(actualXML.begin(), actualXML.end(), [](char c)-> bool { return std::isspace(c); }), actualXML.end());

      Assert::AreEqual(expectedXML, actualXML);
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_OverwriteFile_DataLoadedFromFile_ReturnsTrue)
    {
      MockData data;

      File dataFile(Path(TempDirectory::getFullPath(), "Data.xml"));
      File(TestResources::getDataXmlFullPath()).copy(dataFile.getFilePath());

      Assert::IsTrue(dataFile.exists());

      data.loadFromFile(dataFile.getFilePath());

      Assert::IsTrue(data.overwriteFile());
    }

#pragma endregion

#pragma region Get Element Data Tests (String Template)

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementData_StringTemplate_ThatDoesntExist_ReturnskDoesNotExist_AndLeavesOutputUnchanged)
    {
      MockData data;
      data.loadFromFile(TestResources::getDataXmlFullPath());

      std::string text;

      Assert::IsTrue(data.getElementData("ThisNodeNameDoesntExist", text) == XML::XMLValueError::kDoesNotExist);
      Assert::IsTrue(text.empty());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementData_StringTemplate_ThatDoesExist_ReturnsElementText)
    {
      MockData data;
      data.loadFromFile(TestResources::getDataXmlFullPath());

      std::string text;
      data.getElementData("BackgroundRelativeFilePath", text);

      Assert::IsFalse(text.empty());
      Assert::AreEqual("Backgrounds\\RainbowNebula.png", text.c_str());
    }

#pragma endregion

#pragma region Get Element Data As Tests (Float Template)

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementData_FloatTemplate_ThatDoesntExist_ReturnsZero)
    {
      MockData data;
      data.loadFromFile(TestResources::getDataXmlFullPath());

      float value = 0;
      data.getElementData("ThisNodeNameDoesntExist", value);

      Assert::AreEqual(0.0f, value);
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementData_FloatTemplate_ThatDoesExist_ReturnsElementValue)
    {
      MockData data;
      data.loadFromFile(TestResources::getDataXmlFullPath());

      float value = 0;
      data.getElementData("HugeAsteroidCount", value);

      Assert::AreEqual(3.0f, value);
    }

#pragma endregion

#pragma region Get Element Data As Vector Tests (String Template)

    /*
      ElementDataAsVectorString.xml contents

      <?xml version="1.0" encoding="utf-8"?>
      <Root>
        <Vector>
          <Item>12.1</Item>
          <Item>true</Item>
          <Item>"1"</Item>
          <Item>hello</Item>
          <Item/>
          <Item>    </Item>
        </Vector>
      </Root>
    */

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementDataAsVector_StringTemplate_ElementIsNullptr_ReturnskError_AndDoesNotModifyList)
    {
      MockData data;
      std::vector<std::string> output;

      Assert::IsNull(data.getDocumentRoot());
      Assert::IsTrue(data.getElementDataAsVector("Element", "Item", output) == XML::XMLValueError::kError);
      Assert::IsTrue(output.empty());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementDataAsVector_StringTemplate_InputtingElementNameThatDoesExist_ReturnskDoesNotExist_AndDoesNotModifyList)
    {
      MockData data;
      XMLElement* element = data.getDocument().NewElement("Test");
      data.getDocument().InsertFirstChild(element);
      std::vector<std::string> output;

      Assert::IsNotNull(data.getDocumentRoot());
      Assert::IsTrue(data.getElementDataAsVector("WubbaLubbaDubDub", "Item", output) == XML::XMLValueError::kDoesNotExist);
      Assert::IsTrue(output.empty());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementDataAsVector_StringTemplate_InputtingExistentElementNameWithNoMatchingItemElements_ReturnskDoesNotExist_AndDoesNotModifyList)
    {
      MockData data;
      data.loadFromFile(TestResources::getElementDataAsVectorStringFullPath());
      std::vector<std::string> output;

      Assert::IsNotNull(data.getDocumentRoot());
      Assert::IsTrue(data.getElementDataAsVector("Vector", "RickyTickyTappy", output) == XML::XMLValueError::kDoesNotExist);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetChildElementDataAsVector_FloatTemplate_InputtingExistentElementNameWithMatchingItemElements_ReturnskSuccess_AndAddsAllChildrenWhichAreConvertibleToStrings)
    {
      MockData data;
      data.loadFromFile(TestResources::getElementDataAsVectorStringFullPath());
      std::vector<std::string> output;

      Assert::IsNotNull(data.getDocumentRoot());
      Assert::IsTrue(data.getElementDataAsVector("Vector", "Item", output) == XML::XMLValueError::kSuccess);
      Assert::AreEqual((size_t)4, output.size());
      Assert::AreEqual("12.1", output[0].c_str());
      Assert::AreEqual("true", output[1].c_str());
      Assert::AreEqual("\"1\"", output[2].c_str());
      Assert::AreEqual("hello", output[3].c_str());
    }

#pragma endregion

#pragma region Get Element Data As Vector Tests (Float Template)

    /*
      ElementDataAsVectorFloat.xml contents

      <?xml version="1.0" encoding="utf-8"?>
      <Root>
        <Vector>
          <Item>12.1</Item>
          <Item>1.212311</Item>
          <Item>"1"</Item>
          <Item>hello</Item>
          <Item/>
          <Item>    </Item>
        </Vector>
      </Root>
    */

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementDataAsVector_FloatTemplate_ElementIsNullptr_ReturnskError_AndDoesNotModifyList)
    {
      MockData data;
      std::vector<float> output;

      Assert::IsNull(data.getDocumentRoot());
      Assert::IsTrue(data.getElementDataAsVector("Element", "Item", output) == XML::XMLValueError::kError);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementDataAsVector_FloatTemplate_InputtingElementNameThatDoesntExist_ReturnskDoesNotExist_AndDoesNotModifyList)
    {
      MockData data;
      XMLElement* element = data.getDocument().NewElement("Test");
      data.getDocument().InsertFirstChild(element);
      std::vector<float> output;

      Assert::IsNotNull(data.getDocumentRoot());
      Assert::IsTrue(data.getElementDataAsVector("WubbaLubbaDubDub", "Item", output) == XML::XMLValueError::kDoesNotExist);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetElementDataAsVector_FloatTemplate_InputtingExistentElementNameWithNoMatchingItemElements_ReturnskDoesNotExist_AndDoesNotModifyList)
    {
      MockData data;
      data.loadFromFile(TestResources::getElementDataAsVectorFloatFullPath());
      std::vector<float> output;

      Assert::IsNotNull(data.getDocumentRoot());
      Assert::IsTrue(data.getElementDataAsVector("Vector", "RickyTickyTappy", output) == XML::XMLValueError::kDoesNotExist);
      Assert::IsTrue(output.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetChildElementDataAsVector_FloatTemplate_InputtingExistentElementNameWithMatchingItemElements_ReturnskSuccess_AndAddsCorrectValues)
    {
      MockData data;
      data.loadFromFile(TestResources::getElementDataAsVectorFloatFullPath());
      std::vector<float> output;

      Assert::IsNotNull(data.getDocumentRoot());
      Assert::IsTrue(data.getElementDataAsVector("Vector", "Item", output) == XML::XMLValueError::kSuccess);
      Assert::AreEqual((size_t)2, output.size());
      Assert::AreEqual(12.1f, output[0]);
      Assert::AreEqual(1.212311f, output[1]);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Data_GetChildElementDataAsVector_FloatTemplate_InputtingExistentElementNameWithMatchingItemElements_InvalidElements_ReturnskError)
    {
      MockData data;
      data.loadFromFile(TestResources::getElementDataAsVectorFloatFullPath());
      XMLElement* element = data.getDocument().NewElement("Item");
      element->SetText("Fail");
      data.getDocumentRoot()->FirstChildElement("Vector")->InsertEndChild(element);
      std::vector<float> output;

      Assert::IsNotNull(data.getDocumentRoot());
      Assert::IsTrue(data.getElementDataAsVector("Vector", "Item", output) == XML::XMLValueError::kError);
    }

#pragma endregion
    };
  }
}