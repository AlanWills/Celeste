#pragma once

#include "Assert/IAsserter.h"
#include "Templates/Unused.h"

#include <memory>

#ifdef _DEBUG
#define ASSERT(condition) Celeste::Assertion::getAsserter().check(condition)
#else
#define ASSERT(condition) celstl::unused(condition);
#endif

#define ASSERT_MSG(condition, message) ASSERT((condition && message))
#define ASSERT_FAIL() ASSERT(false)
#define ASSERT_NOT_NULL(object) ASSERT(object != nullptr)
#define ASSERT_FAIL_MSG(message) ASSERT_MSG(false, message)

#ifdef _DEBUG
#define STATIC_ASSERT(condition, message) static_assert(condition, message);
#else
#define STATIC_ASSERT(condition, message) celstl::unused(condition); celstl::unused(message);
#endif

#define STATIC_ASSERT_FAIL(message) STATIC_ASSERT(false, message)

namespace Celeste
{
  // Not named Assert due to clashes with Unit Test Assert
  class Assertion
  {
    public:
      Assertion(const Assertion&) = delete;
      Assertion(Assertion&&) = delete;
      void operator=(const Assertion&) = delete;

      AssertDllExport static void setAsserter(std::unique_ptr<IAsserter>&& asserter);
      AssertDllExport static IAsserter& getAsserter();
      
    private:
      Assertion() = default;
      static Assertion& instance();

      static std::unique_ptr<IAsserter> m_asserter; 
  };
}