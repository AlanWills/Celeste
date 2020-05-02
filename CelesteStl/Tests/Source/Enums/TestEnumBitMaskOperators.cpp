#define NOMINMAX  // Disable windows.h min/max macros

#include "TestUtils/TestUtils.h"
#include "CelesteStl/Enums/Enum.h"


enum class Test : unsigned int
{
  kOne = 1 << 0,
  kTwo = 1 << 1,
  kFour = 1 << 2
};

namespace celstl
{
  //------------------------------------------------------------------------------------------------
  template<>
  struct EnableBitMaskOperators<Test>
  {
    static constexpr bool enable = true;
  };
}

using namespace celstl;

namespace Testcelstl
{
  TEST_UTILS_TEST_CLASS(TestEnumBitMaskOperators)

#pragma region Inclusive Or Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(InclusiveOrOperator_ReturnsEnum_WithInputsCombined)
  {
    Test t1 = Test::kOne;
    Test t2 = Test::kTwo;

    Test result = t1 | t2;

    Assert::AreEqual(3U, static_cast<unsigned int>(result));
  }

#pragma endregion

#pragma region And Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AndOperator_ReturnsEnum_WithInputsIntersected)
  {
    Test t1 = Test::kOne;
    Test t2 = Test::kTwo;

    Assert::AreEqual(0U, static_cast<unsigned int>(t1 & t2));
    Assert::AreEqual(1U, static_cast<unsigned int>(static_cast<Test>(3U) & t1));
  }

#pragma endregion

#pragma region Exclusive Or Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ExclusiveOrOperator_ReturnsEnum_WithExclusiveOrApplied)
  {
    Test t1 = Test::kOne;
    Test t2 = Test::kTwo;

    Assert::AreEqual(3U, static_cast<unsigned int>(t1 ^ t2));
    Assert::AreEqual(2U, static_cast<unsigned int>(static_cast<Test>(3U) ^ t1));
  }

#pragma endregion

#pragma region Not Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(NotOperator_ReturnsEnum_WithValuesReversed)
  {
    Assert::AreEqual(std::numeric_limits<unsigned int>::max() - 1U, static_cast<unsigned int>(~Test::kOne));
    Assert::AreEqual(std::numeric_limits<unsigned int>::max() - 2U, static_cast<unsigned int>(~Test::kTwo));
    Assert::AreEqual(std::numeric_limits<unsigned int>::max() - 4U, static_cast<unsigned int>(~Test::kFour));
  }

#pragma endregion

#pragma region Inclusive Or Reference Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(InclusiveOrReferenceOperator_CombinesValuesIntoFirstParameter)
  {
    Test t1 = Test::kOne;
    Test t2 = Test::kTwo;

    t1 |= t2;

    Assert::AreEqual(3U, static_cast<unsigned int>(t1));
  }

#pragma endregion

#pragma region And Reference Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(AndReferenceOperator_IntersectsValuesIntoFirstParameter)
  {
    Test t1 = Test::kOne;
    Test t2 = Test::kTwo;

    t1 &= t2;
    t2 &= static_cast<Test>(3U);

    Assert::AreEqual(0U, static_cast<unsigned int>(t1));
    Assert::AreEqual(2U, static_cast<unsigned int>(t2));
  }

#pragma endregion

#pragma region Exclusive Or Reference Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ExclusiveOrReferenceOperator_CombinesExclusiveOrValuesIntoFirstParameter)
  {
    Test t1 = Test::kOne;
    Test t2 = Test::kTwo;

    t1 ^= t2;
    t2 ^= static_cast<Test>(3U);

    Assert::AreEqual(3U, static_cast<unsigned int>(t1));
    Assert::AreEqual(1U, static_cast<unsigned int>(t2));
  }

#pragma endregion

#pragma region Has Flag Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HasFlag_ReturnsTrue)
  {
    Test t = Test::kOne | Test::kTwo | Test::kFour;

    Assert::IsTrue(hasFlag(t, Test::kOne));
    Assert::IsTrue(hasFlag(t, Test::kTwo));
    Assert::IsTrue(hasFlag(t, Test::kFour));
    Assert::IsTrue(hasFlag(t, static_cast<Test>(3U)));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(HasFlag_ReturnsFalse)
  {
    Test t = static_cast<Test>(0U);

    Assert::IsFalse(hasFlag(t, Test::kOne));
    Assert::IsFalse(hasFlag(t, Test::kTwo));
    Assert::IsFalse(hasFlag(t, Test::kFour));
    Assert::IsFalse(hasFlag(t, static_cast<Test>(3U)));
  }

#pragma endregion

  };
}