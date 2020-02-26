#include "UtilityHeaders/UnitTestHeaders.h"
#include "FileSystem/Path.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestPath)

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_DefaultConstructor_SetsPathToEmptystring)
    {
      Path path;

      Assert::AreEqual("", path.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_FullPathConstructor_EmptyString)
    {
      std::string expected("");
      Path path(expected);

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_FullPathConstructor)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");
      expected.push_back(PATH_DELIMITER);
      expected.append("File.txt");

      Path path(expected);

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_FullPathConstructor_WithUpDirCharacters)
    {
      std::string path("Root");
      path.push_back(PATH_DELIMITER);
      path.append("Nested");
      
      std::string expected(path);
      path.push_back(PATH_DELIMITER);
      path.append("Another");
      path.push_back(PATH_DELIMITER);
      path.append(UPDIR_STRING);

      Path p(path);

      Assert::AreEqual(expected, p.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_VariadicConstructor_WithEmptyString)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");

      Path path("Root", "", "Nested");

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_VariadicConstructor)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");
      expected.push_back(PATH_DELIMITER);
      expected.append("File.txt");

      Path path("Root", "Nested", "File.txt");

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_CopyConstructor)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");

      Path original(expected);
      Path copy(original);

      Assert::AreEqual(expected, copy.as_string());
    }

#pragma endregion

#pragma region Assignment Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_AssignmentOperator)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");

      Path original(expected);
      Path copy = original;

      Assert::AreEqual(expected, copy.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_AssignmentOperator_AssignmentToSelf)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");

      Path original(expected);
      original = original;

      Assert::AreEqual(expected, original.as_string());
    }

#pragma endregion

