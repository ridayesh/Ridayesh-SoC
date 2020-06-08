#version 440 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 196) out;

uniform mat4 prvw;
uniform vec3 cameraPosG;
uniform mat4 spmodel;
//uniform float radius;
uniform samplerCube heightSample;
uniform vec3 center;

struct triangle{
	vec4 pUp;
	vec4 pLeft;
	vec4 pRight;
};

out vec3 texCoord;
out vec3 normal;
out vec3 truePos;

//vec4 makeSpherePoint(vec4 v);
float getCameraDistance(triangle T);
void printTriangle(triangle T);
triangle returnMidTriangle(triangle T);
void getSubTriangles(triangle T, inout triangle subT[4]);
vec3 displaceLength(vec3 v);
vec3 returnNormal(triangle T);
//vec4 terrainPoint(vec4 v);

void main()
{
	triangle initialT;
	initialT.pUp = gl_in[0].gl_Position;
	initialT.pLeft = gl_in[1].gl_Position;
	initialT.pRight = gl_in[2].gl_Position;
	
	float cameraDis = getCameraDistance(initialT);
	
	//if(cameraDis >= 40.0f)
	//if(cameraDis >= 40.0f)
	//{
	//	printTriangle(initialT);
	//}	
	//else //if(cameraDis >= 15.0f)
		
		triangle subT[4];
		getSubTriangles(initialT, subT);
		for(int i = 0;i<=3;i++)
		{
			printTriangle(subT[i]);
		}	
		
	////else
	//else
	//{
	//	triangle subT[4], subSubT[4];
	//	getSubTriangles(initialT,subT);
	//	for(int i = 0;i<=3;i++)
	//	{
	//		getSubTriangles(subT[i],subSubT);
	//		for(int j = 0;j<=3;j++)
	//		{
	//			printTriangle(subSubT[j]);
	//		}
	//	}
	//}
	//else
	//{
	//	triangle subT[4], subSubT[4], subSubSubT[4];
	//	getSubTriangles(initialT,subT);
	//	for(int i = 0;i<=3;i++)
	//	{
	//		getSubTriangles(subT[i],subSubT);
	//		for(int j = 0;j<=3;j++)
	//		{
	//			getSubTriangles(subSubT[j],subSubSubT);
	//			for(int k = 0;k<=3;k++)
	//			{
	//				printTriangle(subSubSubT[k]);
	//			}
	//		}
	//	}
	//}
	
}
void getSubTriangles(triangle T, inout triangle array[4])
{
	triangle midTT = returnMidTriangle(T);
	triangle subT[4];
	subT[0].pUp = T.pUp;
	subT[0].pLeft = midTT.pUp;
	subT[0].pRight = midTT.pRight;
	subT[1].pUp = midTT.pUp;
	subT[1].pLeft = T.pLeft;
	subT[1].pRight = midTT.pLeft;
	subT[2].pRight = T.pRight;
	subT[2].pUp = midTT.pRight;
	subT[2].pLeft = midTT.pLeft;
	subT[3] = midTT;

	array = subT;
}
triangle returnMidTriangle(triangle T)
{
	triangle mid;
	mid.pUp = (T.pUp + T.pLeft)/2;
	mid.pLeft = (T.pLeft + T.pRight)/2;
	mid.pRight = (T.pRight + T.pUp)/2;
	return mid;
}

float getCameraDistance(triangle T)
{
	float D1, D2, D3;
	
	D1 = distance(vec3(T.pUp),cameraPosG);
	D2 = distance(vec3(T.pLeft),cameraPosG);
	D3 = distance(vec3(T.pRight),cameraPosG);
	
	return ((D1 + D2 + D3)/3);
}
void printTriangle(triangle T)
{
	vec3 tempNormal = normalize(returnNormal(T));
	vec3 temp;
	texCoord = vec3(vec3(T.pUp) - center);
	normal = tempNormal;
	temp = displaceLength(vec3(T.pUp));
	truePos = temp + vec3(T.pUp);
	gl_Position = prvw*spmodel*(vec4((vec3(T.pUp) + temp),1.0f));
	EmitVertex();
	texCoord = vec3(vec3(T.pLeft) - center);
	normal = tempNormal;
	temp = displaceLength(vec3(T.pLeft));
	truePos = temp + vec3(T.pLeft);
	gl_Position = prvw*spmodel*(vec4((vec3(T.pLeft) + temp),1.0f));
	
	EmitVertex();
	texCoord = vec3(vec3(T.pRight) - center);
	normal = tempNormal;
	temp = displaceLength(vec3(T.pRight));
	truePos = temp + vec3(T.pRight);
	gl_Position = prvw*spmodel*(vec4((vec3(T.pRight) + temp),1.0f));
	
	EmitVertex();

	EndPrimitive();

}

vec3 displaceLength(vec3 v)
{
	float displaceFactor = texture(heightSample,(v - center)).x;
	float scale = 6.0f;
	displaceFactor = exp(2.5*displaceFactor) - 1;
	
	return scale*displaceFactor*(normalize(v));
	//return vec3(0.0f);
}

vec3 returnNormal(triangle T)
{
	return cross(vec3(T.pUp - T.pRight), vec3(T.pLeft - T.pRight));
}