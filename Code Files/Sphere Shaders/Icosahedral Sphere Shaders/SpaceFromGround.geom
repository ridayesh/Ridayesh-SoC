#version 440 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 196) out;

uniform mat4 prvw;
uniform vec3 cameraPosGA;
uniform float outer_radius;
uniform float inner_radius;
uniform vec3 center;

struct triangle{
	vec4 pUp;
	vec4 pLeft;
	vec4 pRight;
};

//out vec3 Vcolour;
vec3 Vcolour;
out float opacity;
out vec3 dir;
//out vec3 texCoord;
//out vec3 normal;
//out vec3 truePos;

vec3 lightDir, lightPos, cameraRay, InvWavelength;
vec3 Esun;
float cameraHeight, Kr, Km;

float getNearIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2);
float getFarIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2);
vec4 makeSpherePoint(vec4 v);
float scale(float fcos);
float getMiePhase(float fCos);
float getRayleighPhase(float fCos);
vec3 computeColour(vec3 vertex);
void printTriangle(triangle T);
triangle returnMidTriangle(triangle T);
void getSubTriangles(triangle T, inout triangle subT[4]);


//vec4 terrainPoint(vec4 v);

void main()
{
	cameraHeight = length(cameraPosGA - center);
	InvWavelength = vec3(1/pow(7.0f,4),1/pow(5.4,4),1/pow(4.7,4));
	//Esun = vec3(1.0f,1.0f,1.0f);
	Kr = 0.0021f;
	Km = 0.008f;
	lightPos = vec3(0.0f,650.0f,0.0f);
	//Esun = vec3(1.0f,1.0f,1.0f);
	lightDir = vec3(0.0f,0.0f,1.0f);
	
	Esun = vec3(2000.0f,2000.0f, 2000.0f);
	
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
	Vcolour = computeColour(vec3(makeSpherePoint(T.pUp)));
	dir = vec3(makeSpherePoint(T.pUp)) - cameraPosGA;
	gl_FrontSecondaryColor.rgb = Vcolour * Km*Esun;
	gl_FrontColor.rgb = Vcolour * (InvWavelength * Kr*Esun);
	gl_Position = prvw*makeSpherePoint((T.pUp));
	EmitVertex();
	Vcolour = computeColour(vec3(makeSpherePoint(T.pLeft)));
	dir = vec3(makeSpherePoint(T.pLeft)) - cameraPosGA;
	gl_FrontSecondaryColor.rgb = Vcolour * Km*Esun;
	gl_FrontColor.rgb = Vcolour * (InvWavelength * Kr*Esun);
	gl_Position = prvw*makeSpherePoint((T.pLeft));
	EmitVertex();
	Vcolour = computeColour(vec3(makeSpherePoint(T.pRight)));
	dir = -vec3(makeSpherePoint(T.pRight)) + cameraPosGA;
	gl_FrontSecondaryColor.rgb = Vcolour * Km*Esun;
	gl_FrontColor.rgb = Vcolour * (InvWavelength * Kr*Esun);
	gl_Position = prvw*makeSpherePoint((T.pRight));
	EmitVertex();

	EndPrimitive();
}
vec4 makeSpherePoint(vec4 v)
{
	return vec4(outer_radius*normalize(vec3(v)),1.0f);
}
float scale(float fCos)
{
	float x = 1.0 - fCos;
	return 0.25 * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
}
float getNearIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B - sqrt(fDet));
}
float getFarIntersection(vec3 v3Pos, vec3 v3Ray, float fDistance2, float fRadius2)
{
	float B = 2.0 * dot(v3Pos, v3Ray);
	float C = fDistance2 - fRadius2;
	float fDet = max(0.0, B*B - 4.0 * C);
	return 0.5 * (-B + sqrt(fDet));
}

float getMiePhase(float fCos)
{
	return 2.1 * (1.0 + fCos*fCos) / pow(1.5625 + 1.5*fCos, 1.5);
}
float getRayleighPhase(float fCos)
{
	//return 1.0;
	return 0.75 + 0.75*fCos*fCos;
}
vec3 computeColour(vec3 vertex)
{
	//vec3 vRay = vertex - cameraPosGA;
	vec3 vRay = cameraPosGA - vertex;
	float d_far = length(vRay);
	cameraRay = vRay/d_far;
	float stepLength = d_far/4.0f;
	float ScaledLength = stepLength/(outer_radius - inner_radius);
	//float ScaledLength = sampleLength/(outer_radius - inner_radius);
	//vec3 startVertex = cameraPosGA + cameraRay*d_near;
	vec3 startVertex = vertex;
	float height,LAngle;
	float Angle = dot(startVertex,-cameraRay)/outer_radius;
	float fdepth,fScatter;
	float startOffset = scale(Angle)*exp(-4.0f);
	vec3 v3attenuate;
	vec3 samplePoint = startVertex;
	vec3 colour = vec3(0.0f,0.0f,0.0f);

	for(int i = 0;i<=4;i++)
	{
		samplePoint += cameraRay*stepLength;
		height = length(samplePoint) - inner_radius;
		Angle = dot(-samplePoint,cameraRay)/length(samplePoint);
		LAngle = dot(samplePoint,normalize(lightPos - samplePoint))/length(samplePoint);
		fdepth = exp(4*(height)/(inner_radius - outer_radius));
		fScatter = startOffset + fdepth*(scale(LAngle) - scale(Angle));
		v3attenuate = exp(-fScatter*(InvWavelength*Kr + Km)*12.566371);
		colour += v3attenuate*fdepth*ScaledLength;
	}

	//Angle = dot(normalize(lightPos - vertex),-cameraRay);
	//colour = colour*(getMiePhase(Angle) + getRayleighPhase(Angle));
	//colour = colour*Esun*(Kr*InvWavelength + Km);
	//colour = vec3(0.0f,0.0f,1.0f);
	return colour;
	
}
//
// Atmospheric scattering vertex shader
//
// Author: Sean O'Neil
//
// Copyright (c) 2004 Sean O'Neil
//

