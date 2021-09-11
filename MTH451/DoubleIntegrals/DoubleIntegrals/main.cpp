#include <cmath>
#include <cstdio>
#include <iostream>
#include "doubleinteg.h"
#define CLEANUP 5
#include "safealloc.h"
using std::cout;

double f1(double);
double f2(double);
double f11(double, double);

double a1(double);
double a2(double);
double a11(double, double);

double c3b(double);
double c3t(double);
double c11(double, double);

int main()
{
	double* ob = (double *)safe_calloc(2,sizeof(double));
	safe_realloc(0,6);
	ob[1] = 1;
	double (*ib[2])(double) = { &c3b, &c3t };
	printf("Result: %.7f", itersimpson2(ob,ib,c11, 4, 8));
	//double* test = (double*)safe_realloc(ob, 0);
	return leakcheck();
}

double c3b(double x)
{
	return x;
}
double c3t(double x)
{
	return 2 * x;
}
double c11(double x, double y)
{
	return x * x + y * y * y;
}

double f1(double x)
{
	return x * x * x;
}
double f2(double x)
{
	return x * x;
}
double f11(double x, double y)
{
	return exp(y/x);
}

double a1(double x)
{
	return 1.2;
}
double a2(double x)
{
	return 1.4;
}
double a11(double x, double y)
{
	return x* y* y;
}