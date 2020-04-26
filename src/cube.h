#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "cglm/cglm.h"

#include "gameState.h"

#define SLOT_LATO 1.5f
#define BORDO (SLOT_LATO / 3)

#define QUADRATO                                       \
    {   -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,  1.0f,       \
         0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  1.0f,       \
         0.5f,  0.5f,  0.0f,  1.0f, 1.0f,  1.0f,       \
        -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f  }

#define SMALL_QUADRATO                                 \
    {   -SLOT_LATO + BORDO, -SLOT_LATO + BORDO,  0.0f,  0.0f, 0.0f,  1.0f,       \
         SLOT_LATO - BORDO, -SLOT_LATO + BORDO,  0.0f,  1.0f, 0.0f,  1.0f,       \
         SLOT_LATO - BORDO,  SLOT_LATO - BORDO,  0.0f,  1.0f, 1.0f,  1.0f,       \
        -SLOT_LATO + BORDO,  SLOT_LATO - BORDO,  0.0f,  0.0f, 1.0f,  1.0f  }

#define SLOT_QUADRATO                                                   \
    {   -SLOT_LATO, -SLOT_LATO,  0.0f,  0.0f,     6.0f / 7,  1.0f,      \
         SLOT_LATO, -SLOT_LATO,  0.0f,  1.0f / 7, 6.0f / 7,  1.0f,      \
         SLOT_LATO,  SLOT_LATO,  0.0f,  1.0f / 7,     1.0f,  1.0f,      \
        -SLOT_LATO,  SLOT_LATO,  0.0f,  0.0f,         1.0f,  1.0f  }

#define SLOT_SELEZIONATO                                                   \
    {   -SLOT_LATO, -SLOT_LATO,  0.0f,  0.0f,     5.0f / 7,  1.0f,      \
         SLOT_LATO, -SLOT_LATO,  0.0f,  1.0f / 7, 5.0f / 7,  1.0f,      \
         SLOT_LATO,  SLOT_LATO,  0.0f,  1.0f / 7, 6.0f / 7,  1.0f,      \
        -SLOT_LATO,  SLOT_LATO,  0.0f,  0.0f,     6.0f / 7,  1.0f  }

#define CUBO_TEXTURE                                   \
     {  -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,      \
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,      \
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,      \
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,      \
                                                       \
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,      \
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,      \
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,      \
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f,      \
                                                       \
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,      \
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,      \
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,      \
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,      \
                                                       \
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,      \
        -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,      \
        -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,      \
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f,      \
                                                       \
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,      \
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,      \
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,      \
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,      \
                                                       \
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  2.0f,      \
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  2.0f,      \
         0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  2.0f,      \
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  2.0f }

#define INDICES_QUADRATO                        \
    {   0, 1, 2,                                \
        2, 3, 0,   }

#define INDICES_CUBO                            \
    {   0, 1, 2,                                \
        2, 3, 0,                                \
                                                \
        4, 5, 6,                                \
        6, 7, 4,                                \
                                                \
        8, 9, 10,                               \
        10, 11, 8,                              \
                                                \
        12, 13, 14,                             \
        14, 15, 12,                             \
                                                \
        16, 17, 18,                             \
        18, 19, 16,                             \
                                                \
        20, 21, 22,                             \
        22, 23, 20   }

#define ACCURACY_EQUAL 0.05f

#define MAX_PIAZZAMENTO_BLOCCHI 4

bool collisionMobY(double py, double ym);

bool collisionMob(vec3 player, Mob *mob);

bool collisionPlayer(vec3 player, int c[3]);

bool collisionPlayerXZ(vec2 player, int cx, int cz);

bool collisionPlayerY(double py, int cy);

bool sopraCubo(vec3 player, int c[3]);

bool checkSbatteSotto(vec3 player, int c[3]);

bool checkSbatteSopra(vec3 player, int c[3]);

//se x y z sono entro i limiti del mondo
bool checkChunkInWorld(int x, int z);

bool checkXZInWorld(int x, int z);

bool checkInWorld(int x, int y, int z);

bool checkConfineWorld(int x, int z);

//se alla posizione {x, y, z} esiste un blocco
bool checkEsisteBlocco(World *world, int x, int y, int z);

bool checkBloccoAdiacente(vec3 pos, int x, int y, int z);

void piazzaBlocco(GameState *state, unsigned char texture);

void puntaBloccoDaRompere(GameState *state);

void addCubeToWorld(World *world, int cube[3], unsigned char texture);

void removeCubeFromWorld(World *world, int cube[3]);

#endif // CUBE_H_INCLUDED
