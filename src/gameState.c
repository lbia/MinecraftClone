#include "gameState.h"

#include "math.h"

int getSegno(int c) {
    int segnoC = 0;
    if (c > 0) {
        segnoC = 1;
    } else if (c < 0) {
        segnoC = -1;
    }
    return segnoC;
}

int getYMassima(World *world, int x, int z) {
    return world->occupati[getIndiceMondo(x, z)][getOccupati(
        x, z)][world->occupati[getIndiceMondo(x, z)][getOccupati(x, z)][0]];
}

float getMax(float f1, float f2) {
    if (f1 >= f2) {
        return f1;
    } else {
        return f2;
    }
}

void getCubePointer(World *world, int x, int y, int z, Cube **cube) {
    Cube *cubeOfficiale = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)];
    *cube = cubeOfficiale;
}

int getCoordinataMondo(int c) {
    bool cNegativo = false;
    if (c < 0) {
        c = -c;
        cNegativo = true;
    }
    int mondoC;
    int veroC = c - HALF_WORLD_SIZE - 1;
    if (veroC < 0) {
        mondoC = 0;
    } else {
        mondoC = (veroC / WORLD_SIZE) + 1;
    }
    if (cNegativo) {
        mondoC = -mondoC;
    }
    return mondoC;
}

int getIndiceMondoDaCoordinateMondo(int mondoX, int mondoZ) {
    return (mondoX + HALF_MONDI_MASSIMI) * MONDI_MASSIMI + mondoZ +
           HALF_MONDI_MASSIMI;
}

int getIndiceMondo(int x, int z) {
    if (x >= -HALF_WORLD_SIZE || z >= -HALF_WORLD_SIZE ||
        x <= HALF_WORLD_SIZE || z <= HALF_WORLD_SIZE) {
        return 0;
    } else {
        return -1;
    }
}

int getCube(int x, int y, int z) {
    if (x < -HALF_WORLD_SIZE || y < 0 || z < -HALF_WORLD_SIZE ||
        x > HALF_WORLD_SIZE || z > HALF_WORLD_SIZE || y > Y_MAX) {
        printf("Provi ad accedere ad un blocco fuori dal mondo\n");
        printf("x: %d y: %d z: %d\n", x, y, z);
        return -1;
    } else {
        int indice = (x + HALF_WORLD_SIZE) * (WORLD_SIZE) * (Y_MAX) +
                     (z + HALF_WORLD_SIZE) * (Y_MAX) + y;
        // printf("x %d y %d z %d indice %d\n", x, y, z, indice);
        return indice;
    }
}

int getOccupati(int x, int z) {
    if (x < -HALF_WORLD_SIZE || z < -HALF_WORLD_SIZE || x > HALF_WORLD_SIZE ||
        z > HALF_WORLD_SIZE) {
        printf("Provi ad accedere ad un blocco occupati fuori dal mondo\n");
        printf("x: %d z: %d\n", x, z);
        return -1;
    }
    int indice = (x + HALF_WORLD_SIZE) * (WORLD_SIZE) + (z + HALF_WORLD_SIZE);
    return indice;
}

int getChunk(int x, int z) {
    if (x < -HALF_CHUNK_NUMBER || z < -HALF_CHUNK_NUMBER ||
        x > HALF_CHUNK_NUMBER || z > HALF_CHUNK_NUMBER) {
        printf("Provi ad accedere ad un chunk fuori dal mondo\n");
        printf("x: %d z: %d\n", x, z);
        return -1;
    } else {
        return (x + HALF_CHUNK_NUMBER) * (CHUNK_NUMBER) +
               (z + HALF_CHUNK_NUMBER);
    }
}

void initPlayer(GameState *state) {
    state->player = malloc(sizeof(Player));
    Player *player = state->player;
    vec3 initialPos = {0, 0, 0};
    player->camera = malloc(sizeof(Camera));
    initializeCameraScalar(player->camera, initialPos[0], initialPos[1],
                           initialPos[2]);
    player->y0 = initialPos[1];
    player->newPositionCamera[0] = initialPos[0];
    player->newPositionCamera[1] = initialPos[2];
    player->previusPosition[0] = initialPos[0];
    player->previusPosition[1] = initialPos[2];
    player->bloccoDaRompere[0] = -1;
    player->bloccoDaRompere[1] = -1;
    player->bloccoDaRompere[2] = -1;
    player->inWater = false;
    player->shift = false;
    player->jump = false;
    player->timeJump = 0;
    player->jumpSpeed = JUMP_VEL;
    player->timeRotturaBlocco = 0;
}

