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
    //we pass LightInyensity to outr FragColor, notice the difference between vector types
    // vec3 and vec4 and how we solved the problem
    
    vec3 diffText = texture( ourTexture, TextCoords ).rgb; 
      vec3 result = diffText * LightIntensity;
      FragColor = vec4(result, 1.0);

    // vec3 diffText = texture( ourTexture, UV ).rgb; 
}
