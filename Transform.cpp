#include "Transform.h"

Transform::Transform()
{
  m_translationMatrix = glm::mat4(1);
  m_rotationMatrix = glm::mat4(1);
  m_scaleMatrix = glm::mat4(1);
  m_transformMatrix = glm::mat4(1);
}

Transform::~Transform()
{
}

void Transform::Translate(glm::vec3 position)
{
  m_translationMatrix = glm::translate(glm::mat4(1), position);
}

void Transform::Rotate(float angle, glm::vec3 axis)
{
  m_rotationMatrix = glm::rotate(m_rotationMatrix, angle, axis);
}

void Transform::Rotate(glm::vec3 euler)
{
  m_rotationMatrix = glm::eulerAngleXYZ(euler.x, euler.y, euler.z);
}

void Transform::Scale(glm::vec3 scale) {
  m_scaleMatrix = glm::scale(glm::mat4(1), scale);
}

glm::vec3 Transform::Rigth()
{
  return glm::vec3(
    m_transformMatrix[0][0],
    m_transformMatrix[0][1],
    m_transformMatrix[0][2]
  );
}

glm::vec3 Transform::Up()
{
  return glm::vec3(
    m_transformMatrix[1][0],
    m_transformMatrix[1][1],
    m_transformMatrix[1][2]
  );
}

glm::vec3 Transform::Forward()
{
  return glm::vec3(
    m_transformMatrix[2][0],
    m_transformMatrix[2][1],
    m_transformMatrix[2][2]
  );
}

glm::vec3 Transform::Position()
{
  return glm::vec3(
    m_transformMatrix[3][0],
    m_transformMatrix[3][1],
    m_transformMatrix[3][2]
  );
}

void Transform::UpdateMatrix()
{
  m_transformMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}
