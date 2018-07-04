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
        int pad[PADDING];
    } Array[4];
    
    omp_set_num_threads(NUMTHREADS);
    double time0 = omp_get_wtime();

    const long bigInt = 100000000;
    int i,j;
    #pragma omp parallel for default(none), shared(Array), private(j)
    for( int i = 0; i < 4; i++ ) {
        for( int j = 0; j < bigInt; j++ ) {
            Array[i].value = Array[i].value + 2.0;
        }
    }
    
    double time1 = omp_get_wtime();
    double performance = (4*bigInt)/(time1-time0)/1000000;
    std::printf("%d, %d, %lf, %ld\n", NUMTHREADS, PADDING, performance, bigInt);
    std::fprintf(results, "%d, %d, %lf, %ld\n", NUMTHREADS, PADDING, performance, bigInt);
    std:fclose(results); 

    return 0;
}