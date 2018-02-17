//
//  Lights.hpp
//  
//
//  Created by Massimiliano Chiappini on 30/07/17.
//
//

#ifndef Lights_hpp
#define Lights_hpp

#include <stdio.h>
#include <math.h>
#include <OpenGl/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#define MAX_N_LIGHTS 8


struct Light {
    glm::vec4 position;
    glm::vec3 color;
    float attenuation;
    float ambientCoefficient;
    float padding1;
    float padding2;
    float padding3;
    glm::vec3 coneDirection;
    float coneOpening;
};

static Light NullLight = {glm::vec4(0.f,0.f,0.f,0.f), glm::vec3(0.f,0.f,0.f), 0.f, 0.f, 0.f, 0.f, 0.f, glm::vec3(0.f,0.f,0.f), 0.f};

Light* CreatePointLight(glm::vec4, glm::vec3);

#endif /* Lights_hpp */
