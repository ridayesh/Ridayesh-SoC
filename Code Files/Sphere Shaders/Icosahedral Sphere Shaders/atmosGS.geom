#version 440 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 196) out;

uniform mat4 prvw;
uniform vec3 cameraPosGA;
uniform float radius;
uniform vec3 center;

struct triangle{
	vec4 pUp;
	vec4 pLeft;
	vec4 pRight;
};

out vec3 Vcolour;
out float opacity;
//out vec3 texCoord;
//out vec3 normal;
//out vec3 truePos;

vec3 lightDir, lightPos;
vec3 Esun;

vec4 makeSpherePoint(vec4 v);
vec3 computeColour(vec3 vertex);
void printTriangle(triangle T);
triangle returnMidTriangle(triangle T);
void getSubTriangles(triangle T, inout triangle subT[4]);
float returnOpacity();

//vec4 terrainPoint(vec4 v);

void main()
{
	//Esun = vec3(0.996f,1.0f,0.8392f);
	lightPos = vec3(0.0f,110.0f,0.0f);
	Esun = vec3(1.0f,1.0f,1.0f);
	lightDir = vec3(0.0f,0.0f,1.0f);
	
	//Esun = vec3(2000.0f,2000.0f, 2000.0f);
	
	triangle initialT;
	initialT.pUp = gl_in[0].gl_Position;
	initialT.pLeft = gl_in[1].gl_Position;
	initialT.pRight = gl_in[2].gl_Position;
	
		
		triangle subT[4],subSubT[4],subSubSubT[4];
		getSubTriangles(initialT, subT);
		for(int i = 0;i<=3;i++)
		{
			getSubTriangles(subT[i],subSubT);
			for(int h = 0;h<=3;h++)
			{
				getSubTriangles(subSubT[h],subSubSubT);
				for(int l = 0;l<=3;l++)
				{
					printTriangle(subSubSubT[l]);
				}
			}
		}
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
void printTriangle(triangle T)
{
	//vec3 tempNormal = normalize(returnNormal(T));
	//vec3 temp;
	//texCoord = vec3(vec3(T.pUp) - center);
	//normal = tempNormal;
	//temp = displaceLength(vec3(T.pUp));
	//truePos = temp + vec3(T.pUp);
	//gl_Position = prvw*(vec4((vec3(T.pUp) + temp),1.0f));
	opacity = returnOpacity();
	Vcolour = computeColour(vec3(makeSpherePoint(T.pUp)));
	gl_Position = prvw*makeSpherePoint((T.pUp));
	EmitVertex();
	//texCoord = vec3(vec3(T.pLeft) - center);
	//normal = tempNormal;
	//temp = displaceLength(vec3(T.pLeft));
	//truePos = temp + vec3(T.pLeft);
	Vcolour = computeColour(vec3(makeSpherePoint(T.pLeft)));
	gl_Position = prvw*makeSpherePoint((T.pLeft));
	EmitVertex();
	//texCoord = vec3(vec3(T.pRight) - center);
	//normal = tempNormal;
	//temp = displaceLength(vec3(T.pRight));
	//truePos = temp + vec3(T.pRight);
	Vcolour = computeColour(vec3(makeSpherePoint(T.pRight)));
	gl_Position = prvw*makeSpherePoint((T.pRight));
	EmitVertex();

	EndPrimitive();
}
vec4 makeSpherePoint(vec4 v)
{
	return vec4(radius*normalize(vec3(v)),1.0f);
}
vec3 computeColour(vec3 vertex)
{
	float dis = length(vertex - cameraPosGA);
	float theta = dot(normalize(vertex - cameraPosGA),normalize(vertex - lightPos));
	//float g = -0.75f;
	
	float attenuation = 1.6/(1.0 + 0.0014*dis + 0.000007*dis*dis);

	float RSconstant_Blue = 0.056f;
	float RSconstant_Red = 0.605f;
	float RSconstant_Green = 0.109f;
	//float RSconstant_Red = 0.1;
	//float RSconstant_Blue = 0.05;
	//float RSconstant_Green = 0.02;
	vec3 colour;
	vec3 br, bm, L0, Lin, Fex, brT, bmT;
	L0 = vec3(1.8f,1.8f,6.0f);

	br = vec3(RSconstant_Red, RSconstant_Green, RSconstant_Blue);
	//br = vec3(5.5e-6, 13.0e-6, 22.4e-6);
	bm = vec3(0.0021f);
	//bm = vec3(21e-6);

	brT = (0.59683)*(1 + theta*theta)*br;
	bmT = (0.243706)*bm*(1/pow((1.5625f + 1.5*theta),1.5));
	
	Fex = exp(-(bm + br)*dis);

	Lin = ((bmT + brT)/(bm + br))*Esun*(vec3(1.0f,1.0f,1.0f) - Fex);

	colour = L0*Fex + Lin;

	//colour += vec3(0.5f,0.5f,0.5f);

	
	//float R_Scat, G_Scat, B_Scat, R, G, B, K;
	//
	// R_Scat = exp((-RSconstant_Red)*dis);
	// G_Scat = exp((-RSconstant_Green)*dis);
	// B_Scat = exp((-RSconstant_Blue)*dis);
	// K = (0.59683)*(1 + theta*theta)*1.0f;
	//
	// R = 0.01*R_Scat + K*(1 - R_Scat);
	// G = 0.01*G_Scat + K*(1 - G_Scat);
	// B = 0.01*B_Scat + K*(1 - B_Scat);

	 //colour = vec3(R,G,B);

	return (colour)*attenuation;
}

float returnOpacity()
{
	float op;

	float height = max(length(cameraPosGA) - 45.0f, 0.0f);
	if(height < 10.0f && 0.0f<height)
	{
		op = exp((-2.9957)*height);
	}
	else
	{
		op = 0.01f;
	}

	//return op;
	return 1.0f;
}
