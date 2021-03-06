//
//  Drawing.cpp
//  
//
//  Created by Massimiliano Chiappini on 16/07/17.
//
//

#include "Meshes.hpp"
#include "Worlds.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


SubMesh::SubMesh(aiMesh *mesh) {
    //I create and bind the vertex array associated to the mesh
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    //The number of verteces of the submesh is 3 time the number of (triangularized) faces
    elementcount = mesh->mNumFaces * 3;
    
    if(mesh->HasPositions()) {
        float *vertices = new float[mesh->mNumVertices * 3];
        for(int i=0;i<mesh->mNumVertices;++i) {
            
            vertices[i * 3] = mesh->mVertices[i].x;
            vertices[i * 3 + 1] = mesh->mVertices[i].y;
            vertices[i * 3 + 2] = mesh->mVertices[i].z;
        }
        
        glGenBuffers(1, &vbo[VERTEX_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (0);
        
        delete[] vertices;
    }
    
    
    if(mesh->HasTextureCoords(0)) {
        float *texCoords = new float[mesh->mNumVertices * 2];
        for(int i=0;i<mesh->mNumVertices;++i) {
            texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
            texCoords[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
        }
        
        glGenBuffers(1, &vbo[TEXCOORD_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORD_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, 2 * mesh->mNumVertices * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (1);
        
        delete[] texCoords;
    }
    
    
    if(mesh->HasNormals()) {
        float *normals = new float[mesh->mNumVertices * 3];
        for(int i=0;i<mesh->mNumVertices;++i) {
            normals[i * 3] = mesh->mNormals[i].x;
            normals[i * 3 + 1] = mesh->mNormals[i].y;
            normals[i * 3 + 2] = mesh->mNormals[i].z;
        }
        
        glGenBuffers(1, &vbo[NORMAL_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), normals, GL_STATIC_DRAW);
        
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (2);
        
        delete[] normals;
    }
    
    
    if(mesh->HasFaces()) {
        unsigned int *indices = new unsigned int[mesh->mNumFaces * 3];
        for(int i=0;i<mesh->mNumFaces;++i) {
            indices[i * 3] = mesh->mFaces[i].mIndices[0];
            indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
            indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
        }
        
        glGenBuffers(1, &vbo[INDEX_BUFFER]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * mesh->mNumFaces * sizeof(GLuint), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray (3);
        
        delete[] indices;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


SubMesh::~SubMesh() {
    //Delete the buffer and vertex arrays associated to the submesh
    
    if(vbo[VERTEX_BUFFER]) {
        glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
    }
    
    if(vbo[TEXCOORD_BUFFER]) {
        glDeleteBuffers(1, &vbo[TEXCOORD_BUFFER]);
    }
    
    if(vbo[NORMAL_BUFFER]) {
        glDeleteBuffers(1, &vbo[NORMAL_BUFFER]);
    }
    
    if(vbo[INDEX_BUFFER]) {
        glDeleteBuffers(1, &vbo[INDEX_BUFFER]);
    }
    
    glDeleteVertexArrays(1, &vao);
}


void SubMesh::Draw() {
    //Bind the vertex array associated to the subMesh
    glBindVertexArray(vao);
    //And draw the vertex in the array as triangles
    glDrawElements(GL_TRIANGLES, elementcount, GL_UNSIGNED_INT, NULL);
    
    //Then unbind the vertex array
    glBindVertexArray(0);
}


Mesh::Mesh(const char *filename)
{
    //Create an assimp importer
    Assimp::Importer importer;
    
    //And use it to import the mesh, given its filename
    const aiScene *scene = importer.ReadFile(filename, 0);
    if(!scene) {
        printf("Unable to laod mesh: %s\n", importer.GetErrorString());
    }
    
    //Then, initialize each of its meshes
    for(int i = 0; i < scene->mNumMeshes; ++i) {
        this->SubMeshes.push_back(new SubMesh(scene->mMeshes[i]));
    }
}

Mesh::Mesh() {
    //Create an assimp importer
    Assimp::Importer importer;
    
    //And use it to import the mesh, given its filename
    const aiScene *scene = importer.ReadFile(DEFAULT_MESH_PATH, 0);
    if(!scene) {
        printf("Unable to laod mesh: %s\n", importer.GetErrorString());
    }
    
    //Then, initialize each of its meshes
    for(int i = 0; i < scene->mNumMeshes; ++i) {
        this->SubMeshes.push_back(new SubMesh(scene->mMeshes[i]));
    }
}


Mesh::~Mesh(void)
{
    //Delete each submesh of the current mesh
    for(int i=0;i<this->SubMeshes.size();++i) {
        delete this->SubMeshes[i];
    }
    this->SubMeshes.clear();
}



void Mesh::Draw() {
    //Draw each submesh
    for(int i=0;i<this->SubMeshes.size();++i) {
        this->SubMeshes[i]->Draw();
    }
}
