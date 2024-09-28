cmake_minimum_required(VERSION 3.16)
project(
    Matrix
    VERSION 0.0.1
    DESCRIPTION "Matrix class"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

set(sources 
    # src/matrix.h
    src/matrix.cpp

    # src/export.h

    # src/c/c_api.h
    src/c/c_api.cpp
)

# Подключение модуля CMake, позволяющего применять макросы экспорта для 
# динамической библиотеки
include(GenerateExportHeader)

# Добавляет target: динамическая библиотека с названием shared-matrixlib
add_library(shared-matrixlib SHARED ${sources})

# Директории, в которых компилятор ищет h/hpp файлы
target_include_directories(shared-matrixlib
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

# Объявление переменной препроцессора (на случай, если эта же библиотека будет
# собираться как статическая. Это позволит дериктивами препроцессора #ifdef  
# выбрать другой h-файл с макросами экспорта, сгенерированный командой 
# generate_export_header)
# target_compile_definitions(
#     static-matrixlib
#     PUBLIC
#         MATH_STATIC_DEFINE
# )

# Префикс к генерируему файлу библиотеки по умолчанию "lib". Следующая команда
# заменяет префикс по умолчанию на "" (т. е. отсутствие префикса)
set_target_properties(shared-matrixlib PROPERTIES PREFIX "")


# Генерирует библиотеку с макросами экспорта с дериктивами препроцессора для 
# экспорта и импорта. С помощью этих макросов можно пометить функции как 
# экспортируемые, чтобы их можно было использовать в других проектах
generate_export_header(
    shared-matrixlib # target
    EXPORT_FILE_NAME "${CMAKE_SOURCE_DIR}/lib/export_shared.h"
    BASE_NAME matrixlib # префикс для названий генерируемых макросов
)

# Создает директорию lib и устанавливает в нее динамическую библиотеку, 
# экспортирующую функции для работы с матрицами (shared-matrixlib).
# Работает только если во вкладке расширения Cmake в параметре "build"->"set  
# build target" выбрать "install" вместо установленного по умолчанию "all"
install(TARGETS shared-matrixlib
    DESTINATION "${CMAKE_SOURCE_DIR}/lib"
)

# Добавляет проект с собственным файлом CMakeLists.txt, содержищий тесты 
# динамической библиотеки
add_subdirectory("${CMAKE_SOURCE_DIR}/exe")
