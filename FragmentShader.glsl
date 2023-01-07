#version 330 core

uniform vec3 light_dir;
uniform float light_int;

uniform sampler2D MainTex;

in vec2 uv;
in vec3 normal;

in vec4 gl_FragCoord;

out vec4 color;

const int levels = 8;

const float[16] M = float[16](0,8,2,10,12,4,14,6,3,11,1,9,15,7,13,5); // taika Bayer matrix numerot

vec4 quantize(vec4 original, int levels) {
  levels = max(1, levels);
  return floor(original * levels) / levels;
}

void main() {
  float threshold = M[int(mod(gl_FragCoord.y - 0.5, 4) * 4 + mod(gl_FragCoord.x - 0.5, 4))] / 16; // matrix indeksi pikselin koordinaateista
  
  float nd = max(0.0, dot(normal, light_dir)) * light_int;

  vec4 dither = vec4(threshold / levels);
  vec4 light = quantize(vec4(nd) + dither, levels);

  color = texture(MainTex, uv) * light;
}