void generateWorld(GameState *state, int mondoX, int mondoZ) {
    World *world = state->world;

    int xInizio = (WORLD_SIZE * mondoX) - HALF_WORLD_SIZE;
    int xFine = xInizio + 2 * HALF_WORLD_SIZE;
    int zInizio = (WORLD_SIZE * mondoZ) - HALF_WORLD_SIZE;
    int zFine = zInizio + 2 * HALF_WORLD_SIZE;
    // printf("xInizio %d xFine %d zInizio %d zFine %d\n", xInizio, xFine,
    // zInizio, zFine);
    int percentualeCompletamento = 0;
    for (int x = xInizio; x <= xFine; x++) {
        if (x % (HALF_WORLD_SIZE / 5) == 0) {
            if (percentualeCompletamento != 0) {
                printf("%d%% world generation\n", percentualeCompletamento);
            }
            percentualeCompletamento += 10;
        }
        for (int z = zInizio; z <= zFine; z++) {
            world->occupati[getIndiceMondo(x, z)][getOccupati(x, z)] =
                (unsigned char *)malloc(sizeof(unsigned char));
            world->occupati[getIndiceMondo(x, z)][getOccupati(x, z)][0] = 0;
            // int alt = interpolateAtlezze(altezze, x, z);
            setPerlinSeed(3);
            float h = getMax(
                350 * getPerlin2d(x, z, 0.01, 1) - 200,
                (50 * getPerlin2d(x, z, 0.01, 1) +
                 50 * getPerlin2d(x, z, 0.02, 2) +
                 10 * getPerlin2d(x, z, 0.04, 3) +
                 5 * getPerlin2d(x, z, 0.08, 4) / (50 + 50 + 10 + 5) * 100));
            // float h = getMax(200 * getPerlin2d(x, z, 0.05, 1) - 60,
            // ALTITUDE_STANDARD); float h = ALTITUDE_STANDARD; printf("x %d z %d
            // h %f\n", x, z, h);
            for (int y = 0; y <= h; y++) {
                int nuovoCubo[3] = {x, y, z};
                addCubeToWorld(world, nuovoCubo, TEX_STONE);
            }
        }
    }
    for (int x = xInizio; x <= xFine; x++) {
        for (int z = zInizio; z <= zFine; z++) {
            int y = getYMassima(world, x, z);
            unsigned char tex =
                world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex;
            while (tex == TEX_LEAVES || tex == TEX_WOOD) {
                y--;
                if (checkEsisteBlocco(world, x, y, z)) {
                    tex = world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]
                              ->tex;
                } else {
                    continue;
                }
            }
            if (y > ALT_SNOW) {
                float randomSnow = rand() % 10;
                if (randomSnow > 5) {
                    world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex =
                        TEX_SNOW;
                }
            } else {
                world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex =
                    TEX_GRASS;
            }
            y++;
            int ranAlbero = rand() % 300;
            if (ranAlbero == 3 && y > ALT_WATER) {
                int posAlbero[3] = {x, y, z};
                plantTree(state, posAlbero, TEX_WOOD);
            }
        }
    }
    for (int x = xInizio; x <= xFine; x++) {
        for (int z = zInizio; z <= zFine; z++) {
            for (int y = ALT_WATER; y >= 0; y--) {
                if (!checkEsisteBlocco(world, x, y, z)) {
                    int posAcqua[3] = {x, y, z};
                    addCubeToWorld(world, posAcqua, TEX_WATER);
                } else if (!checkEsisteBlocco(world, x, y + 1, z) ||
                           world->cubes[getIndiceMondo(x, z)]
                                       [getCube(x, y + 1, z)]
                                           ->tex == TEX_WATER) {
                    world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex =
                        TEX_SAND;
                }
            }
        }
    }

    int yPlayer =
        world->occupati[getIndiceMondo(0, 0)][getOccupati(
            0,
            0)][world->occupati[getIndiceMondo(0, 0)][getOccupati(0, 0)][0]] +
        1;
    int y = 0;
    /*for (y = 0; y < 140; y++){
        int posCube[3] = {0, y + yPlayer, 0};
        addCubeToWorld(world, posCube, TEX_GRASS);
    }*/
    state->player->camera->position[1] = yPlayer + y + 10;
}

