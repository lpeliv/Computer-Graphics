#include <iostream>
#include <string>

#include "Window.h"
#include "Renderer.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInputJerJeRokovSmece(GLFWwindow* window, 
	glm::vec3* cameraPos, glm::vec3* cameraFront, 
	glm::vec3* cameraUp, float deltaTime);


//Camera variables
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Light
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
unsigned int VBO;

int main()
{
	Window window("Vjezba5", SCR_WIDTH, SCR_HEIGHT);

	Model model("res/models/cube.obj");
	Model model2("res/models/dragon.obj");
	Shader shader("res/shaders/vShaderColor.glsl", "res/shaders/fShaderColor.glsl");
	Shader shaderS("res/shaders/vShaderLight.glsl", "res/shaders/fShaderLight.glsl");
	Texture tex("res/textures/container.jpg");

	Renderer render;

	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	//KEEP
	glBindVertexArray(lightCubeVAO);
	//KEEP-

	while (!window.isClosed())
	{
		window.ProcessInput();
		render.Clear();

		//Task-1
		//-----------------------

		//KEEP
		unsigned int lightVAO;
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//KEEP-

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection;

		glm::mat4 modelM = glm::mat4(1.0f);
		modelM = glm::rotate
		(modelM, glm::radians(50.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		int modelLoc = glGetUniformLocation(shader.GetID(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));
		glm::vec3 objectPositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  0.5f, -1.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -2.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -3.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		shader.SetUniformVec3("objectColor", 1.0f, 0.5f, 0.31f);
		shader.SetUniformVec3("lightColor", 1.0f, 1.0f, 1.0f);

		//-----------------------

		//Task-2
		//-----------------------

		//-----------------------

		for (unsigned int i = 0; i < 2; i++)
		{
			modelM = glm::translate(modelM, objectPositions[i]);
			float angle = 10.0f * i;
			modelM = glm::rotate(modelM, glm::radians(angle), 
				glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetUniform4x4("model", modelM);
			model2.Draw(shader, tex);
		}
		glm::mat4 trans = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		int viewLoc = glGetUniformLocation(shader.GetID(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		projection = glm::perspective(glm::radians(45.0f), 
			800.0f / 600.0f, 0.1f, 100.0f);
		int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		processInputJerJeRokovSmece(window.GetWindow(), 
			&cameraPos, &cameraFront, &cameraUp, deltaTime);

		window.SwapAndPoll();
	}

	window.CloseWindow();

	return 0;
}

void processInputJerJeRokovSmece(GLFWwindow* window, 
	glm::vec3* cameraPos, glm::vec3* cameraFront, 
	glm::vec3* cameraUp, float deltaTime)
{
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		*cameraPos += cameraSpeed * *cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		*cameraPos -= cameraSpeed * *cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		*cameraPos -= glm::normalize
		(glm::cross(*cameraFront, *cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		*cameraPos += glm::normalize
		(glm::cross(*cameraFront, *cameraUp)) * cameraSpeed;
}