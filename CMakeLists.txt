cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(Minecraft CXX C)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

find_package(GLEW REQUIRED)

find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.c src/camera.c src/camera.h src/cube.c src/cube.h src/gameState.c src/gameState.h src/global.c src/global.h
    src/mob.c src/mob.h src/renderer.c src/renderer.h src/window.c src/window.h src/world.c src/world.h
    src/engine/indexBuffer.c src/engine/indexBuffer.h src/engine/program.c src/engine/program.h src/engine/shader.c src/engine/shader.h
    src/engine/texture.c src/engine/texture.h src/engine/utils.c src/engine/utils.h src/engine/vertexArray.c src/engine/vertexArray.h
    src/engine/vertexBuffer.c src/engine/vertexBuffer.h src/noise/perlin.c src/noise/perlin.h src/dep/stb_image.c src/dep/stb_image.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src/engine ${CMAKE_CURRENT_SOURCE_DIR}/src/dep ${CMAKE_CURRENT_SOURCE_DIR}/src/noise)

target_link_libraries(${PROJECT_NAME} PUBLIC m Threads::Threads OpenGL GLEW glfw)

# copy resources files to build directory
add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/res)

