#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "XML/XMLObject.h"

using namespace Celeste;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestXMLObject)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(XMLObject_Constructor_DefaultConstructor_SetsIsRequiredToFalse)
  {
    XML::XMLObject object;

    Assert::IsFalse(object.isRequired());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(XMLObject_Constructor_Constructor_SetsIsRequiredToInput)
  {
    XML::XMLObject object(DeserializationRequirement::kRequired);

    Assert::IsTrue(object.isRequired());
  }

#pragma endregion

};

}