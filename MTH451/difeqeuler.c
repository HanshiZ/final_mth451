#include <math.h>
#include <stdio.h>
#define TOL .00001

double f(double, double);
double g(double, double);
double test(double, double);
double e(double, double);
double difeqeuler(const double * point, double leng, double end, double (*f) (double, double));

double modeuler(const double * point, double leng, double end, double (*f) (double, double));
double rungekutta4(const double * point, double leng, double end, double (*f) (double, double));

double p5(double, double);
double p11(double, double);
double e4(double, double);

int main()
{
    double p[2] = {1,2};
    rungekutta4(p,.5,2.0,e4);

    return 0;
}

double e4(double t, double y)
{
    return (1+t)/(1+y);
}

double test(double t, double y)
{
    double sum = 0;
    sum -= (1 + .2/3 + .04/12)*(.2*t);
    
    sum += 1 + .1 - .04/6 - .008/24;
    
    sum += (1 + .1 + .04/6 + .008/24) * (y - t * t);
    
    return sum;
}
double e(double t, double y)
{
    double sum = y*(y + 1) / t;
    printf("\n %.3f ",sum);
    sum += y*y*(y + 1) /(2*t*t);
    printf(" %.3f ",sum);
    sum += y*y*y*(y + 1) / (4*t*t*t);
    printf(" %.3f ",sum);
    sum += y*y*y*y*(y+1) / (8*t*t*t*t); 
    printf("%.3f\n",sum);
    return sum;
}

double p11(double x, double y)
{
    double f = -9.8 - .002 * y * fabs(y) / .11; 
    /*double var = y < 0 ? -1 * f * y * .004 / .11 :f * y * .004 / .11;
    return f + .05 * var;
    */
    return f;
}

double f(double x, double y)
{
    return y - x*x + 1;
}
double g(double x, double y)
{
    return 1 + (x-y)*(x-y);
}

double p5(double x, double y)
{
    return y * (1-y/x) / x + .05 * y*y* (2*y / x - 1) / (x*x*x);
}
double modeuler(const double * point, double leng, double end, double (*f) (double, double))
{
    double start = *point;
    double value = *(point + 1);
    for(int i = 0; start < end - TOL; start = start + leng, ++i)
    {
        printf("Iteration %d: y(%.1f) = %.3f\n",i,start,value);
        double next = (*f)(start,value);
        value = value + .5 * leng*(next + f(start + leng,value + leng*next)); 
    }
    printf("Final estimate: y(%.1f) = %.5f\n",start, value);
    return value;
}



double difeqeuler(const double * point, double leng, double end, double (*f) (double, double))
{
    double start = *point;
    double value = *(point + 1);
    for(int i = 0; start < end - TOL; start += leng, ++i)
    {
        printf("Iteration %d: y(%.1f) = %.5f\n",i,start,value);
        printf("f(%.1f, %.2f) = %.3f\n",start,value,(*f)(start,value));
        value += (*f)(start,value) * leng; 
    }
    printf("Final estimate: y(%.1f) = %.5f\n",start, value);
    return value;
}

double rungekutta4(const double * point, double leng, double end, double (*f) (double, double))
{
    double start = *point;
    double value = *(point + 1);
    double values[4] = {0};
    for(int i = 0; start < end - TOL; start = start + leng, ++i)
    {
        printf("Iteration %d: y(%.1f) = %.9f\n",i,start,value);
        for(int j = 0; j < 4; ++j)
        {
            double input;
            if (j == 3)
                input = f(start + leng, value + values[2]);
            else if (j)
                input = f(start + .5*leng, value + .5 *values[j-1]);
            else
                input = f(start,value);
            values[j] = leng * input; 
            printf("$K_%d = %.3f$\n",j+1,*(values+j));
        }
        value += (values[0] + 2* values[1] + 2*values[2] + values[3] )/ 6.0; 
    }
    printf("Final estimate: y(%.1f) = %.9f\n",start, value);
    return value;
}