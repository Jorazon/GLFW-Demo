#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "GLEW/GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "objloader.hpp"
#include "Transform.h"
#include "Material.h"

class Mesh : public Transform
{
public:
  std::string m_file = "uninitialized mesh";
  Mesh();
  Mesh(Mesh&&) = delete;
  ~Mesh();
  void Init(std::string file, GLuint shader);
  void SetMaterial(Material material) { m_material = material; };
  void DrawMesh();
  void Clear();

private:
  std::vector<glm::vec3> m_vertices;
  std::vector<glm::vec2> m_uvs;
  std::vector<glm::vec3> m_normals;
  GLuint m_vao;// object
  GLuint m_vbo;// position
  GLuint m_vuv;// uv
  GLuint m_vno;// normal

  GLuint m_modelMatrixID;
  GLuint m_inverseTransposeMatrixID;

  Material m_material;

  void Load();
};
