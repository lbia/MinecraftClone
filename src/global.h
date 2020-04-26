#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

/* 3272 linee */
/* 4010 in tutto 30/11/2019 */

#include "utils.h"

#define WIDTH 900
#define HEIGHT 600

#define SIZE_INDICI_QUADRATO (6 * sizeof(unsigned int))
#define SIZE_INDICI_CUBO (6 * SIZE_INDICI_QUADRATO)

#define SIZE_FACCIA (FLOAT_FACCIA * sizeof(float))
#define SIZE_CUBO (6 * SIZE_FACCIA)

#define PIANTA_ALBERO -1

#endif // GLOBAL_H_INCLUDED
