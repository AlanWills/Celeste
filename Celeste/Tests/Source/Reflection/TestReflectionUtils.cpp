#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Reflection/ReflectionUtils.h"


namespace TestCeleste
{
  namespace Reflection
  {
    //------------------------------------------------------------------------------------------------
    class FloatClass
    {
      public:
        float m_float;
    };

    //------------------------------------------------------------------------------------------------
    class IntClass
    {
      public:
        int m_int;
    };

    CELESTE_TEST_CLASS(TestReflectionUtils)

#pragma region Get Member Offset Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetMemberOffset_ReturnsCorrectValue)
    {
      size_t floatOffset = (size_t)&(((FloatClass*)0)->FloatClass::m_float) - (size_t)(((FloatClass*)0));
      size_t intOffset = (size_t) & (((IntClass*)0)->IntClass::m_int) - (size_t)(((IntClass*)0));

      Assert::AreEqual(floatOffset, Celeste::Reflection::getMemberOffset(&FloatClass::m_float));
      Assert::AreEqual(intOffset, Celeste::Reflection::getMemberOffset(&IntClass::m_int));
    }

#pragma endregion

#pragma region Get Member Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GetMember_ReturnsCorrectMemberPointer)
    {
      FloatClass floatClass;
      IntClass intClass;
      float* floatPtr = Celeste::Reflection::getMember(&floatClass, &FloatClass::m_float);
      int* intPtr = Celeste::Reflection::getMember(&intClass, &IntClass::m_int);

      Assert::IsTrue(floatPtr == &floatClass.m_float);
      Assert::IsTrue(intPtr == &intClass.m_int);
    }

#pragma endregion

#pragma region Set Member Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SetMember_SetsMemberToCorrectValue)
    {
      FloatClass floatClass;
      IntClass intClass;
      floatClass.m_float = 0;
      intClass.m_int = 0;

      Assert::AreEqual(0.0f, floatClass.m_float);
      Assert::AreEqual(0, intClass.m_int);

      Celeste::Reflection::setMember(&floatClass, &FloatClass::m_float, 1.0f);
      Celeste::Reflection::setMember(&intClass, &IntClass::m_int, -1);

      Assert::AreEqual(1.0f, floatClass.m_float);
      Assert::AreEqual(-1, intClass.m_int);
    }

#pragma endregion

    };
  }
}