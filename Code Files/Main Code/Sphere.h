#ifndef SPHERE_H
#define SPHERE_H
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <cmath>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stb-master/stb_image.h>

using namespace glm;

class Sphere
{
	//Shader icos_shader{ "C:/Users/Ramesh/Desktop/Planet Atmosphere/Planet-Atmosphere-SoC/Code Files/GLSL Files/icosVs.glsl", "C:/Users/Ramesh/Desktop/Planet Atmosphere/Planet-Atmosphere-SoC/Code Files/GLSL Files/icos_sphereGS.glsl","C:/Users/Ramesh/Desktop/Planet Atmosphere/Planet-Atmosphere-SoC/Code Files/GLSL Files/icosFs.glsl" };
	//Shader icos_shader{ "../../Code Files/Planet/icosVs.txt", "../../Code Files/Planet/icos_sphereTCS.tesc", "../../Code Files/Planet/icos_sphereTES.tese", "../../Code Files/Planet/icos_sphereGS.geom", "../../Code Files/Planet/icosFs.frag" };
	//Shader icos_shader{ "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/icosVs.vert", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/icos_sphereTCS.tesc", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/icos_sphereTES.tese", "", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/icosFs.frag" };
	//Shader icos_shader{ "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/icosVs.vert", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/icos_sphereTCS.tesc", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/icos_sphereTES.tese", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/","../Resources/Sphere Shaders/Icosahedral Sphere Shaders/icosFs.frag" };	
	Shader atmosShader{"../../Code Files/Sphere Shaders/Icosahedral Sphere Shaders/atmosVS.vert", "../../Code Files/Sphere Shaders/Icosahedral Sphere Shaders/atmosGS.geom", "../../Code Files/Sphere Shaders/Icosahedral Sphere Shaders/atmosFS.frag"};
	//Shader atmosShader{ "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/atmosVSNvidia.vert", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/atmosGSNvidia.geom", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/atmosFSNvidia.frag" };
	//Shader atmosShader{ "../Sphere Shaders/Icosahedral Sphere Shaders/SpaceFromGround.vert", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/SpaceFromGround.geom", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/SpaceFromGround.frag" };
	Shader icos_shader{"../../Code Files/Sphere Shaders/Icosahedral Sphere Shaders/icosVs.vert", "../../Code Files/Sphere Shaders/Icosahedral Sphere Shaders/icos_sphereTCS.tesc", "../../Code Files/Sphere Shaders/Icosahedral Sphere Shaders/icos_sphereTES.tese", "../../Code Files/Sphere Shaders/Icosahedral Sphere Shaders/icos_sphereGS.geom", "../../Code Files/Sphere Shaders/Icosahedral Sphere Shaders/icosFS.frag"};

private:

