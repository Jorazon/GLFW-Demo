#include "shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

std::string readFile(const char* filePath) {
  // open file
  std::cout << "Reading " << filePath << std::endl;
  std::ifstream fileStream(filePath, std::ios::in);

  // handle errors
  if (!fileStream.is_open()) {
    std::cerr << "Could not open " << filePath << std::endl;
    return "";
  }

  // read lines to string
  std::string content;
  std::string line = "";
  while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }

  // close file
  fileStream.close();
  return content;
}

void check(GLuint id) {
  int logLength;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<GLchar> error((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(id, logLength, NULL, &error[0]);
  if (logLength > 0) std::cout << &error[0] << std::endl;
}

GLuint LoadShaders(const char* vertex_shader_path, const char* fragment_shader_path) {
  // read shaders
  std::string vertexShaderStr = readFile(vertex_shader_path);
  std::string fragmentShaderStr = readFile(fragment_shader_path);
  const char* vertexShaderSrc = vertexShaderStr.c_str();
  const char* fragmentShaderSrc = fragmentShaderStr.c_str();

  // compile vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  std::cout << "Compiling vertex shader." << std::endl;
  glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
  glCompileShader(vertexShader);
  check(vertexShader);

  // compile fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  std::cout << "Compiling fragment shader." << std::endl;
  glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
  glCompileShader(fragmentShader);
  check(fragmentShader);

  // link shaders to program
  std::cout << "Linking program" << std::endl;
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  check(program);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}

std::map< GLenum, std::string> type_dictionary = {
  {GL_FLOAT, "float"},
  {GL_FLOAT_VEC2, "vec2"},
  {GL_FLOAT_VEC3, "vec3"},
  {GL_FLOAT_VEC4, "vec4"},
  {GL_DOUBLE, "double"},
  {GL_DOUBLE_VEC2, "dvec2"},
  {GL_DOUBLE_VEC3, "dvec3"},
  {GL_DOUBLE_VEC4, "dvec4"},
  {GL_INT, "int"},
  {GL_INT_VEC2, "ivec2"},
  {GL_INT_VEC3, "ivec3"},
  {GL_INT_VEC4, "ivec4"},
  {GL_UNSIGNED_INT, "unsigned int"},
  {GL_UNSIGNED_INT_VEC2, "uvec2"},
  {GL_UNSIGNED_INT_VEC3, "uvec3"},
  {GL_UNSIGNED_INT_VEC4, "uvec4"},
  {GL_BOOL, "bool"},
  {GL_BOOL_VEC2, "bvec2"},
  {GL_BOOL_VEC3, "bvec3"},
  {GL_BOOL_VEC4, "bvec4"},
  {GL_FLOAT_MAT2, "mat2"},
  {GL_FLOAT_MAT3, "mat3"},
  {GL_FLOAT_MAT4, "mat4"},
  {GL_FLOAT_MAT2x3, "mat2x3"},
  {GL_FLOAT_MAT2x4, "mat2x4"},
  {GL_FLOAT_MAT3x2, "mat3x2"},
  {GL_FLOAT_MAT3x4, "mat3x4"},
  {GL_FLOAT_MAT4x2, "mat4x2"},
  {GL_FLOAT_MAT4x3, "mat4x3"},
  {GL_DOUBLE_MAT2, "dmat2"},
  {GL_DOUBLE_MAT3, "dmat3"},
  {GL_DOUBLE_MAT4, "dmat4"},
  {GL_DOUBLE_MAT2x3, "dmat2x3"},
  {GL_DOUBLE_MAT2x4, "dmat2x4"},
  {GL_DOUBLE_MAT3x2, "dmat3x2"},
  {GL_DOUBLE_MAT3x4, "dmat3x4"},
  {GL_DOUBLE_MAT4x2, "dmat4x2"},
  {GL_DOUBLE_MAT4x3, "dmat4x3"},
  {GL_SAMPLER_1D, "sampler1D"},
  {GL_SAMPLER_2D, "sampler2D"},
  {GL_SAMPLER_3D, "sampler3D"},
  {GL_SAMPLER_CUBE, "samplerCube"},
  {GL_SAMPLER_1D_SHADOW, "sampler1DShadow"},
  {GL_SAMPLER_2D_SHADOW, "sampler2DShadow"},
  {GL_SAMPLER_1D_ARRAY, "sampler1DArray"},
  {GL_SAMPLER_2D_ARRAY, "sampler2DArray"},
  {GL_SAMPLER_1D_ARRAY_SHADOW, "sampler1DArrayShadow"},
  {GL_SAMPLER_2D_ARRAY_SHADOW, "sampler2DArrayShadow"},
  {GL_SAMPLER_2D_MULTISAMPLE, "sampler2DMS"},
  {GL_SAMPLER_2D_MULTISAMPLE_ARRAY, "sampler2DMSArray"},
  {GL_SAMPLER_CUBE_SHADOW, "samplerCubeShadow"},
  {GL_SAMPLER_BUFFER, "samplerBuffer"},
  {GL_SAMPLER_2D_RECT, "sampler2DRect"},
  {GL_SAMPLER_2D_RECT_SHADOW, "sampler2DRectShadow"},
  {GL_INT_SAMPLER_1D, "isampler1D"},
  {GL_INT_SAMPLER_2D, "isampler2D"},
  {GL_INT_SAMPLER_3D, "isampler3D"},
  {GL_INT_SAMPLER_CUBE, "isamplerCube"},
  {GL_INT_SAMPLER_1D_ARRAY, "isampler1DArray"},
  {GL_INT_SAMPLER_2D_ARRAY, "isampler2DArray"},
  {GL_INT_SAMPLER_2D_MULTISAMPLE, "isampler2DMS"},
  {GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, "isampler2DMSArray"},
  {GL_INT_SAMPLER_BUFFER, "isamplerBuffer"},
  {GL_INT_SAMPLER_2D_RECT, "isampler2DRect"},
  {GL_UNSIGNED_INT_SAMPLER_1D, "usampler1D"},
  {GL_UNSIGNED_INT_SAMPLER_2D, "usampler2D"},
  {GL_UNSIGNED_INT_SAMPLER_3D, "usampler3D"},
  {GL_UNSIGNED_INT_SAMPLER_CUBE, "usamplerCube"},
  {GL_UNSIGNED_INT_SAMPLER_1D_ARRAY, "usampler2DArray"},
  {GL_UNSIGNED_INT_SAMPLER_2D_ARRAY, "usampler2DArray"},
  {GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE, "usampler2DMS"},
  {GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, "usampler2DMSArray"},
  {GL_UNSIGNED_INT_SAMPLER_BUFFER, "usamplerBuffer"},
  {GL_UNSIGNED_INT_SAMPLER_2D_RECT, "usampler2DRect"},
  {GL_IMAGE_1D, "image1D"},
  {GL_IMAGE_2D, "image2D"},
  {GL_IMAGE_3D, "image3D"},
  {GL_IMAGE_2D_RECT, "image2DRect"},
  {GL_IMAGE_CUBE, "imageCube"},
  {GL_IMAGE_BUFFER, "imageBuffer"},
  {GL_IMAGE_1D_ARRAY, "image1DArray"},
  {GL_IMAGE_2D_ARRAY, "image2DArray"},
  {GL_IMAGE_2D_MULTISAMPLE, "image2DMS"},
  {GL_IMAGE_2D_MULTISAMPLE_ARRAY, "image2DMSArray"},
  {GL_INT_IMAGE_1D, "iimage1D"},
  {GL_INT_IMAGE_2D, "iimage2D"},
  {GL_INT_IMAGE_3D, "iimage3D"},
  {GL_INT_IMAGE_2D_RECT, "iimage2DRect"},
  {GL_INT_IMAGE_CUBE, "iimageCube"},
  {GL_INT_IMAGE_BUFFER, "iimageBuffer"},
  {GL_INT_IMAGE_1D_ARRAY, "iimage1DArray"},
  {GL_INT_IMAGE_2D_ARRAY, "iimage2DArray"},
  {GL_INT_IMAGE_2D_MULTISAMPLE, "iimage2DMS"},
  {GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY, "iimage2DMSArray"},
  {GL_UNSIGNED_INT_IMAGE_1D, "uimage1D"},
  {GL_UNSIGNED_INT_IMAGE_2D, "uimage2D"},
  {GL_UNSIGNED_INT_IMAGE_3D, "uimage3D"},
  {GL_UNSIGNED_INT_IMAGE_2D_RECT, "uimage2DRect"},
  {GL_UNSIGNED_INT_IMAGE_CUBE, "uimageCube"},
  {GL_UNSIGNED_INT_IMAGE_BUFFER, "uimageBuffer"},
  {GL_UNSIGNED_INT_IMAGE_1D_ARRAY, "uimage1DArray"},
  {GL_UNSIGNED_INT_IMAGE_2D_ARRAY, "uimage2DArray"},
  {GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE, "uimage2DMS"},
  {GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY, "uimage2DMSArray"},
  {GL_UNSIGNED_INT_ATOMIC_COUNTER, "atomic_uint"}
};

const char* getTypeString(GLenum data_type) {
  return type_dictionary.at(data_type).c_str();
}