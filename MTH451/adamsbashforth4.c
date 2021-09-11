#define TOL .00001
#include <stdio.h>
#include <math.h>

void adamsbashforth4(double x, double y, double end, double estimates[], int n, double (*f)(double, double));
double rungekutta4(double x, double y, double end, int n, double (*f) (double, double));

double f(double, double);

int main() 
{
    double est[12];
    adamsbashforth4(0,.5,2,est,10,f);
    
    return 0;
}

double f(double x, double y)
{
    return 1 + y - x * x; 
}

/**
 :x: and :y: are the starting point that we are given
 :end: is the ending x value for the algorithm
 :estimates: hold the values we estimated 
 :n: is the number of times we apply the algorithm
 :(*f): is the differential equation we are approximating
*/
void adamsbashforth4(double x, double y, double end, double estimates[], int n, double (*f)(double, double))
{
    double coeff[] = {55.0,-59.0,37.0,-9.0};
    double increment = (end - x) / n;
    estimates[0] = y;
    for(int i = 1; i <= n; ++i)
    {
        if (i < 4)
        {
            estimates[i] = rungekutta4(x,estimates[0],x+i*increment,i,f);
        }
        else
        {
            double new_y = coeff[0] * f(x+(i-1)*increment,estimates[i-1]) +
            coeff[1] * f(x+(i-2)*increment,estimates[i-2]) +
            coeff[2] * f(x+(i-3)*increment,estimates[i-3]) +
            coeff[3] * f(x+(i-4)*increment,estimates[i-4]);
            estimates[i] = estimates[i-1] + increment * new_y / 24;

        }
        printf("f(%.2f) = %.5f\n",x + i*increment, *(estimates + i) );
    }

}

double rungekutta4(double x, double y, double end, int n ,double (*f) (double, double))
{
    double start = x;
    double value = y;
    double values[4] = {0};
    double leng = (end - x)/n;
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
