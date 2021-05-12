#include "cube.h"

#include "math.h"

void plantTree(GameState *state, int pos[3], unsigned char tex);

void addCubeToWorld(World *world, int cube[3], unsigned char texture){
    int x = cube[0];
    int y = cube[1];
    int z = cube[2];

    if (!checkEsisteBlocco(world, x, y, z)){
        world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)] = (Cube *)malloc(sizeof(Cube));
    }
    world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]->tex = texture;

    int indiceMondo = getIndiceMondo(x, z);
    int indice = getOccupati(x, z);
    int numeroBlocchi = world->occupati[indiceMondo][indice][0];
    int posPrimoBloccoPiuGiu = numeroBlocchi;
    while(posPrimoBloccoPiuGiu > 0 && world->occupati[indiceMondo][indice][posPrimoBloccoPiuGiu] > y){
        posPrimoBloccoPiuGiu--;
    }
    if (posPrimoBloccoPiuGiu == 0 || world->occupati[indiceMondo][indice][posPrimoBloccoPiuGiu] != y){
        world->occupati[indiceMondo][indice][0]++;
        numeroBlocchi++;
        world->occupati[indiceMondo][indice] = realloc(world->occupati[indiceMondo][indice], sizeof(unsigned char) * (numeroBlocchi + 1));
        for (int i = numeroBlocchi; i >= posPrimoBloccoPiuGiu + 2; i--){
            world->occupati[indiceMondo][indice][i] = world->occupati[indiceMondo][indice][i - 1];
        }
        world->occupati[indiceMondo][indice][posPrimoBloccoPiuGiu + 1] = y;
    }
}

void removeCubeFromWorld(World *world, int cube[3]){
    int x = cube[0];
    int y = cube[1];
    int z = cube[2];

    if (checkEsisteBlocco(world, x, y, z)){
        free(world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)]);
        world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)] = NULL;
    } else{
        printf("WARNING: stai provando a rimuovere un blocco che non esiste\n");
        printf("x: %d y: %d z: %d\n", x, y, z);
        return;
    }

    int indiceMondo = getIndiceMondo(x, z);
    int indice = getOccupati(x, z);
    int numeroBlocchi = world->occupati[indiceMondo][indice][0];
    int posPrimoBloccoPiuGiu = numeroBlocchi;
    while(posPrimoBloccoPiuGiu > 0 && world->occupati[indiceMondo][indice][posPrimoBloccoPiuGiu] > y){
        posPrimoBloccoPiuGiu--;
    }
    if (posPrimoBloccoPiuGiu != 0 || world->occupati[indiceMondo][indice][posPrimoBloccoPiuGiu] == y){
        for (int i = posPrimoBloccoPiuGiu; i <= numeroBlocchi; i++){
            world->occupati[indiceMondo][indice][i] = world->occupati[indiceMondo][indice][i + 1];
        }
        world->occupati[indiceMondo][indice][0]--;
        numeroBlocchi--;
        world->occupati[indiceMondo][indice] = realloc(world->occupati[indiceMondo][indice], sizeof(unsigned char) * (numeroBlocchi + 1));
    }
}

