#include "world.h"

#include "math.h"
#include <pthread.h>

int getOccupati(int x, int z);

Chunk *allocateChunk(int x, int z){
    Chunk *chunk = malloc(sizeof(Chunk));
    chunk->x = x;
    chunk->z = z;
    chunk->drawStruct = malloc(sizeof(DrawStruct));
    DrawStruct *draw = chunk->drawStruct;
    draw->vertici = malloc(sizeof(float *) * NUMERO_TEXTURES);
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        draw->vertici[i] = malloc(sizeof(float));
    }
    initializeChunk(chunk);
    return chunk;
}

void initializeChunk(Chunk *chunk){
    DrawStruct *draw = chunk->drawStruct;
    float **vertici = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    unsigned int *sizeVertici = malloc(sizeof(unsigned int));
    unsigned int *sizeIndici = malloc(sizeof(unsigned int));
    float **vertSopraSotto = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    unsigned int *sizeVertSopraSotto = malloc(sizeof(unsigned int));
    float **vertDavanti = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    unsigned int *sizeVertDavanti = malloc(sizeof(unsigned int));
    float **vertDietro = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    unsigned int *sizeVertDietro = malloc(sizeof(unsigned int));
    float **vertSinistra = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    unsigned int *sizeVertSinistra = malloc(sizeof(unsigned int));
    float **vertDestra = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    unsigned int *sizeVertDestra = malloc(sizeof(unsigned int));

    for (int i = 0; i < NUMERO_TEXTURES; i++){
        vertici[i] = malloc(sizeof(float));
        vertSopraSotto[i] = malloc(sizeof(float));
        vertDavanti[i] = malloc(sizeof(float));
        vertDietro[i] = malloc(sizeof(float));
        vertSinistra[i] = malloc(sizeof(float));
        vertDestra[i] = malloc(sizeof(float));
    }

    draw->vertici = vertici;
    draw->sizeVertici = sizeVertici;
    draw->sizeIndici = sizeIndici;
    draw->verSopraSotto = vertSopraSotto;
    draw->sizeSopraSotto = sizeVertSopraSotto;
    draw->verDavanti = vertDavanti;
    draw->sizeDavanti = sizeVertDavanti;
    draw->verDietro = vertDietro;
    draw->sizeDietro = sizeVertDietro;
    draw->verSinistra = vertSinistra;
    draw->sizeSinistra = sizeVertSinistra;
    draw->verDestra = vertDestra;
    draw->sizeDestra = sizeVertDestra;
}

void freeChunk(Chunk *chunk){
    DrawStruct *draw = chunk->drawStruct;
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        free(draw->vertici[i]);
        free(draw->verSopraSotto[i]);
        free(draw->verDavanti[i]);
        free(draw->verDietro[i]);
        free(draw->verSinistra[i]);
        free(draw->verDestra[i]);
    }
    free(draw->vertici);
    free(draw->verSopraSotto);
    free(draw->verDavanti);
    free(draw->verDietro);
    free(draw->verSinistra);
    free(draw->verDestra);
    free(draw->sizeVertici);
    free(draw->sizeIndici);
    free(draw->sizeSopraSotto);
    free(draw->sizeDavanti);
    free(draw->sizeDietro);
    free(draw->sizeSinistra);
    free(draw->sizeDestra);

    free(draw);
}

int *getIndiceChunkDiPosizione(Chunk **chunks, int x, int z){
    int *indici = malloc(sizeof(int) * 2);
    int indiceChunkCen = getChunk(0, 0);
    int xChunkCen = chunks[indiceChunkCen]->x;
    int zChunkCen = chunks[indiceChunkCen]->z;

    indici[0] = (int)((float)(x - xChunkCen) / (HALF_CHUNK_SIZE + 1));
    indici[1] = (int)((float)(z - zChunkCen) / (HALF_CHUNK_SIZE + 1));

    return indici;
}

void translateFaccia(float faccia[FLOAT_FACCIA], int x, int y, int z){
    int offSet = FLOAT_FACCIA / 4;
    for (int i = 0; i < 4; i++){
        faccia[offSet * i + 0] += x;
        faccia[offSet * i + 1] += y;
        faccia[offSet * i + 2] += z;
    }
}

float *addFaccia(float *vertici, float faccia[FLOAT_FACCIA], int *quanteFacce){
    int s = *quanteFacce;
    float *verticiNuovi = realloc(vertici, sizeof(float) * FLOAT_FACCIA * (s + 1));
    for (int i = 0; i < FLOAT_FACCIA; i++){
        verticiNuovi[s * FLOAT_FACCIA + i] = faccia[i];
    }
    (*quanteFacce)++;
    return verticiNuovi;
}

