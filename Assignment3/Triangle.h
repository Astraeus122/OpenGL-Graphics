//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Triangle.h
// Description : Header file for the Triangle class, defining the structure and interface.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glew.h>
#include "GLFW/glfw3.h"

class Triangle 
{
public:
    Triangle();  // Constructor
    ~Triangle(); // Destructor

    void Render(unsigned int shaderProgram);

private:
    unsigned int VBO, VAO;
    void setupMesh();
};

#endif