void piazzaBlocco(GameState *state, unsigned char texture){
    World *world = state->world;
    Player *player = state->player;

    int nuovoBlocco[3];

    vec3 davanti;
    glm_vec3_normalize_to(player->camera->front, davanti);

    double xd = player->camera->position[0];
    double yd = player->camera->position[1];
    double zd = player->camera->position[2];

    int x = round(xd);
    int y = round(yd);
    int z = round(zd);
    int prevX = x, prevY = y, prevZ = z;
    float i = 0.0f;
    float deltaI = 0.2f;
    bool continua = true;
    while(checkInWorld(x, y, z) && continua){
        prevX = x;
        prevY = y;
        prevZ = z;
        xd += davanti[0] * deltaI;
        yd += davanti[1] * deltaI;
        zd += davanti[2] * deltaI;
        x = round(xd);
        y = round(yd);
        z = round(zd);
        i += deltaI;
        if (i > MAX_PIAZZAMENTO_BLOCCHI){
            return;
        }
        if (checkEsisteBlocco(world, x, y, z)){
            if(!checkBloccoAdiacente(player->camera->position, prevX, prevY, prevZ)){
                continua = false;
            } else {
                return;
            }
        }
    }
    int numeroDiversi = 0;
    if (prevX != x){
        numeroDiversi++;
    }
    if (prevY != y){
        numeroDiversi++;
    }
    if (prevZ != z){
        numeroDiversi++;
    }
    if (numeroDiversi != 1){
        return;
    }
    nuovoBlocco[0] = prevX;
    nuovoBlocco[1] = prevY;
    nuovoBlocco[2] = prevZ;
    if (state->textureSelezionata == PIANTA_ALBERO){
        plantTree(state, nuovoBlocco, TEX_BIRCH);
    } else{
        addCubeToWorld(world, nuovoBlocco, texture);
    }
    int *indiciChunk = getIndiceChunkDiPosizione(state->chunks, nuovoBlocco[0], nuovoBlocco[2]);
    int xIndiceChunk = indiciChunk[0];
    int zIndiceChunk = indiciChunk[1];
    free(indiciChunk);
    for (int x = xIndiceChunk -1; x <= xIndiceChunk + 1; x++){
        for (int z = zIndiceChunk -1; z <= zIndiceChunk + 1; z++){
            int indice = getChunk(x, z);
            if (indice >= 0){
                setChunkFacce(state, state->chunks[indice], x, z);
            }
        }
    }
    //setChunkFacce(state, state->chunks[getChunk(indiciChunk[0], indiciChunk[1])], indiciChunk[0], indiciChunk[1]);
}

void puntaBloccoDaRompere(GameState *state){
    World *world = state->world;
    Player *player = state->player;

    int bloccoPuntato[3];

    vec3 davanti;
    glm_vec3_normalize_to(player->camera->front, davanti);

    double xd = player->camera->position[0];
    double yd = player->camera->position[1];
    double zd = player->camera->position[2];

    int x = round(xd);
    int y = round(yd);
    int z = round(zd);
    float i = 0.0f;
    float deltaI = 0.2f;
    while(checkInWorld(x, y, z) && !checkEsisteBlocco(world, x, y, z)){
        xd += davanti[0] * deltaI;
        yd += davanti[1] * deltaI;
        zd += davanti[2] * deltaI;
        x = round(xd);
        y = round(yd);
        z = round(zd);
        i += deltaI;
        if (i > MAX_PIAZZAMENTO_BLOCCHI){
            return;
        }
    }
    bloccoPuntato[0] = x;
    bloccoPuntato[1] = y;
    bloccoPuntato[2] = z;

    if (player->bloccoDaRompere[0] == -1 && player->bloccoDaRompere[1] == -1 && player->bloccoDaRompere[2] == -1){
        player->bloccoDaRompere[0] = bloccoPuntato[0];
        player->bloccoDaRompere[1] = bloccoPuntato[1];
        player->bloccoDaRompere[2] = bloccoPuntato[2];
        player->timeRotturaBlocco = state->deltaTime;
    } else {
        if (player->bloccoDaRompere[0] == bloccoPuntato[0] && player->bloccoDaRompere[1] == bloccoPuntato[1] && player->bloccoDaRompere[2] == bloccoPuntato[2]){
            player->timeRotturaBlocco += state->deltaTime;
        } else {
            player->timeRotturaBlocco = state->deltaTime;
            player->bloccoDaRompere[0] = bloccoPuntato[0];
            player->bloccoDaRompere[1] = bloccoPuntato[1];
            player->bloccoDaRompere[2] = bloccoPuntato[2];
        }
    }
}

