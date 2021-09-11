#ifndef GAUSSIANQUAD_H
#define GAUSSIANQUAD_H

#include <math.h>
#include <stdio.h>

#define MAX 5

static const double p1[1] = { 0.0 }; 
static const double w1[1] = { 2.0 };
static const double p2[2] = { pow(3,-0.5), -pow(3,-0.5)}; 
static const double w2[2] = { 1.0, 1.0 };
static const double p3[3] = { sqrt(.6),0,-sqrt(.6)}; 
static const double w3[3] = { 5.0 / 9, 8.0 / 9, 5.0 / 9};
static const double p4[4] = { sqrt(3.0/7 + (2.0/7*sqrt(6.0/5))),sqrt(3.0 / 7 - (2.0 / 7 * sqrt(6.0 / 5))),-sqrt(3.0 / 7 - (2.0 / 7 * sqrt(6.0 / 5))), -sqrt(3.0 / 7 + (2.0 / 7 * sqrt(6.0 / 5))) };
static const double w4[4] = { (18.0-sqrt(30.0))/36, (18.0 + sqrt(30.0)) / 36,(18.0 + sqrt(30.0)) / 36 , (18.0 - sqrt(30.0)) / 36 };
static const double p5[5] = { sqrt(5 + (2.0 * sqrt(10.0 / 7)))/3,sqrt(5 - (2.0 * sqrt(10.0 / 7))) / 3,0.0,-sqrt(5 - (2.0 * sqrt(10.0 / 7))) / 3,-sqrt(5 + (2.0 * sqrt(10.0 / 7))) / 3};
static const double w5[5] = { (322.0 - 13*sqrt(70.0))/900,(322.0 + 13 * sqrt(70.0)) / 900,128.0/225,(322.0 + 13 * sqrt(70.0)) / 900,(322.0 - 13 * sqrt(70.0)) / 900 };

const double* points[MAX] = {p1,p2,p3,p4,p5};
const double* weights[MAX] = { w1,w2,w3,w4,w5 };


double x(int n, int i)
{
	if (n > MAX) { printf("!Values not available!\n"); return -1;}
	if (i > n) { printf("!Invalid input!\n"); return -2; }
	return points[n-1][i-1];
}

double c(int n, int i)
{
	if (n > MAX) { printf("!Values not available!\n"); return -1; }
	if (i > n) { printf("!Invalid input!\n"); return -2; }
	return weights[n-1][i-1];
}

#endif
