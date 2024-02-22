//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Cube.h
// Description : Header file for Cube class, which defines the properties and functions for cube objects.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef CUBE_H
#define CUBE_H

#include <glew.h>
#include "GLFW/glfw3.h"
#include "Shader.h"

class Cube
{
public:
    Cube();
    ~Cube();

    void Render(Shader& shader);

    void deleteBuffers();

private:
    unsigned int VBO, VAO;
    void setupMesh();
};

#endif
