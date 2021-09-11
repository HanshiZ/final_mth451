
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

const double TOL = .0000000001;

void combine(double * r1, double * r2, double scalar, int n);
void printa(double * a , int n);
double ** doubleptrs(int r, int c);
void freeptrs(double ** ptrs,int n);
bool reduce(double ** matrix, double ** addon, int rows, int cols, bool pivot, bool down);
void identity(double ** zero, int n);
/*
int main() 
{
    double ** id = doubleptrs(4,4);
    double ** test = doubleptrs(4,4);
    identity(id,4);
    double a[] = {1.0,-2,0,3};
    double b[] = {-2,3,1,-6};
    double c[] = {-1,4,-4,3};
    double d[] = {5,-8,4,0};

    double *m[4] = {a,b,c,d};
    reduce(m,id,4,4,0,1);
    reduce(m,id,4,4,0,0);

    freeptrs(id,4);
    freeptrs(test,4);
    return 0;
}*/

int main() 
{
    double ** id = doubleptrs(2,2);
    double ** test = doubleptrs(4,4);
    id[0][0] = 59.2;
    id[1][0] = 47;
    double a[] = {58.9,.03,59.2};
    double b[] = {-6.10,5.31,47};


    double *m[] = {a,b};
    reduce(m,id,2,2,0,1);
    reduce(m,id,2,2,0,0);

    freeptrs(id,2);
    return 0;
}


void printa(double * a , int n)
{
    
    for(int i = 0; i < n; ++i)
        printf(" %.5f %s", a[i], i < n - 1 ? "&" : "\\\\ \n");
    
}

double ** doubleptrs(int r, int c)
{
    double ** ret = (double **) calloc(r, sizeof(double*));
    for(int i = 0; i < r; ++i)
        ret[i] = (double*) calloc(c, sizeof(double)); 
    return ret;
}

void freeptrs(double ** ptrs,int n)
{
    for(int i = 0; i < n; ++i)
        free(ptrs[i]);
    free(ptrs);
}


bool reduce(double ** matrix, double ** addon, int rows, int cols, bool pivot, bool down)
{
    static int operation = 0;
    for(int i = 0;i < rows ; ++i)
        printa(matrix[i],cols);
    printf("***\n");
    for(int i = 0; i< rows; ++i)
        printa(addon[i],cols);
    printf("***\n");
    for(int i = down ? 0 : rows -1; down ? i < rows : i; 
    down ? ++i : --i)
    {
        int maxloc = i;
        double max = fabs(matrix[i][i]);
        for(int j = i; down && ((pivot && j < rows) || !max) ;++j)
        {
            if (fabs(matrix[j][i]) > max)
            {
                maxloc = j;
                max = matrix[j][i];
            }
        }
        if (max < TOL)
            return 0;
        if(i != maxloc)
        {
            printf("Swap rows $E_%d: r_%d = r_%d$\n",++operation,i,maxloc);
            double * temp = *(matrix + maxloc);
            *(matrix + maxloc) = *(matrix + i);
            *(matrix + i) = temp;
            
            temp = *(addon + maxloc);
            *(addon + maxloc) = *(addon + i);
            *(addon + i) = temp;
        }
        double pivot = matrix[i][i];
        for(int j2 = down ? i + 1 : i - 1; 
        down ? j2 < rows : j2 > -1 ; down ? ++j2 : --j2)
        {
            double scalar = down ? matrix[j2][i] / pivot : matrix[j2][i] / pivot;
            printf("Combine rows $E_%d: r_%d = r_%d + %.5fr_%d$\n",++operation,j2,j2,-1*scalar,i);
            
            combine(*(matrix + i),*(matrix + j2),scalar,cols ), combine(*(addon + i), *(addon + j2),scalar, cols); 
            
        }
        printf("$\\begin{bmatrix}\n");
        for(int i = 0;i < rows ; ++i)
            printa(matrix[i],cols);
        printf("\\end{bmatrix}$\n");
        printf("$\\begin{bmatrix}\n");
        
        for(int i = 0; i< rows; ++i)
            printa(addon[i],cols);
        printf("\\end{bmatrix}$\n");
    }
     for(int i = 0; i< rows; ++i)
        printa(addon[i],cols);
    
    return 1;
}

void combine(double * r1, double * r2, double scalar, int n)
{
    for(int i = 0; i < n ; ++i)
       *(r2 + i) = *(r2 + i) - *(r1 + i) * scalar;
}
void identity(double ** zero, int n)
{
    for(;n;--n)
        zero[n-1][n-1] = 1;
}

void mult(double ** m1, double ** m2, double ** prod, int r, int n, int c)
{
    for(int i = 0 ; i < r; ++i)
    {
        for(int j = 0; j < c; ++j)
        {
            double sum = 0;
            for(int k = 0; k < n; ++k)
            {
                sum += m1[i][k] * m2[k][j];
            }
            prod[i][j] = sum;
        }
    }
}
