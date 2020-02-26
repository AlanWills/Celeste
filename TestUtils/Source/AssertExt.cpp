#include "AssertExt.h"


namespace TestUtils
{
  //------------------------------------------------------------------------------------------------
  void AssertExt::AreAlmostEqual(float expected, float actual, float epsilon)
  {
    Assert::IsTrue(abs(expected - actual) <= epsilon);
  }

  //------------------------------------------------------------------------------------------------
  void AssertExt::AreAlmostEqual(uint64_t expected, uint64_t actual, uint64_t epsilon)
  {
    if (expected > actual)
    {
      Assert::IsTrue((expected - actual) <= epsilon);
    }
    else
    {
      Assert::IsTrue((actual - expected) <= epsilon);
    }
  }

  //------------------------------------------------------------------------------------------------
  void AssertExt::AreAlmostEqual(const glm::vec3& expected, const glm::vec3& actual, float epsilon)
  {
    AreAlmostEqual(expected.x, actual.x, epsilon);
    AreAlmostEqual(expected.y, actual.y, epsilon);
    AreAlmostEqual(expected.z, actual.z, epsilon);
  }

  //------------------------------------------------------------------------------------------------
  void AssertExt::AreAlmostEqual(const glm::vec4& expected, const glm::vec4& actual, float epsilon)
  {
    AreAlmostEqual(expected.x, actual.x, epsilon);
    AreAlmostEqual(expected.y, actual.y, epsilon);
    AreAlmostEqual(expected.z, actual.z, epsilon);
    AreAlmostEqual(expected.w, actual.w, epsilon);
  }

  //------------------------------------------------------------------------------------------------
  void AssertExt::AreAlmostEqual(const glm::mat4& expected, const glm::mat4& actual, float epsilon)
  {
    AreAlmostEqual(expected[0], actual[0], epsilon);
    AreAlmostEqual(expected[1], actual[1], epsilon);
    AreAlmostEqual(expected[2], actual[2], epsilon);
    AreAlmostEqual(expected[3], actual[3], epsilon);
  }
}