	double icosvertices[180] = {
	   0.0,0.0,1.0,
	   1.0 * cos(atan(0.5)),0.0f,1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 72 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 72 / 180),1.0f * sin(atan(0.5)),
	   0.0,0.0f,1.0f,
	   1.0 * cos(atan(0.5)) * cos(M_PI * 72 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 72 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 144 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 144 / 180),1.0f * sin(atan(0.5)),
	   0.0,0.0f,1.0f,
	   1.0 * cos(atan(0.5)) * cos(M_PI * 144 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 144 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 216 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 216 / 180),1.0f * sin(atan(0.5)),
	   0.0,0.0f,1.0f,
	   1.0 * cos(atan(0.5)) * cos(M_PI * 216 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 216 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 288 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 288 / 180),1.0f * sin(atan(0.5)),
	   0.0,0.0f,1.0f,
	   1.0 * cos(atan(0.5)) * cos(M_PI * 288 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 288 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)),0.0f,1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 288 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 288 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 324 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 324 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)),0.0f,1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 288 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 288 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 252 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 252 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 324 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 324 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 216 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 216 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 252 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 252 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 288 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 288 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 216 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 216 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * (-1),0.0f,-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 252 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 252 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 144 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 144 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * (-1),0.0f,-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 216 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 216 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 144 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 144 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 108 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 108 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * (-1),0.0f,-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 72 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 72 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 108 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 108 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 144 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 144 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 72 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 72 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 36 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 36 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 108 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 108 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)),0.0f,1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 36 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 36 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 72 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 72 / 180),1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)),0.0f,1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 324 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 324 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 36 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 36 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 324 / 180),1.0 * cos(atan(0.5)) * sin(M_PI * 324 / 180),-1.0f * sin(atan(0.5)),
	   0.0,0.0,-1.0,
	   1.0 * cos(atan(0.5)) * cos(M_PI * 36 / 180),1.0f * cos(atan(0.5)) * sin(M_PI * 36 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 36 / 180),1.0f * cos(atan(0.5)) * sin(M_PI * 36 / 180),-1.0f * sin(atan(0.5)),
	   0.0,0.0f,-1.0f,
	   1.0 * cos(atan(0.5)) * cos(M_PI * 108 / 180),1.0f * cos(atan(0.5)) * sin(M_PI * 108 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 108 / 180),1.0f * cos(atan(0.5)) * sin(M_PI * 108 / 180),-1.0f * sin(atan(0.5)),
	   0.0,0.0f,-1.0f,
	   1.0 * cos(atan(0.5)) * (-1),0.0f,-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * (-1),0.0f,-1.0f * sin(atan(0.5)),
	   0.0,0.0f,-1.0f,
	   1.0 * cos(atan(0.5)) * cos(M_PI * 252 / 180),1.0f * cos(atan(0.5)) * sin(M_PI * 252 / 180),-1.0f * sin(atan(0.5)),
	   1.0 * cos(atan(0.5)) * cos(M_PI * 252 / 180),1.0f * cos(atan(0.5)) * sin(M_PI * 252 / 180),-1.0f * sin(atan(0.5)),
	   0.0,0.0f,-1.0f,
	   1.0 * cos(atan(0.5)) * cos(M_PI * 324 / 180),1.0f * cos(atan(0.5)) * sin(M_PI * 324 / 180),-1.0f * sin(atan(0.5))
	};

	
	GLuint icosVBO, icosVAO, hdrFBO, hdrTex, hdrVBO, hdrVAO, hdrRBO;
		
	struct point {
		float x, y, z;
	};
	point center;

	int type;
	
	vec3 colour;
	mat4 spModel{ 1.0f };



public:
	
	float opacity = 1.0f;	
	float outer_radius, inner_radius;

	//Setting up parameters like radius, center coordinates.
	Sphere(float R, float x, float y, float z, int spheretype) :colour(0.0f, 0.0f, 1.0f)
	{
		outer_radius = R;
		center.x = x;
		center.y = y;
		center.z = z;

		type = spheretype;

		spModel = translate(spModel, vec3(x, y, z));

		if (type == 0)
		{
			icos_shader.use();
			icos_shader.setFloat("radius", outer_radius);
			icos_shader.setMat4("spmodel", spModel);
			icos_shader.setVec3("center", vec3(x, y, z));
		}
		else if (type == 1)
		{
			atmosShader.use();
			atmosShader.setFloat("radius",outer_radius);
			//atmosShader.setFloat("outer_radius", outer_radius);
			//atmosShader.setFloat("inner_radius", inner_radius);
			atmosShader.setVec3("center", vec3(x, y, z));
		}

	}
	// some functionalities
private:
	unsigned int spLoadCubemap(std::vector<std::string> path);
	void spDrawIcosahedronSphere();
public:
	void spSetInt(std::string var, int val);
	void spSetFloat(std::string var, float val);
	void spSetBool(std::string var, bool val);
	void spSetVec2(std::string var, vec2 val);
	void spSetVec3(std::string var, vec3 val);
	void spSetVec4(std::string var, vec4 val);
	void spSetMat2(std::string var, mat2 val);
	void spSetMat3(std::string var, mat3 val);
	void spSetMat4(std::string var, mat4 val);
	void spShaderUse();
	void spDrawSphere();
	void spSetColour(vec3 spcolour, float spopacity);
	void spVisiblity(bool visible);
	void spTextureCubeMap(std::string var, int cubemapUnit, std::vector<std::string> paths);
	void spTextureStatus(bool status);
	
};



#endif // !SPHERE_H


