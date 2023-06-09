project(Google_tests)

set(GOOGLE_TESTS_DIR ${CMAKE_SOURCE_DIR}/tests/googletest)

if(NOT EXISTS ${GOOGLE_TESTS_DIR}/googletest)
    find_package(Git REQUIRED)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} clone https://github.com/google/googletest.git ${GOOGLE_TESTS_DIR}
    )
endif()


add_subdirectory(${GOOGLE_TESTS_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'UnitTests.cpp' are source files with tests
add_executable(Google_Tests_run UnitTests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)