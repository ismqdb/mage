cmake_minimum_required(VERSION 3.5.0)
project(mage VERSION 0.1.0 LANGUAGES C)

set(CMAKE_EXE_LINKER_FLAGS "-lglfw -lm")

set(SOURCE_FILES 
    ./glad/glad.c
    lib/loadShader.c
)

add_executable(00_dot ${SOURCE_FILES} src/00_dot/00_dot.c src/00_dot/00_dotSetup.c src/00_dot/00_dotInit.c)
add_executable(01_triangles ${SOURCE_FILES} src/01_triangles/01_triangles.c src/01_triangles/01_trianglesSetup.c src/01_triangles/01_trianglesInit.c)
add_executable(02_cube ${SOURCE_FILES} src/02_cube/02_cube.c src/02_cube/02_cubeSetup.c src/02_cube/02_cubeInit.c)
add_executable(03_star ${SOURCE_FILES} src/03_star/03_star.c src/03_star/03_starSetup.c src/03_star/03_starInit.c)
add_executable(04_filledStar ${SOURCE_FILES} src/04_filledStar/04_filledStar.c src/04_filledStar/04_filledStarSetup.c src/04_filledStar/04_filledStarInit.c)
add_executable(05_moving ${SOURCE_FILES} src/05_moving/05_moving.c src/05_moving/05_movingSetup.c src/05_moving/05_movingInit.c)