//
//  Actors.cpp
//  
//
//  Created by Massimiliano Chiappini on 08/08/17.
//
//

#include "Worlds.hpp"
#include "Actors.hpp"
#include "Meshes.hpp"
#include "Textures.hpp"
#include "Transformations.hpp"
#include "Cameras.hpp"




Actor::Actor(void)
{
    World::RegisterActor(this);
}




Actor::~Actor(void)
{
    World::DeregisterActor(this);
}




Model::Model(void) : Actor()
{
    this->ModelMesh = new Mesh();
    
    this->ModelTexture = new Texture2D();
    
    this->ModelTransform = glm::mat4(1.f);
    
    this->IsVisible = true;
}




Model::Model(Mesh *modelmesh) : Actor()
{
    this->ModelMesh = modelmesh;
    
    this->ModelTexture = new Texture2D();
    
    this->ModelTransform = glm::mat4(1.f);
    
    this->IsVisible = true;
}




Model::Model(Mesh *modelmesh, Texture2D *modeltexture) : Actor()
{
    this->ModelMesh = modelmesh;
    
    this->ModelTexture = modeltexture;
    
    this->ModelTransform = glm::mat4(1.f);
    
    this->IsVisible = true;
}




Model::Model(Mesh *modelmesh, glm::mat4 modeltransform) : Actor()
{
    this->ModelMesh = modelmesh;
    
    this->ModelTexture = new Texture2D();
    
    this->ModelTransform = modeltransform;
    
    this->IsVisible = true;
}




Model::Model(Mesh *modelmesh, Texture2D *modeltexture, glm::mat4 modeltransform) : Actor()
{
    this->ModelMesh = modelmesh;
    
    this->ModelTexture = modeltexture;
    
    this->ModelTransform = modeltransform;
    
    this->IsVisible = true;
}



void Model::SetMesh(Mesh *modelmesh)
{
    delete this->ModelMesh;
    this->ModelMesh = modelmesh;
}



Mesh* Model::GetMesh(void)
{
    return this->ModelMesh;
}



void Model::SetTexture(Texture2D *modeltexture)
{
    delete this->ModelTexture;
    this->ModelTexture = modeltexture;
}



Texture2D* Model::GetTexture(void)
{
    return this->ModelTexture;
}




void Model::SetTransform(glm::mat4 modeltransform)
{
    this->ModelTransform = modeltransform;
}




glm::mat4 Model::GetTransform(void)
{
    return this->ModelTransform;
}




void Model::SetVisibility(bool isvisible)
{
    this->IsVisible = isvisible;
}




bool Model::GetVisibility(void)
{
    return this->IsVisible;
}




void Model::ApplyTransform(glm::mat4 transform)
{
    this->ModelTransform = transform * this->ModelTransform;
}




void Model::Rotate(const float& degrees, const glm::vec3& axis)
{
    //Get the transformation matrix
    glm::mat4 rot = RotationMatrix(degrees, axis);
    
    //And apply the transformation
    this->ModelTransform = rot * this->ModelTransform;
}




void Model::Rotate(const glm::mat3& rMatrix)
{
    //Apply the transformation
    this->ModelTransform = glm::mat4(rMatrix) * this->ModelTransform;
}




void Model::Scale(const float& sx, const float& sy, const float& sz)
{
    //Get the transformation matrix
    glm::mat4 scale = ScaleMatrix(sx, sy, sz);
    
    //And apply the transformation
    this->ModelTransform = scale * this->ModelTransform;
}




void Model::Translate(const float& dx, const float& dy, const float& dz)
{
    //Get the transformation matrix
    glm::mat4 transl = TranslationMatrix(dx, dy, dz);
    
    //And apply the transformation
    this->ModelTransform = transl * this->ModelTransform;
}




void Model::Translate(const glm::vec3& d)
{
    //Get the transformation matrix
    glm::mat4 transl = TranslationMatrix(d);
    
    //And apply the transformation
    this->ModelTransform = transl * this->ModelTransform;
}



void Model::onDisplay(int currentTime)
{
    Actor::onDisplay(currentTime);
    
    //If the model is visible
    if(this->GetVisibility())
    {
        //Get the model transformation's matrix
        glm::mat4 TransformationMatrix = this->GetTransform();
    
        //Send the model's transformation to the buffer
        glUniformMatrix4fv(World::GetModelTransformationMatrix(), 1, GL_FALSE, &(TransformationMatrix[0][0]));
        
        //Bind the model's texture to the shader
        this->GetTexture()->Bind();
        
        //Draw the model
        this->GetMesh()->Draw();
        
        //And unbind the texture
        this->GetTexture()->Unbind();
    }
}




