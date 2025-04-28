cmake_minimum_required(VERSION 3.10.0)
project(mage VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXE_LINKER_FLAGS "-lglfw -lm")

set(SOURCE_FILES 
    ./glad/glad.c
    lib/loadShader.cpp
    lib/vec.cpp
    lib/particle.cpp
    lib/simpleArray.cpp
)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(00_dot ${SOURCE_FILES} 
    src/00_dot/00_dot.cpp)

add_executable(01_triangle ${SOURCE_FILES} 
    src/01_triangle/01_triangle.cpp)  

add_executable(02_cube ${SOURCE_FILES} 
    src/02_cube/02_cube.cpp) 

add_executable(03_texTriangle ${SOURCE_FILES} 
    src/03_texTriangle/03_texTriangle.cpp) 

add_executable(04_rdot ${SOURCE_FILES} 
    src/04_rdot/04_rdot.cpp)

target_link_libraries(00_dot glm::glm)
target_link_libraries(01_triangle glm::glm)
target_link_libraries(02_cube glm::glm)
target_link_libraries(03_texTriangle glm::glm)
target_link_libraries(04_rdot glm::glm)