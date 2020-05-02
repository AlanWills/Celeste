#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/BindingsGenerator.h"
#include "Mocks/Objects/MockScriptableObject.h"
#include "Serialization/MathsSerializers.h"
#include "Deserialization/MathsDeserializers.h"
#include "TestResources/TestResources.h"
#include "TestUtils/Assert/FileAssert.h"

using namespace Celeste::Bindings;


namespace TestCeleste
{

  CELESTE_TEST_CLASS(TestBindingsGenerator)

  //------------------------------------------------------------------------------------------------
  class ScriptableObjectWithFields : public MockScriptableObject
  {
    SCRIPTABLE_OBJECT_BINDINGS_GENERATION(ScriptableObjectWithFields)
    SCRIPTABLE_OBJECT_TYPE_FUNCTION(ScriptableObjectWithFields)

    public:
      static std::string type_name() { return "ScriptableObjectWithFields"; }

      ScriptableObjectWithFields() :
        m_intField(createValueField("int_field", 5)),
        m_stringField(createReferenceField<std::string>("string_field", "Test Value")),
        m_vector2Field(createReferenceField<glm::vec2>("vector2_field", glm::vec2(-5.55f, 12345)))
      {
      }

    private:
      ValueField<int>& m_intField;
      ReferenceField<std::string>& m_stringField;
      ReferenceField<glm::vec2>& m_vector2Field;
  };

  //------------------------------------------------------------------------------------------------
  class ScriptableObjectWithScriptableObject : public MockScriptableObject
  {
    SCRIPTABLE_OBJECT_BINDINGS_GENERATION(ScriptableObjectWithScriptableObject)
    SCRIPTABLE_OBJECT_TYPE_FUNCTION(ScriptableObjectWithScriptableObject)

    public:
      static std::string type_name() { return "ScriptableObjectWithScriptableObject"; }

      ScriptableObjectWithScriptableObject() :
        m_scriptableObject(createScriptableObject<ScriptableObjectWithFields>("Child Scriptable Object"))
      {
      }

    private:
      ScriptableObjectWithFields& m_scriptableObject;
  };

  //------------------------------------------------------------------------------------------------
  class ScriptableObjectWithScriptableObjectFromDifferentNamespace : public MockScriptableObject
  {
    SCRIPTABLE_OBJECT_BINDINGS_GENERATION(ScriptableObjectWithScriptableObjectFromDifferentNamespace)
    SCRIPTABLE_OBJECT_TYPE_FUNCTION(ScriptableObjectWithScriptableObjectFromDifferentNamespace)

    public:
      static std::string type_name() { return "ScriptableObjectWithScriptableObjectFromDifferentNamespace"; }

      ScriptableObjectWithScriptableObjectFromDifferentNamespace() :
        m_scriptableObject(createScriptableObject<MockScriptableObject>("Child Scriptable Object"))
      {
      }

