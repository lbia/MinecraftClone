#ifndef PERLIN_H_INCLUDED
#define PERLIN_H_INCLUDED

/* 90 linee noise */

double getPerlin2d(double x, double y, double freq, int depth);

void setPerlinSeed(int seed);

#endif // PERLIN_H_INCLUDED
