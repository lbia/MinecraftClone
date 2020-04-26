#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <pthread.h>

#include "global.h"
#include "world.h"
#include "perlin.h"

#define INT_FALSE 9999999

#define FPS_UPDATE 120
#define MAX_TIME_UPDATE 1.0f / FPS_UPDATE

#define LATO_PLAYER 0.8f
#define LATO_CUBE 1.0f

#define JUMP_VEL 5
#define GRAVITY 6

#define QUANTI_MONDI 3

#define TIME_ROTTURA_BLOCCO 0.8f

void initGameState(GameState *state);

void destroyGameState(GameState *state);

void updateGameState(GameState *state);

void processMouseScroll(GameState *state, double scorrimento);

void startJump(Player *player, float jumpSpeed, float yStart);

void endJump(Player *player, float yNew);

void updateWorld(World *world, int x, int y, int z);

/*Cube *getCubePointer(World *world, int x, int y, int z);*/

int getYMassima(World *world, int x, int z);

int getCoordinataMondo(int c);

int getIndiceMondo(int x, int z);

int getCube(int x, int y, int z);

int getOccupati(int x, int z);

int getChunk(int x, int z);

#endif // GAMESTATE_H_INCLUDED
