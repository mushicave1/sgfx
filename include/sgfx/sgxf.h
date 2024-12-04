#ifndef SGFX_H
#define SGFX_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define SGFX_HANDLE(TYPE) \
    typedef struct { \
        uint16_t idx; \
    } TYPE##Handle ; \

SGFX_HANDLE(SGFXVertexBuffer);
SGFX_HANDLE(SGFXIndexBuffer);
SGFX_HANDLE(SGFXVertexInput);
SGFX_HANDLE(SGFXProgram);
SGFX_HANDLE(SGFXTexture);

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


typedef struct {
    uint32_t stride;
    uint32_t *offsets;
    uint32_t *element_counts;
    uint32_t len;
} SGFXBufferView;

const char* sgfxReadFile(const char* file_path);

int sgfxInit(GraphicsBackend backend);

SGFXVertexBufferHandle sgfxCreateVertexBuffer(void *data, size_t byte_size);
void sgfxDestroyVertexBuffer(SGFXVertexBufferHandle *handle);

SGFXIndexBufferHandle sgfxCreateIndexBuffer(void *data, size_t byte_size);
void sgfxDestroyIndexBuffer(SGFXIndexBufferHandle *handle);

SGFXVertexInputHandle sgfxCreateVertexInput(SGFXVertexBufferHandle vertex_buffer, SGFXBufferView buffer_view, SGFXIndexBufferHandle index_buffer);
void sgfxDestroyVertexInput(SGFXVertexInputHandle *handle);

SGFXProgramHandle sgfxCreateProgram(const char *vs_code, const char *fs_code);
void sgfxDestroyProgram(SGFXProgramHandle *handle);

SGFXTextureHandle sgfxCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count);
void sgfxDestroyTexture(SGFXTextureHandle *handle);


void sgfxDrawIndexed(size_t count, SGFXVertexInputHandle vertex_input, SGFXProgramHandle program);


#endif /** SGFX_H */