Character::Character(void) : Actor()
{
    this->CharacterCamera = new Camera(glm::vec3(0.f,0.f,0.f),glm::vec3(1.f,0.f,0.f),glm::vec3(0.f,0.f,1.f));
    World::ActivateCamera(this->CharacterCamera);
    
    this->CharacterModel = new Model();
}




Character::Character(Model* charactermodel) : Actor()
{
    this->CharacterCamera = new Camera(glm::vec3(0.f,0.f,0.f),glm::vec3(1.f,0.f,0.f),glm::vec3(0.f,0.f,1.f));
    World::ActivateCamera(this->CharacterCamera);
    
    this->CharacterModel = charactermodel;
}




Character::Character(Model* charactermodel, Camera* charactercamera) : Actor()
{
    this->CharacterCamera = charactercamera;
    World::ActivateCamera(this->CharacterCamera);
    
    this->CharacterModel = charactermodel;
}




void Character::SetCamera(Camera* charactercamera)
{
    this->CharacterCamera = charactercamera;
}




Camera* Character::GetCamera(void)
{
    return this->CharacterCamera;
}




void Character::SetModel(Model* charactermodel)
{
    //I should unregister previous model
    
    this->CharacterModel = charactermodel;
}




Model* Character::GetModel(void)
{
    return this->CharacterModel;
}




void Character::onKeyboardClick(int currentTime, unsigned char key, int x, int y)
{
    Actor::onKeyboardClick(currentTime, key, x, y);
    
    switch(key)
    {
        case 'w': //'w' to move forwards
            this->MoveForward(currentTime);
            
            break;
            
        case 'a': //'w' to move left
            this->MoveLeft(currentTime);
            
            break;
            
        case 's': //'w' to move backwards
            this->MoveBackward(currentTime);
            
            break;
            
        case 'd': //'d' to move right
            this->MoveRight(currentTime);
            
            break;
            
        default:
            break;
    }
}




void Character::onMouseDrag(int currentTime, int x, int y)
{
    Actor::onMouseDrag(currentTime, x, y);
    
    int Dx, Dy;
    
    //Get the variation of the position of the mouse
    Dx = x - World::GetMouseX();
    Dy = y - World::GetMouseY();
    
    
    //Consequently rotate the actor
    this->RotateX(Dx);
    this->RotateY(Dy);
}




void Character::onMouseMovement(int currentTime, int x, int y)
{
    Actor::onMouseMovement(currentTime, x, y);
    
    int Dx, Dy;
    
    //Get the variation of the position of the mouse
    Dx = x - World::GetMouseX();
    Dy = y - World::GetMouseY();
        
        
    //Consequently rotate the actor
    this->RotateX(Dx);
    this->RotateY(Dy);
}




void Plane::UpdatePosition(int dt)
{
    float dr = this->Speed * dt;
    glm::vec3 dPosition = dr * this->Axis;
    
    this->Position = this->Position + dPosition;
    this->GetModel()->Translate(dPosition);
    this->GetCamera()->Translate(dPosition);
}




Plane::Plane(void) : Character(new Model(), new Camera(glm::vec3(0.f,0.f,0.f),glm::vec3(1.f,0.f,0.f),glm::vec3(0.f,0.f,1.f)))
{
    this->Position = glm::vec3(0.f,0.f,0.f);
    this->Axis = glm::vec3(1.f,0.f,0.f);
    this->Up = glm::vec3(0.f,0.f,1.f);
    
    this->MinSpeed = MIN_PLANE_SPEED;
    this->MaxSpeed = MAX_PLANE_SPEED;
    this->Speed = this->MinSpeed;
    this->Acceleration = PLANE_ACCELERATION;
    
    this->RollSpeed = PLANE_ROLL_SPEED;
    this->YawSpeed = PLANE_YAW_SPEED;
    this->PitchSpeed = PLANE_PITCH_SPEED;
    
    this->time = glutGet(GLUT_ELAPSED_TIME);
}



Plane::Plane(Model* planemodel)  : Character(planemodel, new Camera(glm::vec3(0.f,0.f,0.f),glm::vec3(1.f,0.f,0.f),glm::vec3(0.f,0.f,1.f)))
{
    this->Position = glm::vec3(0.f,0.f,0.f);
    this->Axis = glm::vec3(1.f,0.f,0.f);
    this->Up = glm::vec3(0.f,0.f,1.f);
    
    this->MinSpeed = MIN_PLANE_SPEED;
    this->MaxSpeed = MAX_PLANE_SPEED;
    this->Speed = this->MinSpeed;
    this->Acceleration = PLANE_ACCELERATION;
    
    this->RollSpeed = PLANE_ROLL_SPEED;
    this->YawSpeed = PLANE_YAW_SPEED;
    this->PitchSpeed = PLANE_PITCH_SPEED;
    
    this->time = glutGet(GLUT_ELAPSED_TIME);
}




