//
//  Cameras.hpp
//  
//
//  Created by Massimiliano Chiappini on 30/07/17.
//
//

#ifndef Cameras_hpp
#define Cameras_hpp

#include <stdio.h>
#include <math.h>
#include <OpenGl/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


//Parameters
#define MAX_LATITUDE 5


class Camera
{
    protected:
        glm::vec3 Eye;
        glm::vec3 ViewDirection;
        glm::vec3 Up;
    
        bool ViewingChanged;
    
    public:
        //Constructors
        Camera(void)
        {
            this->Eye = glm::vec3(0.f,0.f,0.f);
            this->ViewDirection = glm::vec3(1.f,0.f,0.f);
            this->Up = glm::vec3(0.f,0.f,1.f);
        
            this->ViewingChanged = true;
        }
        Camera(glm::vec3 eye, glm::vec3 viewdirection, glm::vec3 up)
        {
            this->Eye = eye;
            this->ViewDirection = viewdirection;
            this->Up = up;
        
            this->ViewingChanged = true;
        }
        Camera(glm::vec3 vectors[3])
        {
            this->Eye = vectors[0];
            this->ViewDirection = vectors[1];
            this->Up = vectors[3];
            
            this->ViewingChanged = true;
        }
        Camera(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat vx, GLfloat vy, GLfloat vz, GLfloat ux, GLfloat uy, GLfloat uz)
        {
            this->Eye.x = ex;
            this->Eye.y = ey;
            this->Eye.z = ez;
        
            this->ViewDirection.x = vx;
            this->ViewDirection.y = vy;
            this->ViewDirection.z = vz;
        
            this->Up.x = ux;
            this->Up.y = uy;
            this->Up.z = uz;
        
            this->ViewingChanged = true;
        }
        Camera(GLfloat vectors[][3])
        {
            this->Eye.x = vectors[0][0];
            this->Eye.y = vectors[0][1];
            this->Eye.z = vectors[0][2];
        
            this->ViewDirection.x = vectors[1][0];
            this->ViewDirection.y = vectors[1][1];
            this->ViewDirection.z = vectors[1][2];
        
            this->Up.x = vectors[2][0];
            this->Up.y = vectors[2][1];
            this->Up.z = vectors[2][2];
        
            this->ViewingChanged = true;
        }
        Camera(GLfloat vectors[])
        {
            this->Eye.x = vectors[0];
            this->Eye.y = vectors[1];
            this->Eye.z = vectors[2];
        
            this->ViewDirection.x = vectors[3];
            this->ViewDirection.y = vectors[4];
            this->ViewDirection.z = vectors[5];
        
            this->Up.x = vectors[6];
            this->Up.y = vectors[7];
            this->Up.z = vectors[8];
        
            this->ViewingChanged = true;
        }
    
        //Set and get methods
        bool GetViewingChanged(void);
        void SetViewingChanged(bool viewingchanged);
    
        glm::mat4 GetLookAt(void);
    
        void SetEye(glm::vec3 eye);
        glm::vec3 GetEye(void);
        void SetUp(glm::vec3 up);
        glm::vec3 GetUp(void);
        void SetViewDirection(glm::vec3 viewdirection);
        glm::vec3 GetViewDirection(void);
    
        //Camera movement
        //In particular, a camera is just a reference frame set in the eye position, with axis given by up and viewdirection
        void Translate(glm::vec3 d);
        void Translate(GLfloat dx, GLfloat dy, GLfloat dz);
        void Translate(GLfloat d[3]);
    
        void Rotate(const float& degrees, const glm::vec3& axis);
        void Rotate(glm::mat3 rMatrix);
};

#endif /* Cameras_hpp */