#pragma region Equality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_EqualityOperator_ShouldReturnTrue)
    {
      Path original("Root", "Nested");
      Path copy("Root", "Nested");

      Assert::IsTrue(original == copy);

      Path roundaboutCopy("Root", "Nested", "Another", "..");

      Assert::IsTrue(original == roundaboutCopy);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_EqualityOperator_ShouldReturnFalse)
    {
      Path original("Root", "Nested");
      Path incorrectCopy("Root", "Nested_");

      Assert::IsFalse(original == incorrectCopy);

      Path incorrectRoundaboutCopy("Root", "Nested", "Another", "..", "..");

      Assert::IsFalse(original == incorrectRoundaboutCopy);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_EqualityOperator_CompareWithSelf_ShouldReturnTrue)
    {
      Path original("Root", "Nested");

      // Check reflexive
      Assert::IsTrue(original == original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_EqualityOperator_ShouldBeSymmetric)
    {
      Path original("Root", "Nested");
      Path copy(original);

      // Check symmetric
      Assert::IsTrue(original == copy);
      Assert::IsTrue(copy == original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_EqualityOperator_ShouldBeTransitive)
    {
      Path original("Root", "Nested");
      Path copy(original);
      Path roundaboutCopy("Root", "Nested", "Another", "..");

      // This should be true for the transitivity to work
      Assert::IsTrue(original == roundaboutCopy);

      // Check transitivity - we know original == copy && original == roundaboutCopy => copy == roundaboutCopy
      Assert::IsTrue(copy == roundaboutCopy);
    }

#pragma endregion

#pragma region Inequality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_InequalityOperator_ShouldReturnTrue)
    {
      Path original("Root", "Nested");
      Path different("Root_", "Nested_");

      Assert::IsTrue(original != different);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_InequalityOperator_ShouldReturnFalse)
    {
      Path original("Root", "Nested");
      Path copy("Root", "Nested");

      Assert::IsFalse(original != copy);

      Path roundaboutCopy("Root", "Nested", "Another", "..");

      Assert::IsFalse(original != roundaboutCopy);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_InequalityOperator_CompareWithSelf_ShouldReturnFalse)
    {
      Path original("Root", "Nested");

      // Check reflexivity
      Assert::IsFalse(original != original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_InequalityOperator_IsSymmetric)
    {
      Path original("Root", "Nested");
      Path different("Root_", "Nested_");

      // Check symmetric
      Assert::IsTrue(original != different);
      Assert::IsTrue(different != original);
    }

    // Inequality operator is not transitive

#pragma endregion

#pragma region String Equality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_StringEqualityOperator_ShouldReturnTrue)
    {
      std::string copy("Root");
      copy.push_back(PATH_DELIMITER);
      copy.append("Nested");

      Path original("Root", "Nested");

      Assert::IsTrue(original == copy);

      std::string roundaboutCopy("Root");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append("Nested");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append("Another");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append(UPDIR_STRING);

      Assert::IsTrue(original == roundaboutCopy);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_StringEqualityOperator_ShouldReturnFalse)
    {
      std::string incorrectCopy("Root_");
      incorrectCopy.push_back(PATH_DELIMITER);
      incorrectCopy.append("Nested_");

      Path original("Root", "Nested");

      Assert::IsFalse(original == incorrectCopy);

      std::string incorrectRoundaboutCopy("Root_");
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append("Nested_");
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append("Another");
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append("Third");
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append(UPDIR_STRING);
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append(UPDIR_STRING);

      Assert::IsFalse(original == incorrectRoundaboutCopy);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_StringEqualityOperator_IsSymmetric)
    {
      Path original("Root", "Nested");

      std::string copy("Root");
      copy.push_back(PATH_DELIMITER);
      copy.append("Nested");

      // Check symmetric
      Assert::IsTrue(original == copy);
      Assert::IsTrue(copy == original);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_StringInequalityOperator_ShouldReturnTrue)
    {
      Path original("Root", "Nested");

      std::string different("Root_");
      different.push_back(PATH_DELIMITER);
      different.append("Nested_");

      Assert::IsTrue(original != different);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_StringInequalityOperator_ShouldReturnFalse)
    {
      Path original("Root", "Nested");

      std::string copy("Root");
      copy.push_back(PATH_DELIMITER);
      copy.append("Nested");

      Assert::IsFalse(original != copy);

      std::string roundaboutCopy("Root");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append("Nested");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append("Another");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append(UPDIR_STRING);

      Assert::IsFalse(original != roundaboutCopy);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_StringInequalityOperator_IsSymmetric)
    {
      Path original("Root", "Nested");

      std::string different("Root_");
      different.push_back(PATH_DELIMITER);
      different.append("Nested_");

      // Check symmetric
      Assert::IsTrue(original != different);
      Assert::IsTrue(different != original);
    }

    // Inequality operator is not transitive

#pragma endregion

#pragma region Char Array Equality Operator Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_CharArrayEqualityOperator_ShouldReturnTrue)
    {
      std::string copy("Root");
      copy.push_back(PATH_DELIMITER);
      copy.append("Nested");

      Path original("Root", "Nested");

      Assert::IsTrue(original == copy.c_str());

      std::string roundaboutCopy("Root");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append("Nested");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append("Another");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append(UPDIR_STRING);

      Assert::IsTrue(original == roundaboutCopy.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_CharArrayEqualityOperator_ShouldReturnFalse)
    {
      std::string incorrectCopy("Root_");
      incorrectCopy.push_back(PATH_DELIMITER);
      incorrectCopy.append("Nested_");

      Path original("Root", "Nested");

      Assert::IsFalse(original == incorrectCopy.c_str());

      std::string incorrectRoundaboutCopy("Root_");
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append("Nested_");
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append("Another");
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append("Third");
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append(UPDIR_STRING);
      incorrectRoundaboutCopy.push_back(PATH_DELIMITER);
      incorrectRoundaboutCopy.append(UPDIR_STRING);

      Assert::IsFalse(original == incorrectRoundaboutCopy.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_CharArrayEqualityOperator_IsSymmetric)
    {
      Path original("Root", "Nested");

      std::string copy("Root");
      copy.push_back(PATH_DELIMITER);
      copy.append("Nested");

      // Check symmetric
      Assert::IsTrue(original == copy.c_str());
      Assert::IsTrue(copy == original.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_CharArrayInequalityOperator_ShouldReturnTrue)
    {
      Path original("Root", "Nested");

      std::string different("Root_");
      different.push_back(PATH_DELIMITER);
      different.append("Nested_");

      Assert::IsTrue(original != different.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_CharArrayInequalityOperator_ShouldReturnFalse)
    {
      Path original("Root", "Nested");

      std::string copy("Root");
      copy.push_back(PATH_DELIMITER);
      copy.append("Nested");

      Assert::IsFalse(original != copy.c_str());

      std::string roundaboutCopy("Root");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append("Nested");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append("Another");
      roundaboutCopy.push_back(PATH_DELIMITER);
      roundaboutCopy.append(UPDIR_STRING);

      Assert::IsFalse(original != roundaboutCopy.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_CharArrayInequalityOperator_IsSymmetric)
    {
      Path original("Root", "Nested");

      std::string different("Root_");
      different.push_back(PATH_DELIMITER);
      different.append("Nested_");

      // Check symmetric
      Assert::IsTrue(original != different.c_str());
      Assert::IsTrue(different != original.c_str());
    }

    // Inequality operator is not transitive

#pragma endregion

#pragma region Combine Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_CombineNonEmptyString_OntoEmptyPath)
    {
      std::string expected("NonEmpty");

      Path path("");
      path.combine(expected);

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_CombineEmptyString_OntoNonEmptyPath)
    {
      std::string expected("NonEmpty");

      Path path(expected);
      path.combine("");

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_SingleCharArray)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");
      expected.push_back(PATH_DELIMITER);
      expected.append("Third");
      
      Path path("Root", "Nested");
      path.combine("Third");

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_SingleString)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");
      expected.push_back(PATH_DELIMITER);
      expected.append("Third");

      std::string third("Third");

      Path path("Root", "Nested");
      path.combine(third);

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_SinglePath)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");
      expected.push_back(PATH_DELIMITER);
      expected.append("Third");

      Path path("Root", "Nested"), third("Third");
      path.combine(third);

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_MultipleCharArrays)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");
      expected.push_back(PATH_DELIMITER);
      expected.append("Third");

      Path path("Root");
      path.combine("Nested", "Third");

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_MultipleStrings)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");
      expected.push_back(PATH_DELIMITER);
      expected.append("Third");

      std::string nested("Nested"), third("Third");

      Path path("Root");
      path.combine(nested, third);

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_MultiplePaths)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");
      expected.push_back(PATH_DELIMITER);
      expected.append("Third");

      Path path("Root"), nested("Nested"), third("Third");
      path.combine(nested, third);

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_UpDir)
    {
      std::string expected("Root");
      
      Path path("Root", "Nested");
      path.combine(UPDIR_STRING);

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_UpDirAtEndOfString)
    {
      std::string expected("Root");
      std::string path("Nested");
      path.push_back(PATH_DELIMITER);
      path.append(UPDIR_STRING);

      Path p("Root");
      p.combine(path);

      Assert::AreEqual(expected, p.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_UpDirAtStartOfString)
    {
      std::string expected("Nested");
      std::string path(UPDIR_STRING);
      path.push_back(PATH_DELIMITER);
      path.append("Nested");

      Path p("Root");
      p.combine(path);

      Assert::AreEqual(expected, p.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Combine_UpDirInMiddleOfString)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");

      std::string path("Middle");
      path.push_back(PATH_DELIMITER);
      path.append(UPDIR_STRING);
      path.push_back(PATH_DELIMITER);
      path.append("Nested");

      Path p("Root");
      p.combine(path);

      Assert::AreEqual(expected, p.as_string());
    }

#pragma endregion

#pragma region Get Parent Directory Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_GetParentDirectory_ClearsInput)
    {
      std::string parent("This string should be cleared");
      Path path("Root", "Nested");
      path.getParentDirectory(parent);

      Assert::AreNotEqual("This string should be cleared", parent.c_str());

      parent = "This string should be cleared";
      path = Path("Root");
      path.getParentDirectory(parent);

      Assert::AreNotEqual("This string should be cleared", parent.c_str());

      parent = "This string should be cleared";
      path = Path("");
      path.getParentDirectory(parent);

      Assert::AreNotEqual("This string should be cleared", parent.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_GetParentDirectory_WithEmptyPath_ReturnsEmptyString)
    {
      Path path("");

      std::string parent;
      path.getParentDirectory(parent);

      Assert::AreEqual("", path.getParentDirectory().c_str());
      Assert::AreEqual("", parent.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_GetParentDirectory_WithSingleDirectoryPath_ReturnsEmptyString)
    {
      Path path("Root");

      std::string parent;
      path.getParentDirectory(parent);

      Assert::AreEqual("", path.getParentDirectory().c_str());
      Assert::AreEqual("", parent.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_GetParentDirectory_WithMultipleDirectoryPath_ReturnsParentPath)
    {
      std::string expected("Root");
      Path path("Root", "Nested");

      std::string parent;
      path.getParentDirectory(parent);

      Assert::AreEqual(expected, parent);
      Assert::AreEqual(expected, path.getParentDirectory());
      Assert::AreEqual(expected, Path::getParentDirectory(path.as_string()));

      expected.push_back(PATH_DELIMITER);
      expected.append("Nested");
      path = Path("Root", "Nested", "Third");

      parent.clear();
      path.getParentDirectory(parent);

      Assert::AreEqual(expected, parent);
      Assert::AreEqual(expected, path.getParentDirectory());
      Assert::AreEqual(expected, Path::getParentDirectory(path.as_string()));
    }

#pragma endregion

#pragma region Reset Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Reset_FullPath)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Directory.txt");

      Path path("Womp");
      path.reset(expected);

      Assert::AreEqual(expected, path.as_string());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_Reset_Variadic)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Directory.txt");

      Path path("Womp");
      path.reset("Root", "Directory.txt");

      Assert::AreEqual(expected, path.as_string());
    }

#pragma endregion

#pragma region Is Ancestor Of Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_IsAncestorOf_InputtingValidChild_ReturnsTrue)
    {
      Path path("Parent", "Nested");
      Path child("Parent", "Nested", "Child");

      Assert::IsTrue(path.isAncestorOf(child));

      child.combine("AnotherLevel");

      Assert::IsTrue(path.isAncestorOf(child));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_IsAncestorOf_InputtingSamePath_ReturnsFalse)
    {
      Path path("Parent", "Nested");
      Path path2(path);

      Assert::IsFalse(path.isAncestorOf(path2));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_IsAncestorOf_InputtingDifferentPathOfSameLength_ReturnsFalse)
    {
      Path path("Parent", "Nested");
      Path path2("Parent", "AnotherNested");

      Assert::IsFalse(path.isAncestorOf(path2));
      Assert::IsFalse(path2.isAncestorOf(path));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_IsAncestorOf_InputtingPathOfShallowerDepth_ReturnsFalse)
    {
      Path path("Parent", "Nested");
      Path path2("Parent");

      Assert::IsFalse(path.isAncestorOf(path2));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_IsAncestorOf_InputtingInvalidChild_ReturnsFalse)
    {
      Path path("Parent", "Nested");
      Path path2("Parent", "Another Nested", "Child");

      Assert::IsFalse(path.isAncestorOf(path2));
    }

#pragma endregion

#pragma region Relative To Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_RelativeTo_ValidAncestor_ReturnsCorrectRelativePath)
    {
      Path parentPath("Root");
      Path path("Root", "Nested", "Third.txt");

      std::string expected("Nested");
      expected.push_back(PATH_DELIMITER);
      expected.append("Third.txt");

      Assert::AreEqual(expected, path.relativeTo(parentPath));

      parentPath = Path("Root", "Nested");
      expected = "Third.txt";

      Assert::AreEqual(expected, path.relativeTo(parentPath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Path_RelativeTo_InvalidAncestor_ReturnsEmptyString)
    {
      std::string expected("");

      Path nonParent("Hello");
      Path path("Root", "Nested", "Third.txt");

      Assert::AreEqual(expected, path.relativeTo(nonParent));
    }

#pragma endregion
  };
}