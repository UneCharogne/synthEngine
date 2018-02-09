//
//  Worlds.hpp
//  
//
//  Created by Massimiliano Chiappini on 01/08/17.
//
//

#ifndef Worlds_hpp
#define Worlds_hpp

#include <stdio.h>
#include <vector>
#include <set>
#include <OpenGl/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



//Forward declarations
class Camera;
class Actor;



//The world is a container for all the object that take part to the game
//It holds and regulates the cameras, and controls the callbacks
//Every object that has callbacks, namely that interacts with the user and appear on screen,
//has to be an actor registered to the world
class World
{
        World();
    
        //Render program
        static GLuint RenderProgram;
    
        //Shader attributes addresses
        static GLuint ProjectionMatrix;
        static GLuint ModelViewMatrix;
        static GLuint ModelTransformationMatrix;
    
        //flags
        static bool FirstMouseMovement;
        static bool PerspectiveChanged;
    
        //Background
        static std::vector<glm::vec4> BackgroundColors;
        static int activeBackgroundColor;
    
        //Cameras
        static Camera* DefaultCamera;
        static Camera* ActiveCamera;
    
        //Actors
        static std::set<Actor*> Actors;
    
        //Perspective parameters (Maybe we should create a perspective class, to be a bit more elegant)
        static float fov;
        static int w;
        static int h;
        static float n;
        static float f;
    
        //Mouse position (Maybe we should need a mouse class, to be a bit more elegant)
        static int MouseX;
        static int MouseY;
    
    public:
        //Initialization
        static void InitializeWorld(int *argc, char** argv);
    
        //Background registration
        static void RegisterBackgroundColor(glm::vec4);
    
        //Camera activation and deactivation
        static void ActivateCamera(Camera* CameraToActivate);
        static void DeactivateCamera(void);
    
        //Actor registration and deregistration
        static void RegisterActor(Actor* ActorToRegister);
        static void DeregisterActor(Actor *ActorToDeregister);
    
        //Set and get methods
        static GLuint GetRenderProgram(void);
        static GLuint GetModelTransformationMatrix(void);
        static Camera* GetActiveCamera(void);
    
        static int GetMouseX(void);
        static int GetMouseY(void);
    
        //Callback functions
        static void onIdle(void);
        static void onDisplay(void);
        static void onWindowReshape(int neww, int newh);
        static void onKeyboardClick(unsigned char key, int x, int y);
        static void onMouseClick(int button, int state, int x, int y);
        static void onMouseDrag(int x, int y);
        static void onMouseMovement(int x, int y);
};


#endif /* Worlds_hpp */
