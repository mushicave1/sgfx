set(SGFX_EXAMPLE_SOURCES
    demo_opengl.c
)

add_executable(sgfx_examples ${SGFX_EXAMPLE_SOURCES})

target_link_libraries(sgfx_examples PRIVATE sgfx)

target_include_directories(sgfx_examples
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/include/sgfx
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/extern/glad/include
    ${CMAKE_SOURCE_DIR}/extern/glfw/3.4/include
)