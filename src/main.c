#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "program.h"
#include "global.h"
#include "window.h"
#include "renderer.h"
#include "camera.h"
#include "gameState.h"
#include "cube.h"

#include "cglm/cglm.h"

int main(){

    GameState *state = malloc(sizeof(GameState));

    GLFWwindow* window;
    window = initializeWindow("Mine", state, true);

    float dataVertexBuffer[] = QUADRATO;

    unsigned int dataIndici[] = INDICES_QUADRATO;

    VertexArray vaGui;
    initializeVertexArray(&vaGui);

    VertexBuffer vbGui;
    initializeVertexBuffer(&vbGui);
    sendDataVertexBuffer(&vbGui, dataVertexBuffer, 6 * 4 * sizeof(float), true);

    VertexBufferLayout layoutGui;
    initializeVertexBufferLayout(&layoutGui);
    pushElementToVertexBufferLayout(&layoutGui, GL_FLOAT, 3, GL_FALSE);
    pushElementToVertexBufferLayout(&layoutGui, GL_FLOAT, 2, GL_FALSE);
    pushElementToVertexBufferLayout(&layoutGui, GL_FLOAT, 1, GL_FALSE);
    addBufferToVertexArray(&vaGui, &vbGui, &layoutGui);
    IndexBuffer ibGui;
    initializeIndexBuffer(&ibGui);
    sendDataIndexBuffer(&ibGui, dataIndici, SIZE_INDICI_QUADRATO, false);

    VertexArray va;
    initializeVertexArray(&va);

    VertexBuffer vb;
    initializeVertexBuffer(&vb);
    //sendDataVertexBuffer(&vb, cubo, 6 * 6 * 4 * sizeof(float), true);

    VertexBufferLayout layout;
    initializeVertexBufferLayout(&layout);
    pushElementToVertexBufferLayout(&layout, GL_FLOAT, 3, GL_FALSE);
    pushElementToVertexBufferLayout(&layout, GL_FLOAT, 2, GL_FALSE);
    pushElementToVertexBufferLayout(&layout, GL_FLOAT, 1, GL_FALSE);
    //normals
    pushElementToVertexBufferLayout(&layout, GL_FLOAT, 3, GL_FALSE);
    addBufferToVertexArray(&va, &vb, &layout);

    IndexBuffer ib;
    initializeIndexBuffer(&ib);
    //sendDataIndexBuffer(&ib, indicesCubo, SIZE_INDICI_CUBO, true);

    Shader shader;
    //initializeShaderOnePath(&shader, "res/shaders/basic.shader");
    initializeShaderTwoPaths(&shader, "res/shaders/blockVertex.shader", "res/shaders/blockFragment.shader");

    Shader shaderGui;
    initializeShaderTwoPaths(&shaderGui, "res/shaders/basicVertex.shader", "res/shaders/basicFragment.shader");

    Program worldProgram;
    Program guiProgram;
    guiProgram.vb = &vbGui;
    guiProgram.va = &vaGui;
    guiProgram.ib = &ibGui;
    guiProgram.shader = &shaderGui;

    worldProgram.vb = &vb;
    worldProgram.va = &va;
    worldProgram.ib = &ib;
    worldProgram.shader = &shader;

    mat4 proj, view, model;

    bindShader(&shader);
    setShaderUniform1i(&shader, "u_BlockTop", 0);
    setShaderUniform1i(&shader, "u_BlockSide", 1);
    setShaderUniform1i(&shader, "u_BlockBottom", 2);
    float colorBase[4] = {1, 1, 1, 1};
    //setShaderUniformVec4(&shader, "u_TexColor", colorBase);
    float lightBase[3] = {1, 1, 1};
    setShaderUniformVec3(&shader, "u_LightColor", lightBase);
    float lightPosition[3] = {0, 1000, 0};
    setShaderUniformVec3(&shader, "u_LightPosition", lightPosition);
    glm_perspective(glm_rad(50), (float)WIDTH/(float)HEIGHT, 0.1f, VIEW_BLOCKS * 2, proj);
    setShaderUniformMat4f(&shader, "u_Proj", &proj);
    glm_mat4_identity(model);
    setShaderUniformMat4f(&shader, "u_Model", &model);

    bindShader(&shaderGui);
    setShaderUniform1i(&shaderGui, "u_MouseBianco", 0);
    glm_ortho(-SCALA_ORTHO, SCALA_ORTHO, -SCALA_ORTHO, SCALA_ORTHO, -1, 1, proj);
    setShaderUniformMat4f(&shaderGui, "u_Proj", &proj);
    setShaderUniformMat4f(&shaderGui, "u_Model", &model);

    bindVertexArray(&va);
    bindIndexBuffer(&ib);

    initGameState(state);
    state->programWorld = &worldProgram;
    Player *player = state->player;

    float time = 0;
    float timeUpdate = 0;

    int frameRender = 0;
    int frameUpdate = 0;

    float delta = 0.0f;
    float previousFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window)){
        processInput(window);

        float currentFrame = glfwGetTime();
        delta = currentFrame - previousFrame;
        previousFrame = currentFrame;
        time += delta;
        frameRender++;
        if (time >= 1.0f){
            printf("%d\n", frameRender);
            //printf("%d\n", frameUpdate);
            time = 0;
            frameRender = 0;
            frameUpdate = 0;
        }
        timeUpdate += delta;
        //if (timeUpdate >= MAX_TIME_UPDATE){
        if (timeUpdate >= 0){
            timeUpdate = 0;
            frameUpdate++;
            state->deltaTime = currentFrame - state->lastFrame;
            state->lastFrame = currentFrame;
            updateGameState(state);
        }

        //updateGameState(state);

        clear();

        bindShader(&shader);
        getCameraViewMatrix(player->camera, player->shift, view);
        setShaderUniformMat4f(&shader, "u_View", &view);

        drawWordlChunkView(&worldProgram, state);
        //drawWordlChunk(&va, &vb, &ib, &shader, state);
        drawGui(&guiProgram, state);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    while(state->threadEsecuzione);

    destroyGameState(state);
    free(state);

    destroyVertexBuffer(&vb);
    destroyIndexBuffer(&ib);
    destroyVertexBufferLayout(&layout);
    destroyVertexArray(&va);

    destoyShader(&shader);
    destoyShader(&shaderGui);

    glfwTerminate();
    return 0;
}
