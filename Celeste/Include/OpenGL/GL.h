#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"


namespace Celeste
{
  class CelesteDllExport GL
  {
    public:
      static bool isInitialized() { return m_initialized; }

      static bool glfw_initialize();
      static bool glew_initialize();
      static bool terminate();

      static bool genBuffer(GLuint& outputBuffer);
      static bool isBuffer(GLuint buffer);
      static void deleteBuffer(GLuint buffer);

      static bool genVertexArray(GLuint& outputVertexArray);
      static bool isVertexArray(GLuint vertexArray);
      static void deleteVertexArray(GLuint vertexArray);

      static GLuint createShader(GLenum shaderType);
      static bool isShader(GLuint shader);
      static void deleteShader(GLuint shader);

      static bool isProgram(GLuint program);
      static void deleteProgram(GLuint program);

    private:
      GL() = delete;
      ~GL() = delete;
      GL(const GL&) = delete;
      GL& operator=(const GL&) = delete;

      static bool m_initialized;
  };
}