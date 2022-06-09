#version 330 core
layout (location = 0) in vec3 aPos; 
layout (location = 2) in vec2 aTexCoord;

out vec3 leniTint;
out vec3 bbmTint;
out vec2 TexCoord;

void main() {
	gl_Position = vec4(aPos, 1.0); 
	leniTint = vec3(1.0f, 0.0f, 0.70f); // LENI
	bbmTint = vec3(1.00f, 0.00f, 0.00f); // BBM
	TexCoord = aTexCoord;
}