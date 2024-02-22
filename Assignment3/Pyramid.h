//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Pyramid.h
// Description : Header file (and the only file) for the Pyramid class, defining the structure of the 3d pyramid in the scene.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef PYRAMID_H
#define PYRAMID_H

#include "GLEW/glew.h"
#include <vector>

class Pyramid 
{
private:
    GLuint VAO, VBO, EBO;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

public:
    Pyramid() 
    {
        // Pyramid vertices (Position x, y, z, Normal x, y, z, Texture coordinates u, v)
        vertices = 
        {
            // Base (normal pointing downwards)
            -1.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // A
             1.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // B
             1.0f, 0.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // C
            -1.0f, 0.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // D
            // Peak (approximate normals for sides)
             0.0f, 2.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.5f, 0.5f,  // Top - A
             0.0f, 2.0f,  0.0f, 1.0f,  0.0f, 0.0f, 0.5f, 0.5f,  // Top - B
             0.0f, 2.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.5f, 0.5f, // Top - C
             0.0f, 2.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.5f // Top - D
        };

        // Indices for the triangles
        indices =
        {
            // Base square
            0, 1, 2, 0, 2, 3,
            // Sides
            0, 1, 4, // A, B, T
            1, 2, 4, // B, C, T
            2, 3, 4, // C, D, T
            3, 0, 4  // D, A, T
            // Add more indices for the other sides of the pyramid if needed
        };

        // Create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Load data into vertex buffers
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

        // Set the vertex attribute pointers
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // Texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0); // Unbind VAO
    }

    ~Pyramid()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void Render() 
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

#endif 
