#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cstring>
#define NUM_MAX 10000

using namespace std;
using namespace std::chrono;

void mergeSort(int* arr, int len);
void mergeSort4(int* arr, int len);
void merge(int* arr, int mid, int len);


int main(int argc, char* argv[])
{
    unsigned seed;

    seed = time(NULL);
    srand(seed);
    
    int startSize;
    int iterations;
    int stepSize;
    
    if (argc != 4) {        
        cout << "Usage: merge4Time [startSize] [iterations] [stepSize]" << endl;
        return -1;

    }
    startSize = atoi(argv[1]);
    iterations = atoi(argv[2]);
    stepSize = atoi(argv[3]);
    int arrLen;
    int i, j;

    int* array;

    cout << "Merge4 sort:" << endl;
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
        mergeSort4(array, arrLen);
        auto stopTime = high_resolution_clock::now();
        auto timeElapsed = duration_cast<milliseconds>(stopTime - startTime);

        
        cout << arrLen << "\t" << timeElapsed.count() << endl;
        delete [] array;      
        
    }  
    
    return 0;
}

void merge(int* arr, int mid, int len){

    int i = 0;
    int j = mid;
    int k = 0;
    int tmp[len];

    while (i < mid && j < len) {
        tmp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
    }
    memcpy(tmp+k, arr+i, (mid - i) * sizeof *arr);
    memcpy(arr, tmp, (k + (mid - i)) * sizeof *arr);


}

void mergeSort(int* arr, int len)
{
    int mid;
    if (len < 2) return; //base case

    mid = len / 2; //mid index

    mergeSort(arr, mid);
    mergeSort(arr + mid, len - mid);
    merge(arr, mid, len);

}
void mergeSort4(int* arr, int len)
{
    if (len < 4)//base case
    { 
        mergeSort(arr, len);
        return;
    }
    //quartile indexes
    int m1 = len / 4;
    int m2 = len / 2;
    int m3 = len - m1;
    //merge sort on 4 subarrays
    mergeSort4(arr, m1);
    mergeSort4(arr + m1, m2 - m1);
    mergeSort4(arr + m2, m3 - m2);
    mergeSort4(arr + m3, len - m3);
    //merge 3 times
    merge(arr,m1,m2);
    merge(arr,m2,m3);
    merge(arr,m3,len);
    
}