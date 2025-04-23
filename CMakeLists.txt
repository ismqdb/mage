cmake_minimum_required(VERSION 3.5.0)
project(mage VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXE_LINKER_FLAGS "-lglfw -lm")

set(SOURCE_FILES 
    ./glad/glad.c
    lib/loadShader.cpp
    lib/vec.cpp
    lib/color.cpp
    lib/point.cpp
)

find_package(glm REQUIRED)

add_executable(00_dot ${SOURCE_FILES} 
    src/00_dot/00_dot.cpp)

add_executable(01_triangle ${SOURCE_FILES} 
    src/01_triangle/01_triangle.cpp)  

add_executable(02_cube ${SOURCE_FILES} 
    src/02_cube/02_cube.cpp) 

add_executable(03_texTriangle ${SOURCE_FILES} 
    src/03_texTriangle/03_texTriangle.cpp) 

target_link_libraries(00_dot glm::glm)
target_link_libraries(01_triangle glm::glm)
target_link_libraries(02_cube glm::glm)
target_link_libraries(03_texTriangle glm::glm)