#include "Material.h"

#include "BMP.h"

Material::Material()
{
  m_colorTexID = 0;
  m_colorTex = 0;
  m_shader = 0;
}

Material::Material(std::string colorTexFile, GLuint shader) : Material()
{
  printf("Create material.\n");

  printf("Load texture %s.\n", colorTexFile.c_str());
  m_colorTex = new BMP(colorTexFile);
  
  m_shader = shader;

  m_colorTexID = glGetUniformLocation(m_shader, "MainTex");
}

Material::~Material()
{
}

void Material::Clear()
{
  m_colorTex->Clear();
}
