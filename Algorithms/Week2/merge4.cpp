#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

void mergeSort(int* arr, int len);
void mergeSort4(int* arr, int len);
void merge(int* arr, int mid, int len);

int main()
{
    ifstream in;
    ofstream out;
    int size;
    string str;
    in.open("data.txt");
    out.open("merge4.txt");

    in >> size;
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        in >> arr[i];
    }
    mergeSort4(arr, size);

        
    for (int i = 0; i < size; i++)
    {
        out << arr[i] << " ";
    }
    out << endl;        

    while (getline(in, str)){
        in >> size;
        int arr[size];
        for (int i = 0; i < size; i++)
        {
            in >> arr[i];
        }
        mergeSort4(arr, size);

        
        for (int i = 0; i < size; i++)
        {
            out << arr[i] << " ";
        }
        out << endl;
    }    
    in.close();
    out.close();
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

