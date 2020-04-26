#ifndef MOB_H_INCLUDED
#define MOB_H_INCLUDED

#include "program.h"
#include "texture.h"

#define LUNGHEZZA_TEX 64.0f
#define LENGHT_QUADRETTO 8.0f
#define H_CORPO 12.0f
#define W_CORPO 4.0f
#define LATO_SOTTO 4.0f

#define MOL_MOB 0.8f

#define FACCE_ZOMBIE 26

#define ZOMBIE_TEXTURE                                                                                                                                      \
    {   -0.25f, 1.5f - 0.5f,  0.25f, (1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,                 \
         0.25f, 1.5f - 0.5f,  0.25f, (2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,                 \
         0.25f, 1.5f       ,  0.25f, (2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,                 \
        -0.25f, 1.5f       ,  0.25f, (1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,                 \
                                                                                                                                                            \
        -0.25f,        1.5f,  0.25f, (1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                 \
         0.25f,        1.5f,  0.25f, (2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                 \
         0.25f,        1.5f, -0.25f, (2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 0 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                 \
        -0.25f,        1.5f, -0.25f, (1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 0 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                 \
                                                                                                                                                            \
        -0.25f, 1.5f - 0.5f, -0.25f, (0 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,                 \
        -0.25f, 1.5f - 0.5f,  0.25f, (1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,                 \
        -0.25f, 1.5f       ,  0.25f, (1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,                 \
        -0.25f, 1.5f       , -0.25f, (0 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,                 \
                                                                                                                                                            \
         0.25f, 1.5f - 0.5f,  0.25f, (2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,                 \
         0.25f, 1.5f - 0.5f, -0.25f, (3 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,                 \
         0.25f, 1.5f       , -0.25f, (3 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,                 \
         0.25f, 1.5f       ,  0.25f, (2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,                 \
                                                                                                                                                            \
        -0.25f, 1.5f - 0.5f, -0.25f, (3 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,                 \
         0.25f, 1.5f - 0.5f, -0.25f, (4 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,                 \
         0.25f, 1.5f       , -0.25f, (4 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,                 \
        -0.25f, 1.5f       , -0.25f, (3 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,                 \
                                                                                                                                                            \
        -0.25f, 1.5f - 0.5f,  0.25f, (2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                 \
         0.25f, 1.5f - 0.5f,  0.25f, (3 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 1 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                 \
         0.25f, 1.5f - 0.5f, -0.25f, (3 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 0 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                 \
        -0.25f, 1.5f - 0.5f, -0.25f, (2 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 0 * LENGHT_QUADRETTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                 \
                                                                                                                                                            \
        -0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, ( 5 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,   \
         0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, ( 7 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,   \
         0.25f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, ( 7 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,   \
        -0.25f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, ( 5 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,   \
                                                                                                                                                            \
         -0.5f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (10 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,    \
         -0.5f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,    \
         -0.5f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,    \
         -0.5f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (10 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,    \
                                                                                                                                                            \
          0.5f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  1.0f,  0.0f,  0.0f,    \
          0.5f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  1.0f,  0.0f,  0.0f,    \
          0.5f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  1.0f,  0.0f,  0.0f,    \
          0.5f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  1.0f,  0.0f,  0.0f,    \
                                                                                                                                                            \
        -0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, ( 8 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
         0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (10 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
         0.25f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (10 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
        -0.25f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, ( 8 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
                                                                                                                                                            \
         -0.5f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
        -0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
        -0.25f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
         -0.5f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
                                                                                                                                                            \
         0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
          0.5f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
          0.5f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
         0.25f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
                                                                                                                                                            \
         -0.5f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
        -0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (14 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
        -0.25f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (14 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
         -0.5f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
                                                                                                                                                            \
         0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
          0.5f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (14 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
          0.5f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (14 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
         0.25f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
                                                                                                                                                            \
        -0.25f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 1 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
          0.0f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
          0.0f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
        -0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, ( 1 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
                                                                                                                                                            \
          0.0f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 1 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
         0.25f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
         0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
          0.0f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, ( 1 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f,  1.0f,    \
                                                                                                                                                            \
        -0.25f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 0 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  1.0f,  0.0f,  0.0f,    \
        -0.25f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 1 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  1.0f,  0.0f,  0.0f,    \
        -0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, ( 1 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  1.0f,  0.0f,  0.0f,    \
        -0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, ( 0 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  1.0f,  0.0f,  0.0f,    \
                                                                                                                                                            \
         0.25f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,    \
         0.25f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,    \
         0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,    \
         0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f, -1.0f,  0.0f,  0.0f,    \
                                                                                                                                                            \
        -0.25f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
          0.0f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 4 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
          0.0f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, ( 4 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
        -0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
                                                                                                                                                            \
          0.0f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
         0.25f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 4 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 1 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
         0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, ( 4 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
          0.0f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO - 0 * H_CORPO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  0.0f, -1.0f,    \
                                                                                                                                                            \
         -0.5f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                  \
        -0.25f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                  \
        -0.25f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                  \
         -0.5f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                  \
                                                                                                                                                            \
         0.25f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                  \
          0.5f * MOL_MOB,  1.0f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                  \
          0.5f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                  \
         0.25f * MOL_MOB,  1.0f, -0.25f * MOL_MOB, (11 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f,  1.0f,  0.0f,                  \
                                                                                                                                                            \
         -0.5f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
        -0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
        -0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
         -0.5f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
                                                                                                                                                            \
         0.25f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
          0.5f * MOL_MOB, 0.25f,  0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
          0.5f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (13 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
         0.25f * MOL_MOB, 0.25f, -0.25f * MOL_MOB, (12 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
                                                                                                                                                            \
        -0.25f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
          0.0f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
          0.0f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
        -0.25f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
                                                                                                                                                            \
          0.0f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
         0.25f * MOL_MOB, -0.5f,  0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO - LATO_SOTTO) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
         0.25f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 3 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
          0.0f * MOL_MOB, -0.5f, -0.25f * MOL_MOB, ( 2 * W_CORPO) / LUNGHEZZA_TEX, (LUNGHEZZA_TEX - 2 * LENGHT_QUADRETTO             ) / LUNGHEZZA_TEX,  1.0f,  0.0f, -1.0f,  0.0f,                  \
                                                                                                                                                            \
    }

#define ACQUA_CUBO                                     \
     {  -0.5f, -0.5f,  0.5f,  0.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f, -0.5f,  0.5f,  1.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f,  0.5f,  0.5f,  1.0f,                 1.0f,  1.0f,      \
        -0.5f,  0.5f,  0.5f,  0.0f,                 1.0f,  1.0f,      \
                                                       \
        -0.5f, -0.5f, -0.5f,  0.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f, -0.5f, -0.5f,  1.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f,  0.5f, -0.5f,  1.0f,                 1.0f,  1.0f,      \
        -0.5f,  0.5f, -0.5f,  0.0f,                 1.0f,  1.0f,      \
                                                       \
         0.5f, -0.5f,  0.5f,  0.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f, -0.5f, -0.5f,  1.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f,  0.5f, -0.5f,  1.0f,                 1.0f,  1.0f,      \
         0.5f,  0.5f,  0.5f,  0.0f,                 1.0f,  1.0f,      \
                                                       \
        -0.5f, -0.5f, -0.5f,  0.0f,  (512 - 16) / 512.0f,  1.0f,      \
        -0.5f, -0.5f,  0.5f,  1.0f,  (512 - 16) / 512.0f,  1.0f,      \
        -0.5f,  0.5f,  0.5f,  1.0f,                 1.0f,  1.0f,      \
        -0.5f,  0.5f, -0.5f,  0.0f,                 1.0f,  1.0f,      \
                                                       \
        -0.5f,  0.5f,  0.5f,  0.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f,  0.5f,  0.5f,  1.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f,  0.5f, -0.5f,  1.0f,                 1.0f,  1.0f,      \
        -0.5f,  0.5f, -0.5f,  0.0f,                 1.0f,  1.0f,      \
                                                       \
        -0.5f, -0.5f,  0.5f,  0.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f, -0.5f,  0.5f,  1.0f,  (512 - 16) / 512.0f,  1.0f,      \
         0.5f, -0.5f, -0.5f,  1.0f,                 1.0f,  1.0f,      \
        -0.5f, -0.5f, -0.5f,  0.0f,                 1.0f,  1.0f }

//con normal
#define ACQUA_FACCIA_DAVANTI                                            \
    {   -0.5f, -0.5f,  0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,  0.0f,  0.0f,  1.0f,         \
         0.5f, -0.5f,  0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,  0.0f,  0.0f,  1.0f,         \
         0.5f,  0.5f,  0.5f,  1.0f,                1.0f,  1.0f,  0.0f,  0.0f,  1.0f,         \
        -0.5f,  0.5f,  0.5f,  0.0f,                1.0f,  1.0f,  0.0f,  0.0f,  1.0f  }
#define ACQUA_FACCIA_DIETRO                                                                  \
    {   -0.5f, -0.5f, -0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,  0.0f,  0.0f, -1.0f,         \
         0.5f, -0.5f, -0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,  0.0f,  0.0f, -1.0f,         \
         0.5f,  0.5f, -0.5f,  1.0f,                1.0f,  1.0f,  0.0f,  0.0f, -1.0f,         \
        -0.5f,  0.5f, -0.5f,  0.0f,                1.0f,  1.0f,  0.0f,  0.0f, -1.0f  }
#define ACQUA_FACCIA_DESTRA                                                                  \
    {    0.5f, -0.5f,  0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,  1.0f,  0.0f,  0.0f,         \
         0.5f, -0.5f, -0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,  1.0f,  0.0f,  0.0f,         \
         0.5f,  0.5f, -0.5f,  1.0f,                1.0f,  1.0f,  1.0f,  0.0f,  0.0f,         \
         0.5f,  0.5f,  0.5f,  0.0f,                1.0f,  1.0f,  1.0f,  0.0f,  0.0f  }
 #define ACQUA_FACCIA_SINISTRA                                                               \
    {   -0.5f, -0.5f, -0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f, -1.0f,  0.0f,  0.0f,         \
        -0.5f, -0.5f,  0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f, -1.0f,  0.0f,  0.0f,         \
        -0.5f,  0.5f,  0.5f,  1.0f,                1.0f,  1.0f, -1.0f,  0.0f,  0.0f,         \
        -0.5f,  0.5f, -0.5f,  0.0f,                1.0f,  1.0f, -1.0f,  0.0f,  0.0f  }
#define ACQUA_FACCIA_SOPRA                                                                   \
    {   -0.5f,  0.5f,  0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,  0.0f,  1.0f,  0.0f,         \
         0.5f,  0.5f,  0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,  0.0f,  1.0f,  0.0f,         \
         0.5f,  0.5f, -0.5f,  1.0f,                1.0f,  1.0f,  0.0f,  1.0f,  0.0f,         \
        -0.5f,  0.5f, -0.5f,  0.0f,                1.0f,  1.0f,  0.0f,  1.0f,  0.0f  }
#define ACQUA_FACCIA_SOTTO                                                                   \
    {   -0.5f, -0.5f,  0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,  0.0f, -1.0f,  0.0f,         \
         0.5f, -0.5f,  0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,  0.0f, -1.0f,  0.0f,         \
         0.5f, -0.5f, -0.5f,  1.0f,                1.0f,  1.0f,  0.0f, -1.0f,  0.0f,         \
        -0.5f, -0.5f, -0.5f,  0.0f,                1.0f,  1.0f,  0.0f, -1.0f,  0.0f  }

/*#define ACQUA_FACCIA_SOPRA                                              \
    {   -0.5f,  0.5f,  0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f,  0.5f,  0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f,  0.5f, -0.5f,  1.0f,                1.0f,  1.0f,         \
        -0.5f,  0.5f, -0.5f,  0.0f,                1.0f,  1.0f  }
#define ACQUA_FACCIA_SOTTO                                              \
    {   -0.5f, -0.5f,  0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f, -0.5f,  0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f, -0.5f, -0.5f,  1.0f,                1.0f,  1.0f,         \
        -0.5f, -0.5f, -0.5f,  0.0f,                1.0f,  1.0f  }
#define ACQUA_FACCIA_DAVANTI                                            \
    {   -0.5f, -0.5f,  0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f, -0.5f,  0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f,  0.5f,  0.5f,  1.0f,                1.0f,  1.0f,         \
        -0.5f,  0.5f,  0.5f,  0.0f,                1.0f,  1.0f  }
#define ACQUA_FACCIA_DIETRO                                             \
    {   -0.5f, -0.5f, -0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f, -0.5f, -0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f,  0.5f, -0.5f,  1.0f,                1.0f,  1.0f,         \
        -0.5f,  0.5f, -0.5f,  0.0f,                1.0f,  1.0f  }
#define ACQUA_FACCIA_DESTRA                                             \
    {    0.5f, -0.5f,  0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f, -0.5f, -0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,         \
         0.5f,  0.5f, -0.5f,  1.0f,                1.0f,  1.0f,         \
         0.5f,  0.5f,  0.5f,  0.0f,                1.0f,  1.0f  }
 #define ACQUA_FACCIA_SINISTRA                                          \
    {   -0.5f, -0.5f, -0.5f,  0.0f, (512 - 16) / 512.0f,  1.0f,         \
        -0.5f, -0.5f,  0.5f,  1.0f, (512 - 16) / 512.0f,  1.0f,         \
        -0.5f,  0.5f,  0.5f,  1.0f,                1.0f,  1.0f,         \
        -0.5f,  0.5f, -0.5f,  0.0f,                1.0f,  1.0f  }*/


typedef struct{

    float x, y, z;

    float dir[2];

    unsigned char type;

} Mob;

typedef struct{

    float x, y, z;

} Zombie;

typedef struct{

    float x, y, z;

} Slime;

void normalizeVec2(float vec[2]);

void drawZombie(Program *program, Texture *textures, Mob *zombie);

void drawSlime(Program *program, BlockTexture *blockTextures, Slime *slime);

#endif // MOB_H_INCLUDED
