//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Cube.cpp
// Description : Implementation of the Cube class to create and manage cube geometry.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#include "Cube.h"

// Constructor
Cube::Cube() 
{
    setupMesh();
}

// Destructor
Cube::~Cube() 
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Cube::setupMesh() 
{
    // Define the vertices of the cube
    float vertices[] = 
    {
        // positions          
        -0.5f, -0.5f, -0.5f,  // back face triangle 1 : start
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,  // back face triangle 1 : end
         0.5f,  0.5f, -0.5f,  // back face triangle 2 : start
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,  // back face triangle 2 : end

        -0.5f, -0.5f,  0.5f,  // front face triangle 1 : start
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,  // front face triangle 1 : end
         0.5f,  0.5f,  0.5f,  // front face triangle 2 : start
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,  // front face triangle 2 : end

        -0.5f,  0.5f,  0.5f,  // left face triangle 1 : start
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,  // left face triangle 1 : end
        -0.5f, -0.5f, -0.5f,  // left face triangle 2 : start
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,  // left face triangle 2 : end

         0.5f,  0.5f,  0.5f,  // right face triangle 1 : start
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,  // right face triangle 1 : end
         0.5f, -0.5f, -0.5f,  // right face triangle 2 : start
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,  // right face triangle 2 : end

        -0.5f, -0.5f, -0.5f,  // bottom face triangle 1 : start
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,  // bottom face triangle 1 : end
         0.5f, -0.5f,  0.5f,  // bottom face triangle 2 : start
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,  // bottom face triangle 2 : end

        -0.5f,  0.5f, -0.5f,  // top face triangle 1 : start
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,  // top face triangle 1 : end
         0.5f,  0.5f,  0.5f,  // top face triangle 2 : start
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f   // top face triangle 2 : end
    };

    // Create buffers on the GPU
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cube::Render(Shader& shader) 
{
    shader.use();

    // Bind VAO and draw the cube
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36); // Drawing 12 triangles, each made up of 3 vertices, so 36 vertices total
    glBindVertexArray(0); // Unbind VAO
}

void Cube::deleteBuffers() 
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}
