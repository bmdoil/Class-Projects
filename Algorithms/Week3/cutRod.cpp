//https://www.geeksforgeeks.org/cutting-a-rod-dp-13/
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <iostream>

int cutRod(int price[], int n);


int main() 
{ 
    int arr[] = {3, 5, 8, 9, 10, 17, 17, 20}; 
    int size = sizeof(arr)/sizeof(arr[0]); 
    printf("Maximum Obtainable Value is %d\n", cutRod(arr, size));
    return 0; 
} 
int cutRod(int price[], int n) {
    int val[n + 1];
    int i, j;
    std::cout << "j" << "  i" << "  max" << std::endl;
    for (i = 1; i <= n; i++) {
        
        int max_val = INT_MIN;
        for (j = 0; j < i; j++) {
            max_val = std::max(max_val, price[j] + val[i-j-1]);
            std::cout << j << "  " << i << "  " << max_val << std::endl;
            
        }
        val[i] = max_val;
        
        
    }
    return val[n];
}



