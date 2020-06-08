#version 440 core

in vec3 Vcolour;
out vec4 fragment;

void main()
{
	fragment = vec4(Vcolour,1.0f);
}