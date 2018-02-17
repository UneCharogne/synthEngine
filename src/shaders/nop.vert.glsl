# version 410

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexCoord;
layout (location = 2) in vec3 vNormal;

uniform mat4 ProjectionMatrix; //Projection matrix
uniform mat4 ModelViewMatrix; //Model view matrix
uniform mat4 ModelTransformationMatrix; //Transformation matrix

out vec3 fPosition;
out vec2 fTexCoord;
out vec3 fNormal;
out mat4 fModelTransformationMatrix;

void main()
{
    gl_Position = ProjectionMatrix * ModelViewMatrix * ModelTransformationMatrix * vec4(vPosition, 1.0);
    
    fPosition = vPosition;
    fTexCoord = vTexCoord;
    fNormal = vNormal;
    fModelTransformationMatrix = ModelTransformationMatrix;
}
