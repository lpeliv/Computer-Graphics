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

int main()
{
    Window window("Vjezba3", SCR_WIDTH, SCR_HEIGHT);
  
    Model model("res/models/rectangle.obj");
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
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        
        //Comented for task 3 - 3D
        /*int modelLoc = glGetUniformLocation(shader.GetID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));*/

        int viewLoc = glGetUniformLocation(shader.GetID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        //--------------------------------------------
        
        //Task 3 - 3D not working
        //--------------------------------------------
        modelM = glm::rotate
        (modelM, (float)glfwGetTime() * glm::radians(50.0f), 
            glm::vec3(0.5f, 1.0f, 0.0f));
        int modelLoc = glGetUniformLocation(shader.GetID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelM));
        //--------------------------------------------
        
        //Task 4-1 not working
        //--------------------------------------------
        //Object rotating, but not can't load 3D
        //--------------------------------------------
        
        //Task 4-2 not working
        //--------------------------------------------
        /*unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);

        glm::vec3 rectanglePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 modelM = glm::mat4(1.0f);
            modelM = glm::translate(modelM, rectanglePositions[i]);
            float angle = 20.0f * i;
            modelM = glm::rotate(modelM, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetUniform4x4("model", modelM);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }*/
        //--------------------------------------------

        //Task 4-3 not working
        //--------------------------------------------

        //--------------------------------------------

        //Task 4-4 not working
        //--------------------------------------------
        
        //--------------------------------------------

        model.Draw(shader, tex);

        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}