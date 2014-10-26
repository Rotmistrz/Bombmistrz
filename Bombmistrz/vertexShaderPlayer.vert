#version 150 core
in vec2 position;
in vec3 color;
out vec3 Color;
uniform vec2 translation;
void main() {
   Color = color;
  gl_Position = vec4(position.x+translation.x, position.y+translation.y, 0.0, 1.0);
}