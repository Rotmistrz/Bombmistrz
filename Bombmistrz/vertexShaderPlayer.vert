#version 150 core
in vec2 position;
in vec3 color;
in vec2 texture;

out vec3 Color;
out vec2 Texture;

uniform vec2 translation;
void main() {
  Color = color;
  Texture = texture;
  gl_Position = vec4(position.x+translation.x, position.y+translation.y, 0.0, 1.0);
}