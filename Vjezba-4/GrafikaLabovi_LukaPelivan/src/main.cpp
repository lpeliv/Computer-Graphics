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

void processInputJerJeRokovSmece(GLFWwindow* window, glm::vec3* cameraPos, glm::vec3* cameraFront, glm::vec3* cameraUp, float deltaTime);


//Camera variables
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Timing

float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main()
{
    Window window("Vjezba4", SCR_WIDTH, SCR_HEIGHT);
  
    //Model model("res/models/rectangle.obj");
    Model model("res/models/dragon.obj");
    //Model model("res/models/cube.obj");
    Shader shader("res/shaders/vShaderLab4.glsl", "res/shaders/fShader.glsl");
    Texture tex("res/textures/container.jpg");
    Texture tex2("res/textures/awesomeface.png");

    Renderer render;
    while (!window.isClosed())
    {  
        window.ProcessInput();
        render.Clear();

        //Task 2
        //--------------------------------------------
        /*glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        vec = trans * vec;

        unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/
        //--------------------------------------------
        
        //Task 3 - 2D
        //--------------------------------------------
        glm::mat4 modelM = glm::mat4(1.0f);
        //Comented for task 3 - 3D
        //modelM = glm::rotate(modelM, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        
        
        glm::mat4 view = glm::mat4(1.0f);
        //Comented for task 4 - 4
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        
        //Comented for task 3 - 3D
        /*int modelLoc = glGetUniformLocation(shader.GetID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));*/
        /*

        int viewLoc = glGetUniformLocation(shader.GetID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));*/

        int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        //--------------------------------------------
        
        //Task 3 - 3D
        //--------------------------------------------
        /*modelM = glm::rotate
        (modelM, (float)glfwGetTime() * glm::radians(50.0f), 
            glm::vec3(0.0f, 1.0f, 0.0f));
        int modelLoc = glGetUniformLocation(shader.GetID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));*/
        //--------------------------------------------
        
        //Task 4-1 object rotation
        //--------------------------------------------
        /*modelM = glm::rotate
        (modelM, (float)glfwGetTime() * glm::radians(50.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));
        int modelLoc = glGetUniformLocation(shader.GetID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));
        */
        modelM = glm::rotate
        (modelM, glm::radians(50.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));
        int modelLoc = glGetUniformLocation(shader.GetID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));
        //--------------------------------------------
        
        //Task 4-2 15 objects
        //--------------------------------------------
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
        
        for (unsigned int i = 0; i < 10; i++)
        {
            modelM = glm::translate(modelM, objectPositions[i]);
            float angle = 20.0f * i;
            /*if (i % 3 == 0)
                angle = glfwGetTime() * 25.0f;*/
            modelM = glm::rotate(modelM, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetUniform4x4("model", modelM);

            model.Draw(shader, tex);
        }
        //--------------------------------------------

        //Task 4-3 rotate camera around object
        //--------------------------------------------
        /*glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));*/

        //--------------------------------------------

        //Task 4-4 not working
        //--------------------------------------------
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
        unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        int viewLoc = glGetUniformLocation(shader.GetID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInputJerJeRokovSmece(window.GetWindow(), &cameraPos, &cameraFront, &cameraUp, deltaTime);
        
        //--------------------------------------------

        //Commented for Task 4-2
        //model.Draw(shader, tex);

        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}

void processInputJerJeRokovSmece(GLFWwindow* window, glm::vec3 *cameraPos, glm::vec3 *cameraFront, glm::vec3 *cameraUp, float deltaTime)
{
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        *cameraPos += cameraSpeed * *cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        *cameraPos -= cameraSpeed * *cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        *cameraPos -= glm::normalize(glm::cross(*cameraFront, *cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        *cameraPos += glm::normalize(glm::cross(*cameraFront, *cameraUp)) * cameraSpeed;
}