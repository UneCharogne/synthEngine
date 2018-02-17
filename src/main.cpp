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
#include "Lights.hpp"
#include "Cameras.hpp"
#include "Transformations.hpp"




#define eye0 5.f




int main(int argc, char** argv)
{
    //Initialize the world
    World::InitializeWorld(&argc, argv);
    
    
    //Create the main character
    Character* MainCharacter = new Plane(new Model(new Mesh(), ScaleMatrix(0.f,0.f,0.f)));
    
    
    
    
    
    //Initialize and register the first model
    World::RegisterActor(new Model(new Mesh(), TranslationMatrix(50.f,0.f,0.f)));
    
    
    
    
    //Fiat lux.
    World::RegisterLight(CreatePointLight(glm::vec4(0.f,0.f,0.f,1.f), glm::vec3(0.f,0.f,1.f)));
    World::RegisterLight(CreatePointLight(glm::vec4(100.f,1.f,0.f,1.f), glm::vec3(1.f,0.f,0.f)));
    printf("%lu\n", sizeof(bool));
    //Run the main loop
    glutMainLoop();
    
    
    
    
    //Return zero
    return 0;
}
