//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : pointLight.cpp
// Description : Implementation of the PointLight class, handling the properties of the point light sources.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#include "pointLight.h"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float constant, float linear, float quadratic)
    : Light(position, ambient, diffuse, specular), constant(constant), linear(linear), quadratic(quadratic) 
{
}

void PointLight::SetUniforms(const Shader& shader, int index) 
{
    std::string indexStr = std::to_string(index);

    shader.setVec3("pointLights[" + indexStr + "].position", position);
    shader.setVec3("pointLights[" + indexStr + "].ambient", ambient);
    shader.setVec3("pointLights[" + indexStr + "].diffuse", diffuse);
    shader.setVec3("pointLights[" + indexStr + "].specular", specular);

    shader.setFloat("pointLights[" + indexStr + "].constant", constant);
    shader.setFloat("pointLights[" + indexStr + "].linear", linear);
    shader.setFloat("pointLights[" + indexStr + "].quadratic", quadratic);

    // Set the 'enabled' state
    shader.setBool("pointLights[" + std::to_string(index) + "].enabled", enabled); 
}

void PointLight::SetColor(const glm::vec3& color) 
{
    ambient = color * glm::vec3(0.1f); 
    diffuse = color; // main color
    specular = glm::vec3(1.0f, 1.0f, 1.0f); 
}
