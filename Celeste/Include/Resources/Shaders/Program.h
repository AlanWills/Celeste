#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>


namespace Celeste::Resources
{
  class Program
  {
    public:
      // Constructor reads and builds the shader
      CelesteDllExport Program();
      CelesteDllExport ~Program();

      CelesteDllExport GLuint createFromFiles(const std::string& vertexShaderRelativePath, const std::string& fragmentShaderRelativePath);
      CelesteDllExport GLuint createFromCode(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
      CelesteDllExport void destroy();

      // Sets the current program as active
      CelesteDllExport void bind() const;
      void unbind() const { glUseProgram(0); }

      bool hasAttribute(const std::string& attributeName) const { return m_attributes.find(attributeName) != m_attributes.end(); }
      bool hasUniform(const std::string& uniformName) const { return m_uniforms.find(uniformName) != m_uniforms.end(); }

      size_t getAttributesCount() const { return m_attributes.size(); }
      size_t getUniformsCount() const { return m_uniforms.size(); }

      GLint getAttributeLocation(const std::string& name) const
      {
        glAssert(hasAttribute(name));
        return hasAttribute(name) ? (*m_attributes.find(name)).second : static_cast<GLint>(-1);
      }

      GLint getUniformLocation(const std::string& name) const
      {
        glAssert(hasUniform(name));
        return hasUniform(name) ? (*m_uniforms.find(name)).second : static_cast<GLint>(-1);
      }

      GLuint getProgramHandle() const { return m_programHandle; }

      // Utility functions
      CelesteDllExport void setFloat(const GLchar* name, GLfloat value) const;
      CelesteDllExport void setInteger(const GLchar* name, GLint value) const;
      CelesteDllExport void setVector2f(const GLchar* name, GLfloat x, GLfloat y) const;
      void setVector2f(const GLchar* name, const glm::vec2& value) const { setVector2f(name, value.x, value.y); }
      CelesteDllExport void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z) const;
      void setVector3f(const GLchar* name, const glm::vec3& value) const { setVector3f(name, value.x, value.y, value.z); }
      CelesteDllExport void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
      void setVector4f(const GLchar* name, const glm::vec4& value) const { setVector4f(name, value.x, value.y, value.z, value.w); }
      CelesteDllExport void setMatrix4(const GLchar* name, const glm::mat4& matrix) const;
      CelesteDllExport void setMatrix4(GLint location, const glm::mat4& matrix) const;

    private:
      GLuint create(GLuint vertexShaderHandle, GLuint fragmentShaderHandle);

      // Compiles the shader from given source code
      void checkCompileErrors();

      // Obtains all of the locations and names of the program's active attributes
      void getAttributeLocations();

      // Obtains all of the locations and names of the program's active uniforms
      void getUniformLocations();

      // The program
      GLuint m_programHandle;

      // A lookup of all the discovered attributes and uniforms along with their locations
      std::unordered_map<std::string, GLint> m_attributes;
      std::unordered_map<std::string, GLint> m_uniforms;
  };
}