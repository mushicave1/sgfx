set(SFGFX_TEST_SOURCES
    test.c
    test_array_list.c
)

# Conditionally add test_opengl.c if USE_GLFW is set
if(USE_GLFW)
    add_definitions(-DUSE_GLFW)
    list(APPEND SFGFX_TEST_SOURCES test_opengl.c)
endif()

add_executable(sgfx_test ${SFGFX_TEST_SOURCES})

target_link_libraries(sgfx_test PRIVATE sgfx)

target_include_directories(sgfx_test
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/extern/glad/include
    ${CMAKE_SOURCE_DIR}/extern/glfw/3.4/include
)



