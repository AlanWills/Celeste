#include "UtilityHeaders/UnitTestHeaders.h"

#include "Resources/Shaders/Program.h"
#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"
#include "OpenGL/GL.h"

using namespace Celeste::Resources;


namespace TestCeleste
{
  namespace Resources
  {
    CELESTE_TEST_CLASS(TestProgram)

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_Constructor_SetsValuesToDefault)
    {
      Program program;

      Assert::AreEqual((GLuint)0, program.getProgramHandle());
      Assert::AreEqual((size_t)0, program.getAttributesCount());
      Assert::AreEqual((size_t)0, program.getUniformsCount());
    }

    //----------------------------------------------------------------------------------------------------------
    void TestProgram::testInitialize()
    {
      getResourceManager().unloadAll<VertexShader>();
      getResourceManager().unloadAll<FragmentShader>();
    }

    //----------------------------------------------------------------------------------------------------------
    void TestProgram::testCleanup()
    {
      getResourceManager().unloadAll<VertexShader>();
      getResourceManager().unloadAll<FragmentShader>();
    }

#pragma region Create From Files Tests

    /*
      sprite.vert contents

      #version 330 core
      layout (location = 0) in vec4 vertex;

      out vec2 TexCoords;

      uniform mat4 model;
      uniform mat4 projection;

      void main()
      {
        TexCoords = vertex.zw;
        gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
      }
    */

    /*
      sprite.frag contents

      #version 330 core
      in vec2 TexCoords;
      out vec4 color;

      uniform sampler2D image;
      uniform vec3 spriteColor;

      void main()
      {
        color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
      }
    */

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromFiles_WithNonExistentVertexShaderPath_DoesNotCreateProgram)
    {
      Program program;
      GLuint p = program.createFromFiles("ThisVertexShaderDoesntExist.vert", TestResources::getSpriteFragmentShaderRelativePath());

      Assert::AreEqual((GLuint)0, p);
      Assert::AreEqual(program.getProgramHandle(), p);
      Assert::IsFalse(Celeste::GL::isProgram(p));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromFiles_WithNonExistentFragmentShaderPath_DoesNotCreateProgram)
    {
      Program program;
      GLuint p = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), "ThisVertexShaderDoesntExist.frag");

      Assert::AreEqual((GLuint)0, p);
      Assert::AreEqual(program.getProgramHandle(), p);
      Assert::IsFalse(Celeste::GL::isProgram(p));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromFiles_WithExistentVertexAndFragmentShaderPaths_CreatesProgram)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        GLuint p = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::AreNotEqual((GLuint)0, p);
        Assert::AreEqual(program.getProgramHandle(), p);
        Assert::IsTrue(Celeste::GL::isProgram(p));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromFiles_WhenProgramAlreadyCreated_DoesNothing)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        GLuint p = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::AreNotEqual((GLuint)0, p);
        Assert::AreEqual(program.getProgramHandle(), p);
        Assert::IsTrue(glIsProgram(p));

        GLuint p2 = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::AreEqual(p2, p);
        Assert::AreEqual(p2, program.getProgramHandle());
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromFiles_PopulatesAttributeAndUniformLookups)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        GLuint p = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::IsTrue(glIsProgram(p));
        Assert::AreEqual((size_t)1, program.getAttributesCount());
        Assert::AreEqual((size_t)4, program.getUniformsCount());
      }
    }

#pragma endregion

