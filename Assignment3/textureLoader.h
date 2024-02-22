//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : textureLoader.h
// Description : Header file for the texture loader, declaring functions for texture loading and management.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <string>
#include <glew.h>

class TextureLoader 
{
public:
    static GLuint LoadTexture(const char* filePath);
};

#endif
