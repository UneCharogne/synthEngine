//
//  Shaders.cpp
//  
//
//  Created by Massimiliano Chiappini on 16/07/17.
//
//

#include "Shaders.hpp"


string textFileRead(const char *filename)
{
    string str,ret = "";
    ifstream file;
    file.open(filename);
    if(file.is_open())
    {
        getline (file,str);
        while (file) {
            ret += str + "\n";
            getline (file,str);
        }
        //    cout << "Shader below\n" << ret << "\n";
        return ret;
    }
    else
    {
        printf("Error opening file \"%s\", program will be arrested.\n", filename);
        exit(EXIT_FAILURE);
    }
}


GLuint InitializeShader(GLenum ShaderType, const char *filename)
{
    GLint compiled;
    //Create a shader
    GLuint Shader = glCreateShader(ShaderType);
    
    //Open the file containing the shader
    string str = textFileRead(filename);
    GLchar *cstr = new GLchar[str.size()+1];
    const GLchar *cstr2 = cstr; // Weirdness to get a const char
    strcpy(cstr,str.c_str());
    
    //Copy its content in the buffer
    glShaderSource(Shader, 1, &cstr2, NULL);
    //And compile it
    glCompileShader(Shader);
    
    //Check if the shader has been correctly compiled
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled)
    {
        GLint maxLength = 0;
        glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(Shader, maxLength, &maxLength, &errorLog[0]);
        
        for (std::vector<char>::const_iterator i = errorLog.begin(); i != errorLog.end(); ++i)
            cout << *i << ' ';

        printf("Error compiling the shader \"%s\", program will be arrested.\n", filename);
        exit(EXIT_FAILURE);
    }
    
    //Then return the shader
    return Shader;
}


GLuint InitializeProgram(GLuint VertexShader, GLuint FragmentShader)
{
    GLint linked;
    
    //Create the program
    GLuint Program = glCreateProgram();
    
    //Attach the shaders to the program
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);
    
    //Link the program
    glLinkProgram(Program);
    
    //Test if the program has been correctly linked
    glGetProgramiv(Program, GL_LINK_STATUS, &linked);
    if(linked)
    {
        //If yes, utilize this program for shading
        glUseProgram(Program);
    }
    else
    {
        printf("Error linking the shading program, program will be arrested.\n");
        exit(EXIT_FAILURE);
    }
    
    //Then return the program
    return Program;
}
