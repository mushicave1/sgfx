#include <sgfx/sgxf.h>

#include <stdio.h>
#include <stdlib.h>


extern int openglCreateVertexBuffer(void *data, size_t byte_size, VertexBufferHandle *handle);
extern void openglDestroyVertexBuffer(VertexBufferHandle *handle);

extern int openglCreateIndexBuffer(void *data, size_t byte_size, IndexBufferHandle *handle);
extern void openglDestroyIndexBuffer(IndexBufferHandle *handle);

extern int openglCreateProgram(const char *fs_code, const char *vs_code, ProgramHandle *handle);
extern void openglDestroyProgram(ProgramHandle *handle);

extern int openglCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count, TextureHandle *handle);
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
    int (*createVertexBuffer)(void *data, size_t byte_size, VertexBufferHandle *handle);
    void (*destroyVertexBuffer)(VertexBufferHandle *handle);

    int (*createIndexBuffer)(void *data, size_t byte_size, IndexBufferHandle *handle);
    void (*destroyIndexBuffer)(IndexBufferHandle *handle);

    int (*createProgram)(const char *fs_code, const char *vs_code, ProgramHandle *handle);
    void (*destroyProgram)(ProgramHandle *handle);

    int (*createTexture)(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count, TextureHandle *handle);
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


int sfgxCreateVertexBuffer(void *data, size_t byte_size, VertexBufferHandle *handle) 
{
    return s_context.createVertexBuffer(data, byte_size, handle);
}

void sfgxDestroyVertexBuffer(VertexBufferHandle *handle) 
{
    return s_context.destroyVertexBuffer(handle);
}

int sfgxCreateIndexBuffer(void *data, size_t byte_size, IndexBufferHandle *handle) 
{
    return s_context.createIndexBuffer(data, byte_size, handle);
}

void sfgxDestroyIndexBuffer(IndexBufferHandle *handle) 
{
    return s_context.destroyIndexBuffer(handle);
}


int sfgxCreateProgram(const char *fs_code, const char *vs_code, ProgramHandle *handle) 
{
    return s_context.createProgram(fs_code, vs_code, handle);
}

void sfgxDestroyProgram(ProgramHandle *handle) 
{
    return s_context.destroyProgram(handle);
}  


int sfgxCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count, TextureHandle *handle) 
{
    return s_context.createTexture(pixels, width, height, format, internal_format, mip_map_count, handle);
}

void sfgxDestroyTexture(TextureHandle *handle) 
{
    return s_context.destroyTexture(handle);
}


