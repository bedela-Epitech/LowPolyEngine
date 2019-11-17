
//#include <stb_image.h>

#include "encapsulation/Input.hpp"
#include "encapsulation/L_OpenGL.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// settings
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    L_OpenGL opengl("../7.1.camera.vs", "../7.1.camera.fs");
    // build and compile our shader zprogram
    // ------------------------------------

    opengl.linkVertices();
    opengl.linkColors();
    opengl.linkNormals();

    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 2512.f);
    opengl._shader.setMat4("projection", projection);

    Camera *camera = new Camera(0.f, 0.0f, -3.f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    Input inputKeys(camera);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        // -----
        inputKeys.KeyManager(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        opengl._shader.use();

        camera->updateCamera();

        opengl._shader.setVec3("cameraDir", camera->_dirLook);
        opengl._shader.setMat4("view", camera->_view);

        // render boxes
        glBindVertexArray(opengl._VAO);

        glDrawArrays(GL_TRIANGLES, 0, opengl._vertices.size() / 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &opengl._VAO);
    glDeleteBuffers(1, &opengl._VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}