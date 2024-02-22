//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : LightManager.cpp
// Description : Implementation of the LightManager class to coordinate multiple light sources.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#include "LightManager.h"

LightManager::LightManager()
    : arePointLightsOn(true), isSpotlightOn(true),
    spotlight(glm::vec3(0.0f, 5.0f, 5.0f),
        glm::vec3(0.0f, -1.0f, -1.0f),
        glm::cos(glm::radians(12.5f)),
        glm::cos(glm::radians(17.5f)),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(2.0f, 2.0f, 2.0f),
        glm::vec3(1.0f, 1.0f, 1.0f))
{
}

LightManager::~LightManager()
{
}

void LightManager::AddPointLight(const PointLight& pointLight)
{
    pointLights.push_back(pointLight);
}

void LightManager::AddSpotLight(const SpotLight& spotLight)
{
    spotlight = spotLight;
}

void LightManager::UpdateLights(Shader& shader)
{
    for (size_t i = 0; i < pointLights.size(); ++i)
    {
        pointLights[i].SetUniforms(shader, i);
    }
    spotlight.SetUniforms(shader);
}

void LightManager::TogglePointLights()
{
    arePointLightsOn = !arePointLightsOn;
    for (auto& pointLight : pointLights)
    {
        pointLight.SetEnabled(arePointLightsOn);
    }
}

void LightManager::ToggleSpotLight()
{
    isSpotlightOn = !isSpotlightOn;
    spotlight.SetEnabled(isSpotlightOn);
}

void LightManager::UpdateSpotLightPositionAndDirection(const glm::vec3& position, const glm::vec3& direction)
{
    spotlight.position = position;
    spotlight.direction = direction;
}
