#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "World.h"
#include "State.h"
#include "Menu.h"
#include "Crosshair.h"

#include <iostream>
#include <functional>

//function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window); 
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//global variables
//screensize
const int screenWidth = 800, screenHeight = 600;
//camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)(screenWidth / 2.f);
float lastY = (float)(screenHeight / 2.f);
bool firstMouse = true;

// time
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//chunks (numberOfChunks is a perfect square)
int numberOfChunks = 16;

enum class state {
	game,
	menu
};

state gameState = state::menu;
bool swappedState = false, rightPosition = false;

int main() {
	//initialize the window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//initialize the window
	GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Minecraft", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}


	//set callback functions
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	//initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//some other opengl settings
	glEnable(GL_DEPTH_TEST);
	
	if(gameState == state::game) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else if (gameState == state::menu) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	

	//create a shaderprogram
	Shader defShader("shaders/vertexShader.vs", "shaders/fragementShader.fs");
	Shader menuShader("shaders/menV.vs", "shaders/menF.fs");
	//create the minecraft world
	std::unique_ptr<State> state;
	if (gameState == state::game) state = std::make_unique<World>(numberOfChunks, defShader);
	else state = std::make_unique<Menu>(menuShader);
	//projection matrix - model and view are elsewhere
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

	//diffuse lighting
	glm::vec3 lightPos = glm::vec3(15, 10, 15);
	defShader.setVec3("lightPos", lightPos);
	glm::vec3 lightColor = glm::vec3(1, 1, 1);
	defShader.setVec3("lightColor", lightColor);
	
	//day/night cycle
	bool day = true;

	//crosshair
	Crosshair hair;
	hair.loadCrosshair(menuShader);

	//render loop 
	while (!glfwWindowShouldClose(window)) {
		//check the game state
		if (swappedState) {
			if (gameState == state::game) state = std::make_unique<World>(numberOfChunks, defShader);
			else if (gameState == state::menu) state = std::make_unique<Menu>(menuShader);

			if (gameState == state::game) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else if (gameState == state::menu) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			swappedState = false;
		}
		//calculate time
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//process key input
		state->processInput(window, camera, deltaTime);
		
		//view matrix (updated every frame)
		glm::mat4 view = camera.GetViewMatrix();

		// draw here ----------------------------------------------------------------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//forward the view and projection matrices (they're intrinsic)
		defShader.setMat4("view", view);
		defShader.setMat4("projection", projection);	
		//lighting
		defShader.setVec3("viewPos", camera.Position);
		defShader.setVec3("lightPos", lightPos);

		//lighting--
		lightPos.x = 18;
		lightPos.z = abs(std::sin(glfwGetTime() / 8)) * 36; // * is number of blocks
		lightPos.y = 50 * std::sin(glfwGetTime() / 4);      // / has to be 2x on z than y

		if (lightPos.y < -16) lightColor = glm::vec3(0, 0, 0);
		else lightColor = glm::vec3(1, 1, 1);
		defShader.setVec3("lightColor", lightColor);
		//---

		if (gameState == state::game) hair.drawCrosshair(menuShader);
		//draw the world
		if (gameState == state::game) state->draw(defShader); 
		else if(gameState == state::menu) state->draw(menuShader);

		
		
		//----------------------------------------------------------------------------------
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
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	if (gameState == state::game) camera.ProcessMouseMovement(xoffset, yoffset);
	if (xpos > 211 && xpos < 586 && ypos > 271 && ypos < 316) rightPosition = true; else rightPosition = false;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (gameState == state::menu && rightPosition && action == GLFW_PRESS) {
		rightPosition = false;
		gameState = state::game;
		swappedState = true;
	}
}