#pragma region Create From Code Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromCode_WithEmptyVertexShaderCode_DoesNotCreateProgram)
    {
      std::string spriteFragmentShaderCode(
        "#version 330 core \n \
      in vec2 TexCoord; \n \
      \n \
      out vec4 color; \n \
      \n \
      // Texture samplers \n \
      uniform sampler2D sprite; \n \
      uniform vec4 spriteColour; \n \
      \n \
      void main() \n \
      { \n \
        vec4 actualColour = spriteColour; \n \
        color = actualColour * texture(sprite, TexCoord); \n \
      }");

      Program program;
      GLuint p = program.createFromCode("", spriteFragmentShaderCode);

      Assert::AreEqual((GLuint)0, p);
      Assert::AreEqual(program.getProgramHandle(), p);
      Assert::IsFalse(Celeste::GL::isProgram(p));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromCode_WithInvalidVertexShaderCode_DoesNotCreateProgram)
    {
      std::string invalidCode("ThisIsInvalid");
      std::string spriteFragmentShaderCode(
        "#version 330 core \n \
      in vec2 TexCoord; \n \
      \n \
      out vec4 color; \n \
      \n \
      // Texture samplers \n \
      uniform sampler2D sprite; \n \
      uniform vec4 spriteColour; \n \
      \n \
      void main() \n \
      { \n \
        vec4 actualColour = spriteColour; \n \
        color = actualColour * texture(sprite, TexCoord); \n \
      }");

      Program program;
      GLuint p = program.createFromCode(invalidCode, spriteFragmentShaderCode);

      Assert::AreEqual((GLuint)0, p);
      Assert::AreEqual(program.getProgramHandle(), p);
      Assert::IsFalse(Celeste::GL::isProgram(p));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromCode_WithEmptyFragmentShaderCode_DoesNotCreateProgram)
    {
      std::string spriteVertexShaderCode(
        "#version 330 core \n \
      layout(location = 0) in vec2 position; \n \
      layout(location = 1) in vec2 texCoord; \n \
      \n \
      out vec2 TexCoord; \n \
      \n \
      uniform mat4 projection; \n \
      uniform mat4 view; \n \
      uniform mat4 model; \n \
      \n \
      void main() \n \
      { \n \
        // We swap the y-axis by substracing our coordinates from 1. This is done because most images have the top y-axis inversed with OpenGL's top y-axis. \n \
        TexCoord = vec2(texCoord.x, 1.0 - texCoord.y); \n \
        gl_Position = projection * view * model * vec4(position.xy, 0.0f, 1.0f); \n \
      }");

      Program program;
      GLuint p = program.createFromCode(spriteVertexShaderCode, "");

      Assert::AreEqual((GLuint)0, p);
      Assert::AreEqual(program.getProgramHandle(), p);
      Assert::IsFalse(Celeste::GL::isProgram(p));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromCode_WithInvalidFragmentShaderCode_DoesNotCreateProgram)
    {
      std::string invalidCode("ThisCodeIsInvalid");
      std::string spriteVertexShaderCode(
        "#version 330 core \n \
      layout(location = 0) in vec2 position; \n \
      layout(location = 1) in vec2 texCoord; \n \
      \n \
      out vec2 TexCoord; \n \
      \n \
      uniform mat4 projection; \n \
      uniform mat4 view; \n \
      uniform mat4 model; \n \
      \n \
      void main() \n \
      { \n \
        // We swap the y-axis by substracing our coordinates from 1. This is done because most images have the top y-axis inversed with OpenGL's top y-axis. \n \
        TexCoord = vec2(texCoord.x, 1.0 - texCoord.y); \n \
        gl_Position = projection * view * model * vec4(position.xy, 0.0f, 1.0f); \n \
      }");

      Program program;
      GLuint p = program.createFromCode(spriteVertexShaderCode, invalidCode);

      Assert::AreEqual((GLuint)0, p);
      Assert::AreEqual(program.getProgramHandle(), p);
      Assert::IsFalse(Celeste::GL::isProgram(p));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromCode_WithValidVertexAndFragmentCode_CreatesProgram)
    {
      if (Celeste::GL::isInitialized())
      {
        std::string spriteVertexShaderCode(
          "#version 330 core \n \
      layout(location = 0) in vec2 position; \n \
      layout(location = 1) in vec2 texCoord; \n \
      \n \
      out vec2 TexCoord; \n \
      \n \
      uniform mat4 projection; \n \
      uniform mat4 view; \n \
      uniform mat4 model; \n \
      \n \
      void main() \n \
      { \n \
        // We swap the y-axis by substracing our coordinates from 1. This is done because most images have the top y-axis inversed with OpenGL's top y-axis. \n \
        TexCoord = vec2(texCoord.x, 1.0 - texCoord.y); \n \
        gl_Position = projection * view * model * vec4(position.xy, 0.0f, 1.0f); \n \
      }");

        std::string spriteFragmentShaderCode(
          "#version 330 core \n \
      in vec2 TexCoord; \n \
      \n \
      out vec4 color; \n \
      \n \
      // Texture samplers \n \
      uniform sampler2D sprite; \n \
      uniform vec4 spriteColour; \n \
      \n \
      void main() \n \
      { \n \
        vec4 actualColour = spriteColour; \n \
        color = actualColour * texture(sprite, TexCoord); \n \
      }");

        Program program;
        GLuint p = program.createFromCode(spriteVertexShaderCode, spriteFragmentShaderCode);

        Assert::AreNotEqual((GLuint)0, p);
        Assert::AreEqual(program.getProgramHandle(), p);
        Assert::IsTrue(glIsProgram(p));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromCode_WhenProgramAlreadyCreated_DoesNothing)
    {
      if (Celeste::GL::isInitialized())
      {
        std::string spriteVertexShaderCode(
          "#version 330 core \n \
        layout(location = 0) in vec2 position; \n \
        layout(location = 1) in vec2 texCoord; \n \
        \n \
        out vec2 TexCoord; \n \
        \n \
        uniform mat4 projection; \n \
        uniform mat4 view; \n \
        uniform mat4 model; \n \
        \n \
        void main() \n \
        { \n \
          // We swap the y-axis by substracing our coordinates from 1. This is done because most images have the top y-axis inversed with OpenGL's top y-axis. \n \
          TexCoord = vec2(texCoord.x, 1.0 - texCoord.y); \n \
          gl_Position = projection * view * model * vec4(position.xy, 0.0f, 1.0f); \n \
        }");

        std::string spriteFragmentShaderCode(
          "#version 330 core \n \
        in vec2 TexCoord; \n \
        \n \
        out vec4 color; \n \
        \n \
        // Texture samplers \n \
        uniform sampler2D sprite; \n \
        uniform vec4 spriteColour; \n \
        \n \
        void main() \n \
        { \n \
          vec4 actualColour = spriteColour; \n \
          color = actualColour * texture(sprite, TexCoord); \n \
        }");

        Program program;

        {
          GLuint p = program.createFromCode(spriteVertexShaderCode, spriteFragmentShaderCode);

          Assert::AreNotEqual((GLuint)0, p);
          Assert::AreEqual(program.getProgramHandle(), p);
          Assert::IsTrue(glIsProgram(p));
        }

        {
          GLuint p2 = program.createFromCode(spriteVertexShaderCode, spriteFragmentShaderCode);

          Assert::AreNotEqual((GLuint)0, p2);
          Assert::AreEqual(program.getProgramHandle(), p2);
          Assert::IsTrue(glIsProgram(p2));
        }
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_CreateFromCode_PopulatesAttributeAndUniformLookups)
    {
      if (Celeste::GL::isInitialized())
      {
        std::string spriteVertexShaderCode(
          "#version 330 core \n \
        layout(location = 0) in vec2 position; \n \
        layout(location = 1) in vec2 texCoord; \n \
        \n \
        out vec2 TexCoord; \n \
        \n \
        uniform mat4 projection; \n \
        uniform mat4 view; \n \
        uniform mat4 model; \n \
        \n \
        void main() \n \
        { \n \
          // We swap the y-axis by substracing our coordinates from 1. This is done because most images have the top y-axis inversed with OpenGL's top y-axis. \n \
          TexCoord = vec2(texCoord.x, 1.0 - texCoord.y); \n \
          gl_Position = projection * view * model * vec4(position.xy, 0.0f, 1.0f); \n \
        }");

        std::string spriteFragmentShaderCode(
          "#version 330 core \n \
        in vec2 TexCoord; \n \
        \n \
        out vec4 color; \n \
        \n \
        // Texture samplers \n \
        uniform sampler2D sprite; \n \
        uniform vec4 spriteColour; \n \
        \n \
        void main() \n \
        { \n \
          vec4 actualColour = spriteColour; \n \
          color = actualColour * texture(sprite, TexCoord); \n \
        }");

        Program program;
        GLuint p = program.createFromCode(spriteVertexShaderCode, spriteFragmentShaderCode);

        Assert::IsTrue(glIsProgram(p));
        Assert::AreEqual((size_t)2, program.getAttributesCount());
        Assert::AreEqual((size_t)5, program.getUniformsCount());
      }
    }

#pragma endregion

#pragma region Has Attribute Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_HasAttribute_ShouldReturnTrue)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::IsTrue(program.hasAttribute("vertex"));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_HasAttribute_ShouldReturnFalse)
    {
      Program program;
      program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

      Assert::IsFalse(program.hasAttribute("wubbalubbadubdub"));
      Assert::IsFalse(program.hasAttribute("rickytickytappy"));
    }

#pragma endregion

#pragma region Has Uniform Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_HasUniform_ShouldReturnTrue)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::IsTrue(program.hasUniform("projection"));
        Assert::IsTrue(program.hasUniform("image"));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_HasUniform_ShouldReturnFalse)
    {
      Program program;
      program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

      Assert::IsFalse(program.hasUniform("wubbalubbadubdub"));
      Assert::IsFalse(program.hasUniform("rickytickytappy"));
    }

#pragma endregion

#pragma region Get Attribute Location Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_GetAttributeLocation_ForAttributeThatDoesntExist_ShouldReturnNegativeOne)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::IsTrue(program.hasAttribute("vertex"));
        Assert::AreNotEqual(-1, program.getAttributeLocation("vertex"));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_GetAttributeLocation_ForAttributeThatDoesExist_ShouldReturnPositiveInteger)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::IsFalse(program.hasAttribute("wubbalubbadubdub"));
        Assert::AreEqual(-1, program.getAttributeLocation("wubbalubbadubdub"));
        Assert::IsFalse(program.hasAttribute("rickytickytappy"));
        Assert::AreEqual(-1, program.getAttributeLocation("rickytickytappy"));
      }
    }

