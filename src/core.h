#ifndef SGFX_CORE_H
#define SGFX_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SGFX_NULL_INDEX -1

#define SGFX_ASSERT(condition)                                             \
    do {                                                                    \
        if ( !(condition) ) {                                                 \
            fprintf(                                                        \
                stderr,                                                     \
                "Assertion Failed: %s\r\nFile: %s\r\nLine: %d\r\n",         \
                #condition,                                                 \
                __FILE__,                                                   \
                __LINE__                                                    \
            );                                                               \
        }                                                                   \
    } while (0)                                                             \

#endif



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