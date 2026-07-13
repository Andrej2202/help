cmake_minimum_required(VERSION 3.16)
project(MatrixProject LANGUAGES CXX)

# Устанавливаем стандарт C++20 (нужен для concepts)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Добавляем исполняемый файл
add_executable(matrix_test main.cpp)

# Указываем пути к заголовочным файлам
target_include_directories(matrix_test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/Array
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/List
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include/Sequence
)

# Опционально: включаем предупреждения компилятора
if(MSVC)
    target_compile_options(matrix_test PRIVATE /W4)
else()
    target_compile_options(matrix_test PRIVATE -Wall -Wextra -Wpedantic)
endif()