#pragma endregion

#pragma region Get Uniform Location Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_GetUniformLocation_ForUniformThatDoesntExist_ShouldReturnNegativeOne)
    {
      Program program;
      program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

      Assert::IsFalse(program.hasUniform("wubbalubbadubdub"));
      Assert::AreEqual(-1, program.getUniformLocation("wubbalubbadubdub"));
      Assert::IsFalse(program.hasUniform("rickytickytappy"));
      Assert::AreEqual(-1, program.getUniformLocation("rickytickytappy"));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_GetUniformLocation_ForUniformThatDoesExist_ShouldReturnPositiveInteger)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::IsTrue(program.hasUniform("projection"));
        Assert::AreNotEqual(-1, program.getUniformLocation("projection"));
        Assert::IsTrue(program.hasUniform("image"));
        Assert::AreNotEqual(-1, program.getUniformLocation("image"));
      }
    }

#pragma endregion

#pragma region Destroy Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_Destroy_WhenProgramNotCreated_DoesNothing)
    {
      Program program;

      Assert::IsFalse(Celeste::GL::isProgram(program.getProgramHandle()));

      program.destroy();

      Assert::IsFalse(Celeste::GL::isProgram(program.getProgramHandle()));
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_Destroy_WhenProgramCreated_DeletesProgram_AndSetsHandleToZero)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        GLuint p = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::AreNotEqual((GLuint)0, p);
        Assert::AreEqual(program.getProgramHandle(), p);
        Assert::IsTrue(glIsProgram(p));

        program.destroy();

        Assert::AreEqual((GLuint)0, program.getProgramHandle());
        Assert::IsFalse(glIsProgram(program.getProgramHandle()));
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_Destroy_ClearsAttributeAndUniformLookups)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        GLuint p = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        Assert::IsTrue(glIsProgram(p));
        Assert::AreNotEqual((size_t)0, program.getAttributesCount());
        Assert::AreNotEqual((size_t)0, program.getUniformsCount());

        program.destroy();

        Assert::AreEqual((size_t)0, program.getAttributesCount());
        Assert::AreEqual((size_t)0, program.getUniformsCount());
      }
    }

