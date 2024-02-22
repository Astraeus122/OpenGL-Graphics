//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Camera.cpp
// Description : Implementation of the Camera class to manage view transformations.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#include "Camera.h"

Camera* Camera::CurrentInstance = nullptr;
float Camera::LastX = 1920.0f / 2.0;
float Camera::LastY = 1080.0f / 2.0;
bool Camera::FirstMouse = true;

// Constructor with vectors
Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = startPosition;
    WorldUp = startUp;
    Yaw = startYaw;
    Pitch = startPitch;
    CurrentInstance = this;
    updateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() 
{
    return glm::lookAt(Position, Position + Front, Up);
}

// Processes input received from the keyboard
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) 
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if (direction == UP)
        Position += WorldUp * velocity;
    if (direction == DOWN)
        Position -= WorldUp * velocity;
}

// Processes input received from the mouse.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel.
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::MouseCallback(GLFWwindow* window, double xpos, double ypos) 
{
    if (FirstMouse) 
    {
        LastX = xpos;
        LastY = ypos;
        FirstMouse = false;
    }

    float xoffset = xpos - LastX;
    float yoffset = LastY - ypos; // Reversed since y-coordinates go from bottom to top

    LastX = xpos;
    LastY = ypos;

    CurrentInstance->ProcessMouseMovement(xoffset, yoffset);
}

void Camera::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    CurrentInstance->ProcessMouseScroll(yoffset);
}
