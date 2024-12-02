#ifndef SGFX_H
#define SGFX_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define SFGX_INVALID_HANDLE (-1)

#define SGFX_MAX_VERTEX_BUFFERS 100
#define SGFX_MAX_INDEX_BUFFERS 100
#define SGFX_MAX_PROGRAMS 100
#define SGFX_MAX_TEXTURES 100

#define SGFX_HANDLE(TYPE) \
    typedef struct { \
        uint16_t idx; \
    } TYPE##Handle ; \

#define SGFX_ASSERT_HANDLE_IS_VALID(HANDLE) \
    do { \
        if( (HANDLE).idx != SGFX_INVALID_HANDLE) { \
            fprintf(stderr, "Error: sgfx handle is not valid. \r\n file: %s \r\n line: %d", __FILE__, __LINE__); \
        } \
    } while (false) \



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

int sfgxCreateVertexBuffer(void *data, size_t byte_size, VertexBufferHandle *handle);
void sfgxDestroyVertexBuffer(VertexBufferHandle *handle);

int sfgxCreateIndexBuffer(void *data, size_t byte_size, IndexBufferHandle *handle);
void sfgxDestroyIndexBuffer(IndexBufferHandle *handle);

int sfgxCreateProgram(const char *fs_code, const char *vs_code, ProgramHandle *handle);
void sfgxDestroyProgram(ProgramHandle *handle);

int sfgxCreateTexture(const unsigned char *pixels, size_t width, size_t height, TextureFormat format, TextureInternalFormat internal_format, size_t mip_map_count, TextureHandle *handle);
void sfgxDestroyTexture(TextureHandle *handle);


#endif /** SGFX_H */