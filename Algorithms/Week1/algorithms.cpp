#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

#define NUM_MAX 10000
#define DEF_ITER 5
using namespace std;
using namespace std::chrono;

void mergeSort(int* arr, int len);

void insertSort(int* A, int len) {
    //create indexes
    int i, j, key;

    //for j = 1 to len - 1
    for (j = 1; j < len; j++) {
        key = A[j];                     //set key to first unsorted value
        i = j - 1;                      //set i to last sorted value
        while (i >= 0 && A[i] > key) { //while valid index and value at index is > key
            A[i + 1] = A[i];            // move value of A[i] forward 1 place in array
            i--;                        // decrement index
        }
        A[i + 1] = key;                 //Place key in the open spot we created by moving forward all the values > key
    }                                   //Placed at i + 1 because i is either -1 (while loop false) or A[i] <= key
}


bool linearSearch(int* A, int len, int val) {
    for (int i = 0; i < len; i++) {
        if (A[i] == val) return true;
    }
    return false;
}

bool binarySearch(int* A, int len, int val) {
    //sort array using mergeSort
    mergeSort(A,len);
    int L = 0;
    int R = len - 1;
    int mid;
    while (L < R){
        mid = std::ceil( (L+R)/2 );
        if (L == R) return true;
        if (A[mid] < val) L = mid + 1;
        else if (A[mid] > val) R = mid;        
    }
    return false;    
}

//Returns pointer to the new array
//In: Two n-element arrays A and B containing binary digits of two numbers a and b
//Out: An n+1 element array C containing the binary digits of a + b
int* addBinary(int A[], int B[], int n) {
    int carry = 0, i = 1;
    int* C = new int[n + 1];
    for (i = 1; i <= n; i++) {
        C[i + 1] = ((A[i] + B[i] + carry) % 2); //remainder 
        carry = (A[i] + B[i] + carry) / 2;  //floor division results in carry of 0 or 1
    }
    C[i] = carry;
    return C; 
}

void selectSort(int* A, int len) {
    int min, j, i, tmp;
    for (j = 0; j < len - 1; j++) {
        min = j;
        for (i = j + 1; i < len; i++) {
            if (A[i] < A[min]) min = i;
        }
        tmp = A[min];
        A[min] = A[j];
        A[j] = tmp;
    }
}
void merge(int* arr, int mid, int len) {

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
void mergeSort(int* arr, int len) { 
    int mid;
    if (len < 2) return; //base case
    mid = len / 2; //mid index
    mergeSort(arr, mid);
    mergeSort(arr + mid, len - mid);
    merge(arr, mid, len);
}

int* randArr(int arrLen) {
    int* array = new int[arrLen];
    for (int j = 0; j < arrLen; j++) array[j] = rand() % NUM_MAX;
    return array;
}

template<typename Function>
void printSortTiming(int* A, int len, Function func) {    
    
    auto startTime = high_resolution_clock::now();
    func(A, len);
    auto stopTime = high_resolution_clock::now();
    auto timeElapsed = duration_cast<milliseconds>(stopTime - startTime);
    cout << len << "\t" << timeElapsed.count()<< endl;
}

template<typename Function>
void testTiming(int startSize, int iterations, Function sortFunc, string funcName) {

    for (int i = 1; i <= iterations; i++) {
        int arrLen = startSize * i;
        int* array = randArr(arrLen);
        if (i == 1) cout << funcName << " Timing\nn\tms\n";
        printSortTiming(array, arrLen, sortFunc);
        delete [] array;
    }
}

void printarr(int A[], int len) {
    for (int i = 0; i < len; i++) cout << A[i] << " ";
    cout << endl;
}

int main(int argc, char* argv[]) {

    int startSize, iterations;

    if (argc != 3) {
        cout << "Usage: algTest [startSize] [iterations]" << endl;
        return 1;
    }    
    
    startSize = atoi(argv[1]);        
    iterations = atoi(argv[2]);     
    
    testTiming(startSize, iterations, selectSort, "Select");
    testTiming(startSize, iterations, insertSort, "Insert");
    testTiming(startSize, iterations, mergeSort, "Merge");

    return 0;    
}