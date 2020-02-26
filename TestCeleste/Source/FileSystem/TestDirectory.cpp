#include "UtilityHeaders/UnitTestHeaders.h"

#include "Resources/TestResources.h"
#include "FileSystem/Directory.h"
#include "AssertSpecialization/FileSystem.h"
#include "AssertExt.h"

#include "direct.h"


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestDirectory)

    //------------------------------------------------------------------------------------------------
    template <typename T>
    T create(const Path& fullPath)
    {
      T obj(fullPath);
      obj.create();
      Assert::IsTrue(obj.exists());

      return obj;
    }

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_Constructor_StringPath)
    {
      Path path(TestResources::getTempDirectory(), "Test");
      Directory dir(path.as_string());

      Assert::AreEqual(path, dir.getDirectoryPath());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_Constructor_Path)
    {
      Path path(TestResources::getTempDirectory(), "Test");
      Directory dir(path);

      Assert::AreEqual(path, dir.getDirectoryPath());
    }

#pragma endregion

#pragma region Copy Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_CopyConstructor)
    {
      Path path(TestResources::getTempDirectory(), "Test");
      Directory dir(path);
      Directory dirCopy(dir);

      Assert::AreEqual(path, dirCopy.getDirectoryPath());
    }

#pragma endregion

#pragma region Assignment Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_AssignmentOperator)
    {
      Path path(TestResources::getTempDirectory(), "Test");
      Directory dir(path);
      Directory dirCopy = dir;

      Assert::AreEqual(path, dirCopy.getDirectoryPath());

      // Now check with a directory that has had another path assigned to it
      Directory dirReassignment(Path(TestResources::getTempDirectory(), "Another"));
      dirReassignment = dir;

      Assert::AreEqual(path, dirReassignment.getDirectoryPath());
    }

#pragma endregion

