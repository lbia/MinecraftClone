#include "renderer.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "global.h"
#include "cube.h"
#include "mob.h"

void clear(){
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

float getArea(int x1, int y1, int x2, int y2, int x3, int y3){
    float area = (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0f;
    if (area < 0){
        area = -area;
    }
    return area;
}

bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y){
    /* Calculate area of triangle ABC */
    float a = getArea(x1, y1, x2, y2, x3, y3);

    /* Calculate area of triangle PBC */
    float a1 = getArea(x, y, x2, y2, x3, y3);

    /* Calculate area of triangle PAC */
    float a2 = getArea(x1, y1, x, y, x3, y3);

    /* Calculate area of triangle PAB */
    float a3 = getArea(x1, y1, x2, y2, x, y);

    /* Check if sum of A1, A2 and A3 is same as A */
    float areaFine = a - a1 - a2 - a3;
    float acc = 0.05f;
    if (areaFine > -acc && areaFine < acc){
        return true;
    } else{
        return false;
    }
}

float *rotateVec2(float *vec, float angle){
    float *result = malloc(sizeof(float) * 2);
    float x = vec[0];
    float z = vec[1];
    result[0] = x * cos(angle) - z * sin(angle);
    result[1] = x * sin(angle) + z * cos(angle);
    return result;
}

void drawGui(Program *program, GameState *state){
    VertexBuffer *vb = program->vb;
    VertexArray *va = program->va;
    IndexBuffer *ib = program->ib;
    Shader *shader = program->shader;
    bindShader(shader);
    bindVertexArray(va);
    bindIndexBuffer(ib);

    mat4 model;
    glm_mat4_identity(model);
    setShaderUniformMat4f(shader, "u_Model", &model);
    bindTexture(state->mouseTexture, 0);
    float dataMouse[] = QUADRATO;
    sendDataVertexBuffer(vb, dataMouse, 6 * 4 * sizeof(float), true);
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));

    Texture *textureTop = &(state->blockTextures[state->textureSelezionata].side);
    float dataSlot[] = SLOT_QUADRATO;
    float dataSlotSelezionato[] = SLOT_SELEZIONATO;
    float dataSlotPiccolo[] = SMALL_QUADRATO;

    bindTexture(state->slotTexture, 0);
    sendDataVertexBuffer(vb, dataSlot, 6 * 4 * sizeof(float), true);

    for (int i = -4; i <= 4; i++){
        vec3 pos = {2 * SLOT_LATO * i, -16, 0};
        glm_mat4_identity(model);
        glm_translate(model, pos);
        setShaderUniformMat4f(shader, "u_Model", &model);

        if (i == -4){
            bindTexture(textureTop, 0);
            sendDataVertexBuffer(vb, dataSlotPiccolo, 6 * 4 * sizeof(float), true);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
            bindTexture(state->slotTexture, 0);
            sendDataVertexBuffer(vb, dataSlotSelezionato, 6 * 4 * sizeof(float), true);
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
            //sendDataVertexBuffer(vb, dataSlot, 6 * 4 * sizeof(float), true);
        } else{
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
        }
    }
}

