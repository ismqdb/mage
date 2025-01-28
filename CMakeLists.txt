cmake_minimum_required(VERSION 3.5.0)
project(mage VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXE_LINKER_FLAGS "-lglfw -lm")

set(SOURCE_FILES 
    ./glad/glad.c
    lib/init.cpp
    lib/loadShader.cpp
)

find_package(glm REQUIRED)

add_executable(00_dot ${SOURCE_FILES} src/00_dot/00_dot.cpp src/00_dot/00_dotSetup.cpp)
add_executable(01_triangles ${SOURCE_FILES} src/01_triangles/01_triangles.cpp src/01_triangles/01_trianglesSetup.cpp)
add_executable(02_cube ${SOURCE_FILES} src/02_cube/02_cube.cpp src/02_cube/02_cubeSetup.cpp)
add_executable(03_star ${SOURCE_FILES} src/03_star/03_star.cpp src/03_star/03_starSetup.cpp)
add_executable(04_filledStar ${SOURCE_FILES} src/04_filledStar/04_filledStar.cpp src/04_filledStar/04_filledStarSetup.cpp)

target_link_libraries(00_dot glm::glm)
target_link_libraries(01_triangles glm::glm)
target_link_libraries(02_cube glm::glm)
target_link_libraries(03_star glm::glm)
target_link_libraries(04_filledStar glm::glm)