void initWorld(GameState *state) {
    state->world = malloc(sizeof(World));
    World *world = state->world;

    world->cubes =
        (Cube ***)malloc(sizeof(Cube **) * MONDI_MASSIMI * MONDI_MASSIMI);
    world->cubes[getIndiceMondo(0, 0)] =
        (Cube **)malloc(sizeof(Cube *) * WORLD_SIZE * WORLD_SIZE * Y_MAX);
    world->occupati = (unsigned char ***)malloc(sizeof(unsigned char **) *
                                                MONDI_MASSIMI * MONDI_MASSIMI);
    world->occupati[getIndiceMondo(0, 0)] = (unsigned char **)malloc(
        sizeof(unsigned char *) * WORLD_SIZE * WORLD_SIZE);

    generateWorld(state, getCoordinataMondo(0), getCoordinataMondo(0));

    updateWorld(world, 0, round(state->player->camera->position[1]), 0);
}

void initChunks(GameState *state) {
    Player *player = state->player;
    state->maxSizeIndici = 0;
    int xp = player->camera->position[0];
    int zp = player->camera->position[2];
    state->chunks =
        (Chunk **)malloc(sizeof(Chunk *) * CHUNK_NUMBER * CHUNK_NUMBER);
    for (int x = -HALF_CHUNK_NUMBER; x <= HALF_CHUNK_NUMBER; x++) {
        for (int z = -HALF_CHUNK_NUMBER; z <= HALF_CHUNK_NUMBER; z++) {
            int indice = getChunk(x, z);
            int xNuovo = xp + (x * CHUNK_SIZE);
            int zNuovo = zp + (z * CHUNK_SIZE);
            state->chunks[indice] = allocateChunk(xNuovo, zNuovo);
            // setChunk(state, state->chunks[indice]);
            setChunkFacce(state, state->chunks[indice], x, z);
        }
    }
    setDrawStruct(state);
    state->threadEsecuzione = true;
    while (state->threadEsecuzione)
        ;
}

void initZombie(GameState *state) {
    World *world = state->world;
    state->zombie = malloc(sizeof(Mob));
    Mob *zombie = state->zombie;
    zombie->type = MOB_ZOMBIE;
    zombie->x = 0;
    zombie->z = -3;
    zombie->y =
        world->occupati[getIndiceMondo(zombie->x, zombie->z)]
                       [getOccupati(zombie->x, zombie->z)]
                       [world->occupati[getIndiceMondo(zombie->x, zombie->z)]
                                       [getOccupati(zombie->x, zombie->z)][0]] +
        1;
    state->slime = malloc(sizeof(Slime));
    /*Slime *slime = state->slime;
    slime->x = 0;
    slime->z = -2;
    slime->y = world->occupati[getOccupati(slime->x,
    slime->z)][world->occupati[getOccupati(slime->x, slime->z)][0]] + 1;*/
    zombie->dir[0] = -1;
    zombie->dir[1] = 1;
}

void initTextures(GameState *state) {
    state->blockTextures = createBlockTexture();
    /*printf("prima %u\n", state->mobTextures);
    state->mobTextures = createMobTexture();
    printf("dopo %u\n", state->mobTextures[MOB_ZOMBIE]);
    printf("prova %u\n", state->mobTextures[MOB_ZOMBIE]->m_RendererID);*/
    state->mobTextures = malloc(sizeof(Texture));
    initializeTexture(state->mobTextures, "res/mob/pigzombie.png");
    state->mouseTexture = malloc(sizeof(Texture));
    initializeTexture(state->mouseTexture, "res/textures/mouseBianco.png");
    state->slotTexture = malloc(sizeof(Texture));
    initializeTexture(state->slotTexture, "res/gui/slot.png");
    state->waterTexture = malloc(sizeof(Texture));
    initializeTexture(state->waterTexture, "res/blocks/water.png");
}

