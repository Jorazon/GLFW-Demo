#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 mm;
uniform mat4 vm;
uniform mat4 pm;

uniform mat3 it;

out vec2 uv;
out vec3 normal;

void main() {
  gl_Position = pm * vm * mm * vec4(vertex_position, 1);
  uv = vertex_uv;
  normal = normalize(it * vertex_normal);
}
