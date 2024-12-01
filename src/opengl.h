#ifndef SGFX_OPENGL_H
#define SGFX_OPENGL_H

#include <glad/glad.h>

#include "core.h"


#ifdef USE_GLFW 
    #include <GLFW/glfw3.h> 

    #define SGFX_OPENGL_GLFW_INIT() \
        do { \
            glfwInit(); \
            const GLFWwindow* window = glfwCreateWindow(600, 400, "Test", NULL, NULL); \
            glfwMakeContextCurrent(window); \
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { \
                fprintf(stderr, "Failed to initialize GLAD\n"); \
                return -1; \
            } \
        } while (false) 
#endif

typedef struct { 
    void *vertices;
    GLuint vbo;
} GLVertexBuffer;

typedef struct {
    void *indices;
    GLuint ebo;
} GLIndexBuffer;

typedef struct {
    GLuint program;
} GLProgram;

typedef struct {
    GLuint tex;
    void* pixels;
    GLuint width;
    GLuint height;
    GLuint format;
    GLuint internal_format;
    GLuint mip_map_levels;
} GLTexture;


inline static GLenum openglTextureFormat(TextureFormat format) 
{
    switch(format) {
        case R: return GL_R; break;
        case Rg: return GL_RG; break;
        case Rgb: return GL_RGB; break;
        case Rgba: return GL_RGBA; break;
    }
}

inline static GLenum openglTextureInternalFormat(TextureInternalFormat internal_format) 
{
    switch(internal_format) {
        case Rgb32: return GL_RGB; break;
        case Rgb32f: return GL_RGB32F; break;
        case Rgba32: return GL_RGBA; break;
        case Rgba32f: return GL_RGBA32F; break;
    }
}


void sgfxOpenglInit();

int sgfxOpenglCreateVertexBuffer(void *data, size_t byte_size, GLVertexBuffer *buffer);
void sgfxOpenglDestroyVertexBuffer(GLVertexBuffer *vertex_buffer);

int sgfxOpenglCreateIndexBuffer(void *data, size_t byte_size, GLIndexBuffer *buffer);
void sgfxOpenglDestroyIndexBuffer(GLIndexBuffer *index_buffer);

int sgfxOpenglCreateProgram(const char *fs_code, const char *vs_code, GLProgram *program);
void sgfxOpenglDestroyProgram(GLProgram *program);

int sgfxOpenglCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count, GLTexture *texture);
void sgfxOpenglDestroyTexture(GLTexture *texture);








#endif /** SGFX_OPENGL_H */