void plantTree(GameState *state, int pos[3], unsigned char tex){
    World *world = state->world;
    if (!checkEsisteBlocco(world, pos[0], pos[1] - 1, pos[2])){
        printf("Non puoi piantare qui\n");
        return;
    }
    for (int y = pos[1]; y <= pos[1] + 8; y++){
        int blocco[3] = {pos[0], y, pos[2]};
        if (checkInWorld(blocco[0], blocco[1], blocco[2]) && !checkEsisteBlocco(world, pos[0], y, pos[2]) && !collisionPlayer(state->player->camera->position, blocco)){
            addCubeToWorld(world, blocco, tex);
        }
    }
    int latoFoglie = 1;
    for (int y = pos[1] + 4; y <= pos[1] + 5; y++, latoFoglie++){
        for (int x = pos[0] - latoFoglie; x <= pos[0] + latoFoglie; x++){
            for (int z = pos[2] - latoFoglie; z <= pos[2] + latoFoglie; z++){
                int blocco[3] = {x, y, z};
                if (checkInWorld(blocco[0], blocco[1], blocco[2]) && !checkEsisteBlocco(world, blocco[0], blocco[1], blocco[2]) && !collisionPlayer(state->player->camera->position, blocco)){
                    addCubeToWorld(world, blocco, TEX_LEAVES);
                }
            }
        }
    }
    for (int y = pos[1] + 6; y <= pos[1] + 8; y++, latoFoglie--){
        for (int x = pos[0] - latoFoglie; x <= pos[0] + latoFoglie; x++){
            for (int z = pos[2] - latoFoglie; z <= pos[2] + latoFoglie; z++){
                int blocco[3] = {x, y, z};
                if (checkInWorld(blocco[0], blocco[1], blocco[2]) && !checkEsisteBlocco(world, blocco[0], blocco[1], blocco[2]) && !collisionPlayer(state->player->camera->position, blocco)){
                    addCubeToWorld(world, blocco, TEX_LEAVES);
                }
            }
        }
    }
}

bool checkChunkInWorld(int x, int z){
    if (x - HALF_CHUNK_SIZE < -HALF_WORLD_SIZE || x + HALF_CHUNK_SIZE > HALF_WORLD_SIZE ||
        z - HALF_CHUNK_SIZE < -HALF_WORLD_SIZE || z + HALF_CHUNK_SIZE > HALF_WORLD_SIZE){
        return false;
    } else {
        return true;
    }
}

bool checkXZInWorld(int x, int z){
    if (x < -HALF_WORLD_SIZE || z < -HALF_WORLD_SIZE || x > HALF_WORLD_SIZE || z > HALF_WORLD_SIZE){
        return false;
    } else {
        return true;
    }
}

bool checkConfineWorld(int x, int z){
    if (x <= -HALF_WORLD_SIZE || x >= HALF_WORLD_SIZE || z <= -HALF_WORLD_SIZE || z >= HALF_WORLD_SIZE){
        return true;
    } else {
        return false;
    }
}

bool checkInWorld(int x, int y, int z){
    if (x < -HALF_WORLD_SIZE || x > HALF_WORLD_SIZE || z < -HALF_WORLD_SIZE || z > HALF_WORLD_SIZE || y < 0 || y > Y_MAX){
        return false;
    } else {
        return true;
    }
}

bool checkBloccoAdiacente(vec3 pos, int x, int y, int z){
    if (!checkInWorld(x, y, z)){
        return false;
    }
    int posy = round(pos[1]);
    int posx1 = round(pos[0]);
    int posz1 = round(pos[2]);
    int posx2, posz2;
    if (pos[0] - posx1 > 0){
        posx2 = posx1 + 1;
    } else if (pos[0] - posx1 < 0){
        posx2 = posx1 - 1;
    }
    if (pos[2] - posz1 > 0){
        posz2 = posz1 + 1;
    } else if (pos[2] - posz1 < 0){
        posz2 = posz1 - 1;
    }
    if ((y == posy || y == posy - 1) && (x == posx1 || x == posx2) && (z == posz1 || z == posz2)){
        return true;
    } else {
        return false;
    }
}

bool checkEsisteBlocco(World *world, int x, int y, int z){
    if (!checkInWorld(x, y, z)){
        //printf("Provi ad accedere ad un blocco fuori dal mondo\n");
        //printf("x: %d y: %d z: %d\n", x, y, z);
        return false;
    }
    int indice = getCube(x, y, z);
    if (world->cubes[getIndiceMondo(x, z)][getCube(x, y, z)] != NULL){
        return true;
    } else{
        return false;
    }
}

