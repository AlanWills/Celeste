#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/Shaders/MockFragmentShader.h"
#include "TestResources/TestResources.h"
#include "AutoGLDeallocator.h"
#include "OpenGL/GL.h"

using namespace Celeste::Resources;


namespace TestCeleste
{
  namespace Resources
  {
    CELESTE_TEST_CLASS(TestFragmentShader)

#pragma region Create Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(FragmentShader_Create_WithSourceLoaded_ReturnsShaderHandle)
    {
      if (Celeste::GL::isInitialized())
      {
        FragmentShader shader;
        shader.loadFromFile(TestResources::getSpriteFragmentShaderFullPath());

        GLuint result = shader.create();

        Assert::AreNotEqual((GLuint)0, result);
        Assert::IsTrue(glIsShader(result));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(FragmentShader_Create_WhenAlreadyCreated_ReturnsShaderHandle)
    {
      if (Celeste::GL::isInitialized())
      {
        FragmentShader shader;
        shader.loadFromFile(TestResources::getSpriteFragmentShaderFullPath());

        Assert::AreNotEqual((GLuint)0, shader.create());
        Assert::AreNotEqual((GLuint)0, shader.create());
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(FragmentShader_Create_WithInvalidSourceCode_ReturnsZero)
    {
      MockFragmentShader shader;
      shader.loadFromCode("WubbaLubbaDubDub");

      AutoGLDeallocator deallocator(shader.getShaderHandle_Public());

      Assert::AreEqual((GLuint)0, shader.create());
    }

#pragma endregion

#pragma region Unload Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(FragmentShader_Unload_WithShaderCreated_ClearsSourceCode_AndDeletesShader)
    {
      if (Celeste::GL::isInitialized())
      {
        MockFragmentShader shader;
        shader.loadFromFile(TestResources::getSpriteFragmentShaderFullPath());

        GLuint result = shader.create();

        Assert::AreNotEqual((GLuint)0, result);
        Assert::IsTrue(glIsShader(result));

        shader.unload();

        Assert::AreEqual((GLuint)0, shader.getShaderHandle_Public());
        Assert::IsFalse(glIsShader(shader.getShaderHandle_Public()));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(FragmentShader_Unload_SetsResourceIdToZero)
    {
      MockFragmentShader shader;
      shader.loadFromFile(TestResources::getSpriteFragmentShaderFullPath());

      Assert::AreNotEqual(static_cast<StringId>(0), shader.getResourceId());

      shader.unload();

      Assert::AreEqual(static_cast<StringId>(0), shader.getResourceId());
    }

#pragma endregion
    };
  }
}