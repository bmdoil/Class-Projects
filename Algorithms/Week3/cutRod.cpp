//https://www.geeksforgeeks.org/cutting-a-rod-dp-13/
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <iostream>



int bottomUpCutRod(int price[], int len);
int topDownCutRod(int price[], int len);
int topDownCutRodAux(int price[], int len, int revenue[]);


int main() 
{ 
    int arr[] = {1, 5, 8, 9, 10, 17, 17, 20}; 
    int size = sizeof(arr)/sizeof(arr[0]);
    std::cout << "Bottom Up\n";
    printf("Maximum Obtainable Value is %d\n", bottomUpCutRod(arr, size));
    std::cout << "Top Down\n";
    printf("Maximum Obtainable Value is %d\n", topDownCutRod(arr, size));
    return 0; 
} 
/*
BOTTOM-UP-CUT-ROD(A, len)
let r[0 ... len] be a new array (size len + 1)
r[0] = 0
for j = 1 to len
    q = - 1 
        for i = 1 to j
            q = max(q, A[i] + r[j-i] )
        r[j] = q
return r[ len ]

*/
int bottomUpCutRod(int price[], int len) {
    int revenue[len + 1];
    int i, j, q;
    //std::cout << "j" << "  i" << "  max" << std::endl;
    revenue[0] = 0;
    for (j = 1; j <= len; j++) {
        q = INT_MIN;
        for (i = 0; i < j; i++) {
            q = std::max(q, price[i] + revenue[j - i - 1]);
        }
        revenue[j] = q;
        std::cout << "Revenue[" << j << "]" << revenue[j] << std::endl;
    }
    
    return revenue[len];
}

int topDownCutRod(int price[], int len) {
    int revenue[len + 1], i;
    for (i = 0; i <= len; i++) revenue[i] = INT_MIN;
    return topDownCutRodAux(price, len, revenue);
}

int topDownCutRodAux(int price[], int len, int revenue[]) {
    int q, i, val;
    if (revenue[len] >= 0) return revenue[len];
    if (len == 0) q = 0;
    else q = INT_MIN;
        for (i = 1; i <= len; i++) {
            q = std::max(q, price[i - 1] + topDownCutRodAux(price, len - i, revenue));             
            }
    revenue[len] = q;
    std::cout << "Revenue[" << len << "]" << revenue[len] << std::endl;
    return q;
}






