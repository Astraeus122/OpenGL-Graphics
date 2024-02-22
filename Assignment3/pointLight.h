//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : pointLight.h
// Description : Header file for the PointLight class, defining the point light sources.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef POINT_LIGHT_h
#define POINT_LIGHT_h

#include "Light.h"

class PointLight : public Light
{
public:
    float constant;
    float linear;
    float quadratic;

    PointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float constant, float linear, float quadratic);

    void SetUniforms(const Shader& shader, int index) override;

    // Method to get the color of the light, based on its diffuse component
    glm::vec3 GetColor() const 
    {
        return diffuse;
    }

    // Method to get the position of the light
    glm::vec3 GetPosition() const
    {
        return position;
    }
    // Method to set the color of the light
    void SetColor(const glm::vec3& color);

    // Method to enable or disable the point light
    void SetEnabled(bool enabled) 
    {
        this->enabled = enabled;
    }

private:
    bool enabled;
};

#endif