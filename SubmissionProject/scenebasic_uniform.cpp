#include "scenebasic_uniform.h"

#include <iostream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;

#define STB_IMAGE_IMPLEMENTATION
#include "helper/stb/stb_image.h"

//variables
vec3 cameraPos = vec3(4.0f, 4.0f, 4.0f);

//constructor for teapot
SceneBasic_Uniform::SceneBasic_Uniform() : teapot(150, glm::translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.25f))) {}

void SceneBasic_Uniform::initScene()
{
    compile();
	glEnable(GL_DEPTH_TEST);
   
    //initialise the model matrix
    model = mat4(1.0f);
    
    model = glm::translate(model, vec3(0.0, -1.0, 0.0));
    model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    view = glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    projection = mat4(1.0f);

    //uniforms
    prog.setUniform("Material.Kd", 0.9f, 0.7f, 0.8f); 
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);    
    prog.setUniform("Light.Position", view * glm::vec4(5.0f, 5.0f, 2.0f, 0.0f)); 
    prog.setUniform("CameraPosition", cameraPos);

    loadTextureFromFile("media/teapot-texture-heart.png");
    
    // Pass the texture to the shader.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturebuffer);
    glUniform1i(texturebuffer, 0);
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    //rotating the model to show off shader
    model = glm::rotate(model, glm::radians(1.0f), vec3(0.0f, 0.0f, -1.0f));
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setMatrices(); //we set matrices 
    
    teapot.render();
}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model; //we create a model view matrix
    
    prog.setUniform("ModelViewMatrix", mv); //set the uniform for the model view matrix
    
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //we set the uniform for normal matrix
    
    prog.setUniform("MVP", projection * mv); //we set the model view matrix by multiplying the mv with the projection matrix
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}

//texture
//======================

void SceneBasic_Uniform::loadTextureFromFile(const char* filePath) {
    if (strcmp(filePath, "") != 0) {
        printf("Loading Image %s...", filePath);
        GLint programID = prog.getHandle();
        glGenTextures(1, &texturebuffer);
        int width, height, comp;
        unsigned char* image = stbi_load(filePath, &width, &height, &comp, STBI_rgb_alpha);
        if (image == nullptr) {
            printf("Failed. Image wasn't able to load.\n");
        }
        else {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texturebuffer);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            stbi_image_free(image);
            glUniform1i(glGetUniformLocation(programID, "ourTexture"), 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            printf("Done\n");
        }
    }
}



