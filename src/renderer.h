#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <stdbool.h>

#include "program.h"
#include "gameState.h"
#include "texture.h"

#define SCALA_ORTHO 20

#define CONVERTER_FROM_RGBA 255.0f
#define CLEAR_COLOR 0.7725f, 0.9372f, 0.9686f, 1.0f

void clear();

void drawGui(Program *program, GameState *state);

void drawWordlChunkView(Program *program, GameState *state);

//void drawWordlChunk(Program *program, GameState *state);

#endif // RENDERER_H_INCLUDED
