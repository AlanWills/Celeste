#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/Resources/2D/MockTexture2D.h"
#include "Resources/TestResources.h"
#include "OpenGL/GL.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste
{
  namespace Resources
  {
    CELESTE_TEST_CLASS(TestTexture2D)

#pragma region Load From File Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_LoadFromFile_WithNonExistentTextureFile_LeavesTextureObjectUnchanged)
    {
      MockTexture2D texture;
      texture.loadFromFile(Path("ThisTextureShouldntExist.png"));

      Assert::AreEqual(glm::zero<glm::vec2>(), texture.getDimensions());
      Assert::AreEqual((GLuint)0, texture.getTextureHandle());
      Assert::IsFalse(glIsTexture(texture.getTextureHandle()));
      Assert::AreEqual((GLuint)GL_RGBA, texture.getInternalFormat());
      Assert::AreEqual((GLuint)GL_RGBA, texture.getImageFormat());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_LoadFromFile_WithExistentNonTextureFile_ReturnsFalse)
    {
      MockTexture2D texture;

      Assert::IsFalse(texture.loadFromFile(TestResources::getArialTtfFullPath()));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_LoadFromFile_WithExistentNonTextureFile_LeavesTextureObjectUnchanged)
    {
      MockTexture2D texture;
      texture.loadFromFile(TestResources::getArialTtfFullPath());

      Assert::AreEqual(glm::zero<glm::vec2>(), texture.getDimensions());
      Assert::AreEqual((GLuint)0, texture.getTextureHandle());
      Assert::IsFalse(glIsTexture(texture.getTextureHandle()));
      Assert::AreEqual((GLuint)GL_RGBA, texture.getInternalFormat());
      Assert::AreEqual((GLuint)GL_RGBA, texture.getImageFormat());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_LoadFromFile_WithExistentTextureFile_ReturnsTrue)
    {
      MockTexture2D texture;

      Assert::IsTrue(texture.loadFromFile(TestResources::getBlockPngFullPath()));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_LoadFromFile_WithExistentTextureFile_SetsTextureObjectValues)
    {
      if (GL::isInitialized())
      {
        MockTexture2D texture;
        texture.loadFromFile(TestResources::getBlockPngFullPath());

        Assert::AreNotEqual(glm::zero<glm::vec2>(), texture.getDimensions());
        Assert::AreNotEqual((GLuint)0, texture.getTextureHandle());
        Assert::IsTrue(glIsTexture(texture.getTextureHandle()));
        Assert::AreEqual((GLuint)GL_RGBA, texture.getInternalFormat());
        Assert::AreEqual((GLuint)GL_RGBA, texture.getImageFormat());
      }
    }

#pragma endregion

#pragma region Unload Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_Unload_WithNonloadedTexture_DoesNotThrow)
    {
      MockTexture2D texture;
      texture.unload();

      Assert::AreEqual(glm::zero<glm::vec2>(), texture.getDimensions());
      Assert::AreEqual((GLuint)0, texture.getTextureHandle());
      Assert::IsFalse(glIsTexture(texture.getTextureHandle()));
      Assert::AreEqual((GLuint)GL_RGBA, texture.getInternalFormat());
      Assert::AreEqual((GLuint)GL_RGBA, texture.getImageFormat());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_Unload_WithLoadedTexture_ResetsTextureObject)
    {
      MockTexture2D texture;
      texture.loadFromFile(TestResources::getBlockPngFullPath());
      texture.unload();

      Assert::AreEqual(glm::zero<glm::vec2>(), texture.getDimensions());
      Assert::AreEqual((GLuint)0, texture.getTextureHandle());
      Assert::IsFalse(glIsTexture(texture.getTextureHandle()));
      Assert::AreEqual((GLuint)GL_RGBA, texture.getInternalFormat());
      Assert::AreEqual((GLuint)GL_RGBA, texture.getImageFormat());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_UnloadFromFile_WithNonLoadedTexture2D_SetsResourceIdToZero)
    {
      Texture2D texture;
      texture.loadFromFile(Path("ThisFileShouldntExist.png"));

      Assert::AreEqual(static_cast<StringId>(0), texture.getResourceId());

      texture.unload();

      Assert::AreEqual(static_cast<StringId>(0), texture.getResourceId());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_UnloadFromFile_WithLoadedTexture2D_SetsResourceIdToZero)
    {
      Texture2D texture;
      texture.loadFromFile(TestResources::getBlockPngFullPath());

      Assert::AreNotEqual(static_cast<StringId>(0), texture.getResourceId());

      texture.unload();

      Assert::AreEqual(static_cast<StringId>(0), texture.getResourceId());
    }

#pragma endregion

#pragma region Generate Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_Generate_CreatesNewTexture)
    {
      if (GL::isInitialized())
      {
        MockTexture2D texture;

        Assert::AreEqual(static_cast<GLuint>(0), texture.getTextureHandle());
        Assert::IsFalse(glIsTexture(texture.getTextureHandle()));

        unsigned char data[1];
        texture.generate(1, 1, data);

        Assert::AreNotEqual(static_cast<GLuint>(0), texture.getTextureHandle());
        Assert::IsTrue(glIsTexture(texture.getTextureHandle()));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_Generate_SetsDimensions_ToInputtedValues)
    {
      MockTexture2D texture;

      Assert::AreEqual(glm::zero<glm::vec2>(), texture.getDimensions());

      unsigned char data[10];
      texture.generate(2, 5, data);

      Assert::AreEqual(glm::vec2(2, 5), texture.getDimensions());
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(DISABLED_Texture2D_Generate_SetsPixels_ToInputtedValues)
    {
      if (GL::isInitialized())
      {
        MockTexture2D texture;

        Assert::AreEqual(glm::zero<glm::vec2>(), texture.getDimensions());

        unsigned char data[10]
        {
          0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        };
        texture.generate(2, 5, data);
        
        Assert::Fail();
      }
    }

#pragma endregion

#pragma region Set Wrap S Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_SetWrapS_UpdatesWrapSValue)
    {
      MockTexture2D texture;

      Assert::IsTrue(GL_REPEAT == texture.getWrapS());

      texture.setWrapS(GL_WRAP_BORDER);

      Assert::IsTrue(GL_WRAP_BORDER == texture.getWrapS());
    }

#pragma endregion

#pragma region Set Wrap T Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_SetWrapT_UpdatesWrapTValue)
    {
      MockTexture2D texture;

      Assert::IsTrue(GL_REPEAT == texture.getWrapT());
      
      texture.setWrapT(GL_WRAP_BORDER);

      Assert::IsTrue(GL_WRAP_BORDER == texture.getWrapT());
    }

#pragma endregion

#pragma region Set Pixel Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_SetPixel_InputtingInvalidCoordinate_DoesNothing)
    {
      // Need way to read pixels which I currently can't figure out
      // Come back to these tests I guess
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2D_SetPixel_InputtingValidCoordinate_UpdatesPixelData)
    {
      // Need way to read pixels which I currently can't figure out
      // Come back to these tests I guess
    }

#pragma endregion

    };
  }
}