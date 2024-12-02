set(SGFX_SRC_SOURCES
    ${CMAKE_SOURCE_DIR}/extern/glad/src/glad.c
    sgfx.c
    array_list.c
    opengl.c
)

add_library(${PROJECT_NAME} ${SGFX_SRC_SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/extern/glad/include
    ${CMAKE_SOURCE_DIR}/extern/glfw/3.4/include
)
