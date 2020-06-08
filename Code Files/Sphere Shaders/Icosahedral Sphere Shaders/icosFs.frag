#version 440 core

layout (early_fragment_tests) in;

out vec4 Fragment;
uniform samplerCube planetTexture;

in vec3 texCoord;
in vec3 normal;
in vec3 truePos;

uniform vec3 colour;
uniform bool textured;

vec3 ambientColor(vec3 lightcolour, float ambient);
vec3 diffuseLighting(vec3 lightcolour, vec3 normal);
float attenuation(vec3 pos);

vec3 result, ambient, diffuse, lightDir;

void main()
{
	lightDir = vec3(0.0f,0.0f,1.0f);
	float d = distance(truePos,vec3(0.0f,0.0f,200.0f));
	float attenuation = 1.6/(1.0 + 0.0014*d + 0.000007*d*d);
	ambient = ambientColor(vec3(1.0f,1.0f,1.0f), 0.1);
	diffuse = diffuseLighting(vec3(1.0f,1.0f,1.0f), normal);
	result = ambient + diffuse;
	result *= attenuation;
	if(textured)
		//Fragment = texture(planetTexture, texCoord);
		Fragment = vec4(result*vec3(texture(planetTexture, texCoord)),1.0f);
	else
		Fragment = vec4(colour, 1.0f);
}
vec3 ambientColor(vec3 lightcolour, float ambient)
{
	return lightcolour*ambient;
}

vec3 diffuseLighting(vec3 lightcolour, vec3 normal)
{
	return lightcolour*max(dot(lightDir,normal), 0.0f);
}

