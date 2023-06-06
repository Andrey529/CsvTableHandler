project(Google_tests)

set(GOOGLE_TESTS_DIR ${CMAKE_SOURCE_DIR}/tests/googletest)
find_package(Git REQUIRED)
execute_process(
        COMMAND ${GIT_EXECUTABLE} submodule add https://github.com/google/googletest.git ${GOOGLE_TESTS_DIR}
)

add_subdirectory(${GOOGLE_TESTS_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'UnitTests.cpp' are source files with tests
add_executable(Google_Tests_run UnitTests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)