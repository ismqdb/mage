cmake_minimum_required(VERSION 3.5.0)
project(mage VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXE_LINKER_FLAGS "-lglfw -lm")

set(SOURCE_FILES 
    ./glad/glad.c
    lib/loadShader.cpp
)

find_package(glm REQUIRED)

add_executable(00_dot ${SOURCE_FILES} 
    src/00_dot/00_dot.cpp)

target_compile_options(00_dot PRIVATE 
    -O0
    -g
    #-Wall 
    #-Werror 
    #-pedantic 
    -std=c++20
)

target_link_libraries(00_dot glm::glm)
