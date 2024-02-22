//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : TextureManager.h
// Description : Header file for the TextureManager class, defining methods for managing texture resources.
// Author : Ryan Van Ingen-kal
// Mail : Ryan.IngenKal@mds.ac.nz
//

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <glew.h>
#include <string>
#include "textureLoader.h"

class TextureManager 
{
private:
    std::map<std::string, GLuint> loadedTextures;
    static TextureManager* instance;

    TextureManager() {}

public:
    static TextureManager* getInstance() 
    {
        if (!instance)
            instance = new TextureManager();
        return instance;
    }

    GLuint getTexture(const std::string& filePath)
    {
        if (loadedTextures.find(filePath) == loadedTextures.end())
        {
            // Texture not loaded yet, load it now
            loadedTextures[filePath] = TextureLoader::LoadTexture(filePath.c_str());
        }
        return loadedTextures[filePath];
    }

    void clear() {
        // Delete all textures
        for (auto& tex : loadedTextures) 
        {
            glDeleteTextures(1, &tex.second);
        }
        loadedTextures.clear();
    }

    ~TextureManager() 
    {
        clear();
    }
};

// Initialize the static instance pointer
TextureManager* TextureManager::instance = nullptr;

#endif