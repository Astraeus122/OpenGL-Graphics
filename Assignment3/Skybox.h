//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Skybox.h
// Description : Header file for the Skybox class, defining the interface and structure of the skybox.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>
#include <glew.h>
#include <glm/glm.hpp>
#include "Shader.h"

class Skybox 
{
private:
    GLuint VAO, VBO;
    GLuint cubemapTexture;
    Shader skyboxShader;

public:
    Skybox(const std::vector<std::string>& faces);
    ~Skybox();

    void Render(const glm::mat4& view, const glm::mat4& projection);
    GLuint LoadCubemap(const std::vector<std::string>& faces);
    GLuint GetCubemapTexture() const {
        return cubemapTexture;
    }
};

#endif 
