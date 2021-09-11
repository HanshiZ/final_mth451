#include "doubleinteg.h"
#include "GaussianQuad.h"
#include <stdio.h>

double gaussianquad2(double* outer, double (*inner[])(double), double (*f)(double, double), int n, int m)
{
	double integral = 0;
	double halfdif = .5 * (outer[1] - outer[0]);
	double mid = .5 * (outer[0] + outer[1]);
	for (int i = 1; i <= m; ++i)
	{
		double xintegral = 0;
		double xval = halfdif * x(m, i) + mid;
		double y1 = midf(xval, inner);
		double y2 = midf(xval, inner, 1);
		for (int j = 1; j <= n; ++j)
		{
			double yval = y1 * x(n, j) + y2;
			xintegral = xintegral + c(n, j) * f(xval, yval);
		}
		double inner = c(m, i) * y1 * xintegral;
		printf("Inner integral evaluation %d: %.3f\n", i, inner * halfdif);
		integral = integral + inner;
	}
	return integral * halfdif;
}

double midf(double value, double (*funcs[]) (double), bool pos, double pieces)
{
	return (pos ? (funcs[1](value) + funcs[0](value)) : (funcs[1](value) - funcs[0](value))) / pieces;
}

double itersimpson2(double* outer, double (*inner[])(double), double (*f)(double, double), int n, int m)
{
	double inter = (outer[1] - *outer) / n;
	double ends = 0;
	double evens = 0;
	double odds = 0;
	for (int i = 0; i <= n; ++i)
	{
		double xval = *outer + i * inter;
		double xdif = midf(xval, inner, 0, (double)m);
		double xends = f(xval, inner[0](xval)) + f(xval, inner[1](xval));
		double xodds = 0;
		double xevens = 0;
		for (int j = 1; j < m; ++j)
			j % 2 ? xodds = xodds + f(xval, (*inner)(xval) + j * xdif)
			: xevens = xevens + f(xval, (*inner)(xval) + j * xdif);

		double strip = xdif * (xends + 2 * xevens + 4 * xodds) / 3;
		printf("Weighted integral from %.3f to %.3f for f(%.3f,y) dy = ", inner[0](xval), inner[1](xval), xval);
		printf("%.5f\n", inter * (strip / 3.0) * ((!i || i == n) ? 1.0 : double((i % 2) + 1.0) * 2 ));
		if (!i || i == n)
			ends = ends + strip;
		else if (i % 2)
			odds = odds + strip;
		else
			evens = evens + strip;
	}
	return inter * (ends + 2 * evens + 4 * odds) / 3;
}

double simpson2(double* outer, double (*inner[])(double), double (*f)(double, double), int m)
{
	double sum = 0;
	double half = .5 * (outer[1] - *outer);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			double line = (j * half) + outer[0];
			double dif = midf(line, inner, 0, (double)m);
			double bottom = inner[0](line) + dif * m;
			double top = bottom + dif;
			sum = sum + ((j == 1) ? 4 * simpson2line(line, bottom, top, f) : simpson2line(line, bottom, top, f));
		}
	}
	sum = sum * half / 3;
	printf("Integral bewtween %.3f, %.3f: %.5f\n", *outer, outer[1], sum);
	return sum;
}

double simpson2line(double cnst, double bot, double top, double (*f)(double, double))
{
	double mid = .5 * (bot + top);
	double sum = f(cnst, bot) + 4 * f(cnst, mid) + f(cnst, top);
	return mid * sum / 3;
}