float *addToVertici(float *ver, unsigned int *sizeVertici, float *add, unsigned int sizeAdd){
    unsigned int sizeVer = *sizeVertici;
    //printf("sopra size vertici %u size add % u\n", sizeVer, sizeAdd);
    //printf("p %p\n", ver);
    float *verticiNuovi = realloc(ver, sizeVer + sizeAdd);
    //printf("sotto size vertici %u size add % u\n", sizeVer, sizeAdd);
    int quantiVerAdd = sizeAdd / (sizeof(float));
    int posFineVer = sizeVer / (sizeof(float));
    for (int i = 0; i < quantiVerAdd; i++){
        verticiNuovi[posFineVer + i] = add[i];
    }
    //printf("sotto size vertici %u size add % u\n", sizeVer, sizeAdd);
    *sizeVertici += sizeAdd;
    return verticiNuovi;
}

void setChunkVertici(GameState *state, Chunk *chunk, int x, int z){
    World *world = state->world;
    DrawStruct *draw = chunk->drawStruct;

    float **vert = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    unsigned int *sizeVert = malloc(sizeof(unsigned int) * NUMERO_TEXTURES);
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        vert[i] = malloc(sizeof(float));
        sizeVert[i] = 0;
    }

    unsigned int *sizeIndi = malloc(sizeof(unsigned int) * NUMERO_TEXTURES);
    int maxSizeIndici = 0;
    int qualeTexMaxSizeIndici = -1;
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        vert[i] = addToVertici(vert[i], &(sizeVert[i]), draw->verSopraSotto[i], draw->sizeSopraSotto[i]);
        if ((x >= -1 && x <= 1) || (z >= -1 && z <= 1)){
            vert[i] = addToVertici(vert[i], &(sizeVert[i]), draw->verSinistra[i], draw->sizeSinistra[i]);
            vert[i] = addToVertici(vert[i], &(sizeVert[i]), draw->verDestra[i], draw->sizeDestra[i]);
            vert[i] = addToVertici(vert[i], &(sizeVert[i]), draw->verDietro[i], draw->sizeDietro[i]);
            vert[i] = addToVertici(vert[i], &(sizeVert[i]), draw->verDavanti[i], draw->sizeDavanti[i]);
        } else{
            if (x > 0){
                vert[i] = addToVertici(vert[i], &(sizeVert[i]), draw->verSinistra[i], draw->sizeSinistra[i]);
            } else if(x < 0){
                vert[i] = addToVertici(vert[i], &(sizeVert[i]), draw->verDestra[i], draw->sizeDestra[i]);
            }
            if (z > 0){
                vert[i] = addToVertici(vert[i], &(sizeVert[i]), draw->verDietro[i], draw->sizeDietro[i]);
            } else if(z < 0){
                vert[i] = addToVertici(vert[i], &(sizeVert[i]), draw->verDavanti[i], draw->sizeDavanti[i]);
            }
        }
        sizeIndi[i] = sizeVert[i] * sizeof(unsigned int) / (4 * sizeof(float));
        if (sizeIndi[i] > maxSizeIndici){
            maxSizeIndici = sizeIndi[i];
            qualeTexMaxSizeIndici = i;
        }
    }
    float **verVecchi = draw->vertici;
    unsigned int *sizeVerVecchi = draw->sizeVertici;
    unsigned int *sizeIndiciVecchi = draw->sizeIndici;
    draw->vertici = vert;
    draw->sizeVertici = sizeVert;
    draw->sizeIndici = sizeIndi;
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        free(verVecchi[i]);
    }
    free(verVecchi);
    free(sizeVerVecchi);
    free(sizeIndiciVecchi);
    if (maxSizeIndici > state->maxSizeIndici){
        unsigned int *indi = malloc(maxSizeIndici);
        for (int i = 0; i < sizeIndi[qualeTexMaxSizeIndici] / (6 * sizeof(unsigned int)); i++){
            indi[i * 6 + 0] = i * 4 + 0;
            indi[i * 6 + 1] = i * 4 + 1;
            indi[i * 6 + 2] = i * 4 + 2;
            indi[i * 6 + 3] = i * 4 + 2;
            indi[i * 6 + 4] = i * 4 + 3;
            indi[i * 6 + 5] = i * 4 + 0;
        }
        state->indici = indi;
        state->maxSizeIndici = maxSizeIndici;
    }
}

Cube *getCubePointerStessa(World *world, int x, int y, int z){
    Cube *cube = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)];
    return cube;
}

