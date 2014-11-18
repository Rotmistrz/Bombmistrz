#version 150 core
in vec3 Color;
in vec2 Texture;

out vec4 outColor;
uniform sampler2D tex;
void main() {
   outColor = texture(tex, Texture);// * vec4(Color, 1.0);
}