#include "UtilityHeaders/UnitTestHeaders.h"

#include "TestResources/TestResources.h"
#include "FileSystem/File.h"
#include "AssertCel.h"
#include "FileAssert.h"
#include "AssertSpecialization/FileSystem.h"
#include "AssertExt.h"

#include <fstream>


namespace TestCeleste
{
  static Path parentDirectory = Path(Directory::getExecutingAppDirectory());
  static std::string testFileName = "TestFile.txt";
  static Path testFilePath = Path(Directory::getExecutingAppDirectory(), testFileName);

  CELESTE_TEST_CLASS(TestFile)

    //------------------------------------------------------------------------------------------------
    void checkTestFileExists()
    {
      struct stat buf;
      Assert::AreNotEqual(-1, stat(testFilePath.c_str(), &buf));
    }

    //------------------------------------------------------------------------------------------------
    void writeToTestFile(const std::string& output)
    {
      std::ofstream fStream(testFilePath.as_string());
      Assert::IsTrue(fStream.good());

      // Write something to the file
      fStream << output;
      fStream.close();
    }

    //------------------------------------------------------------------------------------------------
    void checkTestFileContents(const std::string& expected)
    {
      FileAssert::FileContentsEqual(testFilePath.as_string(), expected);
    }

    //------------------------------------------------------------------------------------------------
    void TestFile::testInitialize() override
    {
      // Remove our test file so that we have a fresh file for each test
      std::remove(testFilePath.c_str());
    }

