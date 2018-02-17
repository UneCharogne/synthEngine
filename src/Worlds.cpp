//
//  Worlds.cpp
//  
//
//  Created by Massimiliano Chiappini on 01/08/17.
//
//




#include "Worlds.hpp"
#include "Shaders.hpp"
#include "Lights.hpp"
#include "Cameras.hpp"
#include "Actors.hpp"



//Parameters
#define fov0 30.f
#define n0 0.01f
#define f0 100.f

#define VERTEX_SHADER_URL "shaders/nop.vert.glsl"
#define FRAGMENT_SHADER_URL "shaders/nop.frag.glsl"
#define LIGHT_SOURCES_NAME "LightSources"
#define PROJECTION_MATRIX_NAME "ProjectionMatrix"
#define MODEL_VIEW_MATRIX_NAME "ModelViewMatrix"
#define MODEL_TRANSFORMATION_MATRIX_NAME "ModelTransformationMatrix"

#define delta 0.2




//Initialization of static variables
GLuint World::RenderProgram = -1;

GLuint World::ProjectionMatrix = -1;
GLuint World::ModelViewMatrix = -1;
GLuint World::ModelTransformationMatrix = -1;

GLuint World::LightSourcesIndex = -1;
GLuint World::LightSourcesBindingPoint = -1;
GLuint World::LightSourcesBuffer = -1;

bool World::FirstMouseMovement = true;
bool World::PerspectiveChanged = false;
bool World::LightsChanged = true;

std::vector<glm::vec4> World::BackgroundColors = std::vector<glm::vec4>();
int World::activeBackgroundColor = -1;

std::vector<Light*> World::Lights = std::vector<Light*>();

Camera* World::DefaultCamera = new Camera();
Camera* World::ActiveCamera = NULL;

std::set<Actor*> World::Actors = std::set<Actor*>();

float World::fov = fov0;
int World::w = 100;
int World::h = 100;
float World::n = n0;
float World::f = f0;

int World::MouseX = 0;
int World::MouseY = 0;




void World::InitializeWorld(int *argc, char** argv)
{
    //Initialize glut
    glutInit(argc, argv);
    
    //Request the types of buffers
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    //And if this is not an APPLE system initialize glew
    #ifndef __APPLE__
    glewInit();
    #endif
    
    
    //Resize window given the screen size
    World::w = glutGet(GLUT_SCREEN_WIDTH);
    World::h = glutGet(GLUT_SCREEN_HEIGHT);
    
    
    //Initialize the window's size
    glutInitWindowSize(World::w, World::h);
    
    //And position
    glutInitWindowPosition(World::w/2, World::h/2);
    
    //Then create the window
    glutCreateWindow("MyGameEngine");
    
    
    //Initialize the viewport
    glViewport(0,0, (GLsizei)w, (GLsizei)h);
    
    
    //Initialize shaders
    GLuint VertexShader = InitializeShader(GL_VERTEX_SHADER, VERTEX_SHADER_URL);
    GLuint FragmentShader = InitializeShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_URL);
    //Link shaders
    World::RenderProgram = InitializeProgram(VertexShader, FragmentShader);
    //Detach and delete the shaders
    glDetachShader(World::RenderProgram, VertexShader);
    glDeleteShader(VertexShader);
    glDetachShader(World::RenderProgram, FragmentShader);
    glDeleteShader(FragmentShader);
    
    
    //Get the attributes for the matrices
    World::ProjectionMatrix = glGetUniformLocation(World::RenderProgram, PROJECTION_MATRIX_NAME);
    World::ModelViewMatrix = glGetUniformLocation(World::RenderProgram, MODEL_VIEW_MATRIX_NAME);
    World::ModelTransformationMatrix = glGetUniformLocation(World::RenderProgram, MODEL_TRANSFORMATION_MATRIX_NAME);
    
    
    //Get the index of the uniform buffer block in the fragment shader
    if((World::LightSourcesIndex = glGetUniformBlockIndex(World::RenderProgram, LIGHT_SOURCES_NAME)) == GL_INVALID_INDEX) {
        std::cout << "Error locating the block " << LIGHT_SOURCES_NAME << " in the fragment shader, program will be arrested.\n";
        exit(EXIT_FAILURE);
    }
    //And its binding point
    glUniformBlockBinding(World::RenderProgram, World::LightSourcesIndex, World::LightSourcesBindingPoint);
    //Then, generate the buffer for the light sources
    glGenBuffers(1, &(World::LightSourcesBuffer));
    
    
    //Enable depth test
    glEnable(GL_DEPTH_TEST);
    
    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    //Set the starting background
    World::RegisterBackgroundColor(glm::vec4(0.f,0.f,0.f,0.f));
    glClearColor(World::BackgroundColors[activeBackgroundColor].r, World::BackgroundColors[activeBackgroundColor].g, World::BackgroundColors[activeBackgroundColor].b, World::BackgroundColors[activeBackgroundColor].a);
    
    //Activate the camera
    World::ActivateCamera(World::DefaultCamera);
    
    
    //Setup callbacks
    glutIdleFunc(World::onIdle);
    glutDisplayFunc(World::onDisplay);
    glutReshapeFunc(World::onWindowReshape);
    glutKeyboardFunc(World::onKeyboardClick);
    glutMouseFunc(World::onMouseClick);
    glutMotionFunc(World::onMouseMovement);
    glutPassiveMotionFunc(World::onMouseMovement);
}




