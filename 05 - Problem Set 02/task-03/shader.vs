#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;
uniform float offset;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
   vertexColor = vec4(aPos, 1.0f); // setting color
}
