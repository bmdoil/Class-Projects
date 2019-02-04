#include <iostream>
#include <cstdlib>

using namespace std;

void insertSort(int A[], int len) {
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


bool linearSearch(int A[], int len, int val) {
    for (int i = 0; i < len; i++) {
        if (A[i] == val) return true;
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