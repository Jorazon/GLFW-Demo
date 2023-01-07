#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "GLEW/GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Mesh.h"
#include "Light.h"
#include "Camera.h"

class Scene
{
public:
  Scene();
  ~Scene();
  Mesh* AddMesh(std::string file);
  void DrawScene();
  void Clear();
  void LoadScene(std::string filepath);

private:
  GLuint m_viewMatrixID;
  GLuint m_projectionMatrixID;
  GLuint m_shaderID;
  GLuint m_lightAmountID;
  GLuint m_lightDirectionID;

  std::vector<Mesh*> m_meshes;
  Light m_light;
  Camera m_camera;
};
