cmake_minimum_required(VERSION 3.31)
project(DS_Core C)

set(CMAKE_C_STANDARD 23)

file(GLOB_RECURSE MYLIB_SRC CONFIGURE_DEPENDS src/*.c)
add_library(mylib STATIC ${MYLIB_SRC})

# lib output
target_include_directories(mylib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ds_core
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/src
)

option(MYLIB_ENABLE_TESTS "Enable internal tests for mylib" ON)
if(MYLIB_ENABLE_TESTS)
    enable_testing()

    file(GLOB_RECURSE MYLIB_TEST_SRC CONFIGURE_DEPENDS tests/*.c)

    foreach(test_file ${MYLIB_TEST_SRC})
        get_filename_component(test_name ${test_file} NAME_WE)

        add_executable(${test_name} ${test_file})

        target_link_libraries(${test_name} PRIVATE mylib)

        target_include_directories(${test_name} PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}/include
                ${CMAKE_CURRENT_SOURCE_DIR}/internal
        )

        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()
endif()