void setChunkFacce(GameState *state, Chunk *chunk, int x, int z){
    World *world = state->world;
    //Chunk *chunk = state->chunks[getChunk(x, z)];
    DrawStruct *draw = chunk->drawStruct;

    float **vertSopraSotto = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    int facceSopraSotto[NUMERO_TEXTURES];
    float **vertDavanti = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    int facceDavanti[NUMERO_TEXTURES];
    float **vertDietro = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    int facceDietro[NUMERO_TEXTURES];
    float **vertSinistra = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    int facceSinistra[NUMERO_TEXTURES];
    float **vertDestra = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    int facceDestra[NUMERO_TEXTURES];

    for (int i = 0; i < NUMERO_TEXTURES; i++){
        vertSopraSotto[i] = malloc(sizeof(float));
        facceSopraSotto[i] = 0;
        vertDavanti[i] = malloc(sizeof(float));
        facceDavanti[i] = 0;
        vertDietro[i] = malloc(sizeof(float));
        facceDietro[i] = 0;
        vertSinistra[i] = malloc(sizeof(float));
        facceSinistra[i] = 0;
        vertDestra[i] = malloc(sizeof(float));
        facceDestra[i] = 0;
    }

    //printf("inizio chunk x: %d chunk z %d\n", chunk->x, chunk->z);
    for (int x = chunk->x - HALF_CHUNK_SIZE; x <= chunk->x + HALF_CHUNK_SIZE; x++){
        for (int z = chunk->z - HALF_CHUNK_SIZE; z <= chunk->z + HALF_CHUNK_SIZE; z++){
            //printf("x: %d z: %d\n", x, z);
            if (checkConfineWorld(x, z)){
                continue;
            }
            //printf("x coord %d %d z coord %d %d\n", x, getCoordinataMondo(x), z, getCoordinataMondo(z));
            int indiceDaCoord = x - (getCoordinataMondo(x) * WORLD_SIZE) + HALF_WORLD_SIZE;
            //printf("x da coord %d\n", indiceDaCoord);
            int maxY = world->occupati[getIndiceMondo(x, z)][getOccupati(x, z)][0];
            for (int yo = maxY; yo >= 1; yo--){
                int y = world->occupati[getIndiceMondo(x, z)][getOccupati(x, z)][yo];
                Cube *c;
                getCubePointer(world, x, y, z, &c);
                unsigned char tex = c->tex;
                if (tex != TEX_WATER){
                    if (!checkEsisteBlocco(world, x, y + 1, z) || world->cubes[getIndiceMondo(x, z)][getCube(x, y + 1, z)]->tex == TEX_WATER){
                        float faccia[] = FACCIA_SOPRA;
                        translateFaccia(faccia, x, y, z);
                        if (tex == TEX_DIRT){
                            if (y > ALT_SNOW){
                                c->tex = TEX_SNOW;
                            } else{
                                c->tex = TEX_GRASS;
                            }
                        }
                        vertSopraSotto[tex] = addFaccia(vertSopraSotto[tex], faccia, &(facceSopraSotto[tex]));
                    } else{
                        if (tex == TEX_GRASS || tex == TEX_SNOW){
                            c->tex = TEX_DIRT;
                        }
                    }
                    if (y > 0 && (!checkEsisteBlocco(world, x, y - 1, z) || (y > 1 && world->cubes[getIndiceMondo(x, z)][getCube(x, y - 1, z)]->tex == TEX_WATER))){
                        float faccia[] = FACCIA_SOTTO;
                        translateFaccia(faccia, x, y, z);
                        vertSopraSotto[tex] = addFaccia(vertSopraSotto[tex], faccia, &(facceSopraSotto[tex]));
                    }
                    if (!checkEsisteBlocco(world, x, y, z + 1) || world->cubes[getIndiceMondo(x, z + 1)][getCube(x, y, z + 1)]->tex == TEX_WATER){
                        float faccia[] = FACCIA_DAVANTI;
                        translateFaccia(faccia, x, y, z);
                        vertDavanti[tex] = addFaccia(vertDavanti[tex], faccia, &(facceDavanti[tex]));
                    }
                    if (!checkEsisteBlocco(world, x, y, z - 1) || world->cubes[getIndiceMondo(x, z - 1)][getCube(x, y, z - 1)]->tex == TEX_WATER){
                        float faccia[] = FACCIA_DIETRO;
                        translateFaccia(faccia, x, y, z);
                        vertDietro[tex] = addFaccia(vertDietro[tex], faccia, &(facceDietro[tex]));
                    }
                    if (!checkEsisteBlocco(world, x - 1, y, z) || world->cubes[getIndiceMondo(x - 1, z)][getCube(x - 1, y, z)]->tex == TEX_WATER){
                        float faccia[] = FACCIA_SINISTRA;
                        translateFaccia(faccia, x, y, z);
                        vertSinistra[tex] = addFaccia(vertSinistra[tex], faccia, &(facceSinistra[tex]));
                    }
                    if (!checkEsisteBlocco(world, x + 1, y, z) || world->cubes[getIndiceMondo(x + 1, z)][getCube(x + 1, y, z)]->tex == TEX_WATER){
                        float faccia[] = FACCIA_DESTRA;
                        translateFaccia(faccia, x, y, z);
                        vertDestra[tex] = addFaccia(vertDestra[tex], faccia, &(facceDestra[tex]));
                    }
                } else{
                    if (!checkEsisteBlocco(world, x, y + 1, z) || world->cubes[getIndiceMondo(x, z)][getCube(x, y + 1, z)]->tex != TEX_WATER){
                        float faccia[] = ACQUA_FACCIA_SOPRA;
                        translateFaccia(faccia, x, y, z);
                        vertSopraSotto[tex] = addFaccia(vertSopraSotto[tex], faccia, &(facceSopraSotto[tex]));
                    }
                    if (y != 0 && !checkEsisteBlocco(world, x, y - 1, z)){
                        float faccia[] = ACQUA_FACCIA_SOTTO;
                        translateFaccia(faccia, x, y, z);
                        vertSopraSotto[tex] = addFaccia(vertSopraSotto[tex], faccia, &(facceSopraSotto[tex]));
                    }
                    if (!checkEsisteBlocco(world, x, y, z + 1)){
                        float faccia[] = ACQUA_FACCIA_DAVANTI;
                        translateFaccia(faccia, x, y, z);
                        vertDavanti[tex] = addFaccia(vertDavanti[tex], faccia, &(facceDavanti[tex]));
                    }
                    if (!checkEsisteBlocco(world, x, y, z - 1)){
                        float faccia[] = ACQUA_FACCIA_DIETRO;
                        translateFaccia(faccia, x, y, z);
                        vertDietro[tex] = addFaccia(vertDietro[tex], faccia, &(facceDietro[tex]));
                    }
                    if (!checkEsisteBlocco(world, x - 1, y, z)){
                        float faccia[] = ACQUA_FACCIA_SINISTRA;
                        translateFaccia(faccia, x, y, z);
                        vertSinistra[tex] = addFaccia(vertSinistra[tex], faccia, &(facceSinistra[tex]));
                    }
                    if (!checkEsisteBlocco(world, x + 1, y, z)){
                        float faccia[] = ACQUA_FACCIA_DESTRA;
                        translateFaccia(faccia, x, y, z);
                        vertDestra[tex] = addFaccia(vertDestra[tex], faccia, &(facceDestra[tex]));
                    }
                }
            }
        }
    }
    unsigned int *sizeSopraSotto = malloc(sizeof(unsigned int) * NUMERO_TEXTURES);
    unsigned int *sizeDavanti = malloc(sizeof(unsigned int) * NUMERO_TEXTURES);
    unsigned int *sizeDietro = malloc(sizeof(unsigned int) * NUMERO_TEXTURES);
    unsigned int *sizeSinistra = malloc(sizeof(unsigned int) * NUMERO_TEXTURES);
    unsigned int *sizeDestra = malloc(sizeof(unsigned int) * NUMERO_TEXTURES);
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        sizeSopraSotto[i] = facceSopraSotto[i] * FLOAT_FACCIA * sizeof(float);
        sizeDavanti[i] = facceDavanti[i] * FLOAT_FACCIA * sizeof(float);
        sizeDietro[i] = facceDietro[i] * FLOAT_FACCIA * sizeof(float);
        sizeSinistra[i] = facceSinistra[i] * FLOAT_FACCIA * sizeof(float);
        sizeDestra[i] = facceDestra[i] * FLOAT_FACCIA * sizeof(float);
    }

    float **verSopraSottoVecchi = draw->verSopraSotto;
    float **verDavantiVecchi = draw->verDavanti;
    float **verDietroVecchi = draw->verDietro;
    float **verSinistraVecchi = draw->verSinistra;
    float **verDestraVecchi = draw->verDestra;
    draw->verSopraSotto = vertSopraSotto;
    draw->verDavanti = vertDavanti;
    draw->verDietro = vertDietro;
    draw->verSinistra = vertSinistra;
    draw->verDestra = vertDestra;
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        free(verSopraSottoVecchi[i]);
        free(verDavantiVecchi[i]);
        free(verDietroVecchi[i]);
        free(verSinistraVecchi[i]);
        free(verDestraVecchi[i]);
    }
    free(verSopraSottoVecchi);
    free(verDavantiVecchi);
    free(verDietroVecchi);
    free(verSinistraVecchi);
    free(verDestraVecchi);

    unsigned int *sizeSopraSottoVecchi = draw->sizeSopraSotto;
    unsigned int *sizeDavantiVecchi = draw->sizeDavanti;
    unsigned int *sizeDietroVecchi = draw->sizeDietro;
    unsigned int *sizeSinistraVecchi = draw->sizeSinistra;
    unsigned int *sizeDestraVecchi = draw->sizeDestra;
    draw->sizeSopraSotto = sizeSopraSotto;
    draw->sizeDavanti = sizeDavanti;
    draw->sizeDietro = sizeDietro;
    draw->sizeSinistra = sizeSinistra;
    draw->sizeDestra = sizeDestra;
    free(sizeSopraSottoVecchi);
    free(sizeDavantiVecchi);
    free(sizeDietroVecchi);
    free(sizeSinistraVecchi);
    free(sizeDestraVecchi);

    setChunkVertici(state, chunk, x, z);
}

