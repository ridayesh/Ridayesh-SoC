#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <stb-master/stb_image.h>
#include <vector>
#include "Sphere.h"

using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path);
unsigned int loadCubemap(std::vector<std::string> faces);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int count = 0;
GLuint skybox, skyboxVAO, skyboxVBO, hdrRBO, hdrVBO, hdrVAO, hdrFBO, hdrTex;
vec3 cameraFront = vec3(0.0f, 0.0f, 1.0f), cameraPos(0.0f, 0.0f, 411.0f), cameraUp(0.0f, -1.0f, 0.0f);
float FOV = 30.0f, currentframe, lastframe, deltatime, lastX = 400.0f, lastY = 400.0f;
bool firstMouse = true;
float sensitivity = 0.05f;
float yawX = 270.0f, pitchY = 0.0f;
mat4 view(1.0f), projection(1.0f), modelTexture(1.0f);
std::vector<std::string> PlanetFaces = {
    "../Resources/Earth Textures/BluePlanet2.png",
    "../Resources/Earth Textures/BluePlanet4.png",
    "../Resources/Earth Textures/BluePlanet5.png",
    "../Resources/Earth Textures/BluePlanet6.png",
    "../Resources/Earth Textures/BluePlanet1.png",
    "../Resources/Earth Textures/BluePlanet3.png"
};
//std::vector<std::string> PlanetFaces = {
//    "../Resources/Earth Textures/EarthRight.jpg",
//    "../Resources/Earth Textures/EarthLeft.jpg",
//    "../Resources/Earth Textures/EarthTop.jpg",
//    "../Resources/Earth Textures/EarthBottom.jpg",
//    "../Resources/Earth Textures/EarthFront.jpg",
//    "../Resources/Earth Textures/EarthBack.jpg"
//};
/*std::vector<std::string> SkyboxFaces = {
    "../Resources/background/skybox images/right.png",
    "../Resources/background/skybox images/left.png",
    "../Resources/background/skybox images/top.png",
    "../Resources/background/skybox images/bot.png",
    "../Resources/background/skybox images/front.png",
    "../Resources/background/skybox images/back.png"

};*/
std::vector<std::string> TerrainMapPath = {
    "../Resources/Earth Textures/HeightMapRight.png",
    "../Resources/Earth Textures/HeightMapBack.png",
    "../Resources/Earth Textures/HeightMapUp.png",
    "../Resources/Earth Textures/HeightMapDown.png",
    "../Resources/Earth Textures/HeightMapFront.png",
    "../Resources/Earth Textures/HeightMapLeft.png"
};
//float skyboxVertices[] = {
//    // Back face
//    -0.5f, -0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//    -0.5f,  0.5f, -0.5f,
//    // Front face
//    -0.5f, -0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    -0.5f, -0.5f,  0.5f,
//    // Left face
//    -0.5f,  0.5f,  0.5f,
//    -0.5f,  0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f, -0.5f,
//    -0.5f, -0.5f,  0.5f,
//    -0.5f,  0.5f,  0.5f,
//    // Right face
//     0.5f,  0.5f,  0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f,  0.5f, -0.5f,
//     0.5f, -0.5f, -0.5f,
//     0.5f,  0.5f,  0.5f,
//     0.5f, -0.5f,  0.5f,
//     // Bottom face
//     -0.5f, -0.5f, -0.5f,
//      0.5f, -0.5f, -0.5f,
//      0.5f, -0.5f,  0.5f,
//      0.5f, -0.5f,  0.5f,
//     -0.5f, -0.5f,  0.5f,
//     -0.5f, -0.5f, -0.5f,
//     // Top face
//     -0.5f,  0.5f, -0.5f,
//      0.5f,  0.5f,  0.5f,
//      0.5f,  0.5f, -0.5f,
//      0.5f,  0.5f,  0.5f,
//     -0.5f,  0.5f, -0.5f,
//     -0.5f,  0.5f,  0.5f,
//};

