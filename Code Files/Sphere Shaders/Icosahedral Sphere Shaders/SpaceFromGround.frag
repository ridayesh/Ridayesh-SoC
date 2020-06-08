#version 440 core

vec3 Vcolour;

in vec3 dir;
//out vec4 Fragment;

float getMiePhase(float fCos);

void main()
{
	float c = dot(normalize(dir),vec3(0.0f,1.0f,0.0f));
	float Mcon = getMiePhase(c);
	gl_FragColor = gl_Color + Mcon * gl_SecondaryColor;
	gl_FragColor.a = gl_FragColor.b;
	//Fragment = vec4(Vcolour,1.0f);
}
float getMiePhase(float fCos)
{
	return 2.1 * (1.0 + fCos*fCos) / pow(1.5625 + 1.5*fCos, 1.5);
}
//float getRayleighPhase(float fCos)
//{
//	//return 1.0;
//	return 0.75 + 0.75*fCos*fCos;
//}