void initGameState(GameState *state) {
    initPlayer(state);
    initWorld(state);
    initChunks(state);
    initZombie(state);

    initTextures(state);

    state->creative = false;
    state->spazioPremuto = false;
    state->scendiPremuto = false;

    state->threadEsecuzione = false;

    state->leftPress = false;
    state->rightPress = false;

    state->textureSelezionata = TEX_GRASS;

    state->firstMouse = true;
    state->lastX = WIDTH / 2.0;
    state->lastY = HEIGHT / 2.0;

    state->deltaTime = 0;
    state->lastFrame = 0;
}

void destroyGameState(GameState *state) {
    free(state->player->camera);
    free(state->player);
    free(state->world);
}

void processMouseScroll(GameState *state, double scorrimento) {
    if (scorrimento > 0) {
        state->textureSelezionata--;
        if (state->textureSelezionata < 0) {
            state->textureSelezionata = NUMERO_TEXTURES - 1;
        }
    } else if (scorrimento < 0) {
        state->textureSelezionata++;
        if (state->textureSelezionata >= NUMERO_TEXTURES) {
            state->textureSelezionata = 0;
        }
    }
}

void restartJump(Player *player) {
    player->timeJump = 0;
    player->y0 = player->camera->position[1];
}

void startJump(Player *player, float jumpSpeed, float yStart) {
    player->jump = true;
    player->timeJump = 0;
    player->y0 = yStart;
    player->camera->position[1] = yStart;
    player->jumpSpeed = jumpSpeed;
}

void endJump(Player *player, float yNew) {
    player->jump = false;
    player->timeJump = 0;
    player->camera->position[1] = yNew;
}

void updateWorld(World *world, int x, int y, int z) {
    // printf("x: %d y: %d z: %d\n", x, y, z);
    world->zUpdateInizio = z - HALF_UPDATE_CUBES_SIZE;
    if (world->zUpdateInizio < -HALF_WORLD_SIZE) {
        world->zUpdateInizio = -HALF_WORLD_SIZE;
    }
    world->zUpdateFine = z + HALF_UPDATE_CUBES_SIZE;
    if (world->zUpdateFine > HALF_WORLD_SIZE) {
        world->zUpdateFine = HALF_WORLD_SIZE;
    }
    world->xUpdateInizio = x - HALF_UPDATE_CUBES_SIZE;
    if (world->xUpdateInizio < -HALF_WORLD_SIZE) {
        world->xUpdateInizio = -HALF_WORLD_SIZE;
    }
    world->xUpdateFine = x + HALF_UPDATE_CUBES_SIZE;
    if (world->xUpdateFine > HALF_WORLD_SIZE) {
        world->xUpdateFine = HALF_WORLD_SIZE;
    }
    world->yUpdateInizio = y - HALF_UPDATE_CUBES_SIZE;
    if (world->yUpdateInizio < 0) {
        world->yUpdateInizio = 0;
    }
    world->yUpdateFine = y + HALF_UPDATE_CUBES_SIZE;
    if (world->yUpdateFine > Y_MAX) {
        world->yUpdateFine = Y_MAX;
    }
}

void updateBloccoDaRompere(GameState *state) {
    World *world = state->world;
    Player *player = state->player;
    if (state->leftPress) {
        puntaBloccoDaRompere(state);
    }
    if (player->timeRotturaBlocco >= TIME_ROTTURA_BLOCCO) {
        removeCubeFromWorld(world, player->bloccoDaRompere);
        int *indiciChunk =
            getIndiceChunkDiPosizione(state->chunks, player->bloccoDaRompere[0],
                                      player->bloccoDaRompere[2]);
        int xIndiceChunk = indiciChunk[0];
        int zIndiceChunk = indiciChunk[1];
        free(indiciChunk);
        for (int x = xIndiceChunk - 1; x <= xIndiceChunk + 1; x++) {
            for (int z = zIndiceChunk - 1; z <= zIndiceChunk + 1; z++) {
                int indice = getChunk(x, z);
                if (indice >= 0) {
                    setChunkFacce(state, state->chunks[indice], x, z);
                }
            }
        }
        // setChunk(state, state->chunks[getChunk(indiciChunk[0],
        // indiciChunk[1])]);
        player->bloccoDaRompere[0] = -1;
        player->bloccoDaRompere[1] = -1;
        player->bloccoDaRompere[2] = -1;
        player->timeRotturaBlocco = 0;
        state->leftPress = false;
    }
}