    private:
      MockScriptableObject& m_scriptableObject;
  };

#pragma region Generate Scriptable Object Bindings Tests

#pragma region Inputting Object

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(BindingsGenerator_GenerateScriptableObjectBindings_InputtingObject_FileExists_DoesNothing)
  {
    Path path(TempDirectory::getFullPath(), "MockScriptableObject.cs");
    File file(path);
    file.create(true);
    file.append("Text");

    FileAssert::FileExists(path.as_string());
    FileAssert::FileContentsEqual(path.as_string(), "Text");

    std::unique_ptr<MockScriptableObject> soPtr = ScriptableObject::create<MockScriptableObject>("");
    BindingsGenerator::generateScriptableObjectBindings(Directory(TempDirectory::getFullPath()), Reflection::Type<MockScriptableObject>(), *soPtr);

    FileAssert::FileExists(path.as_string());
    FileAssert::FileContentsEqual(path.as_string(), "Text");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(BindingsGenerator_GenerateScriptableObjectBindings_InputtingObject_GeneratesFieldInfoCorrectly)
  {
    File file(Path(TempDirectory::getFullPath(), "ScriptableObjectWithFields.cs"));
    ScriptableObjectWithFields fields;
    
    FileAssert::FileDoesNotExist(file.getFilePath().as_string());

    BindingsGenerator::generateScriptableObjectBindings(Directory(TempDirectory::getFullPath()), Reflection::Type<ScriptableObjectWithFields>(), fields);

    std::string expected;
    expected.append("using System;\n");
    expected.append("using System.Collections.Generic;\n");
    expected.append("using System.Linq;\n");
    expected.append("using System.Text;\n");
    expected.append("using System.Windows;\n");
    expected.append("using System.Windows.Controls;\n");
    expected.append("using System.Threading.Tasks;\n");
    expected.append("using System.Xml.Serialization;\n");
    expected.append("using BindingsKernel;\n\n");
    expected.append("namespace TestCeleste.TestBindingsGenerator\n");
    expected.append("{\n");
    expected.append("\tpublic class ScriptableObjectWithFields : ScriptableObject");
    expected.append("\n\t{\n");
    expected.append("\t\t[Serialize, DisplayPriority(1)]\n");
    expected.append("\t\t[XmlAttribute(\"int_field\"), DisplayName(\"Int Field\")]\n");
    expected.append("\t\tpublic int IntField { get; set; } = 5;\n\n");
    expected.append("\t\t[Serialize, DisplayPriority(2)]\n");
    expected.append("\t\t[XmlAttribute(\"string_field\"), DisplayName(\"String Field\")]\n");
    expected.append("\t\tpublic string StringField { get; set; } = \"Test Value\";\n\n");
    expected.append("\t\t[Serialize, DisplayPriority(3)]\n");
    expected.append("\t\t[XmlAttribute(\"vector2_field\"), DisplayName(\"Vector2 Field\")]\n");
    expected.append("\t\tpublic Vector2 Vector2Field { get; set; } = new Vector2(-5.550000f, 12345.000000f);\n");
    expected.append("\t}\n");
    expected.append("}");

    FileAssert::FileExists(file.getFilePath().as_string());
    FileAssert::FileContentsEqual(file.getFilePath().as_string(), expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(BindingsGenerator_GenerateScriptableObjectBindings_InputtingObject_GeneratesChildScriptableObjectInfoCorrectly)
  {
    File file(Path(TempDirectory::getFullPath(), "ScriptableObjectWithScriptableObject.cs"));
    ScriptableObjectWithScriptableObject object;

    FileAssert::FileDoesNotExist(file.getFilePath().as_string());

    BindingsGenerator::generateScriptableObjectBindings(Directory(TempDirectory::getFullPath()), Reflection::Type<ScriptableObjectWithScriptableObject>(), object);

    std::string expected;
    expected.append("using System;\n");
    expected.append("using System.Collections.Generic;\n");
    expected.append("using System.Linq;\n");
    expected.append("using System.Text;\n");
    expected.append("using System.Windows;\n");
    expected.append("using System.Windows.Controls;\n");
    expected.append("using System.Threading.Tasks;\n");
    expected.append("using System.Xml.Serialization;\n");
    expected.append("using BindingsKernel;\n\n");
    expected.append("namespace TestCeleste.TestBindingsGenerator\n");
    expected.append("{\n");
    expected.append("\tpublic class ScriptableObjectWithScriptableObject : ScriptableObject");
    expected.append("\n\t{\n");
    expected.append("\t\t[Serialize, DisplayPriority(1)]\n");
    expected.append("\t\t[DisplayName(\"Child Scriptable Object\")]\n");
    expected.append("\t\tpublic ScriptableObjectWithFields ChildScriptableObject { get; set; }\n");
    expected.append("\t}\n");
    expected.append("}");

    FileAssert::FileExists(file.getFilePath().as_string());
    FileAssert::FileContentsEqual(file.getFilePath().as_string(), expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(BindingsGenerator_GenerateScriptableObjectBindings_InputtingObject_AddsRelevantNamespacesForChildScriptableObjects)
  {
    File file(Path(TempDirectory::getFullPath(), "ScriptableObjectWithScriptableObjectFromDifferentNamespace.cs"));
    ScriptableObjectWithScriptableObjectFromDifferentNamespace object;

    FileAssert::FileDoesNotExist(file.getFilePath().as_string());

    BindingsGenerator::generateScriptableObjectBindings(Directory(TempDirectory::getFullPath()), Reflection::Type<ScriptableObjectWithScriptableObjectFromDifferentNamespace>(), object);

    std::string expected;
    expected.append("using CelesteMocks;\n");
    expected.append("using System;\n");
    expected.append("using System.Collections.Generic;\n");
    expected.append("using System.Linq;\n");
    expected.append("using System.Text;\n");
    expected.append("using System.Windows;\n");
    expected.append("using System.Windows.Controls;\n");
    expected.append("using System.Threading.Tasks;\n");
    expected.append("using System.Xml.Serialization;\n");
    expected.append("using BindingsKernel;\n\n");
    expected.append("namespace TestCeleste.TestBindingsGenerator\n");
    expected.append("{\n");
    expected.append("\tpublic class ScriptableObjectWithScriptableObjectFromDifferentNamespace : ScriptableObject");
    expected.append("\n\t{\n");
    expected.append("\t\t[Serialize, DisplayPriority(1)]\n");
    expected.append("\t\t[DisplayName(\"Child Scriptable Object\")]\n");
    expected.append("\t\tpublic MockScriptableObject ChildScriptableObject { get; set; }\n");
    expected.append("\t}\n");
    expected.append("}");

    FileAssert::FileExists(file.getFilePath().as_string());
    FileAssert::FileContentsEqual(file.getFilePath().as_string(), expected);
  }

#pragma endregion

#pragma region Template

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(BindingsGenerator_GenerateScriptableObjectBindings_Template_FileExists_DoesNothing)
  {
    Path path(TempDirectory::getFullPath(), "MockScriptableObject.cs");
    File file(path);
    file.create(true);
    file.append("Text");

    FileAssert::FileExists(path.as_string());
    FileAssert::FileContentsEqual(path.as_string(), "Text");

    BindingsGenerator::generateScriptableObjectBindings<MockScriptableObject>(Directory(TempDirectory::getFullPath()));

    FileAssert::FileExists(path.as_string());
    FileAssert::FileContentsEqual(path.as_string(), "Text");
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(BindingsGenerator_GenerateScriptableObjectBindings_Template_GeneratesFieldInfoCorrectly)
  {
    File file(Path(TempDirectory::getFullPath(), "ScriptableObjectWithFields.cs"));

    FileAssert::FileDoesNotExist(file.getFilePath().as_string());

    BindingsGenerator::generateScriptableObjectBindings<ScriptableObjectWithFields>(Directory(TempDirectory::getFullPath()));

    std::string expected;
    expected.append("using System;\n");
    expected.append("using System.Collections.Generic;\n");
    expected.append("using System.Linq;\n");
    expected.append("using System.Text;\n");
    expected.append("using System.Windows;\n");
    expected.append("using System.Windows.Controls;\n");
    expected.append("using System.Threading.Tasks;\n");
    expected.append("using System.Xml.Serialization;\n");
    expected.append("using BindingsKernel;\n\n");
    expected.append("namespace TestCeleste.TestBindingsGenerator\n");
    expected.append("{\n");
    expected.append("\tpublic class ScriptableObjectWithFields : ScriptableObject");
    expected.append("\n\t{\n");
    expected.append("\t\t[Serialize, DisplayPriority(1)]\n");
    expected.append("\t\t[XmlAttribute(\"int_field\"), DisplayName(\"Int Field\")]\n");
    expected.append("\t\tpublic int IntField { get; set; } = 5;\n\n");
    expected.append("\t\t[Serialize, DisplayPriority(2)]\n");
    expected.append("\t\t[XmlAttribute(\"string_field\"), DisplayName(\"String Field\")]\n");
    expected.append("\t\tpublic string StringField { get; set; } = \"Test Value\";\n\n");
    expected.append("\t\t[Serialize, DisplayPriority(3)]\n");
    expected.append("\t\t[XmlAttribute(\"vector2_field\"), DisplayName(\"Vector2 Field\")]\n");
    expected.append("\t\tpublic Vector2 Vector2Field { get; set; } = new Vector2(-5.550000f, 12345.000000f);\n");
    expected.append("\t}\n");
    expected.append("}");

    FileAssert::FileExists(file.getFilePath().as_string());
    FileAssert::FileContentsEqual(file.getFilePath().as_string(), expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(BindingsGenerator_GenerateScriptableObjectBindings_Template_GeneratesChildScriptableObjectInfoCorrectly)
  {
    File file(Path(TempDirectory::getFullPath(), "ScriptableObjectWithScriptableObject.cs"));

    FileAssert::FileDoesNotExist(file.getFilePath().as_string());

    BindingsGenerator::generateScriptableObjectBindings<ScriptableObjectWithScriptableObject>(Directory(TempDirectory::getFullPath()));

    std::string expected;
    expected.append("using System;\n");
    expected.append("using System.Collections.Generic;\n");
    expected.append("using System.Linq;\n");
    expected.append("using System.Text;\n");
    expected.append("using System.Windows;\n");
    expected.append("using System.Windows.Controls;\n");
    expected.append("using System.Threading.Tasks;\n");
    expected.append("using System.Xml.Serialization;\n");
    expected.append("using BindingsKernel;\n\n");
    expected.append("namespace TestCeleste.TestBindingsGenerator\n");
    expected.append("{\n");
    expected.append("\tpublic class ScriptableObjectWithScriptableObject : ScriptableObject");
    expected.append("\n\t{\n");
    expected.append("\t\t[Serialize, DisplayPriority(1)]\n");
    expected.append("\t\t[DisplayName(\"Child Scriptable Object\")]\n");
    expected.append("\t\tpublic ScriptableObjectWithFields ChildScriptableObject { get; set; }\n");
    expected.append("\t}\n");
    expected.append("}");

    FileAssert::FileExists(file.getFilePath().as_string());
    FileAssert::FileContentsEqual(file.getFilePath().as_string(), expected);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(BindingsGenerator_GenerateScriptableObjectBindings_Template_AddsRelevantNamespacesForChildScriptableObjects)
  {
    File file(Path(TempDirectory::getFullPath(), "ScriptableObjectWithScriptableObjectFromDifferentNamespace.cs"));

    FileAssert::FileDoesNotExist(file.getFilePath().as_string());

    BindingsGenerator::generateScriptableObjectBindings<ScriptableObjectWithScriptableObjectFromDifferentNamespace>(Directory(TempDirectory::getFullPath()));

    std::string expected;
    expected.append("using CelesteMocks;\n");
    expected.append("using System;\n");
    expected.append("using System.Collections.Generic;\n");
    expected.append("using System.Linq;\n");
    expected.append("using System.Text;\n");
    expected.append("using System.Windows;\n");
    expected.append("using System.Windows.Controls;\n");
    expected.append("using System.Threading.Tasks;\n");
    expected.append("using System.Xml.Serialization;\n");
    expected.append("using BindingsKernel;\n\n");
    expected.append("namespace TestCeleste.TestBindingsGenerator\n");
    expected.append("{\n");
    expected.append("\tpublic class ScriptableObjectWithScriptableObjectFromDifferentNamespace : ScriptableObject");
    expected.append("\n\t{\n");
    expected.append("\t\t[Serialize, DisplayPriority(1)]\n");
    expected.append("\t\t[DisplayName(\"Child Scriptable Object\")]\n");
    expected.append("\t\tpublic MockScriptableObject ChildScriptableObject { get; set; }\n");
    expected.append("\t}\n");
    expected.append("}");

    FileAssert::FileExists(file.getFilePath().as_string());
    FileAssert::FileContentsEqual(file.getFilePath().as_string(), expected);
  }

#pragma endregion

#pragma endregion

};

}