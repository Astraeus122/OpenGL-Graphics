//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Light.cpp
// Description : Implementation of the Light base class to handle light properties.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#include "Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
    : position(position), ambient(ambient), diffuse(diffuse), specular(specular)
{
}

Light::Light(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
    : ambient(ambient), diffuse(diffuse), specular(specular) 
{

}