/*void setChunk(GameState *state, Chunk *chunk){
    World *world = state->world;
    DrawStruct *draw = chunk->drawStruct;
    float **vert = (float **)malloc(sizeof(float *) * NUMERO_TEXTURES);
    int quanteFaccieTexture[NUMERO_TEXTURES];
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        vert[i] = malloc(sizeof(float));
        quanteFaccieTexture[i] = 0;
    }

    //printf("inizio chunk x: %d chunk z %d\n", chunk->x, chunk->z);
    for (int x = chunk->x - HALF_CHUNK_SIZE; x <= chunk->x + HALF_CHUNK_SIZE; x++){
        for (int z = chunk->z - HALF_CHUNK_SIZE; z <= chunk->z + HALF_CHUNK_SIZE; z++){
            //printf("x: %d z: %d\n", x, z);
            if (checkConfineWorld(x, z)){
                continue;
            }
            int maxY = world->occupati[getOccupati(x, z)][0];
            for (int yo = maxY; yo >= 1; yo--){
                int y = world->occupati[getOccupati(x, z)][yo];
                if (!checkEsisteBlocco(world, x, y + 1, z)){
                    float faccia[] = FACCIA_SOPRA;
                    translateFaccia(faccia, x, y, z);
                    Cube *c = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)];
                    if (c->tex == TEX_DIRT){
                        if (y > ALT_SNOW){
                            c->tex = TEX_SNOW;
                        } else{
                            c->tex = TEX_GRASS;
                        }
                    }
                    unsigned char tex = c->tex;
                    vert[tex] = addFaccia(vert[tex], faccia, &(quanteFaccieTexture[tex]));
                } else{
                    Cube *c = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)];
                    if (c->tex == TEX_GRASS || c->tex == TEX_SNOW){
                        c->tex = TEX_DIRT;
                    }
                }
                if (y != 0 && !checkEsisteBlocco(world, x, y - 1, z)){
                    float faccia[] = FACCIA_SOTTO;
                    translateFaccia(faccia, x, y, z);
                    unsigned char tex = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex;
                    vert[tex] = addFaccia(vert[tex], faccia, &(quanteFaccieTexture[tex]));
                }
                if (!checkEsisteBlocco(world, x - 1, y, z)){
                    float faccia[] = FACCIA_SINISTRA;
                    translateFaccia(faccia, x, y, z);
                    unsigned char tex = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex;
                    vert[tex] = addFaccia(vert[tex], faccia, &(quanteFaccieTexture[tex]));
                }
                if (!checkEsisteBlocco(world, x + 1, y, z)){
                    float faccia[] = FACCIA_DESTRA;
                    translateFaccia(faccia, x, y, z);
                    unsigned char tex = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex;
                    vert[tex] = addFaccia(vert[tex], faccia, &(quanteFaccieTexture[tex]));
                }
                if (!checkEsisteBlocco(world, x, y, z - 1)){
                    float faccia[] = FACCIA_DIETRO;
                    translateFaccia(faccia, x, y, z);
                    unsigned char tex = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex;
                    vert[tex] = addFaccia(vert[tex], faccia, &(quanteFaccieTexture[tex]));
                }
                if (!checkEsisteBlocco(world, x, y, z + 1)){
                    float faccia[] = FACCIA_DAVANTI;
                    translateFaccia(faccia, x, y, z);
                    unsigned char tex = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex;
                    vert[tex] = addFaccia(vert[tex], faccia, &(quanteFaccieTexture[tex]));
                }
            }
        }
    }
    //printf("x: %d z: %d, numero facce %d\n", chunk->x, chunk->z, quanteFaccieTexture[0]);
    unsigned int *sizeVert = malloc(sizeof(unsigned int) * NUMERO_TEXTURES);
    unsigned int *sizeIndi = malloc(sizeof(unsigned int) * NUMERO_TEXTURES);
    int maxSizeIndici = 0;
    int qualeTexMaxSizeIndici = -1;
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        sizeVert[i] = quanteFaccieTexture[i] * 24 * sizeof(float);
        sizeIndi[i] = quanteFaccieTexture[i] * 6 * sizeof(unsigned int);
        if (sizeIndi[i] > maxSizeIndici){
            maxSizeIndici = sizeIndi[i];
            qualeTexMaxSizeIndici = i;
        }
    }
    float **verVecchi = draw->vertici;
    unsigned int *sizeVerVecchi = draw->sizeVertici;
    unsigned int *sizeIndiciVecchi = draw->sizeIndici;
    draw->vertici = vert;
    draw->sizeVertici = sizeVert;
    draw->sizeIndici = sizeIndi;
    for (int i = 0; i < NUMERO_TEXTURES; i++){
        free(verVecchi[i]);
    }
    free(verVecchi);
    free(sizeVerVecchi);
    free(sizeIndiciVecchi);
    if (maxSizeIndici > state->maxSizeIndici){
        //printf("Indici aumentati\n");
        unsigned int *indi = malloc(maxSizeIndici);
        for (int i = 0; i < quanteFaccieTexture[qualeTexMaxSizeIndici]; i++){
            indi[i * 6 + 0] = i * 4 + 0;
            indi[i * 6 + 1] = i * 4 + 1;
            indi[i * 6 + 2] = i * 4 + 2;
            indi[i * 6 + 3] = i * 4 + 2;
            indi[i * 6 + 4] = i * 4 + 3;
            indi[i * 6 + 5] = i * 4 + 0;
        }
        state->indici = indi;
        state->maxSizeIndici = maxSizeIndici;
    }
    //printf("fine chunk x: %d chunk z %d\n", chunk->x, chunk->z);
}*/

