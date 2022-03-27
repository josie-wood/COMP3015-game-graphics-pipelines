# COMP3015-game-graphics-pipelines - Toon Teapot Shader

![Shader screenshot](https://github.com/josie-wood/COMP3015-game-graphics-pipelines/blob/main/SubmissionProject/shader-screenshot.png)

### Which version Visual Studio and Operating System you used to test/write the code locally?
I wrote the code in Visual Studio 2019 with Windows 10.

### How does it work?
I've created a 'toony' cel shaded technique inspired by the lighting in Zelda: Breath of the wild. 

The vert shader takes the light direction and the normal direction and performs a dot product calculation with these to create the normalized sDotN float, which gives a value between 0 and 1, where 0 indicates that the vertex is facing away from the light direction, and 1 indicating it is fully facing the light. 
From there, I have rounded this sDotN value up so all vertices have one of 4 values - either 0.25, 0.5, 0.75, or 1. This is then used in the light intensity calculations which is passed on to the frag shader, so there are 4 distinct 'bands' of lighting levels. 

In the frag shader, texturing is applied and specular highlights are managed. 

To make specular highlights in this cartoony style, a spec value is created from the dot product of the camera direction and the angle of reflection off of the surface. Then, if this spec value is creater than a given value (I chose 0.2 for this), indicating the angle between the light reflecting off of the surface and the angle at which the camera looks at the surface is small, the result is automatically set to pure white, vec3(1,1,1).

If the spec value is not within that range, the colour for the fragment is determined by the light intensity passed on from the vert shader and the texture. 

The out value of FragColour is a vec4 version of the result. 

### How does your code fit together and how should a programmer navigate it (not intended to be an exercise in formally documenting the code)?
The main body of code is in SceneBasic_Uniform. 
The model is instantiated in from the provided teapot.cpp method. 
The model data is passed through basic_uniform.vert and the basic_uniform.frag. 

### Anything else which will help us to understand how your prototype works.
I built my prototype around the given project template.
For this prototype, the model used needs to be high poly to ensure smooth shadows. 

### A Link to the unlisted YouTube Video
https://youtu.be/DA_WGD_tWdw

