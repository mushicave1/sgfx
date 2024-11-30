set(SFGFX_TEST_SOURCES
    test.c
    test_array_list.c
)

add_executable(sgfx_test ${SFGFX_TEST_SOURCES})

target_link_libraries(sgfx_test PRIVATE sgfx)

target_include_directories(sgfx_test
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)


