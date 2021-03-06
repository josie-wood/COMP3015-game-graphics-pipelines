#version 460

//in variables
layout (location = 0) in vec3 VertexPosition; 
layout (location = 1) in vec3 VertexNormal; 
layout (location = 2) in vec2 texCoords;

//out variables
out vec2 TextCoords;
out vec3 LightIntensity; 
out vec3 celShade;
out vec3 lightDirection;
out vec3 normal;

 //light information struct
uniform struct LightInfo 
{
  vec4 Position; // Light position in eye coords.
  vec3 Ld;       // Diffuse light intensity
} Light;

//material information struct
uniform struct MaterialInfo 
{
  vec3 Kd;      // Diffuse reflectivity
} Material;

//uniforms for matrices required in the shader
uniform mat4 ModelViewMatrix;   //model view matrix
uniform mat3 NormalMatrix;		//normal matrix
uniform mat4 MVP;				//model view projection matrix
 
void main() 
{ 
  //transfrom normal from model coordinates to view coordinates
    vec3 n = normalize( NormalMatrix * VertexNormal);
    normal = n;
  //transform vertex position from model coordinates to view coordinates
    vec4 pos = ModelViewMatrix * vec4(VertexPosition,1.0);

  //calculate light direction, notice the light is already in the view coordinates 
    vec3 s = normalize(vec3(Light.Position - pos));

    lightDirection = s;

  //calculate dot product for vector s and n using max. Read about max in glsl documentation, if not clear talk to me
    float sDotN = max( dot(s,n), 0.0 );
  
  //calculate bands of shadows based on sDotN

    if( sDotN < 0.25)
    {
        sDotN = 0.25;
    }
    else if (sDotN <0.5)
    {
        sDotN = 0.5;
    }
    else if (sDotN <0.75)
    {
        sDotN = 0.75;
    }
    else
{
        sDotN = 1;
    }
      
    
  //pass the colour to LightIntensity which will transfer it to the fragment shader
    LightIntensity = Light.Ld * Material.Kd * sDotN;;

  //turns any vertex position into model view projection in preparations to 
  //graphics pipeline processes before fragment shader (clipping)
     gl_Position = MVP * vec4(VertexPosition,1.0); 

    TextCoords = texCoords;
} 