cmake_minimum_required(VERSION 3.16)
project(
    MatrixTest
    VERSION 0.0.1
    DESCRIPTION "Matrix class"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(
    test-shared-matrix
    src/test_shared_matrix.cpp
)

# Директории, в которых компилятор ищет h/hpp файлы
target_include_directories(test-shared-matrix
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

# Подключение динамической библиотеки
target_link_libraries(test-shared-matrix
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/matrixlib/shared-matrixlib.so")

