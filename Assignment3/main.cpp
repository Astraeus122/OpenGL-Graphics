//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : main.cpp
// Description : The main application of the program, implements all the classes here
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

// C++ libraries
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

//Open GL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Local Includes
#include "TextureLoader.h"
#include "Shader.h"
#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"
#include "pointLight.h"
#include "SpotLight.h"
#include "LightManager.h"
#include "Pyramid.h"
#include "Skybox.h"
#include "TextureManager.h"

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Technical Demo 3", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Define the viewport dimensions
    glViewport(0, 0, 1920, 1080);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    glfwSetCursorPosCallback(window, Camera::MouseCallback);
    glfwSetScrollCallback(window, Camera::ScrollCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    std::vector<std::string> faces 
    {
        "Textures/skybox/RightSkyCube.jpg",
            "Textures/skybox/LeftSkyCube.jpg",
            "Textures/skybox/TopSkyCube.jpg",
            "Textures/skybox/BottomSkyCube.jpg",
            "Textures/skybox/FrontSkyCube.jpg",
            "Textures/skybox/BackSkyCube.jpg"
    };
    Skybox skybox(faces);

    // Load and bind the reflection control map
    GLuint reflectionControlMapTexture = TextureManager::getInstance()->getTexture("Textures/reflectionMap.png");

    // Load the cube map for reflections
    GLuint reflectionMapTexture = skybox.LoadCubemap(faces);

    // Shader for the skybox
    Shader skyboxShader("SkyboxVertexShader.txt", "SkyboxFragShader.txt");
    if (!skyboxShader.isCompiled())
    {
        std::cerr << "Failed to compile/link skybox shaders.\n";
        return -1;
    }

    // Create a LightManager instance
    LightManager lightManager;

    // Create a pyramid instance
    Pyramid pyramid;

    // Create Shader object for the spheres
    Shader sphereShader("vertexShader.txt", "FragmentShader.txt");

    // Create Sphere objects and set their positions and textures
    std::vector<Sphere> spheres(10, Sphere(40, 40));
    std::vector<glm::vec3> spherePositions(10);
    std::vector<GLuint> textures(10);

    // Use TextureManager to load the texture once and use it for all spheres
    GLuint sharedTexture = TextureManager::getInstance()->getTexture("Textures/AwesomeFace.png");

    for (int i = 0; i < 10; ++i) {
        textures[i] = sharedTexture;
        spherePositions[i] = glm::vec3(
            (std::rand() % 100) / 100.0f * 10.0f - 5.0f,
            (std::rand() % 100) / 100.0f * 10.0f - 5.0f,
            (std::rand() % 100) / 100.0f * 10.0f - 5.0f
        );
    }

    // Sphere with rim lighting
    Sphere rimLightSphere(50, 50);
    glm::vec3 rimSpherePosition = glm::vec3(3.0f, 0.0f, 0.0f);
    GLuint rimSphereTexture = sharedTexture;


    // Camera setup
    Camera camera(glm::vec3(0.0f, 0.0f, 15.0f));

    // For handling key presses
    bool wasPressed1 = false;
    bool wasPressed2 = false;
    bool wasPressed3 = false;

    glEnable(GL_CULL_FACE); // Enable back-face culling
    glCullFace(GL_BACK);    // Cull back-faces
    glFrontFace(GL_CCW);    // Front faces are defined counter-clockwise
    glEnable(GL_MULTISAMPLE); // Enable MSAA

    bool wireframeMode = false; // To keep track of the wireframe mode state

    // Define the initial colors and states for the lights
    bool isDirectionalLightOn = true; // Initially, the directional light is on.
    glm::vec3 directionalLightColor = glm::vec3(1.0f, 0.0f, 0.0f);  // Red color for directional light

    // Create point lights and add them to the LightManager
    std::vector<PointLight> pointLights
    {
        PointLight(glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.4f, 1.4f, 0.4f), glm::vec3(0.5f, 1.5f, 0.5f), 1.0f, 0.09, 0.032), // darker green color
            PointLight(glm::vec3(2.3f, -3.3f, -6.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.4f, 1.4f, 0.4f), glm::vec3(0.5f, 1.5f, 0.5f), 1.0f, 0.09, 0.032)
    };

    for (const auto& pointLight : pointLights)
    {
        lightManager.AddPointLight(pointLight);
    }

    // Create spotlight and add it to the LightManager
    SpotLight spotlight
    (
        glm::vec3(0.0f, 5.0f, 5.0f),    // position
        glm::vec3(0.0f, -1.0f, -1.0f), // direction
        glm::cos(glm::radians(20.0f)),  // wider cutOff angle to make it more visible
        glm::cos(glm::radians(25.0f)),  // wider outerCutOff angle to make it more visible
        glm::vec3(0.2f, 0.2f, 0.8f),    // Ambient for vlue
        glm::vec3(0.0f, 0.0f, 4.0f),    // Diffuse for blue
        glm::vec3(1.0f, 1.0f, 1.0f),    // specular (white for shininess)
        1.0f,                           // constant attenuation
        0.045f,                         // linear attenuation
        0.0075f                         // quadratic attenuation 
    );

    lightManager.AddSpotLight(spotlight);

    // Shader for rendering the lights
    Shader lightShader("lightMarkerVertex.txt", "lightMarkerFragment.txt");

    // Cube for representing the lights in the scene
    Cube lightCube;

    // Current time
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Check for events and clear buffers
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Updating time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Use sphere shader
        sphereShader.use();

        // Set camera and projection matrices (only once, im an idiot and keep redoing it dont do it ryan)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)1920 / (float)1080, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        sphereShader.setVec3("viewPos", camera.Position);
        sphereShader.setMat4("projection", projection);
        sphereShader.setMat4("view", view);

        // Set the uniform for the directional light
        sphereShader.setBool("isDirectionalLightOn", isDirectionalLightOn);
        sphereShader.setVec3("directionalLightColor", directionalLightColor);

        // Update lights in the LightManager
        lightManager.UpdateLights(sphereShader);

        // Toggle lights based on key presses
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !wasPressed1)
        {
            wasPressed1 = true;
            lightManager.TogglePointLights();
        }
        else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE)
        {
            wasPressed1 = false;
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !wasPressed2)
        {
            wasPressed2 = true;
            isDirectionalLightOn = !isDirectionalLightOn; // Toggle the directional light.
        }
        else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE)
        {
            wasPressed2 = false;
        }

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !wasPressed3)
        {
            wasPressed3 = true;
            lightManager.ToggleSpotLight();
        }
        else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_RELEASE)
        {
            wasPressed3 = false;
        }
        // Toggle wireframe mode on '4' key press
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        {
            wireframeMode = !wireframeMode;
            if (wireframeMode)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Normal mode
        }

        // Close the application on escape key press
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        
        // Camera movement
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            camera.ProcessKeyboard(UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            camera.ProcessKeyboard(DOWN, deltaTime);

        // Update the spotlight to follow the camera
        lightManager.UpdateSpotLightPositionAndDirection(camera.Position, camera.Front);

        // Update lights in the LightManager
        lightManager.UpdateLights(sphereShader);

        // Render the skybox
        glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
        glm::mat4 skyboxView = glm::mat4(glm::mat3(view)); // Remove translation for the skybox
        skybox.Render(skyboxView, projection);
        glDepthFunc(GL_LESS); // Set depth function back to default
       
        // Render the point lights as cubes
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        for (const auto& pointLight : pointLights)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLight.GetPosition());
            model = glm::scale(model, glm::vec3(0.2f));
            lightShader.setMat4("model", model);
            lightShader.setVec3("lightColor", pointLight.GetColor());

            lightCube.Render(lightShader);
        }

        // Render spheres with textures
        sphereShader.use();
        sphereShader.setBool("applyReflection", false); // Disable reflection for normal spheres
        sphereShader.setBool("applyRimLighting", false); // Disable rim lighting for normal spheres
        for (size_t i = 0; i < spheres.size(); ++i)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, spherePositions[i]);
            model = glm::scale(model, glm::vec3(0.5f));
            float timeValue = glfwGetTime();
            model = glm::rotate(model, timeValue * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

            sphereShader.setMat4("model", model);
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            sphereShader.setInt("texture1", 0);

            spheres[i].Draw(sphereShader.getProgramID());
        }

        // Render the rim lighted sphere
        sphereShader.setBool("applyRimLighting", true);
        sphereShader.setVec3("rimColor", glm::vec3(1.0f, 1.0f, 1.0f));
        sphereShader.setFloat("rimStrength", 0.5f); 

        glm::mat4 rimSphereModel = glm::mat4(1.0f);
        rimSphereModel = glm::translate(rimSphereModel, rimSpherePosition);
        sphereShader.setMat4("model", rimSphereModel);

        glBindTexture(GL_TEXTURE_2D, rimSphereTexture);
        sphereShader.setInt("texture1", 5);

        rimLightSphere.Draw(sphereShader.getProgramID());

        sphereShader.setBool("applyRimLighting", false);  // Reset for subsequent objects
        

        // Render the pyramid with reflection
        Shader reflectionShader("ReflectionVertexShader.txt", "ReflectionFragmentShader.txt");
        if (!reflectionShader.isCompiled())
        {
            std::cerr << "Reflection shader failed to compile or link." << std::endl;
            return -1;
        }

        reflectionShader.use();
        reflectionShader.setBool("applyReflection", true); // Enable reflection for the pyramid

        // Set the appropriate uniforms for the reflection shader
        reflectionShader.setVec3("viewPos", camera.Position);
        reflectionShader.setMat4("projection", projection);
        reflectionShader.setMat4("view", view);

        glm::mat4 pyramidModel = glm::mat4(1.0f);
        // Pyramid position
        pyramidModel = glm::translate(pyramidModel, glm::vec3(0.0f, 0.0f, 0.0f));
        reflectionShader.setMat4("model", pyramidModel);

        // Load and bind the pyramid texture
        GLuint pyramidTexture = TextureManager::getInstance()->getTexture("Textures/splash.jpg");
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pyramidTexture);
        reflectionShader.setInt("objectTexture", 0); // Binding to texture unit 0

        // Bind the reflection control map texture to texture unit 2
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, reflectionControlMapTexture);
        reflectionShader.setInt("reflectionControlMap", 2); // Binding to texture unit 2

        // Bind the cube map texture for reflections to texture unit 1
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionMapTexture);
        reflectionShader.setInt("reflectionMap", 1); // Binding to texture unit 1

        // Draw the pyramid
        pyramid.Render();
        reflectionShader.setBool("applyReflection", false);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup and exit
    for (auto& sphere : spheres)
    {
        sphere.deleteBuffers();
    }

    skybox.~Skybox();
    glfwTerminate();

    return 0;
}
