#pragma once

#include "CppUnitTest.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TestUtils
{

#define DEFAULT_FLOAT_EPSILON 0.00001f
#define DEFAULT_UINT64_EPSILON 2

  class AssertExt
  {
    public:
      /// Check whether the two inputted float values differ by less than or equal to the inputted epsilon
      /// Asserts if expected and actual are more than epsilon apart
      static void AreAlmostEqual(float expected, float actual, float epsilon = DEFAULT_FLOAT_EPSILON);

      static void AreAlmostEqual(uint64_t expected, uint64_t actual, uint64_t epsilon = DEFAULT_UINT64_EPSILON);

      /// Check the two inputted vector3s' components do not differ by less than or equal to the inputted epsilon
      /// Asserts if any component of expected and actual are more than epsilon apart
      static void AreAlmostEqual(const glm::vec3& expected, const glm::vec3& actual, float epsilon = DEFAULT_FLOAT_EPSILON);

      /// Check the two inputted vector4s' components do not differ by less than or equal to the inputted epsilon
      /// Asserts if any component of expected and actual are more than epsilon apart
      static void AreAlmostEqual(const glm::vec4& expected, const glm::vec4& actual, float epsilon = DEFAULT_FLOAT_EPSILON);

      /// Check the two inputted mat4s' components do not differ by less than or equal to the inputted epsilon
      /// Asserts if any component of expected and actual are more than epsilon apart
      static void AreAlmostEqual(const glm::mat4& expected, const glm::mat4& actual, float epsilon = DEFAULT_FLOAT_EPSILON);

      /// Checks each element in turn to see if they satisfy the Assert::AreEqual condition
      /// Will also fail if the vectors are not the same length
      template <typename T>
      static void VectorContentsEqual(const std::vector<T>& expected, const std::vector<T>& actual);

      /// Checks to see if the inputted unique ptr is null
      template <typename T>
      static void IsNull(const std::unique_ptr<T>& uniquePtr);

      /// Checks to see if the inputted unique ptr is not null
      template <typename T>
      static void IsNotNull(const std::unique_ptr<T>& uniquePtr);

    private:
      // Set up the appropriate constructors and assignment operators so that an instance of this class is impossible to create
      AssertExt() = default;
      AssertExt(const AssertExt& testUtils) = delete;
      AssertExt& operator=(const AssertExt&) = delete;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void AssertExt::VectorContentsEqual(const std::vector<T>& expected, const std::vector<T>& actual)
  {
    Assert::AreEqual(expected.size(), actual.size());

    for (size_t i = 0, n = expected.size(); i < n; ++i)
    {
      Assert::AreEqual(expected[i], actual[i]);
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void AssertExt::IsNull(const std::unique_ptr<T>& uniquePtr)
  {
    Assert::IsNull(uniquePtr.get());
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void AssertExt::IsNotNull(const std::unique_ptr<T>& uniquePtr)
  {
    Assert::IsNotNull(uniquePtr.get());
  }
}