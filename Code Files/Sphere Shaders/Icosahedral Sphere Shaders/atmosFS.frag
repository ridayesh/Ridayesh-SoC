#version 440 core

in vec3 Vcolour;
in float opacity;
out vec4 fragment;

//uniform float opacity;
//uniform sampler2D hdrBuffer;

void main()
{
	//vec3 hdrColour = texture(hdrBuffer,);
	fragment = vec4(Vcolour,opacity);
	//fragment = vec4(0.0f,2.0f,2.0f,1.0f);
}