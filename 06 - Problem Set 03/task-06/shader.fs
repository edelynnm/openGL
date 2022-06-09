#version 330 core
out vec4 FragColor;

in vec3 ourColor; 
in vec2 TexCoord;

uniform sampler2D texture1;
uniform float zoomlvl;

void main() {
	FragColor = texture(texture1, TexCoord / zoomlvl);
}