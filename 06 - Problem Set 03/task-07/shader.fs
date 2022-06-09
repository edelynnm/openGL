#version 330 core
out vec4 FragColor;

in vec3 leniTint;
in vec3 bbmTint; 
in vec2 TexCoord;

uniform sampler2D texture1;
uniform bool isLeni;

void main() {
	vec3 tint;

	if(isLeni) {
		tint = leniTint;
	} else {
		tint = bbmTint;
	}

	FragColor = texture(texture1, TexCoord) * vec4(tint, 1.0f);
}