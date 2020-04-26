#include "mob.h"

#include "cglm/cglm.h"

#include "global.h"
#include "world.h"
#include "cube.h"
#include "math.h"

float dotProduct(float v1[2], float v2[2]){
    float dot = v1[0] * v2[0] + v1[1] * v2[1];
    return dot;
}

float getIpotenusa(float vec[2]){
    float ipotenusa = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
    return ipotenusa;
}

void normalizeVec2(float vec[2]){
    float ipotenusa = sqrt(vec[0] * vec[0] + vec[1] * vec[1]);
    vec[0] = vec[0] / ipotenusa;
    vec[1] = vec[1] / ipotenusa;
}

void drawZombie(Program *program, Texture *textures, Mob *zombie){
    bindTexture(textures, 1);
    vec3 posMob = {zombie->x, zombie->y, zombie->z};
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, posMob);
    vec3 rotateAxis = {0, 1, 0};
    normalizeVec2(zombie->dir);
    float piano[2] = {0, 1};
    float angle = acos(dotProduct(piano, zombie->dir));
    if (zombie->dir[0] < 0){
        angle = -angle;
    }
    glm_rotate(model, angle, rotateAxis);
    setShaderUniformMat4f(program->shader, "u_Model", &model);

    float verticiZombie[] = ZOMBIE_TEXTURE;
    sendDataVertexBuffer(program->vb, verticiZombie, SIZE_FACCIA * FACCE_ZOMBIE, true);
    GLCall(glDrawElements(GL_TRIANGLES, 6 * FACCE_ZOMBIE, GL_UNSIGNED_INT, NULL));
}

void drawSlime(Program *program, BlockTexture *blockTextures, Slime *slime){
    bindBlockTexture(blockTextures, TEX_SLIME);
    vec3 posMob = {slime->x, slime->y, slime->z};
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, posMob);
    vec3 rotateAxis = {1, 0, 0};
    glm_rotate(model, glm_rad(90), rotateAxis);
    setShaderUniformMat4f(program->shader, "u_Model", &model);
    float vertici[] = CUBO_TEXTURE;
    sendDataVertexBuffer(program->vb, vertici, SIZE_CUBO, true);
    GLCall(glDrawElements(GL_TRIANGLES, SIZE_INDICI_CUBO / sizeof(unsigned int), GL_UNSIGNED_INT, NULL));
}

void drawAcquaSopra(Program *program, Texture *waterTex, int x, int y, int z){
    bindTexture(waterTex, 1);
    vec3 posAcqua = {x, y, z};
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, posAcqua);
    setShaderUniformMat4f(program->shader, "u_Model", &model);
    float vertici[] = ACQUA_FACCIA_SOPRA;
    sendDataVertexBuffer(program->vb, vertici, SIZE_FACCIA, true);
    GLCall(glDrawElements(GL_TRIANGLES, SIZE_INDICI_QUADRATO / sizeof(unsigned int), GL_UNSIGNED_INT, NULL));
}

void drawAcqua(Program *program, World *world, Texture *waterTex, int x, int y, int z){
    if (checkEsisteBlocco(world, x, y, z)){
        printf("ATTENZIONE: non puoi mettere acqua qui\n");
    } else{
        bindTexture(waterTex, 1);
        vec3 posAcqua = {x, y, z};
        mat4 model;
        glm_mat4_identity(model);
        glm_translate(model, posAcqua);
        setShaderUniformMat4f(program->shader, "u_Model", &model);
        float vertici[] = ACQUA_CUBO;
        sendDataVertexBuffer(program->vb, vertici, SIZE_CUBO, true);
        GLCall(glDrawElements(GL_TRIANGLES, SIZE_INDICI_CUBO / sizeof(unsigned int), GL_UNSIGNED_INT, NULL));
    }
}
