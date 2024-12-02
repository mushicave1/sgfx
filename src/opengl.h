#ifndef SGFX_OPENGL_H
#define SGFX_OPENGL_H

#include <glad/glad.h>

#include <sgfx/sgxf.h>


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

int openglCreateVertexBuffer(void *data, size_t byte_size, VertexBufferHandle *handle);
void openglDestroyVertexBuffer(VertexBufferHandle *handle);

int openglCreateIndexBuffer(void *data, size_t byte_size, IndexBufferHandle *handle);
void openglDestroyIndexBuffer(IndexBufferHandle *handle);

int openglCreateProgram(const char *fs_code, const char *vs_code, ProgramHandle *handle);
void openglDestroyProgram(ProgramHandle *handle);

int openglCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count, TextureHandle *handle);
void openglDestroyTexture(TextureHandle *handle);



#endif /** SGFX_OPENGL_H */