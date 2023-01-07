#pragma once

#include <GLEW/GL/glew.h>
#include <glm/glm.hpp>

#include "Transform.h"

class Camera : public Transform
{
public:
  Camera();
  ~Camera();
  void UpdateMatrix();
  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix();

private:
  glm::mat4 m_viewMatrix;
  glm::mat4 m_projectionMatrix;
};
