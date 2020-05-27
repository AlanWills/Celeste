#include "TestUtils/TestUtils.h"
#include "CelesteStl/Templates/Variant.h"

using namespace celstl;


namespace Testcelstl
{
  TEST_UTILS_TEST_CLASS(TestVariant)

#pragma region Variant Index Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(VariantIndex_InputtingValidType_ReturnsCorrectIndex)
  {
    using TestVariant = std::variant<bool, int, float, std::string>;

    static_assert(celstl::variant_index<TestVariant, bool>() == 0U);
    static_assert(celstl::variant_index<TestVariant, int>() == 1U);
    static_assert(celstl::variant_index<TestVariant, float>() == 2U);
    static_assert(celstl::variant_index<TestVariant, std::string>() == 3U);
  }

#pragma endregion

  };
}