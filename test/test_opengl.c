#include <sgfx/sgxf.h>
#include <opengl.h>
#include <GLFW/glfw3.h>

float vertices[12] = {
    -0.5, -0.5, 1.0, 
    0.5, -0.5, 1.0,
    0.5, 0.5, 1.0,
    -0.5, 0.5, 1.0
}; 

void initGlfw() {
    glfwInit(); 
    const GLFWwindow* window = glfwCreateWindow(600, 400, "Test", NULL, NULL); 
    glfwMakeContextCurrent(window); 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
        fprintf(stderr, "Failed to initialize GLAD\n"); 
    } 
}

int testOpengl() {
    sfgxInit(Vulkan);

    initGlfw();

    GLVertexBuffer vertex_buffer;
    openglCreateVertexBuffer((void*)vertices, sizeof(float) * sizeof(vertices), &vertex_buffer);
    openglDestroyVertexBuffer(&vertex_buffer);

    GLIndexBuffer index_buffer;
    openglCreateIndexBuffer((void*)vertices, sizeof(float) * sizeof(vertices), &index_buffer);
    openglDestroyIndexBuffer(&index_buffer);

    return 0;
}