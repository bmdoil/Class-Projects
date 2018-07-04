#include <math.h>
#include <omp.h> 
#include <iostream>
#include <cstdlib>
#include <cstdio>


int main(int argc, char *argv[]) {
    #ifndef _OPENMP
        fprintf(stderr, "OpenMP is not available\n");
        return 1;
    #endif
    FILE *results = std::fopen(argv[1], "a");   
  
    struct s {
        float value;
    } Array[4];
   
               
    omp_set_num_threads(NUMTHREADS);
    double time0 = omp_get_wtime();

    const long bigInt = 100000000;
    int i,j;
    #pragma omp parallel for default(none), shared(Array), private(j)
    for( int i = 0; i < 4; i++ ) {
        int sum = Array[i].value;
        for( int j = 0; j < bigInt; j++ ) {
                sum += 2.0;
            }
            Array[i].value = sum;
        }
           
    double time1 = omp_get_wtime();
    double performance = (4*bigInt)/(time1-time0)/1000000; 
    std::printf("%d, %lf, %ld\n", NUMTHREADS, performance, bigInt);
    std::fprintf(results, "%d, %lf, %ld\n", NUMTHREADS, performance, bigInt);
    std:fclose(results);             

    return 0;
}