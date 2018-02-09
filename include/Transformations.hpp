//
//  Transformations.hpp
//  
//
//  Created by Massimiliano Chiappini on 10/07/17.
//
//

#ifndef Transformations_hpp
#define Transformations_hpp

#include <stdio.h>
#include <math.h>
#include <OpenGl/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define DEGREES_TO_RADIANS 0.01745329251
#define RADIANS_TO_DEGREES 57.2957795131


glm::mat3 RotationMatrix3(const float& degrees, const glm::vec3& axis);

glm::mat4 RotationMatrix(const float& degrees, const glm::vec3& axis);

glm::mat4 TranslationMatrix(const float& dx, const float& dy, const float &dz);

glm::mat4 TranslationMatrix(float d[3]);

glm::mat4 TranslationMatrix(glm::vec3 d);

glm::mat4 ScaleMatrix(const float& sx, const float& sy, const float &sz);

glm::mat4 ScaleMatrix(float s[3]);

glm::mat4 ScaleMatrix(glm::vec3 s);


#endif /* Transformations_hpp */
