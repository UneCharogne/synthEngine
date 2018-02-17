//
//  Cameras.cpp
//  
//
//  Created by Massimiliano Chiappini on 30/07/17.
//
//

#include "Lights.hpp"



Light* CreatePointLight(glm::vec4 position, glm::vec3 color) {
    Light* lightPointer = new Light();
    
    lightPointer->position = position;
    lightPointer->color = color;
    lightPointer->attenuation = 0.f;
    lightPointer->ambientCoefficient = 0.f;
    lightPointer->coneOpening = 3.14;
    lightPointer->coneDirection = glm::vec3(0.f,0.f,0.f);
    
    return lightPointer;
}

