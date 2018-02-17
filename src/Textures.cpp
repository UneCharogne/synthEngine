//
//  Drawing.cpp
//  
//
//  Created by Massimiliano Chiappini on 16/07/17.
//
//

#include "Textures.hpp"
#include "Worlds.hpp"
#include <iostream>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL.h>


Texture2D::Texture2D(GLenum texunit, std::string filename) {
    this->filename = filename;
    this->texunit = texunit;
    
    this->Load();
}


Texture2D::Texture2D(std::string filename) {
    this->filename = filename;
    this->texunit = GL_TEXTURE0;
    
    this->Load();
}


Texture2D::Texture2D(void) {
    this->filename = DEFAULT_TEXTURE_PATH;
    this->texunit = GL_TEXTURE0;
    
    this->Load();
}


void Texture2D::Load(void)
{
    //Load the mesh
    int width, height;
    unsigned char* image =
    SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    
    //Then, generate a texture object
    glGenTextures(1, &tex);
    //and bind it
    glActiveTexture(texunit);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    //Associate texture data and parameters to the texture object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //Unbind the texture object
    glBindTexture(GL_TEXTURE_2D, 0);
    
    //Andu unload the texture data
    SOIL_free_image_data(image);
}

void Texture2D::Bind(void) {
    //Bind the texture object
    glActiveTexture(texunit);
    glBindTexture(GL_TEXTURE_2D, tex);
}

void Texture2D::Unbind(void) {
    //Bind the texture object
    glActiveTexture(texunit);
    glBindTexture(GL_TEXTURE_2D, 0);
}


Texture2D::~Texture2D(void)
{
    //Delete the texture object
    glDeleteTextures(1, &tex);
}
