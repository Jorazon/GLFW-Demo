#include "Mesh.h"

Mesh::Mesh() {
  m_vao = 0;
  m_vbo = 0;
  m_vuv = 0;
  m_vno = 0;
  m_modelMatrixID = 0;
  m_inverseTransposeMatrixID = 0;
}

Mesh::~Mesh()
{
  printf("Destructor of %s\n", m_file.c_str());
  Clear();
}

void Mesh::Init(std::string file, GLuint shader)
{
  m_file = file;

  m_translationMatrix = glm::mat4(1);
  m_rotationMatrix = glm::mat4(1);

  m_modelMatrixID = glGetUniformLocation(shader, "mm");
  m_inverseTransposeMatrixID = glGetUniformLocation(shader, "it");

  Load();
}

void Mesh::Clear()
{
  m_vertices.clear();
  m_uvs.clear();
  m_normals.clear();

  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_vuv);
  glDeleteBuffers(1, &m_vno);
  glDeleteVertexArrays(1, &m_vao);
}

void Mesh::DrawMesh()
{
  UpdateMatrix();
  glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_transformMatrix[0][0]);

  glm::mat3 inverseTransposeMatrix = glm::transpose(glm::inverse(glm::mat3(m_transformMatrix)));
  glUniformMatrix3fv(m_inverseTransposeMatrixID, 1, GL_FALSE, &inverseTransposeMatrix[0][0]);

  glUniform1i(m_material.m_colorTexID, 0);
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, m_material.m_colorTex->get());

  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, (int)m_vertices.size());
}

void Mesh::Load()
{
  loadOBJ(m_file.c_str(), m_vertices, m_uvs, m_normals);

  // generate position buffer
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(
    GL_ARRAY_BUFFER,
    m_vertices.size() * sizeof(glm::vec3),
    &m_vertices[0],
    GL_STATIC_DRAW
  );

  // generate UV buffer
  glGenBuffers(1, &m_vuv);
  glBindBuffer(GL_ARRAY_BUFFER, m_vuv);
  glBufferData(
    GL_ARRAY_BUFFER,
    m_uvs.size() * sizeof(glm::vec2),
    &m_uvs[0],
    GL_STATIC_DRAW
  );

  // generate normal buffer
  glGenBuffers(1, &m_vno);
  glBindBuffer(GL_ARRAY_BUFFER, m_vno);
  glBufferData(
    GL_ARRAY_BUFFER,
    m_normals.size() * sizeof(glm::vec3),
    &m_normals[0],
    GL_STATIC_DRAW
  );

  // generate object arrays
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );

  glBindBuffer(GL_ARRAY_BUFFER, m_vuv);
  glVertexAttribPointer(
    1,
    2,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );

  glBindBuffer(GL_ARRAY_BUFFER, m_vno);
  glVertexAttribPointer(
    2,
    3,
    GL_FLOAT,
    GL_FALSE,
    0,
    (void*)0
  );
}
