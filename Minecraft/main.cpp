#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "World.h"

#include <stb_image.h>
#include <iostream>

//function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);

//global variables
int screenWidth = 800, screenHeight = 600;
//camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)screenWidth / 2.0;
float lastY = (float)screenHeight / 2.0;
bool firstMouse = true;

// time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//chunks (numberOfChunks is a perfect square)
int numberOfChunks = 4;

int main() {
	//initialize the window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//initialize the window
	GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "RPG_F", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	//initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	Shader shaderProgram("shaders/vertexShader.vs", "shaders/fragementShader.fs");

	
	//model matrix
	//in chunk class
	//view matrix
	//not here rn
	//projection matriy
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		
	World world(numberOfChunks, shaderProgram);

	//render loop 
	while (!glfwWindowShouldClose(window)) {
		//calculate time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		
		//view matrix
		glm::mat4 view = camera.GetViewMatrix();

		//block.act(shaderProgram);

		// draw here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//forward the view and projection matrices (they're static)
		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);	

		world.drawWorld(shaderProgram);
		
		//------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//exit
	glfwTerminate();
	return 0;
}

//call this everytime we adjust window size, to change to change the viewport accordingly
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//processes input
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

//process mouse input
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}