cmake_minimum_required(VERSION 3.12)

project(Minecraft VERSION 1.0)

add_executable(${PROJECT_NAME} main.c camera.c cube.c gameState.c global.c mob.c renderer.c window.c world.c engine/indexBuffer.c engine/program.c engine/shader.c engine/texture.c engine/utils.c engine/vertexArray.c engine/vertexBuffer.c noise/perlin.c dep/stb_image.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/engine ${CMAKE_CURRENT_SOURCE_DIR}/dep ${CMAKE_CURRENT_SOURCE_DIR}/noise)

find_package(OpenGL REQUIRED)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(GLEW REQUIRED)
find_package(Threads REQUIRED)

add_dependencies(${PROJECT_NAME} OpenGL::OpenGL OpenGL::GL GLEW::glew)

target_link_libraries(${PROJECT_NAME} m OpenGL::OpenGL OpenGL::GL GLEW::glew glfw Threads::Threads)