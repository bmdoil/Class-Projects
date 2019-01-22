#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

#define NUM_MAX 10000

using namespace std;
using namespace std::chrono;


void mergeSort(int* arr, int n);
void merge(int* arr, int* low, int* high, int lowCount, int highCount);


int main(int argc, char* argv[])
{
    unsigned seed;

    seed = time(NULL);
    srand(seed);
    
    int startSize;
    int iterations;
    int stepSize;
    
    if (argc != 4) {        
        cout << "Usage: mergeTime [startSize] [iterations] [stepSize]" << endl;
        return -1;

    }
    startSize = atoi(argv[1]);
    iterations = atoi(argv[2]);
    stepSize = atoi(argv[3]);
    int arrLen;
    int i, j;

    int* array;

    cout << "Merge sort:" << endl;
    cout << "Array size (n) \t\t Time (ms)\n";

    for (i = 0; i < iterations; i++)
    {
        if (i == 0){
            arrLen = startSize;
        }
        else {
            arrLen = startSize + (i * stepSize);
        }
        array = new int[arrLen];
        for (j = 0; j < arrLen; j++)
            {
                array[j] = rand() % NUM_MAX;
            }

        auto startTime = high_resolution_clock::now();
        mergeSort(array, arrLen);
        auto stopTime = high_resolution_clock::now();
        auto timeElapsed = duration_cast<milliseconds>(stopTime - startTime);

        
        cout << arrLen << "\t" << timeElapsed.count() << endl;
        delete [] array;      
        
    }  
    
    return 0;
}

void merge(int* arr, int* low, int* high, int lowCount, int highCount){
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < lowCount && j < highCount) {
        if (low[i] < high[j]) arr[k++] = low[i++];
        else arr[k++] = high[j++];
    }
    while (i < lowCount) arr[k++] = low[i++];
    while (j < highCount) arr[k++] = high[j++];


}

void mergeSort(int* arr, int n)
{
    int mid, i, *low, *high;
    if (n < 2) return; //base case

    mid = n / 2; //mid index

    low = (int*)malloc(mid*sizeof(int));
    high = (int*)malloc((n-mid)*sizeof(int));

    for (i = 0; i < mid; i++) low[i] = arr[i]; //left subarray
    for (i = mid; i < n; i++) high[i - mid] = arr[i]; //right subarray

    mergeSort(low, mid);
    mergeSort(high, n - mid);
    merge(arr, low, high, mid, n - mid);
    free(low);
    free(high);
}

