#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "XML/XMLObjectFactory.h"
#include "XML/Attributes/DataAttribute.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste;
using namespace Celeste::XML;


namespace TestCeleste
{
  namespace XML
  {
    CELESTE_TEST_CLASS(TestDataAttribute)

#pragma region Is Reference Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataAttribute_IsValue_IsReferenceShouldReturnFalse)
    {
      std::unique_ptr<ValueAttribute<float>> attribute(XMLObjectFactory::create<ValueAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      Assert::IsFalse(attribute->isReference());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataAttribute_IsReference_IsReferenceShouldReturnTrue)
    {
      std::unique_ptr<ReferenceAttribute<float>> attribute(XMLObjectFactory::create<ReferenceAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      Assert::IsTrue(attribute->isReference());
    }

#pragma endregion

#pragma region Clone Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ValueAttribute_Clone_ReturnsNewInstanceOfValueAttribute)
    {
      std::unique_ptr<ValueAttribute<float>> ele(XMLObjectFactory::create<ValueAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      std::unique_ptr<ValueAttribute<float>> ele2(ele->clone());

      AssertExt::IsNotNull(ele2);
      Assert::IsFalse(ele == ele2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ReferenceAttribute_Clone_ReturnsNewInstanceOfReferenceAttribute)
    {
      std::unique_ptr<ReferenceAttribute<float>> ele(XMLObjectFactory::create<ReferenceAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      std::unique_ptr<ReferenceAttribute<float>> ele2(ele->clone());

      AssertExt::IsNotNull(ele2);
      Assert::IsFalse(ele == ele2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataAttribute_Clone_SetsInstanceAttributeNameToSameName)
    {
      std::unique_ptr<ValueAttribute<float>> ele(XMLObjectFactory::create<ValueAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kNotRequired));

      std::unique_ptr<ValueAttribute<float>> ele2(ele->clone());

      Assert::AreEqual(ele->getAttributeName(), ele2->getAttributeName());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataElement_Clone_SetsInstanceValueToSameValue)
    {
      std::unique_ptr<ValueAttribute<float>> ele(XMLObjectFactory::create<ValueAttribute, float>(
        "Test", 5.0f, DeserializationRequirement::kNotRequired));

      std::unique_ptr<ValueAttribute<float>> ele2(ele->clone());

      Assert::AreEqual(ele->getValue(), ele2->getValue());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(DataElement_Clone_SetsInstanceDeserializationRequirementToSameRequirement)
    {
      std::unique_ptr<ValueAttribute<float>> ele(XMLObjectFactory::create<ValueAttribute, float>(
        "Test", 0.0f, DeserializationRequirement::kRequired));

      std::unique_ptr<ValueAttribute<float>> ele2(ele->clone());

      Assert::IsTrue(ele->isRequired());
      Assert::IsTrue(ele2->isRequired());
    }

#pragma endregion

    };
  }
}