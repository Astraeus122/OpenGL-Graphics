//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Triangle.cpp
// Description : Implementation of the Triangle class, handling the geometry and rendering of the triangles for the objects.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#include "Triangle.h"

// Constructor
Triangle::Triangle() 
{
    setupMesh();
}

// Destructor
Triangle::~Triangle() 
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Triangle::setupMesh() 
{
    // Define the vertices of the triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // bottom left corner
         0.5f, -0.5f, 0.0f, // bottom right corner
         0.0f,  0.5f, 0.0f  // top center position
    };

    // Create buffers on the GPU
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind VAO
    glBindVertexArray(0);
}

void Triangle::Render(unsigned int shaderProgram) 
{
    // Use the program object
    glUseProgram(shaderProgram);

    // Bind VAO and draw the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0); // Unbind VAO
}
