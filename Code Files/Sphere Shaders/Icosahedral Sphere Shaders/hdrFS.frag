#version 440 core

in vec2 texCoord;
out vec4 fragment;

vec3 hdrColour, mapped;

uniform sampler2D screen;

void main()
{
	const float gamma = 2.2;

	hdrColour = texture(screen,texCoord).rgb;
	mapped = hdrColour / (hdrColour + vec3(1.0f));
	//mapped = pow(mapped, vec3(1.0 / gamma));

	fragment = vec4(mapped,1.0f);

}