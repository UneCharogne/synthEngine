//
//  Main file of my Open Gl experiment
//  It will contain the initialization of the OpenGl viewing, objects and shaders
//  as well as the GUIT code to move the viewport and interact with the scene
//  Created by Massimiliano Chiappini on 03/07/17.
//
//

#include <stdio.h>
#include <vector>
#include <OpenGl/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Worlds.hpp"
#include "Meshes.hpp"
#include "Actors.hpp"
#include "Cameras.hpp"
#include "Transformations.hpp"




#define eye0 5.f




int main(int argc, char** argv)
{
    //Initialize the world
    World::InitializeWorld(&argc, argv);
    
    
    //Create the main character
    Character* MainCharacter = new Plane(new Model(new Mesh("bench.obj"), ScaleMatrix(0.f,0.f,0.f)));
    
    
    
    
    
    //Initialize and register the first model
    World::RegisterActor(new Model(new Mesh("bench.obj"), TranslationMatrix(4.f,0.f,0.f)));
    
    //Initialize the second model
    World::RegisterActor(new Model(new Mesh("bench.obj"), TranslationMatrix(8.f,0.f,0.f)));
    
    //Run the main loop
    glutMainLoop();
    
    
    
    
    //Return zero
    return 0;
}
