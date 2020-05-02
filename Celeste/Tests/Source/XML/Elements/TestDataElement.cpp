#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "XML/XMLObjectFactory.h"
#include "XML/Elements/DataElement.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste
{
  namespace XML
  {
    CELESTE_TEST_CLASS(TestDataElement)

#pragma region Is Reference Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataElement_IsValue_IsReferenceShouldReturnFalse)
    {
      std::unique_ptr<ValueElement<float>> attribute(XMLObjectFactory::create<ValueElement, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      Assert::IsFalse(attribute->isReference());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataElement_IsReference_IsReferenceShouldReturnTrue)
    {
      std::unique_ptr<ReferenceElement<float>> attribute(XMLObjectFactory::create<ReferenceElement, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      Assert::IsTrue(attribute->isReference());
    }

#pragma endregion

#pragma region Clone Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ValueElement_Clone_ReturnsNewInstanceOfValueElement)
    {
      std::unique_ptr<ValueElement<float>> ele(XMLObjectFactory::create<ValueElement, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      std::unique_ptr<ValueElement<float>> ele2(ele->clone());

      AssertExt::IsNotNull(ele2);
      Assert::IsFalse(ele == ele2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ReferenceElement_Clone_ReturnsNewInstanceOfReferenceElement)
    {
      std::unique_ptr<ReferenceElement<float>> ele(XMLObjectFactory::create<ReferenceElement, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      std::unique_ptr<ReferenceElement<float>> ele2(ele->clone());

      AssertExt::IsNotNull(ele2);
      Assert::IsFalse(ele == ele2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataElement_Clone_SetsInstanceElementNameToSameName)
    {
      std::unique_ptr<ValueElement<float>> ele(XMLObjectFactory::create<ValueElement, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      std::unique_ptr<ValueElement<float>> ele2(ele->clone());

      Assert::AreEqual(ele->getElementName(), ele2->getElementName());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataElement_Clone_SetsInstanceValueToSameValue)
    {
      std::unique_ptr<ValueElement<float>> ele(XMLObjectFactory::create<ValueElement, float>(
        "Test", 5.0f, DeserializationRequirement::kNotRequired));

      std::unique_ptr<ValueElement<float>> ele2(ele->clone());

      Assert::AreEqual(ele->getValue(), ele2->getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataElement_Clone_SetsInstanceDeserializationRequirementToSameRequirement)
    {
      std::unique_ptr<ValueElement<float>> ele(XMLObjectFactory::create<ValueElement, float>(
        "Test", 0.0f, DeserializationRequirement::kRequired));

      std::unique_ptr<ValueElement<float>> ele2(ele->clone());

      Assert::IsTrue(ele->isRequired());
      Assert::IsTrue(ele2->isRequired());
    }

#pragma endregion

    };
  }
}