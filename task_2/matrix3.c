#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

double getTime(){
  struct timeval t;
  double sec, msec;
  
  while (gettimeofday(&t, NULL) != 0);
  sec = t.tv_sec;
  msec = t.tv_usec;
  
  sec = sec + msec/1000000.0;
  
  return sec;
}

int main (int argc, char *argv[])
{
    double t1, t2; 
    unsigned int N = 1000;
    unsigned int K = 8; // length of the block

    double **a = (double **)malloc(N * sizeof(double *));
    double **b = (double **)malloc(N * sizeof(double *));;
    double **c = (double **)malloc(N * sizeof(double *));

    for(int i = 0; i < N; i++)
    {
        a[i] = (double *)malloc(N * sizeof(double));
        b[i] = (double *)malloc(N * sizeof(double));
        c[i] = (double *)malloc(N * sizeof(double));
    }

    // initializing the arrays
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            a[i][j] = i + j;
            b[i][j] = j;
            c[i][j] = 0;
        }
    }

    t1 = getTime();
    /* code to be measured goes here */
    /***************************************/
    for(int i = 0; i < N; i+=K) {
        for(int j = 0; j < N; j+=K) {
            for(int k = 0; k < N; k+=K) {
                for(int ii = i; ii < min(i+K, N); ii++) {
                    for(int jj = j; jj < min(j+K, N); jj++) {
                        for(int kk = k; kk < min(k+K, N); kk++) {
                            c[ii][jj] = c[ii][jj] + a[ii][kk]*b[kk][jj];
                        }
                    }
                }
            }
        }
    }
    /***************************************/
	t2 = getTime(); 

    printf("time: %6.5f secs\n",(t2 - t1));
    printf("printing an element to prevent optimisation: %f\n", c[N/2][N/2]);

    free(a);
    free(b);
    free(c);
}