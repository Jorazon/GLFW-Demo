#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

class Transform
{
public:
  Transform();
  ~Transform();

  void Translate(glm::vec3 position);
  void Rotate(float angle, glm::vec3 axis);
  void Rotate(glm::vec3 euler);
  void Scale(glm::vec3 scale);
  glm::vec3 Rigth();
  glm::vec3 Up();
  glm::vec3 Forward();
  glm::vec3 Position();
  void UpdateMatrix();

protected:
  glm::mat4 m_translationMatrix;
  glm::mat4 m_rotationMatrix;
  glm::mat4 m_scaleMatrix;
  glm::mat4 m_transformMatrix;
};
