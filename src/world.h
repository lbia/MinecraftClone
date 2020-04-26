#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "stdlib.h"
#include "global.h"
#include "camera.h"
#include "mob.h"

#define Y_MAX 254
#define ALTITUDE_STANDARD 62
#define ALT_SNOW 80
#define ALT_WATER 30

#define FREQ_ALT 30

#define HALF_CHUNK_SIZE 7
#define CHUNK_SIZE (2 * HALF_CHUNK_SIZE + 1)
#define HALF_CHUNK_NUMBER 20
#define CHUNK_NUMBER (2 * HALF_CHUNK_NUMBER + 1)

#define VIEW_BLOCKS ((HALF_CHUNK_NUMBER + 1) * CHUNK_SIZE + HALF_CHUNK_SIZE)

#define HALF_CHUNKS_IN_WORLD (HALF_CHUNK_NUMBER)
#define HALF_WORLD_SIZE (HALF_CHUNKS_IN_WORLD * CHUNK_SIZE + HALF_CHUNK_SIZE)
#define WORLD_SIZE (2 * HALF_WORLD_SIZE + 1)

#define HALF_UPDATE_CUBES_SIZE 2

#define HALF_MONDO_SIZE (5 * CHUNK_SIZE)
#define HALF_MONDI_MASSIMI 10
#define MONDI_MASSIMI (2 * HALF_MONDI_MASSIMI + 1)

//senza normal
//#define FLOAT_FACCIA 24
//con normal
#define FLOAT_FACCIA 36

//facce con normal
#define FACCIA_DAVANTI                                                      \
    {   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,       \
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,       \
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,       \
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f  }
#define FACCIA_DIETRO                                                       \
    {   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f, -1.0f,       \
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f, -1.0f,       \
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f, -1.0f,       \
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f, -1.0f  }
#define FACCIA_DESTRA                                                       \
    {    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f,  0.0f,  0.0f,       \
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f,  1.0f,  0.0f,  0.0f,       \
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,       \
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  1.0f,  1.0f,  0.0f,  0.0f  }
 #define FACCIA_SINISTRA                                                    \
    {   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f, -1.0f,  0.0f,  0.0f,       \
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f, -1.0f,  0.0f,  0.0f,       \
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  1.0f, -1.0f,  0.0f,  0.0f,       \
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  1.0f, -1.0f,  0.0f,  0.0f  }
#define FACCIA_SOPRA                                                        \
    {   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,  0.0f,       \
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,  0.0f,       \
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f,       \
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f  }
#define FACCIA_SOTTO                                                        \
    {   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  2.0f,  0.0f, -1.0f,  0.0f,       \
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  2.0f,  0.0f, -1.0f,  0.0f,       \
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  2.0f,  0.0f, -1.0f,  0.0f,       \
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  2.0f,  0.0f, -1.0f,  0.0f  }

/*#define FACCIA_DAVANTI                                 \
    {   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,       \
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f,       \
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  1.0f,       \
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  1.0f  }
#define FACCIA_DIETRO                                  \
    {   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f,       \
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f,       \
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,       \
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  1.0f  }
#define FACCIA_DESTRA                                  \
    {    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,       \
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f,       \
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,       \
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  1.0f  }
 #define FACCIA_SINISTRA                               \
    {   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  1.0f,       \
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  1.0f,       \
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  1.0f,       \
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  1.0f  }
#define FACCIA_SOPRA                                   \
    {   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,       \
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,       \
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,       \
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f  }
#define FACCIA_SOTTO                                   \
    {   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  2.0f,       \
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  2.0f,       \
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  2.0f,       \
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  2.0f  }*/

typedef struct{

    float **verSopraSotto;
    float **verDavanti;
    float **verDietro;
    float **verSinistra;
    float **verDestra;
    unsigned int *sizeSopraSotto;
    unsigned int *sizeDavanti;
    unsigned int *sizeDietro;
    unsigned int *sizeSinistra;
    unsigned int *sizeDestra;

    float **vertici;
    unsigned int *sizeVertici;
    unsigned int *sizeIndici;

} DrawStruct;

typedef struct{

    unsigned char tex;

} Cube;

typedef struct{

    DrawStruct *drawStruct;
    int x, z;

} Chunk;

typedef struct{

    Cube ***cubes;

    unsigned char ***occupati;

    int xUpdateInizio, xUpdateFine;
    int zUpdateInizio, zUpdateFine;
    int yUpdateInizio, yUpdateFine;

} World;

typedef struct{

    Camera *camera;

    vec2 newPositionCamera;
    int previusPosition[2];
    float nuovaPosizione[2];

    int bloccoDaRompere[3];
    float timeRotturaBlocco;

    bool inWater;

    bool shift;

    float y0, jumpSpeed;
    bool jump;
    double timeJump;

} Player;

typedef struct{

    Player *player;
    World *world;
    Mob *zombie;
    Slime *slime;

    BlockTexture *blockTextures;
    Texture *mobTextures;
    Texture *mouseTexture;
    Texture *slotTexture;
    Texture *waterTexture;

    Chunk **chunks;
    unsigned int *indici;
    unsigned int maxSizeIndici;

    Program *programWorld;

    bool creative;
    bool spazioPremuto;
    bool scendiPremuto;

    bool threadEsecuzione;

    bool leftPress;
    bool rightPress;

    int textureSelezionata;

    bool firstMouse;
    float lastX, lastY;

    float deltaTime, lastFrame;

} GameState;

Chunk *allocateChunk(int x, int z);

void freeChunk(Chunk *chunk);

int *getIndiceChunkDiPosizione(Chunk **chunks, int x, int z);

void initializeChunk(Chunk *chunk);

void setDrawStruct(GameState *state);

void setChunk(GameState *state, Chunk *chunk);

#endif // WORLD_H_INCLUDED