void updateJump(GameState *state) {
    World *world = state->world;
    Player *player = state->player;

    player->camera->position[0] = player->nuovaPosizione[0];
    player->camera->position[2] = player->nuovaPosizione[1];
    double prevY = player->camera->position[1];
    player->timeJump += state->deltaTime;
    if (!player->inWater) {
        player->camera->position[1] =
            player->y0 + player->jumpSpeed * player->timeJump -
            GRAVITY * player->timeJump * player->timeJump;
    } else {
        if (state->spazioPremuto) {
            player->camera->position[1] +=
                player->camera->movementSpeed * state->deltaTime;
        } else {
            player->camera->position[1] -=
                player->camera->movementSpeed * state->deltaTime;
        }
    }

    bool fine = false;
    if (player->inWater) {
        endJump(player, state->player->camera->position[1]);
        fine = true;
    }
    if (prevY > player->camera->position[1]) {
        if (checkSbatteSottoMob(player->camera->position, state->zombie)) {
            endJump(player, state->zombie->y + 3);
            fine = true;
        }
    } else if (prevY < player->camera->position[1]) {
        if (checkSbatteSopraMob(player->camera->position, state->zombie)) {
            startJump(player, 0, state->zombie->y - 1);
            fine = true;
        }
    }
    for (int z = world->zUpdateInizio; z <= world->zUpdateFine && !fine; z++) {
        for (int x = world->xUpdateInizio; x <= world->xUpdateFine && !fine;
             x++) {
            for (int y = world->yUpdateInizio; y <= world->yUpdateFine && !fine;
                 y++) {
                if (!checkEsisteBlocco(world, x, y, z) ||
                    world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex ==
                        TEX_WATER) {
                    continue;
                }
                int posizioneCubo[3] = {x, y, z};
                if (prevY > player->camera->position[1]) {
                    if (checkSbatteSotto(player->camera->position,
                                         posizioneCubo)) {
                        endJump(player, posizioneCubo[1] + 2);
                        fine = true;
                        break;
                    }
                } else if (prevY < player->camera->position[1]) {
                    if (checkSbatteSopra(player->camera->position,
                                         posizioneCubo)) {
                        startJump(player, 0, posizioneCubo[1] - 1);
                        fine = true;
                        break;
                    }
                }
            }
        }
    }
}

void updateCheckSopraCubo(GameState *state) {
    World *world = state->world;
    Player *player = state->player;
    vec3 posNuova = {player->nuovaPosizione[0], player->camera->position[1],
                     player->nuovaPosizione[1]};
    bool onCubo = false;
    if (sopraMob(posNuova, state->zombie)) {
        onCubo = true;
    }
    for (int x = world->xUpdateInizio; x <= world->xUpdateFine && !onCubo;
         x++) {
        for (int z = world->zUpdateInizio; z <= world->zUpdateFine && !onCubo;
             z++) {
            for (int y = world->yUpdateInizio;
                 y <= world->yUpdateFine && !onCubo; y++) {
                if (!checkEsisteBlocco(world, x, y, z) ||
                    world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex ==
                        TEX_WATER) {
                    continue;
                }
                int posizioneCubo[3] = {x, y, z};
                if (sopraCubo(posNuova, posizioneCubo)) {
                    onCubo = true;
                    break;
                }
            }
        }
    }
    if (onCubo) {
        player->camera->position[0] = player->nuovaPosizione[0];
        player->camera->position[2] = player->nuovaPosizione[1];
    } else if (!player->shift) {
        player->camera->position[0] = player->nuovaPosizione[0];
        player->camera->position[2] = player->nuovaPosizione[1];
        startJump(player, 0, player->camera->position[1]);
    }
}

