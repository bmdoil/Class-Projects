#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;


void insertSort(int arr[], int n);


int main()
{
    ifstream in;
    ofstream out;
    int size;
    string str;
    in.open("data.txt");
    out.open("insert.txt");

    in >> size;
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        in >> arr[i];
    }
    insertSort(arr, size);

        
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
        insertSort(arr, size);

        
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