void updateChunksFacceThread(void *arg){
    GameState *state = (GameState *)arg;
    state->threadEsecuzione = true;
    World *world = state->world;
    Chunk **chunks = state->chunks;

    int xp = round(state->player->camera->position[0]);
    int yp = round(state->player->camera->position[1]);
    int zp = round(state->player->camera->position[2]);

    int *indiciNuovoCentro = getIndiceChunkDiPosizione(chunks, xp, zp);

    int xNuovoCentro = indiciNuovoCentro[0];
    int zNuovoCentro = indiciNuovoCentro[1];

    free(indiciNuovoCentro);

    //freeare i chunk funziona solo se HALF_CHUNK_IN_WORLD è più grande di HALF_CHUNK_NUMBER cioè se non si accumulano
    if (xNuovoCentro > 0){
        for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
            unsigned int indiceVecchio = getChunk(-HALF_CHUNK_NUMBER, z);
            Chunk *chunkVecchio = chunks[indiceVecchio];
            chunks[indiceVecchio] = chunks[getChunk(-HALF_CHUNK_NUMBER + 1, z)];
            //freeChunk(chunkVecchio);
            //free(chunkVecchio);
        }
        for (int x = -HALF_CHUNK_NUMBER + 1; x < HALF_CHUNK_NUMBER; x++){
            for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
                chunks[getChunk(x, z)] = chunks[getChunk(x + 1, z)];
            }
        }
        for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
            int indiceChunkNuovo = getChunk(HALF_CHUNK_NUMBER, z);
            int xNuovo = chunks[getChunk(HALF_CHUNK_NUMBER - 1, z)]->x + CHUNK_SIZE;
            int zNuovo = chunks[getChunk(HALF_CHUNK_NUMBER - 1, z)]->z;
            if (checkChunkInWorld(xNuovo, zNuovo)){
                Chunk *nuovo = allocateChunk(xNuovo, zNuovo);
                setChunkFacce(state, nuovo, HALF_CHUNK_NUMBER, z);
                chunks[indiceChunkNuovo] = nuovo;
            }
        }
    } else if (xNuovoCentro < 0){
        for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
            unsigned int indiceVecchio = getChunk(HALF_CHUNK_NUMBER, z);
            Chunk *chunkVecchio = chunks[indiceVecchio];
            chunks[indiceVecchio] = chunks[getChunk(HALF_CHUNK_NUMBER - 1, z)];
            //freeChunk(chunkVecchio);
            //free(chunkVecchio);
        }
        for (int x = HALF_CHUNK_NUMBER - 1; x > -HALF_CHUNK_NUMBER; x--){
            for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
                chunks[getChunk(x, z)] = chunks[getChunk(x - 1, z)];
            }
        }
        for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
            int indiceChunkNuovo = getChunk(-HALF_CHUNK_NUMBER, z);
            int xNuovo = chunks[getChunk(-HALF_CHUNK_NUMBER + 1, z)]->x - CHUNK_SIZE;
            int zNuovo = chunks[getChunk(-HALF_CHUNK_NUMBER + 1, z)]->z;
            if (checkChunkInWorld(xNuovo, zNuovo)){
                Chunk *nuovo = allocateChunk(xNuovo, zNuovo);
                setChunkFacce(state, nuovo, -HALF_CHUNK_NUMBER, z);
                chunks[indiceChunkNuovo] = nuovo;
            }
        }
    }
    if (zNuovoCentro > 0){
        for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
            unsigned int indiceVecchio = getChunk(x, -HALF_CHUNK_NUMBER);
            Chunk *chunkVecchio = chunks[indiceVecchio];
            chunks[indiceVecchio] = chunks[getChunk(x, -HALF_CHUNK_NUMBER + 1)];
            //freeChunk(chunkVecchio);
            //free(chunkVecchio);
        }
        for (int z = -HALF_CHUNK_NUMBER + 1; z < HALF_CHUNK_NUMBER; z++){
            for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
                chunks[getChunk(x, z)] = chunks[getChunk(x, z + 1)];
            }
        }
        for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
            int indiceChunkNuovo = getChunk(x, HALF_CHUNK_NUMBER);
            int xNuovo = chunks[getChunk(x, HALF_CHUNK_NUMBER - 1)]->x;
            int zNuovo = chunks[getChunk(x, HALF_CHUNK_NUMBER - 1)]->z + CHUNK_SIZE;
            if (!checkChunkInWorld(xNuovo, zNuovo)){
                Chunk *nuovo = allocateChunk(xNuovo, zNuovo);
                setChunkFacce(state, nuovo, x, HALF_CHUNK_NUMBER);
                chunks[indiceChunkNuovo] = nuovo;
            }
        }
    } else if (zNuovoCentro < 0){
        for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
            unsigned int indiceVecchio = getChunk(x, HALF_CHUNK_NUMBER);
            Chunk *chunkVecchio = chunks[indiceVecchio];
            chunks[indiceVecchio] = chunks[getChunk(x, HALF_CHUNK_NUMBER - 1)];
            //freeChunk(chunkVecchio);
            //free(chunkVecchio);
        }
        for (int z = HALF_CHUNK_NUMBER - 1; z > -HALF_CHUNK_NUMBER; z--){
            for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
                chunks[getChunk(x, z)] = chunks[getChunk(x, z - 1)];
            }
        }
        for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
            int indiceChunkNuovo = getChunk(x, -HALF_CHUNK_NUMBER);
            int xNuovo = chunks[getChunk(x, -HALF_CHUNK_NUMBER + 1)]->x;
            int zNuovo = chunks[getChunk(x, -HALF_CHUNK_NUMBER + 1)]->z - CHUNK_SIZE;
            if (checkChunkInWorld(xNuovo, zNuovo)){
                Chunk *nuovo = allocateChunk(xNuovo, zNuovo);
                setChunkFacce(state, nuovo, x, -HALF_CHUNK_NUMBER);
                chunks[indiceChunkNuovo] = nuovo;
            }
        }
    }
    for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
        setChunkVertici(state, state->chunks[getChunk(x, -1)], x, -1);
        setChunkVertici(state, state->chunks[getChunk(x,  0)], x,  0);
        setChunkVertici(state, state->chunks[getChunk(x,  1)], x,  1);
    }
    for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
        if (z == -1){
            z = 2;
        }
        setChunkVertici(state, state->chunks[getChunk(-1, z)], -1, z);
        setChunkVertici(state, state->chunks[getChunk( 0, z)],  0, z);
        setChunkVertici(state, state->chunks[getChunk( 1, z)],  1, z);
    }
    state->threadEsecuzione = false;
    pthread_exit(0);
}

