#pragma once

// GLEW
#include <GL/glew.h>

// GLFW
#ifndef GLFW_DLL
#define GLFW_DLL
#endif

#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <iostream>

#include "Debug/Assert.h"


#define GL_FATAL_ERROR_NUMBER 0

#if DEBUG_OPENGL
#define glCheckError()  Celeste::GLHeaders::checkGLError_(__FILE__, __LINE__)
#else
#define glCheckError()
#endif

#if DEBUG_OPENGL
#define glAssert(condition)  ASSERT(condition)
#else
#define glAssert(condition)
#endif

namespace Celeste
{
  class GLHeaders
  {
    public:
      static void checkGLError_(const char *file, int line)
      {
        int count = 0;
        GLenum errorCode;

        while ((errorCode = glGetError()) != GL_NO_ERROR)
        {
          std::string error;
          switch (errorCode)
          {
          case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
          case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
          case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
          case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
          case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
          case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
          case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
          }
          std::cout << error << " | " << file << " (" << line << ")" << std::endl;

          if (++count > GL_FATAL_ERROR_NUMBER)
          {
            // Assert if we have too many errors, otherwise just print them out
            ASSERT(false);
            return;
          }
        }
    }
  };
}