//quello giusto
void drawWordlChunkView(Program *program, GameState *state){
    VertexBuffer *vb = program->vb;
    VertexArray *va = program->va;
    IndexBuffer *ib = program->ib;
    Shader *shader = program->shader;
    bindShader(shader);
    bindVertexArray(va);
    bindIndexBuffer(ib);

    mat4 model;
    glm_mat4_identity(model);
    setShaderUniformMat4f(shader, "u_Model", &model);

    sendDataIndexBuffer(ib, state->indici, state->maxSizeIndici, false);

    float frontY = state->player->camera->front[1];
    float cambioAngolo = 0.90f;
    if (frontY > -cambioAngolo){
        float importanzaFrontY = frontY *frontY * frontY * frontY;
        float *davanti = getCameraDavanti2d(state->player->camera);
        float rot = glm_rad(45);
        float mol = (VIEW_BLOCKS / cos(rot)) - 4 * CHUNK_SIZE * importanzaFrontY;
        float *sx = rotateVec2(davanti, rot);
        float *dx = rotateVec2(davanti, -rot);

        float quantoPiuIndietro = 8 * importanzaFrontY * CHUNK_SIZE;
        float x1 = state->player->camera->position[0] - quantoPiuIndietro * davanti[0];
        float y1 = state->player->camera->position[2] - quantoPiuIndietro * davanti[1];

        float x2 = x1 + sx[0] * mol;
        float y2 = y1 + sx[1] * mol;
        float x3 = x1 + dx[0] * mol;
        float y3 = y1 + dx[1] * mol;

        int quantiChunkLato = 1;

        for (int i = 0; i < NUMERO_TEXTURES; i++){
            bindBlockTexture(state->blockTextures, i);
            if (i == TEX_LEAVES){
                float colorLeaves[4] = {46 / CONVERTER_FROM_RGBA, 204 / CONVERTER_FROM_RGBA, 113 / CONVERTER_FROM_RGBA, 1};
                //setShaderUniformVec4(shader, "u_TexColor", colorLeaves);
            }
            for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
                for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
                    Chunk *chunk = state->chunks[getChunk(x, z)];
                    float xChunkS = chunk->x - HALF_CHUNK_SIZE;
                    float xChunkD = chunk->x + HALF_CHUNK_SIZE;
                    float zChunkS = chunk->z - HALF_CHUNK_SIZE;
                    float zChunkD = chunk->z + HALF_CHUNK_SIZE;
                    if (isInside(x1, y1, x2, y2, x3, y3, xChunkS, zChunkS) || isInside(x1, y1, x2, y2, x3, y3, xChunkS, zChunkD) ||
                        isInside(x1, y1, x2, y2, x3, y3, xChunkD, zChunkS) || isInside(x1, y1, x2, y2, x3, y3, xChunkD, zChunkD) ||
                        (x >= -quantiChunkLato && x <= quantiChunkLato && z >= -quantiChunkLato && z <= quantiChunkLato)){
                        DrawStruct *drawChunk = chunk->drawStruct;
                        if (drawChunk->sizeIndici[i] > 0){
                            sendDataVertexBuffer(vb, drawChunk->vertici[i], drawChunk->sizeVertici[i], true);
                            GLCall(glDrawElements(GL_TRIANGLES, drawChunk->sizeIndici[i] / sizeof(unsigned int), GL_UNSIGNED_INT, NULL));
                        }
                    }
                }
            }
            if (i == TEX_LEAVES){
                float colorBase[4] = {1, 1, 1, 1};
                //setShaderUniformVec4(shader, "u_TexColor", colorBase);
            }
        }
    } else{
        int quantiChunk = HALF_CHUNK_NUMBER / 1.75f;
        for (int i = 0; i < NUMERO_TEXTURES; i++){
            bindBlockTexture(state->blockTextures, i);
            if (i == TEX_LEAVES){
                float colorLeaves[4] = {46 / CONVERTER_FROM_RGBA, 204 / CONVERTER_FROM_RGBA, 113 / CONVERTER_FROM_RGBA, 1};
                //setShaderUniformVec4(shader, "u_TexColor", colorLeaves);
            }
            for (int x = -quantiChunk; x <= quantiChunk; x++){
                for (int z = -quantiChunk; z <= quantiChunk; z++){
                    DrawStruct *drawChunk = state->chunks[getChunk(x, z)]->drawStruct;
                    sendDataVertexBuffer(vb, drawChunk->vertici[i], drawChunk->sizeVertici[i], true);
                    GLCall(glDrawElements(GL_TRIANGLES, drawChunk->sizeIndici[i] / sizeof(unsigned int), GL_UNSIGNED_INT, NULL));
                }
            }
            if (i == TEX_LEAVES){
                float colorBase[4] = {1, 1, 1, 1};
                //setShaderUniformVec4(shader, "u_TexColor", colorBase);
            }
        }
    }
    drawZombie(program, state->mobTextures, state->zombie);
    //drawSlime(va, vb, ib, shader, state->blockTextures, state->slime);

    for (int x = -4; x <= -2; x++){
        for (int z = -1; z <= 1; z++){
            int y = getYMassima(state->world, x, z) + 1;
            int maxY = y + 10;
            for (; y < maxY; y++){
                //drawAcqua(program, state->world, state->waterTexture, x, y, z);
            }
        }
    }
    int xWater = -3;
    int zWater = 0;
    int yWater = getYMassima(state->world, xWater, zWater) + 1;
    //drawAcquaSopra(program, state->waterTexture, xWater, yWater, zWater);
}

void drawWordlChunk(VertexArray *va, VertexBuffer *vb, IndexBuffer *ib, Shader *shader, GameState *state){
    bindShader(shader);
    bindVertexArray(va);
    bindIndexBuffer(ib);

    sendDataIndexBuffer(ib, state->indici, state->maxSizeIndici, false);
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        bindBlockTexture(state->blockTextures, i);
        for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
            for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
                DrawStruct *drawChunk = state->chunks[getChunk(x, z)]->drawStruct;
                sendDataVertexBuffer(vb, drawChunk->vertici[i], drawChunk->sizeVertici[i], true);
                GLCall(glDrawElements(GL_TRIANGLES, drawChunk->sizeIndici[i], GL_UNSIGNED_INT, NULL));
            }
        }
    }
}
