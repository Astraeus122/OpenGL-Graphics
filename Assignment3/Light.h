//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Light.h
// Description : Header file for Light class, defining the basic attributes and functionality of lights.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "Shader.h" 

class Light 
{
public:
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // Constructor for lights with a position (e.g., point lights, spotlights)
    Light(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

    // Constructor for lights without a position (e.g., directional lights)
    Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);  // No position parameter

    virtual void SetUniforms(const Shader& shader, int index = 0) = 0;
};

#endif