void updateCollisionPlayer(GameState *state) {
    World *world = state->world;
    Player *player = state->player;
    vec2 posConX = {player->newPositionCamera[0], player->camera->position[2]};
    vec2 posConZ = {player->camera->position[0], player->newPositionCamera[1]};
    bool colX = false;
    bool colZ = false;
    if (collisionMobY(player->camera->position[1], state->zombie->y)) {
        if (collisionMobXZ(posConX, state->zombie->x, state->zombie->z)) {
            colX = true;
        }
        if (collisionMobXZ(posConZ, state->zombie->x, state->zombie->z)) {
            colZ = true;
        }
    }
    for (int z = world->zUpdateInizio;
         z <= world->zUpdateFine && (!colX || !colZ); z++) {
        for (int x = world->xUpdateInizio;
             x <= world->xUpdateFine && (!colX || !colZ); x++) {
            for (int y = world->yUpdateInizio;
                 y <= world->yUpdateFine && (!colX || !colZ); y++) {
                if (!checkEsisteBlocco(world, x, y, z) ||
                    world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex ==
                        TEX_WATER) {
                    continue;
                }
                int posizioneCubo[3] = {x, y, z};
                if (collisionPlayerY(player->camera->position[1],
                                     posizioneCubo[1])) {
                    if (collisionPlayerXZ(posConX, posizioneCubo[0],
                                          posizioneCubo[2])) {
                        colX = true;
                    }
                    if (collisionPlayerXZ(posConZ, posizioneCubo[0],
                                          posizioneCubo[2])) {
                        colZ = true;
                    }
                }
            }
        }
    }
    if (!colX) {
        player->nuovaPosizione[0] = player->newPositionCamera[0];
    }
    if (!colZ) {
        player->nuovaPosizione[1] = player->newPositionCamera[1];
    }
}

void updateMob(GameState *state) {
    Mob *mob = state->zombie;
    mob->dir[0] = state->player->camera->position[0] - state->zombie->x;
    mob->dir[1] = state->player->camera->position[2] - state->zombie->z;
    normalizeVec2(mob->dir);
    float vel = 2.0f;
    // mob->x += mob->dir[0] * vel * state->deltaTime;
    // mob->z += mob->dir[1] * vel * state->deltaTime;
}

void updateCreative(GameState *state) {
    if (state->spazioPremuto) {
        state->player->camera->position[1] +=
            (state->player->camera->movementSpeed / 2.0f) * state->deltaTime;
    } else if (state->scendiPremuto) {
        state->player->camera->position[1] -=
            (state->player->camera->movementSpeed / 2.0f) * state->deltaTime;
    }
}

void updateGameState(GameState *state) {
    Player *player = state->player;
    World *world = state->world;
    Shader *shader = state->programWorld->shader;
    bindShader(shader);
    updateBloccoDaRompere(state);
    // update x e z
    updateCollisionPlayer(state);
    // update y
    if (state->creative == false) {
        if (player->jump) {
            updateJump(state);
        } else {
            updateCheckSopraCubo(state);
        }
    } else {
        player->camera->position[0] = player->nuovaPosizione[0];
        player->camera->position[2] = player->nuovaPosizione[1];
        updateCreative(state);
    }

    int xInt = round(player->camera->position[0]);
    int yInt = round(player->camera->position[1]);
    int zInt = round(player->camera->position[2]);
    if (xInt < player->previusPosition[0] - CHUNK_SIZE ||
        xInt > player->previusPosition[0] + CHUNK_SIZE ||
        zInt < player->previusPosition[1] - CHUNK_SIZE ||
        zInt > player->previusPosition[1] + CHUNK_SIZE) {
        setDrawStruct(state);
        player->previusPosition[0] = xInt;
        player->previusPosition[1] = zInt;
    }
    if (!player->inWater && checkEsisteBlocco(world, xInt, yInt, zInt) &&
        world->cubes[getIndiceMondo(xInt, zInt)][getCube(xInt, yInt, zInt)]
                ->tex == TEX_WATER) {
        player->inWater = true;
        float colorAcqua[4] = {137 / 255.0f, 196 / 255.0f, 244 / 255.0f};
        setShaderUniformVec3(shader, "u_LightColor", colorAcqua);
    } else if (player->inWater && !checkEsisteBlocco(world, xInt, yInt, zInt)) {
        player->inWater = false;
        float colorBase[4] = {1, 1, 1};
        setShaderUniformVec3(shader, "u_LightColor", colorBase);
    }
    updateWorld(world, xInt, yInt, zInt);
    // updateMob(state);
    int zombieX = round(state->zombie->x);
    int zombieY = round(state->zombie->y);
    int zombieZ = round(state->zombie->z);
    if (checkEsisteBlocco(world, zombieX, zombieY, zombieZ)) {
        state->zombie->y += 1;
    } else if (!checkEsisteBlocco(world, zombieX, zombieY - 1, zombieZ)) {
        state->zombie->y -= 1;
    }
}
