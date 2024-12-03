#include <sgfx/sgxf.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "test.h"

float vertices[12] = {
    -0.5, -0.5, 1.0, 
    0.5, -0.5, 1.0,
    0.5, 0.5, 1.0,
    -0.5, 0.5, 1.0
}; 

static void initGlfw() 
{
    glfwInit(); 
    const GLFWwindow* window = glfwCreateWindow(600, 400, "Test", NULL, NULL); 
    glfwMakeContextCurrent(window); 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
        fprintf(stderr, "Failed to initialize GLAD\n"); 
    } 
}

int testHandles() {
    VertexBufferHandle vbo = sfgxCreateVertexBuffer((void*)vertices, sizeof(float) * sizeof(vertices));
    VertexBufferHandle vbo1 = sfgxCreateVertexBuffer((void*)vertices, sizeof(float) * sizeof(vertices));

    ASSERT_TRUE(vbo.idx == 0);
    ASSERT_TRUE(vbo1.idx == 1);

    sfgxDestroyVertexBuffer(&vbo);
    sfgxDestroyVertexBuffer(&vbo1);

    ASSERT_TRUE(vbo.idx == (uint16_t)(-1));
    ASSERT_TRUE(vbo1.idx == (uint16_t)(-1));

    return 1;
}

int testOpengl() {
    initGlfw();
    
    sfgxInit(Opengl);

    RUN_TEST(testHandles);
}