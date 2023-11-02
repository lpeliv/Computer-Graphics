#include <iostream>
#include <string>

#include "Window.h"
#include "Renderer.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window("Vjezba3", SCR_WIDTH, SCR_HEIGHT);
  
    Model model("res/models/rectangle.obj");
    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");
    Texture tex("res/textures/container.jpg");

    Texture secondTex("res/textures/awesomeface.png");

    Renderer render;
    while (!window.isClosed())
    {
        //1st task, changed vShader.glsl file
        //-----------------------------------------
        float xoffset = 0.1f;
        shader.SetUniformFloat("xOffset", xoffset);
        float yoffset = 0.1f;
        shader.SetUniformFloat("yOffset", yoffset);
        //-----------------------------------------

        //2nd task, changed fShader.glsl
        //-----------------------------------------
        float xColor = 0.8f;
        float yColor = 0.8f;
        float zColor = 1.0f;
        shader.SetUniformVec3("xColor", xColor, yColor, zColor);
        //-----------------------------------------

        //3rd task, changed vShader.glsl file
        //-----------------------------------------
        float xXColor = 0.8f;
        float yYColor = 0.8f;
        float zZColor = 0.0f;
        shader.SetUniformVec3("XColor", xXColor, yYColor, zZColor);
        //-----------------------------------------
        
        window.ProcessInput();
        render.Clear();

        model.Draw(shader, tex);

        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}