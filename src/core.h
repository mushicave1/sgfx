#ifndef SGFX_CORE_H
#define SGFX_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SGFX_NULL_INDEX (-1)
#define SGFX_INVALID_HANDLE (-1)

#define SGFX_MAX_VERTEX_BUFFERS 100
#define SGFX_MAX_INDEX_BUFFERS 100
#define SGFX_MAX_VERTEX_INPUTS 100
#define SGFX_MAX_PROGRAMS 100
#define SGFX_MAX_TEXTURES 100

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


#define SGFX_ASSERT_HANDLE_IS_VALID(HANDLE) ((HANDLE).idx != SGFX_INVALID_HANDLE)



#endif
