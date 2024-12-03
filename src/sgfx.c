#include <sgfx/sgxf.h>

#include <stdio.h>
#include <stdlib.h>

extern VertexBufferHandle openglCreateVertexBuffer(void *data, size_t byte_size);
extern void openglDestroyVertexBuffer(VertexBufferHandle *handle);

extern IndexBufferHandle openglCreateIndexBuffer(void *data, size_t byte_size);
extern void openglDestroyIndexBuffer(IndexBufferHandle *handle);

extern ProgramHandle openglCreateProgram(const char *fs_code, const char *vs_code);
extern void openglDestroyProgram(ProgramHandle *handle);

extern TextureHandle openglCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count);
extern void openglDestroyTexture(TextureHandle *handle);

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
    VertexBufferHandle (*createVertexBuffer)(void *data, size_t byte_size);
    void (*destroyVertexBuffer)(VertexBufferHandle *handle);

    IndexBufferHandle (*createIndexBuffer)(void *data, size_t byte_size);
    void (*destroyIndexBuffer)(IndexBufferHandle *handle);

    ProgramHandle (*createProgram)(const char *fs_code, const char *vs_code);
    void (*destroyProgram)(ProgramHandle *handle);

    TextureHandle (*createTexture)(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count);
    void (*destroyTexture)(TextureHandle *handle);
} Context;

static Context s_context;

int sfgxInit(GraphicsBackend backend) 
{
    switch (backend) {
        case Opengl: 
            s_context.createVertexBuffer = openglCreateVertexBuffer;
            s_context.destroyVertexBuffer = openglDestroyVertexBuffer;
            s_context.createIndexBuffer = openglCreateIndexBuffer;
            s_context.destroyIndexBuffer = openglDestroyIndexBuffer;
            s_context.createProgram = openglCreateProgram;
            s_context.destroyProgram = openglDestroyProgram;
            s_context.createTexture = openglCreateTexture;
            s_context.destroyTexture = openglDestroyTexture;
        case Vulkan:
            /** Unimplemented */
            break;
    }
}


VertexBufferHandle sfgxCreateVertexBuffer(void *data, size_t byte_size) 
{
    return s_context.createVertexBuffer(data, byte_size);
}

void sfgxDestroyVertexBuffer(VertexBufferHandle *handle) 
{
    return s_context.destroyVertexBuffer(handle);
}

IndexBufferHandle sfgxCreateIndexBuffer(void *data, size_t byte_size) 
{
    return s_context.createIndexBuffer(data, byte_size);
}

void sfgxDestroyIndexBuffer(IndexBufferHandle *handle) 
{
    return s_context.destroyIndexBuffer(handle);
}


ProgramHandle sfgxCreateProgram(const char *fs_code, const char *vs_code) 
{
    return s_context.createProgram(fs_code, vs_code);
}

void sfgxDestroyProgram(ProgramHandle *handle) 
{
    return s_context.destroyProgram(handle);
}  


TextureHandle sfgxCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count) 
{
    return s_context.createTexture(pixels, width, height, format, internal_format, mip_map_count);
}

void sfgxDestroyTexture(TextureHandle *handle) 
{
    return s_context.destroyTexture(handle);
}