/*void updateChunksThread(void *arg){
    GameState *state = (GameState *)arg;
    state->threadEsecuzione = true;
    World *world = state->world;
    Chunk **chunks = state->chunks;

    int xp = round(state->player->camera->position[0]);
    int yp = round(state->player->camera->position[1]);
    int zp = round(state->player->camera->position[2]);

    int *indiciNuovoCentro = getIndiceChunkDiPosizione(chunks, xp, zp);

    int xNuovoCentro = indiciNuovoCentro[0];
    int zNuovoCentro = indiciNuovoCentro[1];

    //printf("xNuovoCen: %d, zNuovoCen: %d\n", xNuovoCentro, zNuovoCentro);
    //printf("xChunkCen: %d, zChunkCen: %d\n", xChunkCen, zChunkCen);
    if (xNuovoCentro > 0){
        for (int x = -HALF_CHUNK_NUMBER; x < HALF_CHUNK_NUMBER; x++){
            for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
                chunks[getChunk(x, z)] = chunks[getChunk(x + 1, z)];
            }
        }
        for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
            int indiceChunkNuovo = getChunk(HALF_CHUNK_NUMBER, z);
            int xNuovo = chunks[getChunk(HALF_CHUNK_NUMBER - 1, z)]->x + (CHUNK_SIZE + 1);
            int zNuovo = chunks[getChunk(HALF_CHUNK_NUMBER - 1, z)]->z;
            if (checkChunkInWorld(xNuovo, zNuovo)){
                Chunk *nuovo = allocateChunk(xNuovo, zNuovo);
                setChunk(state, nuovo);
                chunks[indiceChunkNuovo] = nuovo;
            }
        }
    } else if (xNuovoCentro < 0){
        for (int x = HALF_CHUNK_NUMBER; x > -HALF_CHUNK_NUMBER; x--){
            for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
                chunks[getChunk(x, z)] = chunks[getChunk(x - 1, z)];
            }
        }
        for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++){
            int indiceChunkNuovo = getChunk(-HALF_CHUNK_NUMBER, z);
            int xNuovo = chunks[getChunk(-HALF_CHUNK_NUMBER + 1, z)]->x - (CHUNK_SIZE + 1);
            int zNuovo = chunks[getChunk(-HALF_CHUNK_NUMBER + 1, z)]->z;
            if (checkChunkInWorld(xNuovo, zNuovo)){
                Chunk *nuovo = allocateChunk(xNuovo, zNuovo);
                setChunk(state, nuovo);
                chunks[indiceChunkNuovo] = nuovo;
            }
        }
    }
    if (zNuovoCentro > 0){
        for (int z = -HALF_CHUNK_NUMBER; z < HALF_CHUNK_NUMBER; z++){
            for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
                chunks[getChunk(x, z)] = chunks[getChunk(x, z + 1)];
            }
        }
        for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
            int indiceChunkNuovo = getChunk(x, HALF_CHUNK_NUMBER);
            int xNuovo = chunks[getChunk(x, HALF_CHUNK_NUMBER - 1)]->x;
            int zNuovo = chunks[getChunk(x, HALF_CHUNK_NUMBER - 1)]->z + (CHUNK_SIZE + 1);
            if (checkChunkInWorld(xNuovo, zNuovo)){
                Chunk *nuovo = allocateChunk(xNuovo, zNuovo);
                setChunk(state, nuovo);
                chunks[indiceChunkNuovo] = nuovo;
            }
        }
    } else if (zNuovoCentro < 0){
        for (int z = HALF_CHUNK_NUMBER; z > -HALF_CHUNK_NUMBER; z--){
            for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
                chunks[getChunk(x, z)] = chunks[getChunk(x, z - 1)];
            }
        }
        for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++){
            int indiceChunkNuovo = getChunk(x, -HALF_CHUNK_NUMBER);
            int xNuovo = chunks[getChunk(x, -HALF_CHUNK_NUMBER + 1)]->x;
            int zNuovo = chunks[getChunk(x, -HALF_CHUNK_NUMBER + 1)]->z - (CHUNK_SIZE + 1);
            if (checkChunkInWorld(xNuovo, zNuovo)){
                Chunk *nuovo = allocateChunk(xNuovo, zNuovo);
                setChunk(state, nuovo);
                chunks[indiceChunkNuovo] = nuovo;
            }
        }
    }
    state->threadEsecuzione = false;
    pthread_exit(0);
}*/

void setDrawStruct(GameState *state){
    if (state->threadEsecuzione == false){
        pthread_t thread;
        //pthread_create(&thread, NULL, updateChunksThread, state);
        pthread_create(&thread, NULL, updateChunksFacceThread, state);
    } else{
        printf("ATTENZIONE: thread non ancora finito\n");
    }
}
