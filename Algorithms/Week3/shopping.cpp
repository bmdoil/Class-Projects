#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int shoppingCost(int*, int*, int, int);
int familyMemberMax(int*, int*, int*, int, int);

int main(int argc, char* argv[]){

     int testCases;     
     int numItems;          

         

     int familySize;          
     

     ifstream in;
     ofstream out;

     // open input file
     in.open("shopping.txt");

     // error check input file

     if (!in.is_open()){
          cout << "can't open the file 'shopping.txt'" << endl;
          return 1;
     }   

     out.open("results.txt");

     // read the number of test cases 

     in >> testCases;

     // process testCases iterations

     for (int k = 0; k < testCases; k++){

        // read the number of items 
        in >> numItems;
        int prices[numItems];     
        int weights[numItems];

        // read the price and weight of each item into arrays

        for (int i = 0; i < numItems; i++){

            in >> prices[i];
            in >> weights[i];
        }        
          
        // read number of family members
        in >> familySize;
        int max[familySize];

        // find maximum price of items that can be carried by each family member and keep track the total of the maximum prices

        for (int j = 0; j < familySize; j++){

            // read the maximum weight that can be carried by current family member
              in >> max[j];

              // find maximum price of items that can be carried bycurrent family member and add it to maxPrice

              out << familyMemberMax(prices,weights,max,numItems,familySize) << endl;

          
          }
     }

     in.close();
     out.close();

     return 0;
}

// Returns the maximum price of items that can be carried by a person, given item weights, prices, number of items, and max weight person can carry
int shoppingCost(int weights[], int prices[], int numItems, int maxWeight){

     int result[numItems + 1][maxWeight + 1];
     // Build result table
     for (int i = 0; i <= numItems; i++){

          for (int j = 0; j <= maxWeight; j++){
              //Base case
              if (i == 0 || j == 0)

                   result[i][j] = 0;

              else if (weights[i - 1] <= j)
                   result[i][j] = max(prices[i - 1] + result[i - 1][j - weights[i - 1]], result[i - 1][j]);
              else
                   result[i][j] = result[i - 1][j];
          }
     }
    // result[numItems][maxWeight] represents the maximum price of items that can be carried by the family member
    return result[numItems][maxWeight];
}


int familyMemberMax(int prices[], int weights[], int max[], int numItems, int family);
{
   
    int totalPrice = 0;
    
    for (int i = 0; i < family; i++)
    {
        // Retrieve max price for current family member
        totalPrice += shoppingCost(price, weight, max[i], number);
    }
    return totalPrice;
}