#include "Scene.h"

#include <fstream>

#include <GLFW/glfw3.h>

#include "shader.h"
#include "objloader.hpp"
#include "Texture.h"
#include "RAW.h"
#include "BMP.h"
#include "Camera.h"
#include "Material.h"

#define CRT_SECURE_NO_WARNINGS

Scene::Scene()
{
  m_shaderID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl");
  glUseProgram(m_shaderID);

  GLint count;
  const GLsizei bufSize = 16; // maximum name length
  GLint size; // size of the variable
  GLenum type; // type of the variable (float, vec3 or mat4, etc)
  GLchar name[bufSize]; // variable name in GLSL
  GLsizei length; // name length

  glGetProgramiv(m_shaderID, GL_ACTIVE_ATTRIBUTES, &count);
  printf("Active attributes: %d\n", count);
  for (GLint i = 0; i < count; i++)
  {
    glGetActiveAttrib(m_shaderID, i, bufSize, &length, &size, &type, name);
    printf("Attribute #%d Type: %s Name: %s\n", i, getTypeString(type), name);
  }
  
  glGetProgramiv(m_shaderID, GL_ACTIVE_UNIFORMS, &count);
  printf("Active uniforms: %d\n", count);
  for (GLint i = 0; i < count; i++)
  {
    glGetActiveUniform(m_shaderID, i, bufSize, &length, &size, &type, name);
    printf("Uniform #%d Type: %s Name: %s\n", i, getTypeString(type), name);
  }

  m_viewMatrixID = glGetUniformLocation(m_shaderID, "vm");
  m_projectionMatrixID = glGetUniformLocation(m_shaderID, "pm");

  m_lightDirectionID = glGetUniformLocation(m_shaderID, "light_dir");
  m_lightAmountID = glGetUniformLocation(m_shaderID, "light_int");

  GLuint m_texture0ID = 0;
  GLuint m_texture1ID = 0;

  m_texture0ID = glGetUniformLocation(m_shaderID, "patternTex");
  m_texture1ID = glGetUniformLocation(m_shaderID, "mainTex");
  
  m_light.Rotate(glm::radians(200.0f), glm::vec3(0, 1, 0));
  m_light.Rotate(glm::radians(-45.0f), glm::vec3(1, 0, 0));
  m_light.UpdateMatrix();

  m_camera.Rotate(glm::radians(225.0f), glm::vec3(0,1,0));
  m_camera.Rotate(glm::radians(-30.0f), glm::vec3(1, 0, 0));

  m_camera.Translate(glm::vec3(-2.5, 5.2f, -2.5f));
  m_camera.UpdateMatrix();
}

Scene::~Scene()
{
  Clear();
}

Mesh* Scene::AddMesh(std::string file)
{
  Mesh* mesh = new Mesh();
  mesh->Init(file, m_shaderID);
  m_meshes.push_back(mesh);
  return mesh;
}

void Scene::DrawScene()
{
  glUseProgram(m_shaderID);
  
  m_camera.Translate(
    glm::vec3(-2.5, 5.2f, -2.5f) + 
    m_camera.Forward() * 
    (float)(((sin(glfwGetTime()) + 1) / 2.0f) * -1)
  );
  
  m_light.UpdateMatrix();
  m_camera.UpdateMatrix();
  glm::mat4 vm = m_camera.GetViewMatrix();
  glm::mat4 pm = m_camera.GetProjectionMatrix();

  glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &vm[0][0]);
  glUniformMatrix4fv(m_projectionMatrixID, 1, GL_FALSE, &pm[0][0]);

  glUniform1f(m_lightAmountID, m_light.m_amount);
  glm::vec3 d = m_light.Forward();
  glUniform3f(m_lightDirectionID, d.x, d.y, d.z);

  for (Mesh* m : m_meshes)
  {
    m->DrawMesh();
  }
}

void Scene::Clear()
{
  for (Mesh* m : m_meshes)
  {
    delete m;
  }
  m_meshes.clear();
}

void Scene::LoadScene(std::string filepath)
{
  std::ifstream file(filepath.c_str(), std::ios::in);

  if (!file.is_open()) {
    printf("Cannot load scene");
    return;
  }
  
  uint32_t count = 0;

  file.read(reinterpret_cast<char*>(&count), sizeof(count));
  printf("Number of objects: %d\n", count);

  for (uint32_t i = 0; i < count; ++i) {
    printf("reading object %d\n", i + 1);
    printf("----\n");

    uint32_t length = 0;

    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    char* meshFileNameBuffer = new char[length + 1];
    file.read(meshFileNameBuffer, length);
    std::string meshFileName;
    meshFileName.append(meshFileNameBuffer, length);
    printf("Mesh: %s\n", meshFileName.c_str());
    
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    char* meshTextureNameBuffer = new char[length + 1];
    file.read(meshTextureNameBuffer, length);
    std::string meshTextureName;
    meshTextureName.append(meshTextureNameBuffer, length);
    printf("Texture: %s\n", meshTextureName.c_str());

    float px, py, pz;
    file.read(reinterpret_cast<char*>(&px), sizeof(float));
    file.read(reinterpret_cast<char*>(&py), sizeof(float));
    file.read(reinterpret_cast<char*>(&pz), sizeof(float));
    glm::vec3 position(px, py, pz);
    printf("\tMesh location: %f, %f, %f\n", px, py, pz);
    
    float rx, ry, rz;
    file.read(reinterpret_cast<char*>(&rx), sizeof(float));
    file.read(reinterpret_cast<char*>(&ry), sizeof(float));
    file.read(reinterpret_cast<char*>(&rz), sizeof(float));
    glm::vec3 rotation(rx, ry, rz);
    printf("\tMesh rotation: %f, %f, %f\n", rx, ry, rz);

    std::string path = filepath.substr(0, filepath.find("/"));

    Mesh* m = new Mesh();
    m->Init(path + "/" + meshFileName, m_shaderID);
    m->Translate(position);
    m->Rotate(rotation);

    Material mat(path + "/" + meshTextureName, m_shaderID);

    m->SetMaterial(mat);

    m_meshes.push_back(m);
  }
}