void World::RegisterBackgroundColor(glm::vec4 BackgroundColorToRegister)
{
    World::BackgroundColors.push_back(BackgroundColorToRegister);
    World::activeBackgroundColor++;
}



void World::RegisterLight(Light* LightToRegister)
{
    World::Lights.push_back(LightToRegister);
    World::LightsChanged = true;
}




void World::DeregisterLight(Light* LightToDeregister)
{
    std::vector<Light*>::iterator light;
    std::vector<Light*>::iterator lighttoerase;
    for(light=World::Lights.begin();light!=World::Lights.end();light++)
    {
        if((*light) == LightToDeregister)
        {
            lighttoerase = light;
        }
    }
    World::Lights.erase(lighttoerase);
    
    World::LightsChanged = true;
}




void World::ActivateCamera(Camera* CameraToActivate)
{
    World::ActiveCamera = CameraToActivate;
    World::ActiveCamera->SetViewingChanged(true);
}




void World::DeactivateCamera(void)
{
    World::ActiveCamera = World::DefaultCamera;
    World::ActiveCamera->SetViewingChanged(true);
}



void World::RegisterActor(Actor* ActorToRegister)
{
    World::Actors.insert(ActorToRegister);
}




void World::DeregisterActor(Actor* ActorToDeregister)
{
    std::set<Actor*>::iterator actor;
    std::set<Actor*>::iterator actortoerase;
    for(actor=World::Actors.begin();actor!=World::Actors.end();actor++)
    {
        if((*actor) == ActorToDeregister)
        {
            actortoerase = actor;
        }
    }
    World::Actors.erase(actortoerase);
}




GLuint World::GetRenderProgram(void)
{
    return World::RenderProgram;
}




GLuint World::GetModelTransformationMatrix(void)
{
    return World::ModelTransformationMatrix;
}




Camera* World::GetActiveCamera(void)
{
    return World::ActiveCamera;
}




int World::GetMouseX(void)
{
    return World::MouseX;
}




int World::GetMouseY(void)
{
    return World::MouseY;
}




void World::onIdle()
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    std::set<Actor*>::iterator actor;
    for(actor=World::Actors.begin();actor!=Actors.end();actor++)
    {
        (*actor)->onIdle(currentTime);
    }
    
    glutPostRedisplay();
}




