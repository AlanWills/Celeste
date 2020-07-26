#include "TestUtils/TestUtils.h"
#include "StringId/string_id.h"


namespace TestStringId
{		
  BASE_TEST_CLASS(TestStringId)
		
#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_DefaultConstructor_SetsIdToEmpty)
  {
    string_id id;

    Assert::AreEqual(string_id(), id);
    Assert::AreEqual("", id.debug_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_HashIdConstructor_SetsIdToInputtedValue)
  {
    string_id id(5);

    Assert::AreEqual(string_id::hash_type(5), id.id());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_HashIdConstructor_SetsDebugStringToEmptyString)
  {
    string_id id(5);

    Assert::AreEqual("", id.debug_string());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_ConstCharStar_Constructor_HashesStringCorrectly)
  {
    const char* string = "Test";
    string_id id(string);

    Assert::AreNotEqual(string_id(), id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_EmptyConstCharStar_Constructor_SetsHashToEmpty)
  {
    const char* string = "";
    string_id id(string);

    Assert::AreEqual(string_id(), id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_String_Constructor_HashesStringCorrectly)
  {
    std::string string = "Test";
    string_id id(string);

    Assert::AreNotEqual(string_id(), id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_EmptyString_Constructor_SetsHashToEmpty)
  {
    std::string string = "";
    string_id id(string);

    Assert::AreEqual(string_id(), id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_StringView_Constructor_HashesStringCorrectly)
  {
    std::string_view string = "Test";
    string_id id(string);

    Assert::AreNotEqual(string_id(), id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_StringView_Constructor_SetsHashToEmpty)
  {
    std::string_view string = "";
    string_id id(string);

    Assert::AreEqual(string_id(), id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_String_Constructor_PreservesDebugStringAfterOriginalStringDestroyed)
  {
    string_id id("");
    
    {
      std::string string = "Test";
      id = string_id(string);

      Assert::AreEqual(string, std::string(id.debug_string()));
    }

    Assert::AreEqual(std::string("Test"), std::string(id.debug_string()));
  }

#pragma endregion

#pragma region Copy Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_CopyConstructor_CopiesId)
  {
    string_id id("Test");
    string_id id2(id);

    Assert::AreEqual(id.id(), id2.id());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_CopyConstructor_CopiesDebugString)
  {
    string_id id("Test");
    string_id id2(id);

    Assert::AreEqual(std::string("Test"), std::string(id2.debug_string()));
    Assert::AreEqual(strlen(id.debug_string()), strlen(id2.debug_string()));
  }

#pragma endregion

#pragma region Equality Operator Tests

#pragma region string_id Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_string_id_ShouldReturnTrue)
  {
    string_id id("Test");

    Assert::IsTrue(id == string_id("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_string_id_ShouldReturnTrue)
  {
    string_id id("Test");

    Assert::IsTrue(string_id("Test") == id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_string_id_ShouldReturnFalse)
  {
    string_id id("Test");

    Assert::IsFalse(id == string_id("Test2"));
    Assert::IsFalse(id == string_id(""));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_string_id_ShouldReturnFalse)
  {
    string_id id("Test");

    Assert::IsFalse(string_id("Test2") == id);
    Assert::IsFalse(string_id("") == id);
  }

#pragma endregion

#pragma region hash_type Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_hash_type_ShouldReturnTrue)
  {
    string_id id("Test");

    Assert::IsTrue(id == fvn::hash("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_hash_type_ShouldReturnTrue)
  {
    string_id id("Test");

    Assert::IsTrue(fvn::hash("Test") == id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_hash_type_ShouldReturnFalse)
  {
    string_id id("Test");

    Assert::IsFalse(id == fvn::hash("Test2"));
    Assert::IsFalse(id == fvn::hash(""));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_hash_type_ShouldReturnFalse)
  {
    string_id id("Test");

    Assert::IsFalse(fvn::hash("Test2") == id);
    Assert::IsFalse(fvn::hash("") == id);
  }

#pragma endregion

#pragma region const char* Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_const_char_star_ShouldReturnTrue)
  {
    const char* str = "Test";
    string_id id(str);

    Assert::IsTrue(id == str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_const_char_star_ShouldReturnTrue)
  {
    const char* str = "Test";
    string_id id(str);

    Assert::IsTrue(str == id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_const_char_star_ShouldReturnFalse)
  {
    string_id id("Test");

    const char* str = "Test2";
    Assert::IsFalse(id == str);
    
    str = "";
    Assert::IsFalse(id == str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_const_char_star_ShouldReturnFalse)
  {
    string_id id("Test");

    const char* str = "Test2";
    Assert::IsFalse(str == id);
    
    str = "";
    Assert::IsFalse(str == id);
  }

#pragma endregion

#pragma region string Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_string_ShouldReturnTrue)
  {
    std::string str = "Test";
    string_id id(str);

    Assert::IsTrue(id == str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_string_ShouldReturnTrue)
  {
    std::string str = "Test";
    string_id id(str);

    Assert::IsTrue(str == id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_string_ShouldReturnFalse)
  {
    string_id id("Test");

    std::string str = "Test2";
    Assert::IsFalse(id == str);

    str = "";
    Assert::IsFalse(id == str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_string_ShouldReturnFalse)
  {
    string_id id("Test");

    std::string str = "Test2";
    Assert::IsFalse(str == id);

    str = "";
    Assert::IsFalse(str == id);
  }

#pragma endregion

#pragma region string_view Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_string_view_ShouldReturnTrue)
  {
    std::string_view str = "Test";
    string_id id(str);

    Assert::IsTrue(id == str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_string_view_ShouldReturnTrue)
  {
    std::string_view str = "Test";
    string_id id(str);

    Assert::IsTrue(str == id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSEqualityWith_string_view_ShouldReturnFalse)
  {
    string_id id("Test");

    std::string_view str = "Test2";
    Assert::IsFalse(id == str);

    str = "";
    Assert::IsFalse(id == str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSEqualityWith_string_view_ShouldReturnFalse)
  {
    string_id id("Test");

    std::string_view str = "Test2";
    Assert::IsFalse(str == id);

    str = "";
    Assert::IsFalse(str == id);
  }

#pragma endregion

#pragma endregion

#pragma region Inequality Operator Tests

#pragma region string_id Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_string_id_ShouldReturnTrue)
  {
    string_id id("Test");

    Assert::IsTrue(id != string_id("Test2"));
    Assert::IsTrue(id != string_id(""));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_string_id_ShouldReturnTrue)
  {
    string_id id("Test");

    Assert::IsTrue(string_id("Test2") != id);
    Assert::IsTrue(string_id("") != id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_string_id_ShouldReturnFalse)
  {
    string_id id("Test");

    Assert::IsFalse(id != string_id("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_string_id_ShouldReturnFalse)
  {
    string_id id("Test");

    Assert::IsFalse(string_id("Test") != id);
  }

#pragma endregion

#pragma region hash_type Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_hash_type_ShouldReturnTrue)
  {
    string_id id("Test");

    Assert::IsTrue(id != fvn::hash("Test2"));
    Assert::IsTrue(id != fvn::hash(""));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_hash_type_ShouldReturnTrue)
  {
    string_id id("Test");

    Assert::IsTrue(fvn::hash("Test2") != id);
    Assert::IsTrue(fvn::hash("") != id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_hash_type_ShouldReturnFalse)
  {
    string_id id("Test");

    Assert::IsFalse(id != fvn::hash("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_hash_type_ShouldReturnFalse)
  {
    string_id id("Test");

    Assert::IsFalse(fvn::hash("Test") != id);
  }

#pragma endregion

#pragma region const char* Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_const_char_star_ShouldReturnTrue)
  {
    string_id id("Test");

    const char* str = "Test2";
    Assert::IsTrue(id != str);

    str = "";
    Assert::IsTrue(id != str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_const_char_star_ShouldReturnTrue)
  {
    string_id id("Test");

    const char* str = "Test2";
    Assert::IsTrue(str != id);

    str = "";
    Assert::IsTrue(str != id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_const_char_star_ShouldReturnFalse)
  {
    const char* str = "Test";
    string_id id(str);

    Assert::IsFalse(id != str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_const_char_star_ShouldReturnFalse)
  {
    const char* str = "Test";
    string_id id(str);

    Assert::IsFalse(str != id);
  }

#pragma endregion

#pragma region string Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_string_ShouldReturnTrue)
  {
    string_id id("Test");

    std::string str = "Test2";
    Assert::IsTrue(id != str);

    str = "";
    Assert::IsTrue(id != str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_string_ShouldReturnTrue)
  {
    string_id id("Test");

    std::string str = "Test2";
    Assert::IsTrue(str != id);

    str = "";
    Assert::IsTrue(str != id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_string_ShouldReturnFalse)
  {
    std::string str = "Test";
    string_id id(str);

    Assert::IsFalse(id != str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_string_ShouldReturnFalse)
  {
    std::string str = "Test";
    string_id id(str);

    Assert::IsFalse(str != id);
  }

#pragma endregion

#pragma region string_view Overload

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_string_view_ShouldReturnTrue)
  {
    string_id id("Test");

    std::string_view str = "Test2";
    Assert::IsTrue(id != str);

    str = "";
    Assert::IsTrue(id != str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_string_view_ShouldReturnTrue)
  {
    string_id id("Test");

    std::string_view str = "Test2";
    Assert::IsTrue(str != id);

    str = "";
    Assert::IsTrue(str != id);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_LHSInequalityWith_string_view_ShouldReturnFalse)
  {
    std::string_view str = "Test";
    string_id id(str);

    Assert::IsFalse(id != str);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(string_id_RHSInequalityWith_string_view_ShouldReturnFalse)
  {
    std::string_view str = "Test";
    string_id id(str);

    Assert::IsFalse(str != id);
  }

#pragma endregion

#pragma endregion

	};
}