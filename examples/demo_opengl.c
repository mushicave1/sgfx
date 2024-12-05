#include <stdio.h>
#include <sgxf.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"

float vertices[12] = {
    -0.5, -0.5, 1.0, 
    0.5, -0.5, 1.0,
    0.5, 0.5, 1.0,
    -0.5, 0.5, 1.0
}; 


uint32_t indices[12] = {
    0, 1, 2,
    2, 3, 0
};

void keyCallback(GLFWwindow* window, int key, int action, int mods, int scancode) {
    if(key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(int argc, char **argv) {

    GLFWwindow* window = createWindow();

    glfwSetKeyCallback(window, keyCallback);

    sgfxInit(Opengl);

    SGFXVertexBufferHandle vbo = sgfxCreateVertexBuffer((void*)vertices, sizeof(float) * sizeof(vertices));
    SGFXIndexBufferHandle ebo = sgfxCreateIndexBuffer((void*)indices, sizeof(indices) * sizeof(uint32_t));
    SGFXProgramHandle program = sgfxCreateProgram(sgfxReadFile("./examples/vs_basic.glsl"), sgfxReadFile("./examples/fs_color.glsl"));

    const uint32_t offsets[3] = {0};
    const uint32_t element_counts[3] = {3}; 
    SGFXBufferView view;
    view.offsets = offsets;
    view.len = 1;
    view.stride = 3 * sizeof(float);
    view.element_counts = element_counts;

    SGFXVertexInputHandle vao = sgfxCreateVertexInput(vbo, view, ebo);

    glViewport(0, 0, 600*2, 400*2);
    while(!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.12, 1.0);

        sgfxDrawIndexed(6, vao, program);
        glfwSwapBuffers(window);
    }

    sgfxDestroyVertexBuffer(&vbo);
    sgfxDestroyIndexBuffer(&ebo);
    sgfxDestroyProgram(&program);
    sgfxDestroyVertexInput(&vao);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
} 