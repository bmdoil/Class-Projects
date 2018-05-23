#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <omp.h>
#include "simd.p5.h"



#define MINSIZE  1000
#define STEP     10000
#define MAXSIZE 320000
#define NUMTRIES 10

float* A = (float*)calloc(MAXSIZE, sizeof(float));
float* B = (float*)calloc(MAXSIZE, sizeof(float));
float* C = (float*)calloc(MAXSIZE, sizeof(float));

float randFloat(unsigned int *seed, float low, float high);
void fillArr(float *arr, int size);

int main() 
{
    #ifndef _OPENMP
        fprintf(stderr, "OpenMP is not available\n");
        return 1;
    #endif

    FILE *results = std::fopen("results.csv", "w");
    std::fprintf(results, "type,arrLength,time,attempt\n"); 

    
    int counter = MINSIZE;
    while (counter <= MAXSIZE) 
    {
        for (int i = 0; i < NUMTRIES; i++) 
        {
            
            int arrLen = counter;

            

            fillArr(A,arrLen);
            fillArr(B,arrLen);

            double time0 = omp_get_wtime();
            for (int j = 0; j < arrLen; j++) 
            {
                C[j] = A[j] * B[j];
            }
            double time1 = omp_get_wtime();
            std::fprintf(results, "%s, %d, %lf, %d\n","seqMul",arrLen,(time1-time0),i);
    
            time0 = omp_get_wtime();
            SimdMul(A, B, C, arrLen);
            time1 = omp_get_wtime();
            std::fprintf(results, "%s, %d, %lf, %d\n","simdMul",arrLen,(time1-time0),i);
    
           
            unsigned long long int sum = 0;
            time0 = omp_get_wtime();
            for (int j = 0; j < arrLen; j++) 
            {
                sum += A[j] * B[j];
            }
            time1 = omp_get_wtime();
            std::fprintf(results, "%s, %d, %lf, %d\n","seqMulRed",arrLen,(time1-time0),i);


            
            time0 = omp_get_wtime();
            double simdSum = SimdMulSum(A, B, arrLen);
            time1 = omp_get_wtime();
            std::fprintf(results, "%s, %d, %lf, %d\n","simdMulRed",arrLen,(time1-time0),i);

           
        }

        counter += STEP;
    }

    std::fclose(results);
    free(A);
    free(B);
    free(C);
    return 0;
}

void fillArr(float *arr, int size) {
	
	unsigned int seed = 0;

	for(int i = 0; i < size; i++)
		arr[i] = randFloat(&seed, -1., 1.);

}

float randFloat(unsigned int *seedp, float low, float high) {

	float r = (float) rand_r(seedp);

	return(low + r * (high - low) / (float) RAND_MAX);
}