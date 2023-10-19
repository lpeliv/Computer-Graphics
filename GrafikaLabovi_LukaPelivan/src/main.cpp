#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();



    //_________________________________________________________________
    //My addition for 2nd exercise
    float finput = 0;
    int polygon = 0.0f;
    std::vector<float> vertices;
    std::vector<float> triangles;
    std::string line;

    std::cout << "What's your object name?: ";
    std::string objectName;
    std::cin >> objectName;

    std::ofstream file(objectName + ".obj");
    file << "# " + objectName + ".obj created by input." << std::endl << std::endl;;
    file << "g " + objectName << std::endl << std::endl;

    for (int i = 0; i <= 2; i++) {
        file << "v ";
        for (int j = 0; j < 2; j++) {

            std::cout << "What's your [" << i + 1 << "," << j + 1 << "] vertex location (0.x format)? : ";
            std::cin >> finput;
            file << finput << "0 ";
        }

        file << "0.0" << std::endl;
    }

    file << std::endl;

    for (int i = 0; i < 2; i++) {
        file << "f";
        for (int j = 0; j < 3; j++) {
            file << " ";
            std::cout << "What's your ["<< i + 1 << "," << j + 1 << "] polygon (x format)? : ";
            std::cin >> polygon;
            file << polygon;
        }
        
        file << std::endl;
    }

    file.close();

    std::ifstream file2(objectName + ".obj");
    while (getline(file2, line)) {
        if (line.find('v') != std::string::npos) {
            line.erase(0, line.find('v '));

            std::istringstream iss(line);
            std::copy(std::istream_iterator<float>(iss),
                std::istream_iterator<float>(),
                std::back_inserter(vertices));

            std::copy(vertices.begin(), vertices.end(),
                std::ostream_iterator<float>(std::cout, "f, "));
            std::cout << "\n";
        }

        else if (line.find('f') != std::string::npos) {
            line.erase(0, line.find('f'));
            std::istringstream iss(line);
            std::copy(std::istream_iterator<float>(iss),
                std::istream_iterator<float>(),
                std::back_inserter(triangles));

            std::copy(triangles.begin(), triangles.end(),
                std::ostream_iterator<float>(std::cout, ", "));
            std::cout << "\n";
        }
    }

    file.close();
    //________________________________________________________________
    //End of my addition
    


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {   
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}