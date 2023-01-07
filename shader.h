#pragma once

#include <string>
#include <map>

#include <GLEW/GL/glew.h>

GLuint LoadShaders(const char* vertex_shader_path, const char* fragment_shader_path);

const char* getTypeString(GLenum data_type);