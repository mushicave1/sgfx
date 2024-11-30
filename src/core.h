#ifndef SGFX_CORE_H
#define SGFX_CORE_H

#include <stdio.h>

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