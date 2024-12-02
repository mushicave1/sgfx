#include "opengl.h"



typedef struct {
    GLVertexBuffer vertex_buffers[SGFX_MAX_VERTEX_BUFFERS];
    GLVertexBuffer index_buffers[SGFX_MAX_INDEX_BUFFERS];
    GLVertexBuffer programs[SGFX_MAX_PROGRAMS];
    GLVertexBuffer textures[SGFX_MAX_TEXTURES];
} OpenglContext;

OpenglContext s_ctx;

int openglCreateVertexBuffer(void *data, size_t byte_size, VertexBufferHandle *handle) 
{
    GLVertexBuffer* buffer = &s_ctx.vertex_buffers[handle->idx];
    glGenBuffers(1, &buffer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->vbo);
    glBufferData(GL_ARRAY_BUFFER, byte_size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    return 1;
}

void openglDestroyVertexBuffer(VertexBufferHandle *handle) 
{
    GLVertexBuffer* buffer = &s_ctx.vertex_buffers[handle->idx];
    glDeleteBuffers(1, &buffer->vbo);
}

int openglCreateIndexBuffer(void *data, size_t byte_size, IndexBufferHandle *handle) 
{
    glGenBuffers(1, &buffer->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
    return 1;
}

void openglDestroyIndexBuffer(IndexBufferHandle *handle) 
{
    glDeleteBuffers(1, &index_buffer->ebo);
}


int openglCreateProgram(const char *fs_code, const char *vs_code, ProgramHandle *handle) 
{
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
        return 0;
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
        return 0;
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
    
    return 1;
}

void openglDestroyProgram(ProgramHandle *handle) 
{
    glDeleteProgram(program->program);
}

int openglCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count, TextureHandle *handle) 
{   
    glGenTextures(1, &texture->tex);
    glBindTexture(GL_TEXTURE_2D, texture->tex);
    glTexImage2D(GL_TEXTURE_2D, 0, openglTextureInternalFormat(internal_format), width, height, 0, openglTextureFormat(format), GL_UNSIGNED_BYTE, (void*)pixels);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    return 1;
}

void openglDestroyTexture(TextureHandle *handle) 
{
    glDeleteTextures(1, &texture->tex);
}



