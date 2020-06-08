#include "Sphere.h"

void Sphere::spDrawSphere()
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setVec3("colour", colour);
		icos_shader.setFloat("opacity", opacity);
		//icos_shader.setFloat("radius", radius);
		spDrawIcosahedronSphere();
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setVec3("colour", colour);
		atmosShader.setFloat("opacity", opacity);
		spDrawIcosahedronSphere();
	}
	
}

// spSetColour: is used to set the sphere colour and transparency

void Sphere::spSetColour(vec3 spcolour = vec3(0.0f, 0.0f, 1.0f), float spopacity = 1.0f)
{
	colour = spcolour;
	opacity = spopacity;
}

//spVisiblity: used to control visiblity of the sphere

void Sphere::spVisiblity(bool visible)
{
	if (!visible)
		opacity = 0.0f;

}

//spTextureCubeMap: used to add texture to our sphere. This texture must be a cubemap.

void Sphere::spTextureCubeMap(std::string var, int cubemapUnit, std::vector<std::string> paths)
{
	GLuint sphereskybox;
	sphereskybox = spLoadCubemap(paths);
	glActiveTexture(GL_TEXTURE0 + cubemapUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, sphereskybox);

	if (type == 0)
	{
		icos_shader.use();
		//icos_shader.setBool("textured", true);
		icos_shader.setInt(var, cubemapUnit);
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setInt(var, cubemapUnit);
	}

}

//spTextureStatus: used to change visiblity of our texture

void Sphere::spTextureStatus(bool status)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setBool("textured", status);
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setBool("textured",status);
	}
}

void Sphere::spDrawIcosahedronSphere()
{
	
	glGenBuffers(1, &icosVBO);
	glGenVertexArrays(1, &icosVAO);
	glBindVertexArray(icosVAO);
	glBindBuffer(GL_ARRAY_BUFFER, icosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(icosvertices), icosvertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), 0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);

	

	if (type == 0)
	{		
		icos_shader.use();
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		glDrawArrays(GL_PATCHES, 0, 60);
				
	}
	else if (type == 1)
	{
		atmosShader.use();
		glDrawArrays(GL_TRIANGLES, 0, 60);
	}	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

//Following functions are used to set sphere shader variables directly from the main program.

void Sphere::spSetBool(std::string var, bool val)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setBool(var, val);
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setBool(var, val);
	}

}
void Sphere::spSetVec2(std::string var, vec2 val)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setVec2(var, val);
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setVec2(var,val);
	}
}
void Sphere::spSetVec3(std::string var, vec3 val)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setVec3(var, val);
	}
	else if(type == 1)
	{
		atmosShader.use();
		atmosShader.setVec3(var, val);
	}

}
void Sphere::spSetVec4(std::string var, vec4 val)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setVec4(var, val);
	}
	else if(type == 1)
	{
		atmosShader.use();
		atmosShader.setVec4(var, val);
	}
}
void Sphere::spSetMat2(std::string var, mat2 val)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setMat2(var, val);
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setMat2(var, val);
	}
}
void Sphere::spSetMat3(std::string var, mat3 val)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setMat3(var, val);
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setMat3(var, val);
	}

}
void Sphere::spSetMat4(std::string var, mat4 val)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setMat4(var, val);
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setMat4(var, val);
	}

}
void Sphere::spShaderUse()
{
	if (type == 0)
		icos_shader.use();
	else if (type == 1)
		atmosShader.use();
}
void Sphere::spSetInt(std::string var, int val)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setInt(var, val);
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setInt(var, val);
	}

}

void Sphere::spSetFloat(std::string var, float val)
{
	if (type == 0)
	{
		icos_shader.use();
		icos_shader.setFloat(var, val);
	}
	else if (type == 1)
	{
		atmosShader.use();
		atmosShader.setFloat(var, val);
	}

}

// spLoadCubemap: internal private function used to load cubemap.

unsigned int Sphere::spLoadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			GLenum format{};
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

