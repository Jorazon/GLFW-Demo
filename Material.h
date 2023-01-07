#pragma once

#include <string>

#include <GLEW/GL/glew.h>

#include "Texture.h"

class Material
{
public:
  GLuint m_colorTexID;
  Texture* m_colorTex;
  Material();
  Material(std::string colorTexFile, GLuint shader);
  ~Material();
  GLuint GetShader() { return m_shader; };
  void Clear();

private:
  GLuint m_shader;
};

