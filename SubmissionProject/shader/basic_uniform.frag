#version 460

//in variable that receives the diffuse calculation from the vertex shader
in vec3 LightIntensity;
in vec3 celShade;
in vec2 TextCoords;
in vec3 lightDirection;
in vec3 normal;

//out variable, this typical for all fragment shaders
layout (location = 0) out vec4 FragColor;

//uniforms
uniform vec3 cameraPos;
uniform sampler2D ourTexture;

void main()
{
    // get final colour using light calcs and texture info
    vec3 Texture = texture( ourTexture, TextCoords ).rgb; 

    // calculate specular highlights
    
    vec3 viewDir = vec3(normalize(vec4(cameraPos, 1.0f) - gl_FragCoord));
    vec3 reflectDir = reflect(-lightDirection, normal);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 result;

    if (spec > 0.2)     // if spec is high enough, set result to pure white
    {
        result = vec3(1,1,1);
    }

    else                // otherwise, set result based on texture colour and light intensity
    {
        result = Texture * LightIntensity;
    }

    FragColor = vec4(result, 1.0);

}
