#ifdef _cplusplus
extern "C"{
#endif
#ifndef SYSTEMSOLVER_H
#define SYSTEMSOLVER_H
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
void printa(double * a, int);
double ** doubleptrs(int r, int c);

void freeptrs(double **,int n);

bool solve(double ** matrix, double * solutions, int rows, int cols);

bool reduce(double ** matrix, int rows, int cols);

void combine(double * r1, double * r2, double scalar, int n);


#endif
#ifdef _cplusplus
};
#endif