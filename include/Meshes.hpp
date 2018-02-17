//
//  Drawing.hpp
//  
//
//  Created by Massimiliano Chiappini on 16/07/17.
//
//

#ifndef Meshes_hpp
#define Meshes_hpp

#include <stdio.h>
#include <vector>
#include <OpenGl/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/mesh.h>

#define N_BUFFERS 4
enum BUFFERS { VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER };

#define DEFAULT_MESH_PATH "resources/meshes/default_mesh.obj"



class SubMesh
{
    private:
        GLuint vao;
        GLuint vbo [N_BUFFERS];
    
        unsigned int elementcount;
        //void LoadSubMesh(aiMesh *mesh);
    
    public:
        SubMesh(aiMesh *mesh);
        ~SubMesh();
    
        void Draw();
};



class Mesh
{
    private:
        std::vector<SubMesh*> SubMeshes;
    
    public:
        //Constructors
        Mesh(void);
        Mesh(const char *filename);
    
        //Drawing methods
        void Draw(void);
    
        //Destructor
        ~Mesh(void);
};

#endif /* Drawing_hpp */
