#include "Camera.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>


Camera::Camera()
{
  m_projectionMatrix = glm::perspective(
    glm::radians(65.0f),
    1.0f,
    0.01f,
    20.0f
  );

  m_viewMatrix = glm::mat4(1.0f);
}

Camera::~Camera()
{
}

void Camera::UpdateMatrix()
{
  Transform::UpdateMatrix();

  float t = (float)glfwGetTime();
  glm::mat4 m(1.0f);
  //m = glm::rotate(m, t, glm::vec3(0, 1, 0));
  m_viewMatrix = glm::inverse(m_transformMatrix) * m;
}

glm::mat4 Camera::GetViewMatrix()
{
  return m_viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
  return m_projectionMatrix;
}
