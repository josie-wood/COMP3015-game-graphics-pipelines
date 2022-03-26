#version 460

//in variable that receives the diffuse calculation from the vertex shader
in vec3 LightIntensity;
in vec3 celShade;
in vec2 TextCoords;

//out variable, this typical for all fragment shaders
layout (location = 0) out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    // get final colour using light calcs and texture info
    vec3 Texture = texture( ourTexture, TextCoords ).rgb; 
    vec3 result = Texture * LightIntensity;
    FragColor = vec4(result, 1.0);

}
