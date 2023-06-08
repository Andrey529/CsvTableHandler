cmake_minimum_required(VERSION 3.21)
project(CsvHandler)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp
        src/CsvTable/CsvTable.cpp src/CsvTable/CsvTable.h
        src/CsvTableCalculator/CsvTableCalculator.cpp src/CsvTableCalculator/CsvTableCalculator.h)
add_subdirectory(tests)