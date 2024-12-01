#include <opengl.h>

float vertices[12] = {
    -0.5, -0.5, 1.0, 
    0.5, -0.5, 1.0,
    0.5, 0.5, 1.0,
    -0.5, 0.5, 1.0
};

int testOpengl() {

    SGFX_OPENGL_GLFW_INIT();

    GLVertexBuffer vertex_buffer;
    sgfxOpenglCreateVertexBuffer((void*)vertices, sizeof(float) * sizeof(vertices), &vertex_buffer);
    sgfxOpenglDestroyVertexBuffer(&vertex_buffer);

    GLIndexBuffer index_buffer;
    sgfxOpenglCreateIndexBuffer((void*)vertices, sizeof(float) * sizeof(vertices), &index_buffer);
    sgfxOpenglDestroyIndexBuffer(&index_buffer);

    return 0;
}