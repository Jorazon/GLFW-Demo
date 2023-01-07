#pragma once

#include <string>
#include <fstream>
#include <errno.h>

#include "GLEW/GL/glew.h"

/**
 * @brief Usage example:
  GLuint textureID = glGetUniformLocation(m_shaderID, "wood");
  Texture *wood = new RAW("wood.raw", 128, 128);
  glUniform1i(textureID, wood->get());
*/
class Texture
{
public:
  Texture() {
    m_textureID = 0;
    // generate texture
    glGenTextures(1, &m_textureID);
  };

  ~Texture() {
    Clear();
  }

  void Activate() {
    glBindTexture(GL_TEXTURE_2D, m_textureID);
  };

  GLint get() { return m_textureID; };

  void Clear() { glDeleteTextures(1, &m_textureID); };

protected:
  virtual void load() = 0;

private:
  GLuint m_textureID;
};
