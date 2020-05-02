#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/Deserializers.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace Celeste;


namespace TestCeleste::Deserialization
{
  CELESTE_TEST_CLASS(TestStringDeserializer)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StringDeserializer_Deserialize_InputtingEmptyText_ReturnsTrue)
  {
    std::string output;
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute("Test", "");

    Assert::AreEqual("", element->Attribute("Test"));
    Assert::IsTrue(deserialize("", output));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StringDeserializer_Deserialize_InputtingEmptyText_SetsOutputToEmptyString)
  {
    std::string output;
    deserialize("", output);

    Assert::IsTrue(output.empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StringDeserializer_Deserialize_InputtingNonEmptyText_ReturnsTrue)
  {
    std::string output;

    Assert::IsTrue(deserialize("Hello World", output));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StringDeserializer_Deserialize_InputtingNonEmptyText_SetsOutputToCorrectString)
  {
    std::string output;
    deserialize("Hello World", output);

    Assert::AreEqual("Hello World", output.c_str());
  }

#pragma endregion

  };
}