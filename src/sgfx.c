#include <sgfx/sgxf.h>

#include <stdio.h>
#include <stdlib.h>

extern SGFXVertexBufferHandle openglCreateVertexBuffer(void *data, size_t byte_size);
extern void openglDestroyVertexBuffer(SGFXVertexBufferHandle *handle);

extern SGFXIndexBufferHandle openglCreateIndexBuffer(void *data, size_t byte_size);
extern void openglDestroyIndexBuffer(SGFXIndexBufferHandle *handle);

extern SGFXVertexInputHandle openglCreateVertexInput(SGFXVertexBufferHandle vertex_buffer, SGFXBufferView buffer_view, SGFXIndexBufferHandle index_buffer);
extern void openglDestroyVertexInput(SGFXVertexInputHandle *handle);

extern SGFXProgramHandle openglCreateProgram(const char *vs_code, const char *vf_code);
extern void openglDestroyProgram(SGFXProgramHandle *handle);

extern SGFXTextureHandle openglCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count);
extern void openglDestroyTexture(SGFXTextureHandle *handle);


extern void openglDrawIndexed(size_t count, SGFXVertexInputHandle vertex_input, SGFXProgramHandle program);

const char* sgfxReadFile(const char* file_path) 
{
    FILE *file = fopen(file_path, "r");
    if(file == NULL) {
        perror("Failed to read file.");
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* source = (char*)malloc((file_size + 1) * sizeof(char));
    if(source == NULL) {
        perror("Error allocating memory.");
        fclose(file);
    }

    fread(source, 1, file_size, file);
    source[file_size] = '\0';

    fclose(file);
    return source;
}


typedef struct {
    SGFXVertexBufferHandle (*createVertexBuffer)(void *data, size_t byte_size);
    void (*destroyVertexBuffer)(SGFXVertexBufferHandle *handle);

    SGFXIndexBufferHandle (*createIndexBuffer)(void *data, size_t byte_size);
    void (*destroyIndexBuffer)(SGFXIndexBufferHandle *handle);

    SGFXVertexInputHandle (*createVertexInput)(SGFXVertexBufferHandle vertex_buffer, SGFXBufferView buffer_view, SGFXIndexBufferHandle index_buffer);
    void (*destroyVertexInput)(SGFXVertexInputHandle *handle);

    SGFXProgramHandle (*createProgram)(const char *vs_code, const char *fs_code);
    void (*destroyProgram)(SGFXProgramHandle *handle);

    SGFXTextureHandle (*createTexture)(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count);
    void (*destroyTexture)(SGFXTextureHandle *handle);

    void (*drawIndexed)(size_t count, SGFXVertexInputHandle vertex_input, SGFXProgramHandle program);
} Context;

static Context s_context;

int sgfxInit(GraphicsBackend backend) 
{
    switch (backend) {
        case Opengl: 
            s_context.createVertexBuffer = openglCreateVertexBuffer;
            s_context.destroyVertexBuffer = openglDestroyVertexBuffer;
            s_context.createIndexBuffer = openglCreateIndexBuffer;
            s_context.destroyIndexBuffer = openglDestroyIndexBuffer;
            s_context.createVertexInput = openglCreateVertexInput;
            s_context.destroyVertexInput = openglDestroyVertexInput;
            s_context.createProgram = openglCreateProgram;
            s_context.destroyProgram = openglDestroyProgram;
            s_context.createTexture = openglCreateTexture;
            s_context.destroyTexture = openglDestroyTexture;

            s_context.drawIndexed = openglDrawIndexed;
        case Vulkan:
            /** Unimplemented */
            break;
    }
}


SGFXVertexBufferHandle sgfxCreateVertexBuffer(void *data, size_t byte_size) 
{
    return s_context.createVertexBuffer(data, byte_size);
}

void sgfxDestroyVertexBuffer(SGFXVertexBufferHandle *handle) 
{
    return s_context.destroyVertexBuffer(handle);
}

SGFXIndexBufferHandle sgfxCreateIndexBuffer(void *data, size_t byte_size) 
{
    return s_context.createIndexBuffer(data, byte_size);
}

void sgfxDestroyIndexBuffer(SGFXIndexBufferHandle *handle) 
{
    return s_context.destroyIndexBuffer(handle);
}

SGFXVertexInputHandle sgfxCreateVertexInput(SGFXVertexBufferHandle vertex_buffer, SGFXBufferView buffer_view, SGFXIndexBufferHandle index_buffer) 
{
    return s_context.createVertexInput(vertex_buffer, buffer_view, index_buffer);
}

void sgfxDestroyVertexInput(SGFXVertexInputHandle *handle) 
{
    return s_context.destroyVertexInput(handle);
}


SGFXProgramHandle sgfxCreateProgram(const char *fs_code, const char *vs_code) 
{
    return s_context.createProgram(fs_code, vs_code);
}

void sgfxDestroyProgram(SGFXProgramHandle *handle) 
{
    return s_context.destroyProgram(handle);
}  


SGFXTextureHandle sgfxCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count) 
{
    return s_context.createTexture(pixels, width, height, format, internal_format, mip_map_count);
}

void sgfxDestroyTexture(SGFXTextureHandle *handle) 
{
    return s_context.destroyTexture(handle);
}



void sgfxDrawIndexed(size_t count, SGFXVertexInputHandle vertex_input, SGFXProgramHandle program) 
{
        return s_context.drawIndexed(count, vertex_input, program);
}
