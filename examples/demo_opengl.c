#include <stdio.h>
#include <sgxf.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float vertices[12] = {
    -0.5, -0.5, 1.0, 
    0.5, -0.5, 1.0,
    0.5, 0.5, 1.0,
    -0.5, 0.5, 1.0
}; 


void keyCallback(GLFWwindow* window, int key, int action, int mods, int scancode) {
    if(key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static GLFWwindow* initGlfw() 
{
    glfwInit(); 
    GLFWwindow* window = glfwCreateWindow(600, 400, "Test", NULL, NULL); 
    glfwMakeContextCurrent(window); 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
        fprintf(stderr, "Failed to initialize GLAD\n"); 
    } 

    glfwSetKeyCallback(window, keyCallback);

    return window;
}


int main(int argc, char **argv) {
    GLFWwindow* window = initGlfw();
    sfgxInit(Opengl);

    VertexBufferHandle vbo = sfgxCreateVertexBuffer((void*)vertices, sizeof(float) * sizeof(vertices));

    while(!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();
        glClearColor(0.1, 0.5, 0.1, 1.0);
        glfwSwapBuffers(window);
    }

    sfgxDestroyVertexBuffer(&vbo);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 