    //------------------------------------------------------------------------------------------------
    void TestFile::testCleanup() override
    {
      // Remove our test file so that we have a fresh file for each test
      std::remove(testFilePath.c_str());
    }

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Constructor_String)
    {
      File file(testFilePath.as_string());

      Assert::AreEqual(testFilePath.as_string(), file.getFilePath().as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Constructor_Path)
    {
      File file(testFilePath);

      Assert::AreEqual(testFilePath, file.getFilePath());
    }

#pragma endregion

#pragma region Copy Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_CopyConstructor)
    {
      File file(testFilePath);
      File copy(file);

      Assert::AreEqual(file.getFilePath(), copy.getFilePath());
    }

#pragma endregion

#pragma region Assignment Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_AssignmentOperator)
    {
      File file(testFilePath);
      File copy = file;

      Assert::AreEqual(file.getFilePath(), copy.getFilePath());

      // Now check with a file object which has already been assigned to
      Path newPath(testFilePath, "Another.txt");
      File fileReassignment(newPath);
      fileReassignment = file;

      Assert::AreEqual(file.getFilePath(), fileReassignment.getFilePath());
    }

#pragma endregion

#pragma region Equality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_EqualityOperator_ShouldReturnTrue)
    {
      File file(testFilePath);
      File copy(testFilePath);

      Assert::IsTrue(file == copy);

      File roundaboutCopy(Path(parentDirectory, "Another", UPDIR_STRING, testFileName));

      Assert::IsTrue(file == roundaboutCopy);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_EqualityOperator_ShouldReturnFalse)
    {
      File file(testFilePath);
      File different(Path(parentDirectory, "Different.txt"));

      Assert::IsFalse(file == different);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_EqualityOperator_CompareWithSelf_ShouldReturnTrue)
    {
      File file(testFilePath);

      // Reflexivity
      Assert::IsTrue(file == file);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_EqualityOperator_IsSymmetric)
    {
      File file(testFilePath);
      File copy(testFilePath);

      // Symmetric
      Assert::IsTrue(file == copy);
      Assert::IsTrue(copy == file);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_EqualityOperator_IsTransitive)
    {
      File file(testFilePath);
      File copy(testFilePath);
      File anotherCopy(Path(parentDirectory, "Another", UPDIR_STRING, testFileName));

      // Transitivity - file == copy and file == anotherCopy => copy == anotherCopy
      Assert::IsTrue(file == anotherCopy);
      Assert::IsTrue(copy == anotherCopy);
    }

#pragma endregion

#pragma region Exists Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Exists_ShouldReturnTrue)
    {
      File file(testFilePath);

      // Write something just to create the file
      writeToTestFile("");
      
      Assert::IsTrue(file.exists());
      Assert::IsTrue(File::exists(testFilePath));
      Assert::IsTrue(File::exists(testFilePath.as_string()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Exists_ShouldReturnFalse)
    {
      File file(testFilePath);

      Assert::IsFalse(file.exists());
      Assert::IsFalse(File::exists(testFilePath));
      Assert::IsFalse(File::exists(testFilePath.as_string()));
      Assert::IsFalse(File::exists(TestResources::getResourcesDirectory()));
    }

#pragma endregion

#pragma region Create Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Create_FileThatDoesntExist)
    {
      File file(testFilePath);
      file.create();

      Assert::IsTrue(file.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Create_FileThatAlreadyExists)
    {
      File file(testFilePath);
      file.create();

      Assert::IsTrue(file.exists());

      file.create();

      Assert::IsTrue(file.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Create_ClearsFileOnCreation)
    {
      File file(testFilePath);
      std::string expected("TestString");

      // Write something just to create the file
      {
        file.create();
        Assert::IsTrue(file.exists());

        writeToTestFile(expected);
        checkTestFileContents(expected);
      }

      // Now recreate the file, but don't clear it and check the contents is the same
      {
      file.create(false);
      Assert::IsTrue(file.exists());

      checkTestFileContents(expected);
      }

      // Now recreate the file, but clear it and check it is now empty
      {
        file.create();
        Assert::IsTrue(file.exists());

        checkTestFileContents("");
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Create_CreatesParentDirectory)
    {
      Path parent(TestResources::getTempDirectory(), "Nested");
      Path filePath(parent, "Text.txt");
      File file(filePath);

      Assert::IsFalse(Directory::exists(parent));

      file.create();

      Assert::IsTrue(file.exists());
      Assert::IsTrue(Directory::exists(parent));
    }

#pragma endregion

#pragma region Copy Tests

#pragma region Copy String Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Copy_StringInput_SourceFileDoesNotExist_DoesNothing)
    {
      File file(Path(TestResources::getTempDirectory(), "WubbaLubbaDubDub"));

      Assert::IsFalse(file.exists());

      Path dest(TestResources::getTempDirectory(), "Test.txt");
      file.copy(dest.as_string());

      AssertCel::FileDoesNotExist(dest);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Copy_StringInput_DestinationFilePathIsInvalid_DoesNothing)
    {
      File file(TestResources::getDataXmlFullPath());
      std::string fileContents;
      file.read(fileContents);

      Assert::IsTrue(file.exists());

      Path dest(TestResources::getTempDirectory(), "WubbaLubba<<!_$DubDub");
      file.copy(dest.as_string());

      AssertCel::FileDoesNotExist(dest);

      std::string newFileContents;
      file.read(newFileContents);

      Assert::AreEqual(fileContents, newFileContents);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Copy_StringInput_WithFilePathThatDoesNotExist_CreatesFileWithSameContents)
    {
      File file(TestResources::getDataXmlFullPath());
      std::string fileContents;
      file.read(fileContents);

      Assert::IsTrue(file.exists());

      Path dest(TestResources::getTempDirectory(), "Test.txt");
      file.copy(dest.as_string());

      AssertCel::FileExists(dest);

      std::string copyFileContents;
      File(dest).read(copyFileContents);

      Assert::AreEqual(fileContents, copyFileContents);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Copy_StringInput_WithFilePathThatDoesExist_DoesNothing)
    {
      File file(TestResources::getDataXmlFullPath());

      Assert::IsTrue(file.exists());

      File dest(TestResources::getBlockPngFullPath());
      std::string destContents;
      dest.read(destContents);
      file.copy(dest.getFilePath().as_string());

      Assert::IsTrue(dest.exists());

      std::string newDestContents;
      dest.read(newDestContents);

      Assert::AreEqual(destContents, newDestContents);
    }

#pragma endregion

#pragma region Copy Path Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Copy_PathInput_SourceFileDoesNotExist_DoesNothing)
    {
      File file(Path(TestResources::getTempDirectory(), "WubbaLubbaDubDub"));

      Assert::IsFalse(file.exists());

      Path dest(TestResources::getTempDirectory(), "Test.txt");
      file.copy(dest);

      AssertCel::FileDoesNotExist(dest);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Copy_PathInput_DestinationFilePathIsInvalid_DoesNothing)
    {
      File file(TestResources::getDataXmlFullPath());
      std::string fileContents;
      file.read(fileContents);

      Assert::IsTrue(file.exists());

      Path dest(TestResources::getTempDirectory(), "WubbaLubba<<!_$DubDub");
      file.copy(dest);

      AssertCel::FileDoesNotExist(dest);

      std::string newFileContents;
      file.read(newFileContents);

      Assert::AreEqual(fileContents, newFileContents);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Copy_PathInput_WithFilePathThatDoesNotExist_CreatesFileWithSameContents)
    {
      File file(TestResources::getDataXmlFullPath());
      std::string fileContents;
      file.read(fileContents);

      Assert::IsTrue(file.exists());

      Path dest(TestResources::getTempDirectory(), "Test.txt");
      file.copy(dest);

      AssertCel::FileExists(dest);

      std::string copyFileContents;
      File(dest).read(copyFileContents);

      Assert::AreEqual(fileContents, copyFileContents);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Copy_PathInput_WithFilePathThatDoesExist_DoesNothing)
    {
      File file(TestResources::getDataXmlFullPath());

      Assert::IsTrue(file.exists());

      File dest(TestResources::getBlockPngFullPath());
      std::string destContents;
      dest.read(destContents);
      file.copy(dest.getFilePath());

      Assert::IsTrue(dest.exists());

      std::string newDestContents;
      dest.read(newDestContents);

      Assert::AreEqual(destContents, newDestContents);
    }

#pragma endregion

#pragma endregion

#pragma region Append Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Append_FileDoesntExist_CreatesFileToo)
    {
      // Write one word so we do not have to do any complex manual retrieval
      std::string expected("TestString");

      File file(Path(TestResources::getTempDirectory(), "Directory1", "Directory2", "Test.txt"));

      Assert::IsFalse(Directory(Path(TestResources::getTempDirectory(), "Directory1", "Directory2")).exists());
      Assert::IsFalse(file.exists());

      file.append(expected);

      Assert::IsTrue(file.exists());
      FileAssert::FileContentsEqual(file.getFilePath().as_string(), "TestString");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Append_FileThatExists)
    {
      // Write one word so we do not have to do any complex manual retrieval
      std::string expected("TestString");

      File file(testFilePath);
      file.create();

      Assert::IsTrue(file.exists());

      file.append(expected);

      checkTestFileContents(expected);
    }

#pragma endregion

#pragma region Remove Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Remove_FileThatExists)
    {
      File file(testFilePath);
      file.create("");

      Assert::IsTrue(file.exists());

      file.remove();

      Assert::IsFalse(file.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Remove_FileThatDoesntExist)
    {
      File file(testFilePath);

      Assert::IsFalse(file.exists());

      file.remove();

      Assert::IsFalse(file.exists());
    }

#pragma endregion

#pragma region Clear Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Clear_FileDoesNotExist)
    {
      File file(testFilePath);

      Assert::IsFalse(file.exists());

      // This should just do nothing
      file.clear();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_Clear_FileExists)
    {
      File file(testFilePath);
      file.create();

      Assert::IsTrue(file.exists());

      file.append("Test");

      // This should clear the file so that there is no test in its
      file.clear();

      std::ifstream file_stream(testFilePath.as_string());
      std::string output;

      while (std::getline(file_stream, output)) { }

      Assert::IsTrue(output.empty());
    }

#pragma endregion

#pragma region Read Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_ReadEmptyFile)
    {
      File file(testFilePath);
      file.create(true);

      std::string actual;
      file.read(actual);

      Assert::IsTrue(actual.empty());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_ReadNonEmptyFile)
    {
      std::string expected("This is a test string");

      File file(testFilePath);
      file.append(expected);

      std::string actual;
      file.read(actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_ReadLines)
    {
      std::vector<std::string> expected =
      {
        "This",
        "is",
        "a",
        "test"
      };

      File file(testFilePath);

      for (const std::string& str : expected)
      {
        file.append(str + "\n");
      }

      std::vector<std::string> actual;
      file.readLines(actual);

      AssertExt::VectorContentsEqual<std::string>(expected, actual);
    }

#pragma endregion

#pragma region Get File Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_GetFileName)
    {
      File file(testFilePath);

      Assert::AreEqual(testFileName, file.getFileName());
    }

#pragma endregion

#pragma region Get Extensionless File Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(File_GetExtensionlessFileName)
    {
      File file(testFilePath);

      Assert::AreEqual("TestFile", file.getExtensionlessFileName().c_str());
    }

#pragma endregion
  };
}