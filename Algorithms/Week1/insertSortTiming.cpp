#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

#define NUM_MAX 10000

using namespace std;
using namespace std::chrono;


void insertSort(int arr[], int n);


int main(int argc, char* argv[])
{
    unsigned seed;
    int startSize;
    int iterations;
    int stepSize;
    seed = time(NULL);
    srand(seed);
    if (argc != 4) {        
        cout << "Usage: insertTime [startSize] [iterations] [stepSize]" << endl;
        return -1;
    }
    startSize = atoi(argv[1]);
    iterations = atoi(argv[2]);
    stepSize = atoi(argv[3]);
    int arrLen;
    int i, j;

    int* array;

    cout << "Insertion sort:" << endl;
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
        insertSort(array, arrLen);
        auto stopTime = high_resolution_clock::now();
        auto timeElapsed = duration_cast<milliseconds>(stopTime - startTime);

        
       cout << arrLen << "\t" << timeElapsed.count() << endl;
        delete [] array;      
        
    }  
    
    return 0;
}

void insertSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
    key = arr[i];
    j = i-1;
    while (j >= 0 && arr[j] > key)
    {
        arr[j+1] = arr[j];
        j = j-1;
    }
        arr[j+1] = key;
    }
}

