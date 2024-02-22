//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Shader.h
// Description : Header file for the Shader class, defining the details for the shader class.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include "GLFW/glfw3.h"

#include <string>
#include <glm/ext/matrix_float4x4.hpp>

class Shader
{
public:
    // The program ID
    GLuint ID;

    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    GLuint getProgramID() const;

    // Use/activate the shader
    void use();

    // Utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;

    bool isCompiled() const;

private:
    // Utility function for checking shader compilation/linking errors.
    void checkCompileErrors(GLuint shader, std::string type);  
};

#endif