void Plane::RotateX(int Dx)
{
    Character::RotateX(Dx);
    
    //The x-movement of the mouse correspond to a yaw rotation of the plane
    //The angle of rotation depends on the speed of yaw
    float degrees = this->YawSpeed * Dx;
    
    //And we have to rotate the axis of the plane around the up axis by this degree
    //So that we have to get the rotation matrix
    glm::mat3 rMatrix = RotationMatrix3(-1.f * degrees, this->Up);
    
    
    //Perform the rotation
    this->Axis = rMatrix * this->Axis;
    
    //And also rotate the model
    this->GetModel()->Rotate(rMatrix);
    
    //And the camera
    this->GetCamera()->SetViewDirection(this->Axis);
    
    
    //Then, update the position
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int dt = currentTime - this->time;
    this->time = currentTime;
    
    this->UpdatePosition(dt);
}




void Plane::RotateY(int Dy)
{
    Character::RotateY(Dy);
    
    //The y-movement of the mouse correspond to a pitch rotation of the plane
    //The angle of rotation depends on the speed of pitch
    float degrees = this->PitchSpeed * Dy;
    
    //And we also have to build the rotation axis, that is ortoghonal to both the up and the axis
    glm::vec3 rAxis = glm::normalize(glm::cross(this->Up, this->Axis));
    
    //And we have to rotate both the axes of the plane
    //So that we have to get the rotation matrix
    glm::mat3 rMatrix = RotationMatrix3(degrees, rAxis);
    
    
    //Perform the rotation
    this->Axis = rMatrix * this->Axis;
    this->Up = rMatrix * this->Up;
    
    //And also rotate the model
    this->GetModel()->Rotate(rMatrix);
    
    //And the camera
    this->GetCamera()->SetViewDirection(this->Axis);
    this->GetCamera()->SetUp(this->Up);
    
    
    //Then, update the position
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int dt = currentTime - this->time;
    this->time = currentTime;
    
    this->UpdatePosition(dt);
}




void Plane::MoveForward(int currentTime)
{
    Character::MoveForward(currentTime);
    
    //Update the speed
    this->Speed += this->Acceleration;
    if(this->Speed > this->MaxSpeed)
    {
        this->Speed = this->MaxSpeed;
    }
    
    
    //And update the position
    int dt = currentTime - this->time;
    this->time = currentTime;
    
    this->UpdatePosition(dt);
}




void Plane::MoveBackward(int currentTime)
{
    Character::MoveBackward(currentTime);
    
    
    //Update the speed
    this->Speed -= this->Acceleration;
    if(this->Speed < this->MinSpeed)
    {
        this->Speed = this->MinSpeed;
    }
    
    
    //And update the position
    int dt = currentTime - this->time;
    this->time = currentTime;
    
    this->UpdatePosition(dt);
}




void Plane::MoveRight(int currentTime)
{
    Character::MoveRight(currentTime);
    
    //MoveRight corresponds to a roll rotation of the plane
    //The angle of rotation depends on the speed of roll
    float degrees = this->RollSpeed;
    
    //And we have to rotate the up axis around the main axis of the plane
    //So that we have to get the rotation matrix
    glm::mat3 rMatrix = RotationMatrix3(degrees, this->Axis);
    
    
    //Perform the rotation
    this->Up = rMatrix * this->Up;
    
    //And also rotate the model
    this->GetModel()->Rotate(rMatrix);
    
    //And the camera
    this->GetCamera()->SetUp(this->Up);
    
    
    //And update the position
    int dt = currentTime - this->time;
    this->time = currentTime;
    
    this->UpdatePosition(dt);
}




void Plane::MoveLeft(int currentTime)
{
    Character::MoveLeft(currentTime);
    
    //MoveLeft corresponds to a roll rotation of the plane
    //The angle of rotation depends on the speed of roll
    float degrees = -1. * this->RollSpeed;
    
    //And we have to rotate the up axis around the main axis of the plane
    //So that we have to get the rotation matrix
    glm::mat3 rMatrix = RotationMatrix3(degrees, this->Axis);
    
    
    //Perform the rotation
    this->Up = rMatrix * this->Up;
    
    //And also rotate the model
    this->GetModel()->Rotate(rMatrix);
    
    //And the camera
    this->GetCamera()->SetUp(this->Up);
    
    
    //And update the position
    int dt = currentTime - this->time;
    this->time = currentTime;
    
    this->UpdatePosition(dt);
}



void Plane::onIdle(int currentTime)
{
    //Update the position
    int dt = currentTime - this->time;
    this->time = currentTime;
    
    this->UpdatePosition(dt);
}