//#version 440 core
//
//uniform vec3 cameraPosGA;		// The camera's current position
//vec3 v3LightPos;		// The direction vector to the light source
//vec3 v3InvWavelength;	// 1 / pow(wavelength, 4) for the red, green, and blue channels
//	// The camera's current height
//	// fCameraHeight^2
//uniform float outer_radius;		// The outer (atmosphere) radius
//uniform float fOuterRadius2;	// fOuterRadius^2
//uniform float inner_radius;		// The inner (planetary) radius
//uniform float fInnerRadius2;	// fInnerRadius^2
////uniform float fKrESun;			// Kr * ESun
////uniform float fKmESun;			// Km * ESun
////uniform float fKr4PI;			// Kr * 4 * PI
////uniform float fKm4PI;			// Km * 4 * PI
////uniform float fScale;			// 1 / (fOuterRadius - fInnerRadius)
////uniform float fScaleDepth;		// The scale depth (i.e. the altitude at which the atmosphere's average density is found)
////uniform float fScaleOverScaleDepth;	// fScale / fScaleDepth
//
//float fScale = 1/(outer_radius - inner_radius);
//float fScaleDepth = 0.25;
//float fScaleOverScaleDepth = fScale/fScaleDepth;
//float Kr = 0.2;
//float Km = 0.1;
//vec3 Esun = vec3(2000.0f,2000.0f,2000.0f);
//
//const int nSamples = 2;
//const float fSamples = 2.0;
//
//float scale(float fCos)
//{
//	float x = 1.0 - fCos;
//	return fScaleDepth * exp(-0.00287 + x*(0.459 + x*(3.83 + x*(-6.80 + x*5.25))));
//}
//
//void main(void)
//{
//	// Get the ray from the camera to the vertex, and its length (which is the far point of the ray passing through the atmosphere)
//	vec3 v3Pos = gl_Vertex.xyz;
//	vec3 v3Ray = v3Pos - v3CameraPos;
//	float fFar = length(v3Ray);
//	v3Ray /= fFar;
//
//	// Calculate the ray's starting position, then calculate its scattering offset
//	vec3 v3Start = v3CameraPos;
//	float fHeight = length(v3Start);
//	float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fCameraHeight));
//	float fStartAngle = dot(v3Ray, v3Start) / fHeight;
//	float fStartOffset = fDepth*scale(fStartAngle);
//
//	// Initialize the scattering loop variables
//	//gl_FrontColor = vec4(0.0, 0.0, 0.0, 0.0);
//	float fSampleLength = fFar / fSamples;
//	float fScaledLength = fSampleLength * fScale;
//	vec3 v3SampleRay = v3Ray * fSampleLength;
//	vec3 v3SamplePoint = v3Start + v3SampleRay * 0.5;
//
//	// Now loop through the sample rays
//	vec3 v3FrontColor = vec3(0.0, 0.0, 0.0);
//	for(int i=0; i<nSamples; i++)
//	{
//		float fHeight = length(v3SamplePoint);
//		float fDepth = exp(fScaleOverScaleDepth * (fInnerRadius - fHeight));
//		float fLightAngle = dot(v3LightPos, v3SamplePoint) / fHeight;
//		float fCameraAngle = dot(v3Ray, v3SamplePoint) / fHeight;
//		float fScatter = (fStartOffset + fDepth*(scale(fLightAngle) - scale(fCameraAngle)));
//		vec3 v3Attenuate = exp(-fScatter * (v3InvWavelength * fKr4PI + fKm4PI));
//		v3FrontColor += v3Attenuate * (fDepth * fScaledLength);
//		v3SamplePoint += v3SampleRay;
//	}
//
//	// Finally, scale the Mie and Rayleigh colors and set up the varying variables for the pixel shader
//	gl_FrontSecondaryColor.rgb = v3FrontColor * fKmESun;
//	gl_FrontColor.rgb = v3FrontColor * (v3InvWavelength * fKrESun);
//	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//	v3Direction = v3CameraPos - v3Pos;
//}

