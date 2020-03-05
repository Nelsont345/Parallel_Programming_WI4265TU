
#include <stdio.h>
//#include <mpi.h>
#include <math.h>
#define N 3



int main ( int argc, char** argv )
{
//double a[3][3] = {{1.0, 1.0, 0.0}, {1.0, 3.0, 1.0}, {2.0, -1.0, 1.0}};
double a[N][N] = {{1.0, 1.0, 2.0}, {1.0, 3.0, -1.0}, {0.0, 1.0, 1.0}};
double c[N];
double d[N];
double t;
int i, j, k;

//calculate orthogonal columns
for ( j = 0; j < N; j++)
{
    for ( k = 0; k < j; k++ )
    {c[k] = 0.0;
    d[k] = 0.0;

        for ( i = 0; i < N; i++ )
        {c[k] += a[i][k] * a[i][j];
        d[k] += a[i][k]* a[i][k];
        }
    //printf("row %d, %f \n", k, c[k]);
    //printf("row %d, %f \n", k, d[k]);
    }
    for ( k = 0; k < j; k++ )
    {
        for ( i = 0; i < N; i++ )
        {a[i][j] -= (c[k] * a[i][k])/d[k];
        }
    }
}
//Normalisation 
/*
for ( i = 0, t = 0.0; i < N; i++ )
{t += a[i][j] * a[i][j];
}


t = 1.0 / sqrt(t);
for ( i = 0; i < N; i++ )
{a[i][j] *= t;
}
*/

//print out columns
for (i=0; i < N; i++)
{
    for (j=0; j < N; j++ )
    {
        printf("%f ", a[i][j]);
    }
    printf("\n");
}

return 0;
}
