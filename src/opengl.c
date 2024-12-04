#include "opengl.h"
#include "core.h"

typedef struct {
    GLVertexBuffer vertex_buffers[SGFX_MAX_VERTEX_BUFFERS];
    GLIndexBuffer index_buffers[SGFX_MAX_INDEX_BUFFERS];
    GLVertexInput vertex_inputs[SGFX_MAX_VERTEX_INPUTS];
    GLProgram programs[SGFX_MAX_PROGRAMS];
    GLTexture textures[SGFX_MAX_TEXTURES];
} OpenglContext;

OpenglContext s_ctx;

SGFXVertexBufferHandle openglCreateVertexBuffer(void *data, size_t byte_size) 
{ 
    static uint16_t counter = -1;
    counter++;
    GLVertexBuffer *buffer = &s_ctx.vertex_buffers[counter];
    glGenBuffers(1, &buffer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, buffer->vbo);
    glBufferData(GL_ARRAY_BUFFER, byte_size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    return (SGFXVertexBufferHandle){.idx = counter};
}

void openglDestroyVertexBuffer(SGFXVertexBufferHandle *handle) 
{
    GLVertexBuffer *buffer = &s_ctx.vertex_buffers[handle->idx];
    glDeleteBuffers(1, &buffer->vbo);
    handle->idx = SGFX_NULL_INDEX;
}

SGFXIndexBufferHandle openglCreateIndexBuffer(void *data, size_t byte_size) 
{
    static uint16_t counter = -1;
    counter++;
    GLIndexBuffer* buffer = &s_ctx.index_buffers[counter];
    glGenBuffers(1, &buffer->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);

    return (SGFXIndexBufferHandle){.idx = counter};
}

void openglDestroyIndexBuffer(SGFXIndexBufferHandle *handle) 
{
    GLIndexBuffer *buffer = &s_ctx.index_buffers[handle->idx];
    glDeleteBuffers(1, &buffer->ebo);
    handle->idx = SGFX_NULL_INDEX;
}

SGFXVertexInputHandle openglCreateVertexInput(SGFXVertexBufferHandle vertex_buffer, SGFXBufferView buffer_view, SGFXIndexBufferHandle index_buffer) 
{
    static uint16_t counter = -1;
    counter++;
    GLVertexInput *vao = &s_ctx.vertex_inputs[counter];

    GLVertexBuffer *vbo = &s_ctx.vertex_buffers[vertex_buffer.idx];

    GLIndexBuffer *ebo = &s_ctx.index_buffers[index_buffer.idx];
    glGenVertexArrays(1, &vao->vao);
    glBindVertexArray(vao->vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->vbo);

    if(SGFX_ASSERT_HANDLE_IS_VALID(index_buffer)) {
        GLIndexBuffer *ebo = &s_ctx.index_buffers[index_buffer.idx];
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->ebo);
    }

    for(size_t i = 0; i < buffer_view.len; i++) 
    {
        glVertexAttribPointer(i, buffer_view.element_counts[i], GL_FLOAT, GL_FALSE, buffer_view.stride, (void*)(buffer_view.offsets[i]));
        glEnableVertexAttribArray(i);
    }    

    glBindVertexArray(GL_NONE);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);

    return (SGFXVertexInputHandle){.idx = counter};
}

void openglDestroyVertexInput(SGFXVertexInputHandle *handle) 
{
    GLVertexInput *vertex_input = &s_ctx.vertex_inputs[handle->idx];
    glDeleteVertexArrays(1, &vertex_input->vao);
    handle->idx = SGFX_NULL_INDEX; 
}


SGFXProgramHandle openglCreateProgram(const char *vs_code, const char *fs_code) 
{
    static uint16_t counter = -1;
    counter++;
    GLProgram* program = &s_ctx.programs[counter];
    const GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &vs_code, NULL);
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
    glShaderSource(f_shader, 1, &fs_code, NULL);
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
    
    return (SGFXProgramHandle){.idx = counter};
}

void openglDestroyProgram(SGFXProgramHandle *handle) 
{
    GLProgram *program = &s_ctx.programs[handle->idx];
    glDeleteProgram(program->program);
    handle->idx = SGFX_NULL_INDEX;
}

SGFXTextureHandle openglCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count) 
{   
    static uint16_t counter = -1;
    counter++;
    GLTexture* texture = &s_ctx.textures[counter];
    glGenTextures(1, &texture->tex);
    glBindTexture(GL_TEXTURE_2D, texture->tex);
    glTexImage2D(GL_TEXTURE_2D, 0, openglTextureInternalFormat(internal_format), width, height, 0, openglTextureFormat(format), GL_UNSIGNED_BYTE, (void*)pixels);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
    
    return (SGFXTextureHandle){.idx = counter};
}

void openglDestroyTexture(SGFXTextureHandle *handle) 
{
    GLTexture *texture = &s_ctx.textures[handle->idx];
    glDeleteTextures(1, &texture->tex);
    handle->idx = SGFX_NULL_INDEX;
}



void openglDrawIndexed(size_t count, SGFXVertexInputHandle vertex_input, SGFXProgramHandle program) 
{
    GLProgram* p = &s_ctx.programs[program.idx];
    GLVertexInput *input = &s_ctx.vertex_inputs[vertex_input.idx];

    glBindVertexArray(input->vao);
    glUseProgram(p->program);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}
