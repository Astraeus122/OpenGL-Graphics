//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : SpotLight.h
// Description : Header file for the SpotLight class, defining the interface and properties of a spotlight.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "Light.h"

class SpotLight : public Light 
{
public:
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    bool enabled;  // Whether the spotlight is enabled or not

    // Add attenuation properties if necessary
    float constant = 1.0f;
    float linear = 0.045f; 
    float quadratic = 0.0075f; 

    SpotLight(const glm::vec3& position, const glm::vec3& direction, float cutOff, float outerCutOff,
        const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
        float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f)
        : Light(position, ambient * 1.5f, diffuse * 1.5f, specular), 
        direction(direction), cutOff(cutOff), outerCutOff(outerCutOff),
        constant(constant), linear(linear), quadratic(quadratic)
    {
        enabled = true;
    }


    void SetUniforms(const Shader& shader, int index = 0) override
    {
        shader.setVec3("spotlight.position", position);
        shader.setVec3("spotlight.direction", direction);
        shader.setFloat("spotlight.cutOff", cutOff);
        shader.setFloat("spotlight.outerCutOff", outerCutOff);
        shader.setVec3("spotlight.ambient", ambient);
        shader.setVec3("spotlight.diffuse", diffuse);
        shader.setVec3("spotlight.specular", specular);
        shader.setFloat("spotlight.constant", constant);
        shader.setFloat("spotlight.linear", linear);
        shader.setFloat("spotlight.quadratic", quadratic);
        shader.setBool("spotlight.enabled", enabled);
    }

    void SetEnabled(bool state) 
    {
        enabled = state;
    }

    bool IsEnabled() const 
    {
        return enabled;
    }
};

#endif
