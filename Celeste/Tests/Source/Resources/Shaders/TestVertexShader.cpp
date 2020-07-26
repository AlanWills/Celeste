#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/Shaders/MockVertexShader.h"
#include "TestResources/TestResources.h"
#include "OpenGL/GL.h"
#include "TestUtils/RAII/AutoGLDeallocator.h"

using namespace Celeste::Resources;


namespace TestCeleste
{
  namespace Resources
  {
    CELESTE_TEST_CLASS(TestVertexShader)

#pragma region Create Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(VertexShader_Create_WithSourceLoaded_ReturnsShaderHandle)
    {
      if (Celeste::GL::isInitialized())
      {
        VertexShader shader;
        shader.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

        GLuint result = shader.create();
        Assert::AreNotEqual((GLuint)0, result);
        Assert::IsTrue(glIsShader(result));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(VertexShader_Create_WhenAlreadyCreated_ReturnsShaderHandle)
    {
      if (Celeste::GL::isInitialized())
      {
        VertexShader shader;
        shader.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

        Assert::AreNotEqual((GLuint)0, shader.create());
        Assert::AreNotEqual((GLuint)0, shader.create());
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(VertexShader_Create_WithInvalidSourceCode_ReturnsZero)
    {
      MockVertexShader shader;
      shader.loadFromCode("WubbaLubbaDubDub");

      AutoGLDeallocator deallocator(shader.getShaderHandle_Public());

      Assert::AreEqual((GLuint)0, shader.create());
    }

#pragma endregion

#pragma region Unload Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(VertexShader_Unload_WithShaderCreated_ClearsSourceCode_AndDeletesShader)
    {
      if (Celeste::GL::isInitialized())
      {
        MockVertexShader shader;
        shader.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

        GLuint result = shader.create();

        Assert::AreNotEqual((GLuint)0, result);
        Assert::IsTrue(glIsShader(result));

        shader.unload();

        Assert::AreEqual((GLuint)0, shader.getShaderHandle_Public());
        Assert::IsFalse(glIsShader(shader.getShaderHandle_Public()));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(VerteShader_Unload_SetsResourceIdToEmptyStringId)
    {
      MockVertexShader shader;
      shader.loadFromFile(TestResources::getSpriteVertexShaderFullPath());

      Assert::AreNotEqual(string_id(), shader.getResourceId());

      shader.unload();

      Assert::AreEqual(string_id(), shader.getResourceId());
    }

#pragma endregion
    };
  }
}