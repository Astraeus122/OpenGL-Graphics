//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : LightManager.h
// Description : Header file for LightManager class, which manages and updates various light sources in the scene.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "Shader.h"
#include "pointLight.h"
#include "SpotLight.h"
#include <vector>

class LightManager
{
public:
    LightManager();
    ~LightManager();

    void AddPointLight(const PointLight& pointLight);
    void AddSpotLight(const SpotLight& spotLight);

    void UpdateLights(Shader& shader);
    void TogglePointLights();
    void ToggleSpotLight();

    void UpdateSpotLightPositionAndDirection(const glm::vec3& position, const glm::vec3& direction);

private:
    std::vector<PointLight> pointLights;
    SpotLight spotlight;
    bool arePointLightsOn;
    bool isSpotlightOn;
};

#endif
