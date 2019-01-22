#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>


using namespace std;


void mergeSort(int* arr, int n);
void merge(int* arr, int* low, int* high, int lowCount, int highCount);

int main()
{
    ifstream in;
    ofstream out;
    int size;
    string str;
    in.open("data.txt");
    out.open("merge.txt");

    in >> size;
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        in >> arr[i];
    }
    mergeSort(arr, size);

        
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
        mergeSort(arr, size);

        
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

