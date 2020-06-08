#version 440 core

layout (location = 0) in vec2 apos;
layout (location = 1) in vec2 atex;

out vec2 texCoord;

void main()
{
	texCoord = atex;
	gl_Position = vec4(apos, 0.0f, 1.0f);
}