#pragma region Equality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_EqualityOperator_ShouldReturnTrue)
    {
      Path path(TestResources::getTempDirectory(), "Test");
      Directory original(path), same(path);

      Assert::IsTrue(original == same);
      
      Path roundaboutPath(TestResources::getTempDirectory(), "Test", "Another", UPDIR_STRING);
      Directory roundaboutDir(roundaboutPath);

      Assert::IsTrue(original == roundaboutDir);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_EqualityOperator_ShouldReturnFalse)
    {
      Directory original(Path(TestResources::getTempDirectory(), "Test"));
      Directory different(Path(TestResources::getTempDirectory(), "Different"));

      Assert::IsFalse(original == different);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_EqualityOperator_CompareWithSelf_ShouldReturnTrue)
    {
      Path path(TestResources::getTempDirectory(), "Test");
      Directory original(path);

      // Reflexive
      Assert::IsTrue(original == original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_EqualityOperator_IsSymmetric)
    {
      Path path(TestResources::getTempDirectory(), "Test");
      Directory original(path);
      Directory copy(original);

      // Symmetric
      Assert::IsTrue(original == copy);
      Assert::IsTrue(copy == original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_EqualityOperator_IsTransitive)
    {
      Path path(TestResources::getTempDirectory(), "Test");
      Directory original(path);
      Directory copy(original);
      Directory roundaboutCopy(Path(path, "Another", ".."));

      // Transitive: original == copy & original == roundaboutCopy => copy == roundaboutCopy
      Assert::IsTrue(original == roundaboutCopy);
      Assert::IsTrue(copy == roundaboutCopy);
    }

#pragma endregion

#pragma region Get Executing App Directory Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_GetExecutingAppDirectory)
    {
      char buffer[1024];
      _getcwd(buffer, 1024);

      std::string executingAppDir;
      Directory::getExecutingAppDirectory(executingAppDir);

      Assert::AreEqual(buffer, executingAppDir.c_str());
      Assert::AreEqual(buffer, Directory::getExecutingAppDirectory().c_str());
    }

#pragma endregion

#pragma region Exists Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_Exists_ShouldReturnTrue)
    {
      Directory dir(Path(TestResources::getTempDirectory(), "Test"));

      _mkdir(dir.getDirectoryPath().c_str());

      Assert::IsTrue(Directory::exists(dir.getDirectoryPath()));
      Assert::IsTrue(Directory::exists(dir.getDirectoryPath().as_string()));
      Assert::IsTrue(dir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_Exists_ShouldReturnFalse)
    {
      Directory dir(Path(TestResources::getTempDirectory(), "Test"));

      _rmdir(dir.getDirectoryPath().c_str());

      Assert::IsFalse(Directory::exists(dir.getDirectoryPath()));
      Assert::IsFalse(Directory::exists(dir.getDirectoryPath().as_string()));
      Assert::IsFalse(Directory::exists(TestResources::getBlockPngFullPath()));
      Assert::IsFalse(dir.exists());
    }

#pragma endregion

#pragma region Find Files Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_FindFiles_InDirectoryOnly)
    {
      // Create some files
      File file1 = create<File>(Path(TestResources::getTempDirectory(), "TestFile1.txt"));
      File file2 = create<File>(Path(TestResources::getTempDirectory(), "TestFile2.txt"));

      std::vector<File> actualFiles, expectedFiles =
      {
        file1,
        file2
      };

      Directory dir(TestResources::getTempDirectory());
      dir.findFiles(actualFiles);

      AssertExt::VectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_FindFiles_InDirectoryOnly_WithPattern)
    {
      // Create some files
      File file1 = create<File>(Path(TestResources::getTempDirectory(), "TestFile1.txt"));
      File file2 = create<File>(Path(TestResources::getTempDirectory(), "TestFile2.html"));

      std::vector<File> actualFiles, expectedFiles =
      {
        file1
      };

      Directory dir(TestResources::getTempDirectory());
      dir.findFiles(actualFiles, ".txt");

      AssertExt::VectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_FindFiles_InAllSubDirectories)
    {
      // Create some files
      File file1 = create<File>(Path(TestResources::getTempDirectory(), "TestFile1.txt"));
      File file2 = create<File>(Path(TestResources::getTempDirectory(), "TestFile2.txt"));

      Path nestedDirPath(TestResources::getTempDirectory(), "NestedDirectory");
      Directory nestedDir(nestedDirPath);

      File file3 = create<File>(Path(nestedDirPath, "TestFile3.txt"));

      std::vector<File> actualFiles, expectedFiles =
      {
        file3,
        file1,
        file2
      };

      Directory dir = create<Directory>(TestResources::getTempDirectory().as_string());
      dir.findFiles(actualFiles, ".", true);
      AssertExt::VectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
      file3.remove();

      Assert::AreEqual(0, _rmdir(nestedDirPath.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_FindFiles_InAllSubDirectories_WithPattern)
    {
      // Create some files
      File file1 = create<File>(Path(TestResources::getTempDirectory(), "TestFile1.txt"));
      File file2 = create<File>(Path(TestResources::getTempDirectory(), "TestFile2.html"));

      Path nestedDirPath(TestResources::getTempDirectory(), "NestedDirectory");
      Directory nestedDir(nestedDirPath);

      File file3 = create<File>(Path(nestedDirPath, "TestFile3.txt"));

      std::vector<File> actualFiles, expectedFiles =
      {
        file3,
        file1,
      };

      Directory dir = create<Directory>(TestResources::getTempDirectory().as_string());
      dir.findFiles(actualFiles, ".txt", true);
      AssertExt::VectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
      file3.remove();

      Assert::AreEqual(0, _rmdir(nestedDirPath.c_str()));
    }

#pragma endregion

#pragma region Find Directories Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_FindDirectories_InDirectoryOnly)
    {
      Path enclosingDirectoryPath(TestResources::getTempDirectory(), "EnclosingDirectory");
      Directory enclosingDirectory = create<Directory>(enclosingDirectoryPath);

      Directory dir1 = create<Directory>(Path(enclosingDirectoryPath, "TestDirectory1"));
      Directory dir2 = create<Directory>(Path(enclosingDirectoryPath, "TestDirectory2"));

      std::vector<Directory> actualDirectories, expectedDirectories =
      {
        dir1,
        dir2
      };

      enclosingDirectory.findDirectories(actualDirectories);
      AssertExt::VectorContentsEqual(expectedDirectories, actualDirectories);

      dir1.remove();
      dir2.remove();
      enclosingDirectory.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_FindDirectories_AllSubDirectories)
    {
      Path enclosingDirectoryPath(TestResources::getTempDirectory(), "EnclosingDirectory");
      Directory enclosingDirectory = create<Directory>(enclosingDirectoryPath);

      Directory dir1 = create<Directory>(Path(enclosingDirectoryPath, "TestDirectory1"));
      Directory dir2 = create<Directory>(Path(enclosingDirectoryPath, "TestDirectory2"));
      Directory dir3 = create<Directory>(Path(enclosingDirectoryPath, "TestDirectory2", "TestDirectory3"));

      std::vector<Directory> actualDirectories, expectedDirectories =
      {
        dir1,
        dir2,
        dir3
      };

      enclosingDirectory.findDirectories(actualDirectories);
      AssertExt::VectorContentsEqual(expectedDirectories, actualDirectories);

      dir1.remove();
      dir2.remove();
      dir3.remove();
      enclosingDirectory.remove();
    }

#pragma endregion

#pragma region Remove Directory Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_RemoveDirectoryThatExists)
    {
      Directory dir = create<Directory>(Path(TestResources::getTempDirectory(), "TestRemove"));
      dir.remove();

      Assert::IsFalse(dir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_RemoveDirectoryThatDoesntExist)
    {
      Directory dir = create<Directory>(Path(TestResources::getTempDirectory(), "TestRemove"));
      dir.remove();

      Assert::IsFalse(dir.exists());

      // Now try to remove it again to see we do not get any errors
      dir.remove();

      Assert::IsFalse(dir.exists());
    }

#pragma endregion

#pragma region Create Directory Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_Create_DirectoryDoesntExist_ShouldCreateDirectory)
    {
      Directory dir(Path(TestResources::getTempDirectory(), "TestCreate"));

      Assert::IsFalse(dir.exists());
      dir.create();

      Assert::IsTrue(dir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_Create_DirectoryAlreadyExists_DoesNothing)
    {
      Directory dir(Path(TestResources::getTempDirectory(), "TestCreate"));

      Assert::IsFalse(dir.exists());
      dir.create();

      Assert::IsTrue(dir.exists());

      // Now try creating it again
      dir.create();

      Assert::IsTrue(dir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_Create_ShouldCreateAllParentDirectoriesToo)
    {
      Path parentDirectory(TestResources::getTempDirectory(), "TestNested");
      Path nestedDirectory(parentDirectory, "TestCreate");

      Directory dir = create<Directory>(nestedDirectory);
      
      Assert::IsTrue(Directory::exists(parentDirectory));
      Assert::IsTrue(Directory::exists(nestedDirectory));
    }

#pragma endregion

#pragma region Create File Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_CreateFile_FileDoesntExist_CreatesFile)
    {
      Directory dir(TestResources::getTempDirectory());
      const File& createdFile = dir.createFile("Test.txt");
      Assert::IsTrue(createdFile.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_CreateFile_FileDoesExist_DoesNothing)
    {
      Directory dir(TestResources::getTempDirectory());
      File createdFile = dir.createFile("Test.txt");
      Assert::IsTrue(createdFile.exists());

      createdFile = dir.createFile("Test.txt");
      Assert::IsTrue(createdFile.exists());
    }

#pragma endregion

#pragma region Create Directory Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_CreateDirectory_DirectoryDoesNotExist_DoesNothing)
    {
      Directory dir(TestResources::getTempDirectory());
      const Directory& createdDir = dir.createDirectory("TestDirectory");
      Assert::IsTrue(createdDir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_CreateDirectory_DirectoryExists_DoesNothing)
    {
      Directory dir(TestResources::getTempDirectory());
      Directory createdDir = dir.createDirectory("TestDirectory");
      Assert::IsTrue(createdDir.exists());

      createdDir = dir.createDirectory("TestDirectory");
      Assert::IsTrue(createdDir.exists());
    }

#pragma endregion

#pragma region Get Directory Name Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Directory_GetDirectoryName)
    {
      Directory dir(TestResources::getTempDirectory());

      Assert::AreEqual("Temp", dir.getDirectoryName().c_str());
    }

#pragma endregion
  };
}