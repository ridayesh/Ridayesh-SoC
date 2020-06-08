#version 440 core

layout(triangles ,equal_spacing, ccw) in;

uniform float radius;

vec3 pixelPos;

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2);
vec4 makeSpherePoint(vec4 v);

void main()
{
	pixelPos = interpolate3D(vec3(gl_in[0].gl_Position),vec3(gl_in[1].gl_Position),vec3(gl_in[2].gl_Position));
	gl_Position = makeSpherePoint(vec4(pixelPos,1.0f));
}
vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
	return (gl_TessCoord.x*v0 + gl_TessCoord.y*v1 + gl_TessCoord.z*v2);
}
vec4 makeSpherePoint(vec4 v)
{
	return vec4(radius*normalize(vec3(v)),1.0f);
}

