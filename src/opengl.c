#include "opengl.h"
#include "core.h"

typedef struct {
    GLVertexBuffer vertex_buffers[SGFX_MAX_VERTEX_BUFFERS];
    GLIndexBuffer index_buffers[SGFX_MAX_INDEX_BUFFERS];
    GLProgram programs[SGFX_MAX_PROGRAMS];
    GLTexture textures[SGFX_MAX_TEXTURES];
} OpenglContext;

OpenglContext s_ctx;

VertexBufferHandle openglCreateVertexBuffer(void *data, size_t byte_size) 
{ 
    static uint16_t counter = -1;
    counter++;
    GLVertexBuffer* buffer = &s_ctx.vertex_buffers[counter];
    glGenBuffers(1, &buffer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->vbo);
    glBufferData(GL_ARRAY_BUFFER, byte_size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    return (VertexBufferHandle){.idx = counter};
}

void openglDestroyVertexBuffer(VertexBufferHandle *handle) 
{
    GLVertexBuffer* buffer = &s_ctx.vertex_buffers[handle->idx];
    glDeleteBuffers(1, &buffer->vbo);
    handle->idx = SGFX_NULL_INDEX;
}

IndexBufferHandle openglCreateIndexBuffer(void *data, size_t byte_size) 
{
    static uint16_t counter = -1;
    counter++;
    GLIndexBuffer* buffer = &s_ctx.index_buffers[counter];
    glGenBuffers(1, &buffer->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);

    return (IndexBufferHandle){.idx = counter};
}

void openglDestroyIndexBuffer(IndexBufferHandle *handle) 
{
    GLIndexBuffer* buffer = &s_ctx.index_buffers[handle->idx];
    glDeleteBuffers(1, &buffer->ebo);
    handle->idx = SGFX_NULL_INDEX;
}


ProgramHandle openglCreateProgram(const char *fs_code, const char *vs_code) 
{
    static uint16_t counter = -1;
    counter++;
    GLProgram* program = &s_ctx.programs[counter];
    const GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, vs_code, NULL);
    glCompileShader(v_shader);
    GLint success;
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        char infoLog[512];
        glGetShaderInfoLog(v_shader, 512, NULL, infoLog);
        printf("Vertex shader compilation error: %s", infoLog);
    }
    
    const GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, fs_code, NULL);
    glCompileShader(f_shader);
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        char infoLog[512];
        glGetShaderInfoLog(f_shader, 512, NULL, infoLog);
        fprintf("Fragment shader compilation error: %s", infoLog);
    }

    program->program = glCreateProgram();
    glAttachShader(program->program, v_shader);
    glAttachShader(program->program, f_shader);
    glLinkProgram(program->program);
    glGetProgramiv(program->program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program->program, 512, NULL, infoLog);
        fprintf("Failed to link shaders into program: %s", infoLog);
    }
    
    return (ProgramHandle){.idx = counter};
}

void openglDestroyProgram(ProgramHandle *handle) 
{
    GLProgram* program = &s_ctx.programs[handle->idx];
    glDeleteProgram(program->program);
    handle->idx = SGFX_NULL_INDEX;
}

TextureHandle openglCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count) 
{   
    static uint16_t counter = -1;
    counter++;
    GLTexture* texture = &s_ctx.textures[counter];
    glGenTextures(1, &texture->tex);
    glBindTexture(GL_TEXTURE_2D, texture->tex);
    glTexImage2D(GL_TEXTURE_2D, 0, openglTextureInternalFormat(internal_format), width, height, 0, openglTextureFormat(format), GL_UNSIGNED_BYTE, (void*)pixels);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    
    return (TextureHandle){.idx = counter};
}

void openglDestroyTexture(TextureHandle *handle) 
{
    GLTexture* texture = &s_ctx.textures[handle->idx];
    glDeleteTextures(1, &texture->tex);
    handle->idx = SGFX_NULL_INDEX;
}



