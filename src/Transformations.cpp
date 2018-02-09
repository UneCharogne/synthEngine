//
//  Rotations.cpp
//  
//
//  Created by Massimiliano Chiappini on 10/07/17.
//
//

#include "Transformations.hpp"


glm::mat3 RotationMatrix3(const float& degrees, const glm::vec3& axis) {
    //First of all, let's normalize the axis of rotation
    glm::vec3 u = glm::normalize(axis);
    
    //And convert the angle to radians
    float radians = degrees * DEGREES_TO_RADIANS;
    
    
    //Then, get the identity matrix
    glm::mat3 Imat3 = glm::mat3(1.f);
    
    //The outer product of the normalized axis with its own transpose
    glm::mat3 uuT = glm::outerProduct(u, u);
    
    //And the cross-product matrix of u
    glm::mat3 uX = glm::mat3(0.f, u.z, -u.y, -u.z, 0.f, u.x, u.y, -u.x, 0.f);
    
    
    //In the end, build the rotation function
    glm::mat3 rot = (cos(radians) * Imat3) + ((1.f - cos(radians)) * uuT) + (uX * sin(radians));
    
    //And return it
    return rot;
}




glm::mat4 RotationMatrix(const float& degrees, const glm::vec3& axis)
{
    //Create the 3x3 rotation matrix
    glm::mat3 rot3 = RotationMatrix3(degrees, axis);
    
    //Convert it to the 4x4 rotation matrix
    glm::mat4 rot = glm::mat4(rot3);
    
    //And return it
    return rot;
}




glm::mat4 TranslationMatrix(const float& dx, const float& dy, const float& dz)
{
    //Create the translation matrix
    glm::mat4 transl = glm::mat4(glm::vec4(1.f,0.f,0.f,0.f),glm::vec4(0.f,1.f,0.f,0.f),glm::vec4(0.f,0.f,1.f,0.f),glm::vec4(dx,dy,dz,1.f));
    
    //And return it
    return transl;
}




glm::mat4 TranslationMatrix(float d[3])
{
    //Create the translation matrix
    glm::mat4 transl = glm::mat4(glm::vec4(1.f,0.f,0.f,0.f),glm::vec4(0.f,1.f,0.f,0.f),glm::vec4(0.f,0.f,1.f,0.f),glm::vec4(d[0],d[1],d[2],1.f));
    
    //And return it
    return transl;
}




glm::mat4 TranslationMatrix(glm::vec3 d)
{
    //Create the translation matrix
    glm::mat4 transl = glm::mat4(glm::vec4(1.f,0.f,0.f,0.f),glm::vec4(0.f,1.f,0.f,0.f),glm::vec4(0.f,0.f,1.f,0.f),glm::vec4(d.x,d.y,d.z,1.f));
    
    //And return it
    return transl;
}




glm::mat4 ScaleMatrix(const float& sx, const float& sy, const float& sz)
{
    //Create the translation matrix
    glm::mat4 scale = glm::mat4(glm::vec4(sx,0.f,0.f,0.f),glm::vec4(0.f,sy,0.f,0.f),glm::vec4(0.f,0.f,sz,0.f),glm::vec4(0.f,0.f,0.f,1.f));
    
    //And return it
    return scale;
}




glm::mat4 ScaleMatrix(float s[3])
{
    //Create the translation matrix
    glm::mat4 scale = glm::mat4(glm::vec4(s[0],0.f,0.f,0.f),glm::vec4(0.f,s[1],0.f,0.f),glm::vec4(0.f,0.f,s[2],0.f),glm::vec4(0.f,0.f,0.f,1.f));
    
    //And return it
    return scale;
}




glm::mat4 ScaleMatrix(glm::vec3 s)
{
    //Create the translation matrix
    glm::mat4 scale = glm::mat4(glm::vec4(s.x,0.f,0.f,0.f),glm::vec4(0.f,s.y,0.f,0.f),glm::vec4(0.f,0.f,s.z,0.f),glm::vec4(0.f,0.f,0.f,1.f));
    
    //And return it
    return scale;
}
