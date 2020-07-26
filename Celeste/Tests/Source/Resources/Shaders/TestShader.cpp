#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"
#include "Mocks/Resources/Shaders/MockShader.h"
#include "OpenGL/GL.h"


namespace TestCeleste
{
  namespace Resources
  {
    CELESTE_TEST_CLASS(TestShader)

#pragma region Load From File Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Shader_LoadFromFile_WithNonExistentPath_ReturnsDoesNotChangeShaderSource)
    {
      MockShader shader;

      Assert::IsTrue(shader.getShaderSource_Public().empty());

      shader.loadFromFile(Path(""));

      Assert::IsTrue(shader.getShaderSource_Public().empty());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Shader_LoadFromFile_WithExistentFilePath_ReturnsTrue)
    {
      MockShader shader;

      Assert::IsTrue(shader.loadFromFile(TestResources::getSpriteVertexShaderFullPath()));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Shader_LoadFromFile_WithExistentFilePath_SetsShaderSourceToFileContents)
    {
      MockShader shader;
      shader.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

      std::string expected;
      File(TestResources::getSpriteVertexShaderFullPath()).read(expected);

      Assert::AreEqual(expected, shader.getShaderSource_Public());
    }

#pragma endregion

#pragma region Load From Code Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Shader_LoadFromCode_SetsShaderSourceToInput)
    {
      MockShader shader;
      shader.loadFromCode("Test");

      Assert::AreEqual("Test", shader.getShaderSource_Public().c_str());
    }

#pragma endregion

#pragma region Create Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Shader_Create_WithNoSourceLoaded_DoesNotThrow_Returns_0)
    {
      MockShader shader;

      GLuint result = shader.create();
      Assert::IsTrue(shader.getShaderSource_Public().empty());
      Assert::AreEqual(static_cast<GLuint>(0), result);
      Assert::IsFalse(Celeste::GL::isShader(result));
    }

#pragma endregion

#pragma region Unload Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Shader_Unload_WithShaderNotCreated_ClearsSourceCode)
    {
      MockShader shader;
      shader.loadFromFile(TestResources::getSpriteVertexShaderFullPath());
      shader.unload();

      Assert::IsTrue(shader.getShaderSource_Public().empty());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Shader_Unload_SetsResourceIdToEmptyStringId)
    {
      MockShader shader;
      shader.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

      Assert::AreNotEqual(string_id(), shader.getResourceId());

      shader.unload();

      Assert::AreEqual(string_id(), shader.getResourceId());
    }

#pragma endregion
    };
  }
}