void World::onDisplay()
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    
    //glm::mat4 PerspectiveMatrix;
    //glm::mat4 LookAtMatrix;
    
    
    //Reset the view
    glClearColor(World::BackgroundColors[activeBackgroundColor].r, World::BackgroundColors[activeBackgroundColor].g, World::BackgroundColors[activeBackgroundColor].b, World::BackgroundColors[activeBackgroundColor].a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    //Eventually update the lights
    if(World::LightsChanged)
    {
        //TODO
        //Build the lights buffer object
        Light LightSources[MAX_N_LIGHTS];
        
        int i=0;
        while((i < MAX_N_LIGHTS) && (i < World::Lights.size())) {
            LightSources[i] = *(World::Lights[i]);
            i++;
        }
        while((i < MAX_N_LIGHTS)) {
            LightSources[i] = NullLight;
            i++;
        }
        
        //Send it to the shader
        glBindBuffer(GL_UNIFORM_BUFFER, World::LightSourcesBuffer);
        glBufferData(GL_UNIFORM_BUFFER, (MAX_N_LIGHTS * sizeof(Light)), LightSources, GL_STATIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, World::LightSourcesIndex, World::LightSourcesBuffer);
        
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        
        World::LightsChanged = false;
    }
    
    
    //Eventually update the perspective matrix
    if(World::PerspectiveChanged)
    {
        //Determine the perspective matrix
        glm::mat4 PerspectiveMatrix = glm::perspective(World::fov, (GLfloat)World::w/(GLfloat)World::h, World::n, World::f);
        //And send it to the shader
        glUniformMatrix4fv(World::ProjectionMatrix, 1, GL_FALSE, &(PerspectiveMatrix[0][0]));
        
        World::PerspectiveChanged = false;
    }
    
    //Eventually update the model view matrix
    //HANDLE IF NO CAMERA!
    if(World::ActiveCamera->GetViewingChanged())
    { 
        //Determine the viewing matrix
        glm::mat4 LookAtMatrix = World::ActiveCamera->GetLookAt();
        //And send it to the shader
        glUniformMatrix4fv(World::ModelViewMatrix, 1, GL_FALSE, &(LookAtMatrix[0][0]));
        
        World::ActiveCamera->SetViewingChanged(false);
    }
    
    std::set<Actor*>::iterator actor;
    for(actor=World::Actors.begin();actor!=Actors.end();actor++)
    {
        (*actor)->onDisplay(currentTime);
    }
    
    glFlush();
}




void World::onWindowReshape(int neww, int newh)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    //Set the new window shape
    World::w = neww;
    World::h = newh;
    
    
    //Adapt the viewport
    glViewport(0,0, (GLsizei)neww, (GLsizei)newh);
    
    
    //And rebuild the matrix of projection
    World::PerspectiveChanged = true;
    
    
    std::set<Actor*>::iterator actor;
    for(actor=World::Actors.begin();actor!=Actors.end();actor++)
    {
        (*actor)->onWindowReshape(currentTime, neww, newh);
    }
    
    glutPostRedisplay();
}




void World::onKeyboardClick(unsigned char key, int x, int y)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    switch(key)
    {
        case 27: //Escape to quit
            exit(0);
            break;
            
        default:
            break;
    }
    
    std::set<Actor*>::iterator actor;
    for(actor=World::Actors.begin();actor!=Actors.end();actor++)
    {
        (*actor)->onKeyboardClick(currentTime, key, x, y);
    }
    
    glutPostRedisplay();
}




void World::onMouseClick(int button, int state, int x, int y)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    std::set<Actor*>::iterator actor;
    for(actor=World::Actors.begin();actor!=Actors.end();actor++)
    {
        (*actor)->onMouseClick(currentTime, button, state, x, y);
    }
    
    glutPostRedisplay();
}




void World::onMouseDrag(int x, int y)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    
    //If this is not the first movement of the mouse
    if(!World::FirstMouseMovement)
    {
        std::set<Actor*>::iterator actor;
        for(actor=World::Actors.begin();actor!=Actors.end();actor++)
        {
            (*actor)->onMouseDrag(currentTime, x, y);
        }
    }
    
    //Update the mouse position
    World::MouseX = x;
    World::MouseY = y;
    
    //This is not (anymore) the first movement of the mouse
    World::FirstMouseMovement = false;
    
    glutPostRedisplay();
}




void World::onMouseMovement(int x, int y)
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    
    //If this is not the first movement of the mouse
    if(!World::FirstMouseMovement)
    {
        std::set<Actor*>::iterator actor;
        for(actor=World::Actors.begin();actor!=Actors.end();actor++)
        {
            (*actor)->onMouseMovement(currentTime, x, y);
        }
    }
    
    //Update the mouse position
    World::MouseX = x;
    World::MouseY = y;
    
    //This is not (anymore) the first movement of the mouse
    World::FirstMouseMovement = false;
    
    glutPostRedisplay();
}
