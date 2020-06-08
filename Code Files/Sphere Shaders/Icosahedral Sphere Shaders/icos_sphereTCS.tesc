#version 440 core

layout (vertices = 3) out;

uniform vec3 cameraPos;

float Distance0, Distance1, Distance2;

float getTessLevel(float D1, float D2);

void main()
{
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	Distance0 = distance(cameraPos, vec3(gl_in[0].gl_Position));
	Distance1 = distance(cameraPos, vec3(gl_in[1].gl_Position));
	Distance2 = distance(cameraPos, vec3(gl_in[2].gl_Position));

	gl_TessLevelOuter[0] = getTessLevel(Distance1, Distance2);
	gl_TessLevelOuter[1] = getTessLevel(Distance0, Distance2);
	gl_TessLevelOuter[2] = getTessLevel(Distance0, Distance1);
	gl_TessLevelInner[0] = gl_TessLevelOuter[0];
		
}

float getTessLevel(float D1, float D2)
{
	if(((D1 + D2)/2.0f) >= 100.0f)
		return 5.0f;
	else if(((D1 + D2)/2.0f) >= 70.0f)
		return 10.0f;
	else if(((D1 + D2)/2.0f) >= 40.0f)
		return 15.0f;
	else if(((D1+D2)/2.0f) >= 30.0f)
		return 50.0f;
	else
		return 64.0f;
}
