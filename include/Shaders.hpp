//
//  Shaders.hpp
//  
//
//  Created by Massimiliano Chiappini on 16/07/17.
//
//

#ifndef Shaders_hpp
#define Shaders_hpp


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <OpenGl/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>


using namespace std;


string textFileRead (const char * filename);


GLuint InitializeShader(GLenum ShaderType, const char *filename);


GLuint InitializeProgram(GLuint VertexShader, GLuint FragmentShader);


#endif /* Shaders_hpp */
