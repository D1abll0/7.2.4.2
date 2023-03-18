#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\dual_quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../include/stb_image.h"
#include "../include/shader.h"
#include "../include/camera.h"
#include "../include/animator.h"
#include "../include/model_animation.h"
#include "../include/model_manager.h"


#include <iostream>

using namespace std;
using namespace glm;

const int W = 800;
const int H = 600;

Camera camera(vec3(0.0f, 0.0f, 3.0f));

float lastX = W / 2;
float lastY = H / 2;
bool firstMouse = 1;

float dt = 0;
float lastFrame = 0;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, true);
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    	camera.ProcessKeyboard(FORWARD, dt);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    	camera.ProcessKeyboard(BACKWARD, dt);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
     	camera.ProcessKeyboard(LEFT, dt);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
     	camera.ProcessKeyboard(RIGHT, dt);
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, dt);
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, dt);  	
		
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.acceleration = 0.1f;  			
	else camera.acceleration = 1.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = 0;
	}
	float ox = xpos - lastX;
	float oy = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	
	camera.ProcessMouseMovement(ox, oy);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(W, H, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    float vertices[]
	{
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
                            
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
                            
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
                            
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
                            
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
                            
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);	


    Shader shaderMDLA("shaders/ModelA/vertex.glsl", "shaders/ModelA/fragment.glsl");
    Shader shaderMDLS("shaders/ModelS/vertex.glsl", "shaders/ModelS/fragment.glsl");
	Shader shaderSUN("shaders/Light/vertex.glsl", "shaders/Light/fragment.glsl");
	
	MDLManager MDL1(STATIC, shaderMDLS, "resources/3D/tetris/figures/S/model.dae");
//	MDLManager MDL2(DYNAMIC, shaderMDLA, "resources/3D/vampire/dancing_vampire.dae", "resources/3D/vampire/dancing_vampire.dae");
	MDLManager MDL2(DYNAMIC, shaderMDLA, "resources/3D/tetris/characters/Ellipsoid/model.dae", "resources/3D/tetris/characters/Ellipsoid/idle.dae");

	shaderMDLS.use();
	shaderMDLS.setInt("material.diffuse", 0);	
	shaderMDLA.use();
	shaderMDLA.setInt("material.diffuse", 0);
	
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

		MDL2.Animate(0);


        glClearColor(0.1, 0.1, 0.1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		vec3 lightPos(.0f, 2.0f, -1.0f);

		mat4 model = mat4(1.0);
        mat4 view = camera.GetViewMatrix();
        mat4 projection = perspective(radians(camera.Zoom), (float)W / (float)H, 0.1f, 100.0f);

		shaderMDLS.use();
		shaderMDLS.setVec3("light.position", lightPos);
		shaderMDLS.setVec3("viewPos", camera.Position);
		shaderMDLS.setVec3("light.ambient", .2f, .2f, .2f);
		shaderMDLS.setVec3("light.diffuse", .5f, .5f, .5f);
		shaderMDLS.setVec3("light.specular", .5f, .5f, .5f);	
		shaderMDLS.setVec3("material.specular", .5f, .5f, .5f);
		shaderMDLS.setFloat("material.shininess", 64.f);	
		
		MDL1.SetModelMat(model);
		MDL1.SetViewMat(view);
		MDL1.SetProjMat(projection);
		MDL1.Scale(0.3);
		MDL1.Draw();		
//---------------------------
		shaderMDLA.use();
		shaderMDLA.setVec3("light.position", lightPos);
		shaderMDLA.setVec3("viewPos", camera.Position);	
		shaderMDLA.setVec3("light.ambient", .2f, .2f, .2f);
		shaderMDLA.setVec3("light.diffuse", .5f, .5f, .5f);
		shaderMDLA.setVec3("light.specular", .5f, .5f, .5f);
		shaderMDLA.setVec3("material.specular", .5f, .5f, .5f);
		shaderMDLA.setFloat("material.shininess", 64.f);
		
		MDL2.SetModelMat(model);
		MDL2.SetViewMat(view);
		MDL2.SetProjMat(projection);
		MDL2.Translate(vec3(2, -1, 0));
		MDL2.Scale(1.);
		MDL2.Draw();
//---------------------------
		shaderSUN.use();
		model = mat4(1.0f);
		model = translate(model, lightPos);
		model = scale(model, vec3(.1f));
		shaderSUN.setMat4("projection", projection);
		shaderSUN.setMat4("view", view);
		shaderSUN.setMat4("model", model);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
