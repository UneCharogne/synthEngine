//
//  Textures.hpp
//  
//
//  Created by Massimiliano Chiappini on 16/07/17.
//
//

#ifndef Textures_hpp
#define Textures_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <OpenGl/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define DEFAULT_TEXTURE_PATH "resources/textures/default_texture.png"



class Texture2D
{
    private:
        std::string filename;
        GLenum texunit;
        GLuint tex;
    
        void Load(void);
    
    public:
        //Constructors
        Texture2D(void);
        Texture2D(std::string filename);
        Texture2D(GLenum, std::string filename);
    
        //Bind/unbind texture
        void Bind(void);
        void Unbind(void);
    
        //Destructor
        ~Texture2D(void);
};

#endif /* Textures_hpp */
