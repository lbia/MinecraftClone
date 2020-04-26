#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/* 648 linee engine */

#include "stdbool.h"
#include "GL/glew.h"

#define NUMERO_MOB_TEXTURES 2
#define MOB_ZOMBIE 0
#define MOB_SLIME 1

#define NUMERO_TEXTURES 11
#define TEX_GRASS 0
#define TEX_STONE 1
#define TEX_LEAVES 2
#define TEX_WOOD 3
#define TEX_SNOW 4
#define TEX_COBBLESTONE 5
#define TEX_SAND 6
#define TEX_DIRT 7
#define TEX_BIRCH 8
#define TEX_SLIME 9
#define TEX_WATER 10

#define ASSERT(x) if (!(x)) exit(-1);
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

#endif // UTILS_H_INCLUDED
