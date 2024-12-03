#ifndef SGFX_H
#define SGFX_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define SGFX_HANDLE(TYPE) \
    typedef struct { \
        uint16_t idx; \
    } TYPE##Handle ; \

SGFX_HANDLE(VertexBuffer);
SGFX_HANDLE(IndexBuffer);
SGFX_HANDLE(Program);
SGFX_HANDLE(Texture);

typedef enum {
    Opengl,
    Vulkan
} GraphicsBackend;

typedef enum {
    R,
    Rg,
    Rgb,
    Rgba
} TextureFormat;

typedef enum {
    Rgb32,
    Rgb32f,
    Rgba32,
    Rgba32f
} TextureInternalFormat;


const char* sgfxReadFile(const char* file_path);


int sfgxInit(GraphicsBackend backend);

VertexBufferHandle sfgxCreateVertexBuffer(void *data, size_t byte_size);
void sfgxDestroyVertexBuffer(VertexBufferHandle *handle);

IndexBufferHandle sfgxCreateIndexBuffer(void *data, size_t byte_size);
void sfgxDestroyIndexBuffer(IndexBufferHandle *handle);

ProgramHandle sfgxCreateProgram(const char *fs_code, const char *vs_code);
void sfgxDestroyProgram(ProgramHandle *handle);

TextureHandle sfgxCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count);
void sfgxDestroyTexture(TextureHandle *handle);


#endif /** SGFX_H */