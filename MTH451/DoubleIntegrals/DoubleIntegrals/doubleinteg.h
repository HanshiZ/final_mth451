#ifndef DOUBLEINTEG_H
#define DOUBLEINTEG_H

double midf(double value, double (*funcs[]) (double), bool pos = 0, double pieces = 2);
double itersimpson2(double* outer, double (*inner[])(double), double (*f)(double, double), int n, int m);
double simpson2(double* outer, double (*inner[])(double), double (*f)(double, double), int m = 1);
double gaussianquad2(double* outer, double (*inner[])(double), double (*f)(double, double), int n = 1, int m = 1);
double simpson2line(double cnst, double bot, double top, double (*f)(double, double));

#endif
