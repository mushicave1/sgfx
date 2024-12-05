#include <sgfx/sgxf.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"

#include "test.h"

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

int testHandles() {
    SGFXVertexBufferHandle vbo = sgfxCreateVertexBuffer((void*)vertices, sizeof(float) * sizeof(vertices));
    SGFXVertexBufferHandle vbo1 = sgfxCreateVertexBuffer((void*)vertices, sizeof(float) * sizeof(vertices));

    ASSERT_TRUE(vbo.idx == 0);
    ASSERT_TRUE(vbo1.idx == 1);

    sgfxDestroyVertexBuffer(&vbo);
    sgfxDestroyVertexBuffer(&vbo1);

    ASSERT_TRUE(vbo.idx == (uint16_t)(-1));
    ASSERT_TRUE(vbo1.idx == (uint16_t)(-1));

    return 1;
}


int test_vertex_input() {
    SGFXVertexBufferHandle vbo = sgfxCreateVertexBuffer((void*)vertices, sizeof(float) * sizeof(vertices));
    SGFXIndexBufferHandle ebo = sgfxCreateIndexBuffer((void*)indices, sizeof(uint32_t) * sizeof(indices));

    const uint32_t offsets[3] = {0, 3*sizeof(float), 5*sizeof(float)};
    const uint32_t element_counts[3] = {3, 3, 2}; 
    SGFXBufferView view;
    view.offsets = offsets;
    view.len = 3;
    view.stride = 8 * sizeof(float);
    view.element_counts = element_counts;

    SGFXVertexInputHandle vao = sgfxCreateVertexInput(vbo, view, ebo);

    sgfxDestroyVertexBuffer(&vbo);
    sgfxDestroyIndexBuffer(&ebo);
    sgfxDestroyVertexInput(&vao);

    return 0;
}

int test_shader_program() {

}

int testOpengl() {
    GLFWwindow* window = createWindow();
    
    sgfxInit(Opengl);

    RUN_TEST(testHandles);
    RUN_TEST(test_vertex_input);
    RUN_TEST(test_shader_program);
}