bool checkSbatteSotto(vec3 player, int c[3]){
    float x = player[0] - c[0];
    float z = player[2] - c[2];
    float y = player[1] - c[1] - 2;
    float l = LATO_PLAYER;
    if (x > -l && x < l && z > -l && z < l){
        if (y > - 0.5f && y < 0){
            return true;
        }
    }
    return false;
}

bool checkSbatteSopra(vec3 player, int c[3]){
    float x = player[0] - c[0];
    float z = player[2] - c[2];
    float y = c[1] - player[1] - 1;
    float l = LATO_PLAYER;
    if (x > -l && x < l && z > -l && z < l){
        if (y > - 0.5f && y < 0){
            return true;
        }
    }
    return false;
}

bool checkSbatteSottoMob(vec3 player, Mob *mob){
    float x = player[0] - mob->x;
    float z = player[2] - mob->z;
    float y = player[1] - mob->y - 3;
    float l = LATO_PLAYER;
    if (x > -l && x < l && z > -l && z < l){
        if (y > - 0.5f && y < 0){
            return true;
        }
    }
    return false;
}

bool checkSbatteSopraMob(vec3 player, Mob *mob){
    float x = player[0] - mob->x;
    float z = player[2] - mob->z;
    float y = mob->y - player[1] - 1;
    float l = LATO_PLAYER;
    if (x > -l && x < l && z > -l && z < l){
        if (y > - 0.5f && y < 0){
            return true;
        }
    }
    return false;
}

bool collisionMob(vec3 player, Mob *mob){
    float x = player[0] - mob->x;
    float z = player[2] - mob->z;
    float y = (player[1] - 0.5f) - (mob->y + 0.5f);
    float lxz = LATO_PLAYER;
    float ly = 2.0f;
    if (x > -lxz && x < lxz && y > -ly && y < ly && z > -lxz && z < lxz){
        return true;
    }
    return false;
}

bool collisionMobXZ(vec2 player, double xm, double zm){
    float x = player[0] - xm;
    float z = player[1] - zm;
    float lxz = LATO_PLAYER;
    if (x > -lxz && x < lxz && z > -lxz && z < lxz){
        return true;
    }
    return false;
}

bool collisionMobY(double py, double ym){
    float y = (py - 0.5f) - (ym + 0.5f);
    float ly = 2.0f;
    if (y > -ly && y < ly){
        return true;
    }
    return false;
}

bool collisionPlayer(vec3 player, int c[3]){
    float x = player[0] - c[0];
    float z = player[2] - c[2];
    float y = (player[1] - 0.5f) - c[1];
    float lxz = LATO_PLAYER;
    float ly = 1.5f;
    if (x > -lxz && x < lxz && y > -ly && y < ly && z > -lxz && z < lxz){
        return true;
    }
    return false;
}

bool collisionPlayerXZ(vec2 player, int cx, int cz){
    float x = player[0] - cx;
    float z = player[1] - cz;
    float lxz = LATO_PLAYER;
    if (x > -lxz && x < lxz && z > -lxz && z < lxz){
        return true;
    }
    return false;
}

bool collisionPlayerY(double py, int cy){
    float y = (py - 0.5f) - cy;
    float ly = 1.5f;
    if (y > -ly && y < ly){
        return true;
    }
    return false;
}

bool sopraMob(vec3 player, Mob *mob){
    float x = player[0] - mob->x;
    float z = player[2] - mob->z;
    float y = player[1] - mob->y - 3;
    float l = LATO_PLAYER;
    if (x > -l && x < l && z > -l && z < l){
        if (y > -ACCURACY_EQUAL && y < ACCURACY_EQUAL){
            return true;
        }
    }
    return false;
}

bool sopraCubo(vec3 player, int c[3]){
    //printf("xp %f yp %f zp %f x %d y %d z %d\n", player[0], player[1], player[2], c[0], c[1], c[2]);
    float x = player[0] - c[0];
    float z = player[2] - c[2];
    float y = player[1] - c[1] - 2;
    float l = LATO_PLAYER;
    if (x > -l && x < l && z > -l && z < l){
        if (y > -ACCURACY_EQUAL && y < ACCURACY_EQUAL){
            return true;
        }
    }
    return false;
}
