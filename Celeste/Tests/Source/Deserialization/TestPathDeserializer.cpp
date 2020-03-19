#include "UtilityHeaders/UnitTestHeaders.h"

#include "Deserialization/Deserializers.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace Celeste;


namespace TestCeleste::Deserialization
{
  CELESTE_TEST_CLASS(TestPathDeserializer)

#pragma region Deserialize Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PathDeserializer_Deserialize_InputtingEmptyText_ReturnsTrue)
  {
    Path output("");
    XMLDocument document;
    XMLElement* element = document.NewElement("Test");
    element->SetAttribute("Test", "");

    Assert::AreEqual("", element->Attribute("Test"));
    Assert::IsTrue(deserialize("", output));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PathDeserializer_Deserialize_InputtingEmptyText_SetsOutputToEmptyString)
  {
    Path output("");
    deserialize("", output);

    Assert::IsTrue(output.as_string().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PathDeserializer_Deserialize_InputtingNonEmptyText_ReturnsTrue)
  {
    Path output("");

    Assert::IsTrue(deserialize("Hello World", output));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(PathDeserializer_Deserialize_InputtingNonEmptyText_SetsOutputToCorrectString)
  {
    Path output("");
    deserialize("HelloWorld/Test\\Path.xml", output);

    Assert::AreEqual("HelloWorld/Test\\Path.xml", output.c_str());
  }

#pragma endregion

  };
}