#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 moveSpeed;

void main()
{
	gl_Position = moveSpeed * vec4(aPos, 1.0f);
}
