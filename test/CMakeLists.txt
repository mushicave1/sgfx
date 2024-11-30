set(SFGFX_TEST_SOURCES
    test.c
)

add_executable(sgfx_test ${SFGFX_TEST_SOURCES})

target_include_directories(sgfx_test
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)


