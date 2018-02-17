# version 410

in vec3 fPosition;
in vec2 fTexCoord;
in vec3 fNormal;
in mat4 fModelTransformationMatrix;

struct Light {
    vec4 position;
    vec3 color;
    float attenuation;
    float ambientCoefficient;
    float padding1;
    float padding2;
    float padding3;
    vec3 coneDirection;
    float coneOpening;
};

layout(std140) uniform LightSources {
    Light Lights[8];
};

out vec4 lightedColor;

uniform sampler2D TextureSampler;

void main()
{
    //Calculate the matrix for normals transformation
    mat3 nModelTransformationMatrix = transpose(inverse(mat3(fModelTransformationMatrix)));
    //Calculate the normal in world coordinates
    vec3 wNormal = normalize(nModelTransformationMatrix * fNormal);
    
    //Calculate the position of the fragment in world coordinates
    vec3 wPosition = vec3(fModelTransformationMatrix * vec4(fPosition, 1.0));
    
    
    //And get the colour of the surface, depending on its texture
    vec4 fColor = texture(TextureSampler, fTexCoord.st);
    
    
    vec3 fToLight;
    vec4 tempColor = vec4(0.f,0.f,0.f,0.f);
    //Then, for each light
    for(int i=0;i<8;i++){
        //Get the distance of the light from the fragment
        fToLight = vec3(Lights[i].position) - wPosition;
            
        //And therefore the brightness, depending on the cosine of the angle of incidence of light
        float bright = dot(wNormal, fToLight) / (length(fToLight) * length(wNormal));
        bright = clamp(bright, 0.f, 1.f);
            
        tempColor = tempColor + vec4(bright * Lights[i].color * fColor.rgb, fColor.a);
    }
    
    //lightedColor = vec4(Lights[1].position);
    //lightedColor = vec4(fColor.rgb,Lights[0].isActive);
    lightedColor = tempColor;
}
