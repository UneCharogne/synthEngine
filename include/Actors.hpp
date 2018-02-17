//
//  Actors.hpp
//  
//
//  Created by Massimiliano Chiappini on 08/08/17.
//
//

#ifndef Actors_hpp
#define Actors_hpp

#include <stdio.h>
#include <vector>
#include <OpenGl/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>




//Forward declarations
class Mesh;
class Texture2D;
class Camera;




//Definitions
#define MIN_PLANE_SPEED 0.0001
#define MAX_PLANE_SPEED 0.0010
#define PLANE_ACCELERATION 0.0001
#define PLANE_ROLL_SPEED 0.5
#define PLANE_YAW_SPEED 0.1
#define PLANE_PITCH_SPEED 0.1




//The most generic possible actor is just a container of virtual callbacks
class Actor
{
public:
    //Constructor
    Actor(void);
    
    //Callback functions
    virtual void onIdle(int currentTime) {}
    virtual void onDisplay(int currentTime) {}
    virtual void onWindowReshape(int currentTime, int neww, int newh) {}
    virtual void onKeyboardClick(int currentTime, unsigned char key, int x, int y) {}
    virtual void onMouseClick(int currentTime, int button, int state, int x, int y) {}
    virtual void onMouseDrag(int currentTime, int x, int y) {}
    virtual void onMouseMovement(int currentTime, int x, int y) {}
    
    //Destructor
    ~Actor(void);
};




//A model is an actor with a mesh, a texture and a transformation
class Model : public Actor
{
    Mesh* ModelMesh;
    Texture2D* ModelTexture;
    glm::mat4 ModelTransform;
    
    bool IsVisible;
    
    
public:
    //Constructors
    Model(void);
    Model(Mesh *modelmesh);
    Model(Mesh *modelmesh, glm::mat4 modeltransform);
    Model(Mesh *modelmesh, Texture2D *modeltexture);
    Model(Mesh *modelmesh, Texture2D *modeltexture, glm::mat4 modeltransform);
    
    //Set and get methods
    void SetMesh(Mesh *modelmesh);
    Mesh* GetMesh(void);
    void SetTexture(Texture2D *modeltexture);
    Texture2D* GetTexture(void);
    void SetTransform(glm::mat4 modeltransform);
    glm::mat4 GetTransform(void);
    void SetVisibility(bool isVisible);
    bool GetVisibility(void);
    
    //Transformation methods
    void ApplyTransform(glm::mat4 transformation);
    void Rotate(const float& degrees, const glm::vec3& axis);
    void Rotate(const glm::mat3& rMatrix);
    void Scale(const float& sx, const float& sy, const float& sz);
    void Translate(const float& dx, const float& dy, const float& dz);
    void Translate(const glm::vec3& d);
    
    //Callback functions
    void onIdle(int currentTime) { Actor::onIdle(currentTime); }
    void onDisplay(int currentTime);
    void onWindowReshape(int currentTime, int neww, int newh) { Actor::onWindowReshape(currentTime, neww, newh); }
    void onKeyboardClick(int currentTime, unsigned char key, int x, int y) { Actor::onKeyboardClick(currentTime, key, x, y); }
    void onMouseClick(int currentTime, int button, int state, int x, int y) { Actor::onMouseClick(currentTime, button, state, x, y); }
    void onMouseDrag(int currentTime, int x, int y) { Actor::onMouseDrag(currentTime, x, y); }
    void onMouseMovement(int currentTime, int x, int y) { Actor::onMouseMovement(currentTime, x, y); }
};




//The character is an actor possessing a model and two cameras (first- and third-person)
//And methods for the control of the character
class Character : public Actor
{
protected:
    Camera* CharacterCamera;
    Model* CharacterModel;
    
public:
    //Costructors
    Character(void);
    Character(Model* charactermodel);
    Character(Model* charactermodel, Camera* charactercamera);
    
    //Set get methods
    void SetModel(Model* charactermodel);
    Model* GetModel(void);
    void SetCamera(Camera* charactercamera);
    Camera* GetCamera(void);
    
    //Transformation methods
    virtual void RotateX(int Dx) {}
    virtual void RotateY(int Dy) {}
    
    virtual void MoveForward(int currentTime) {}
    virtual void MoveBackward(int currentTime) {}
    virtual void MoveRight(int currentTime) {}
    virtual void MoveLeft(int currentTime) {}
    
    //Callback functions
    void onIdle(int currentTime) { Actor::onIdle(currentTime); }
    void onDisplay(int currentTime) { Actor::onDisplay(currentTime); }
    void onWindowReshape(int currentTime, int neww, int newh) { Actor::onWindowReshape(currentTime, neww, newh); }
    void onKeyboardClick(int currentTime, unsigned char key, int x, int y);
    void onMouseClick(int currentTime, int button, int state, int x, int y) { Actor::onMouseClick(currentTime, button, state, x, y); }
    void onMouseDrag(int currentTime, int x, int y);
    void onMouseMovement(int currentTime, int x, int y);
};




class Plane : public Character
{
protected:
    glm::vec3 Position;
    
    glm::vec3 Axis;
    glm::vec3 Up;
    
    float Speed;
    float MinSpeed;
    float MaxSpeed;
    float Acceleration;
    
    float RollSpeed;
    float YawSpeed;
    float PitchSpeed;
    
    int time;
    
    void UpdatePosition(int dt);
    
public:
    //Constructor
    Plane(void);
    Plane(Model* planemodel);
    
    //Transformation methods
    void RotateX(int Dx);
    void RotateY(int Dy);
    
    void MoveForward(int currentTime);
    void MoveBackward(int currentTime);
    void MoveRight(int currentTime);
    void MoveLeft(int currentTime);
    
    void onIdle(int currentTime);
    void onDisplay(int currentTime) { Character::onDisplay(currentTime); }
    void onWindowReshape(int currentTime, int neww, int newh) { Character::onWindowReshape(currentTime, neww, newh); }
    void onKeyboardClick(int currentTime, unsigned char key, int x, int y) { Character::onKeyboardClick(currentTime, key, x, y); }
    void onMouseClick(int currentTime, int button, int state, int x, int y) { Character::onMouseClick(currentTime, button, state, x, y); }
    void onMouseDrag(int currentTime, int x, int y) { Character::onMouseDrag(currentTime, x, y); }
    void onMouseMovement(int currentTime, int x, int y) { Character::onMouseMovement(currentTime, x, y); }
};

#endif /* Actors_hpp */
