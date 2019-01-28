#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int shoppingCost(int*, int*, int, int, vector<int>&);

int main(int argc, char* argv[]){

     int testCases;     
     int numItems;          

     int prices[100];     
     int weights[100];     

     int familySize;          
     int maxWeight = 0;   

     vector<vector<int> > itemList(100);    

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

          // read the price and weight of each item into arrays

          for (int i = 0; i < numItems; i++){

              in >> prices[i];
              in >> weights[i];
          }

          int maxPrice = 0;
          
          // read number of family members
          in >> familySize;

          // find maximum price of items that can be carried by each family member and keep track the total of the maximum prices

          for (int j = 0; j < familySize; j++){

              // read the maximum weight that can be carried by current family member
              in >> maxWeight;

              // find maximum price of items that can be carried bycurrent family member and add it to maxPrice

              maxPrice = maxPrice + shoppingCost(weights, prices, numItems, maxWeight, itemList);

          }
          // Write the maximum total price to out
          out << "Test Case " << k << endl << "Total Price " << maxPrice << endl;    
          out << "Member Items" << endl;

          //Print items 

          for (f = 0; f < familySize; i++) {
              //Sort items for this family member
              sort(itemList[f].begin(), itemList[f].end());
              out << f + 1 << ":";
              for (g = 0; g < itemList.size(); j++)
              {
                  out << itemList[f][g] << " ";
              }
              out << endl;
          }


     }


     in.close();
     out.close();

     return 0;

}

// Returns the maximum price of items that can be carried by a person, given item weights, prices, number of items, and max weight person can carry
int shoppingCost(int weights[], int prices[], int numItems, int maxWeight, vector<int>& items)

{

     int result[numItems + 1][maxWeight + 1];

     // Build result table

     for (int i = 0; i <= numItems; i++)

     {

          for (int j = 0; j <= maxWeight; j++)

          {
              //Base case
              if (i == 0 || j == 0)

                   result[i][j] = 0;

              else if (weights[i - 1] <= j)

                   result[i][w] = max(prices[i - 1] + result[i - 1][j - weights[i - 1]], result[i - 1][j]);

              else

                   result[i][j] = result[i - 1][j];

          }

     }

    // result[numItems][maxWeight] represents the maximum price of items that can be carried by the family member
    int priceMax = result[numItems][maxWeight];
    int w = maxWeight;

    //Add to items vector
    for (int i = numItems; i > 0 && priceMax > 0; i--){
        if (priceMax == result[i - 1][w]) continue;
        else {
            items.push_back(i);
            priceMax = priceMax - prices[i - 1];
            w = w - weights[i - 1];
        }
    }

    return priceMax;

}
