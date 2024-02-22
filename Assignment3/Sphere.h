//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Sphere.h
// Description : Header file for the Sphere class, defining the structure and interface of the sphere object.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glew.h>
#include "GLFW/glfw3.h"

// A simple struct to hold vertex data
struct Vertex 
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Sphere 
{
public:
    Sphere(unsigned int X_SEGMENTS, unsigned int Y_SEGMENTS);
    void Draw(GLuint shaderProgram);
    void deleteBuffers();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;

    void setupMesh();
    void generateSphere(unsigned int X_SEGMENTS, unsigned int Y_SEGMENTS);
};

#endif
