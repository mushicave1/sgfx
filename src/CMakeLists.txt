set(SGFX_SRC_SOURCES
    opengl.c
)

add_library(${PROJECT_NAME} ${SGFX_SRC_SOURCES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    {CMAKE_SOURCE_DIR}/src
)