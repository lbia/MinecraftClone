cmake_minimum_required(VERSION 3.12)

project(Minecraft CXX C)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} src/main.c src/camera.c src/cube.c src/gameState.c src/global.c src/mob.c src/renderer.c src/window.c src/world.c src/engine/indexBuffer.c src/engine/program.c src/engine/shader.c src/engine/texture.c src/engine/utils.c src/engine/vertexArray.c src/engine/vertexBuffer.c src/noise/perlin.c src/dep/stb_image.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/engine ${CMAKE_CURRENT_SOURCE_DIR}/src/dep ${CMAKE_CURRENT_SOURCE_DIR}/src/noise)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glew)

target_link_libraries(${PROJECT_NAME} PUBLIC m Threads::Threads libglew_static glfw)

# copy resources files to build directory
add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/res)

