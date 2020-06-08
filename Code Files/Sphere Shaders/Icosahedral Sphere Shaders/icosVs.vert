//#version 440 core
//
//layout (location = 0) in vec3 apos;
//
//uniform mat4 mmodel;
//
//void main()
//{	
//	gl_Position = mmodel*vec4(apos, 1.0f);
//}
#version 440 core


layout (location = 0) in vec3 apos;

void main()
{
	gl_Position = vec4(apos,1.0f);
}
