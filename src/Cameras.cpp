//
//  Cameras.cpp
//  
//
//  Created by Massimiliano Chiappini on 30/07/17.
//
//

#include "Cameras.hpp"
#include "Transformations.hpp"




bool Camera::GetViewingChanged(void)
{
    return this->ViewingChanged;
}




void Camera::SetViewingChanged(bool viewingchanged)
{
    this->ViewingChanged = viewingchanged;
}




glm::mat4 Camera::GetLookAt(void)
{
    return glm::lookAt(this->Eye, this->Eye + this->ViewDirection, this->Up);
}



void Camera::SetEye(glm::vec3 eye)
{
    this->Eye = eye;
    this->SetViewingChanged(true);
}



glm::vec3 Camera::GetEye(void)
{
    return this->Eye;
}



void Camera::SetUp(glm::vec3 up)
{
    this->Up = up;
    this->SetViewingChanged(true);
}



glm::vec3 Camera::GetUp(void)
{
    return this->Up;
}



void Camera::SetViewDirection(glm::vec3 viewdirection)
{
    this->ViewDirection = viewdirection;
    this->SetViewingChanged(true);
}



glm::vec3 Camera::GetViewDirection(void)
{
    return this->ViewDirection;
}




void Camera::Translate(glm::vec3 d)
{
    this->Eye = this->Eye + d;
    
    this->SetViewingChanged(true);
}




void Camera::Translate(GLfloat dx, GLfloat dy, GLfloat dz)
{
    this->Eye.x += dx;
    this->Eye.y += dy;
    this->Eye.z += dz;
    
    this->SetViewingChanged(true);
}




void Camera::Translate(GLfloat d[3])
{
    this->Eye.x += d[0];
    this->Eye.y += d[1];
    this->Eye.z += d[2];
    
    
    this->SetViewingChanged(true);
}




void Camera::Rotate(const float& degrees, const glm::vec3& axis)
{
    glm::mat3 rMatrix = RotationMatrix3(degrees, axis);
    this->Up = rMatrix * this->Up;
    this->ViewDirection = rMatrix * this->ViewDirection;
    
    this->SetViewingChanged(true);
}




void Camera::Rotate(glm::mat3 rMatrix)
{
    this->Up = rMatrix * this->Up;
    this->ViewDirection = rMatrix * this->ViewDirection;
    
    this->SetViewingChanged(true);
}