float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
                               
        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 800, "First Success", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "FAILED TO CREATE WINDOW";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "FAILED TO INITIALIZE GLAD";
    }
    glViewport(0, 0, 800, 800);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    projection = perspective(FOV, 1.0f, 0.1f, 1000.0f);
    /*skybox = loadCubemap(SkyboxFaces);
    Shader skyboxshader("../Resources/background/skybox shaders/skyboxVs.txt", "../Resources/background/skybox shaders/skyboxFs.txt");
    glGenBuffers(1, &skyboxVBO);
    glGenVertexArrays(1, &skyboxVAO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);*/

    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glGenTextures(1, &hdrTex);
    glBindTexture(GL_TEXTURE_2D, hdrTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 800, 800, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, hdrTex, 0);

    glGenRenderbuffers(1, &hdrRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, hdrRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 800);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, hdrRBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Frame buffer not complete" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenBuffers(1, &hdrVBO);
    glGenVertexArrays(1, &hdrVAO);
    glBindVertexArray(hdrVAO);
    glBindBuffer(GL_ARRAY_BUFFER, hdrVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    Sphere trialsphere(400.0f, 0.0f, 0.0f, 0.0f,0);
    trialsphere.spTextureCubeMap("heightSample", 4, TerrainMapPath);
    trialsphere.spTextureCubeMap("planetTexture",1,PlanetFaces);
    trialsphere.spTextureStatus(true);

    
    Sphere atmosphere(410.0f,0.0f,0.0f,0.0f,1);
    

    Shader hdrShader{ "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/hdrVS.vert", "../Resources/Sphere Shaders/Icosahedral Sphere Shaders/hdrFS.frag" };

    while (!glfwWindowShouldClose(window))
    {
        currentframe = glfwGetTime();
        deltatime = abs(currentframe - lastframe);
        lastframe = currentframe;

        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClearColor(10.0f, 10.0f, 10.0f, 10.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
        processInput(window);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        //glDepthMask(GL_FALSE);
        view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        /*glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
        skyboxshader.use();
        skyboxshader.setInt("skybox", 2);
        skyboxshader.setMat4("projectionview", projection * mat4(mat3(view)));
        glBindVertexArray(skyboxVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);
      
        */
        glEnable(GL_CULL_FACE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        trialsphere.spSetMat4("prvw", projection * view);
        trialsphere.spSetVec3("cameraPos", cameraPos);
        trialsphere.spSetVec3("cameraPosG", cameraPos);
        trialsphere.spDrawSphere();
        glDisable(GL_CULL_FACE);
        atmosphere.spSetMat4("prvw", projection * view);
        atmosphere.spSetVec3("cameraPosGA", cameraPos);        
        atmosphere.inner_radius = 400.0f;
        atmosphere.spDrawSphere();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        hdrShader.use();
        glBindVertexArray(hdrVAO);
        glDisable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, hdrTex);
        hdrShader.setInt("screen", 3);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
        count++;
        std::cout << (int)(count / deltatime)<<std::endl;
    }
    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    float cameraspeed = 10 * deltatime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraspeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraspeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= cameraspeed * normalize(cross(cameraUp, cameraFront));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += cameraspeed * normalize(cross(cameraUp, cameraFront));
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        cameraPos -= cameraspeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        cameraPos += cameraspeed * cameraUp;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yawX += xoffset;
    pitchY += yoffset;
    if (pitchY > 89.0f)
        pitchY = 89.0f;
    if (pitchY < -89.0f)
        pitchY = -89.0f;
    vec3 direction;
    direction.x = cos(radians(yawX)) * cos(radians(pitchY));
    direction.y = sin(radians(pitchY));
    direction.z = cos(radians(pitchY)) * sin(radians(yawX));
    cameraFront = normalize(direction);

}
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format{};
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

unsigned int loadCubemap(std::vector<std::string> faces)
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