#pragma endregion

#pragma region Bind Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_Bind_WithProgramCreated_SetsProgramHandleToBeCurrentActiveProgram)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        GLuint p = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        program.bind();

        GLint id;
        glGetIntegerv(GL_CURRENT_PROGRAM, &id);

        Assert::AreEqual(p, (GLuint)id);
      }
    }

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_Bind_WithProgramNotCreated_LeavesCurrentActiveProgramUnchanged)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program, program2;
        GLuint p = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        program.bind();

        GLint id;
        glGetIntegerv(GL_CURRENT_PROGRAM, &id);

        program2.bind();
        glGetIntegerv(GL_CURRENT_PROGRAM, &id);

        Assert::AreEqual(p, (GLuint)id);
      }
    }

#pragma endregion

#pragma region Unbind Tests

    //----------------------------------------------------------------------------------------------------------
    TEST_METHOD(Program_Unbind_SetsProgramHandleToZero)
    {
      if (Celeste::GL::isInitialized())
      {
        Program program;
        GLuint p = program.createFromFiles(TestResources::getSpriteVertexShaderRelativePath(), TestResources::getSpriteFragmentShaderRelativePath());

        program.bind();

        GLint id;
        glGetIntegerv(GL_CURRENT_PROGRAM, &id);

        Assert::AreEqual(p, (GLuint)id);

        program.unbind();
        glGetIntegerv(GL_CURRENT_PROGRAM, &id);

        Assert::AreEqual(0, id);
      }
    }

#pragma endregion
    };
  }
}