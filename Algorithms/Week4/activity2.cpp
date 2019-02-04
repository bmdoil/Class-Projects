#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//main function

int main()

{

   //read the given file

   freopen("act.txt", "r", stdin);

   //declare the variable for at for activities

//st for start time and ft for finish time

   //sn for set number

   int tt = 1, at, st, ft, sn = 1;

   int i;

   while (cin >> tt)

   {

       //pair template using vector

       vector<pair<int, pair<int, int>>> p;

       for (i = 0; i < tt; ++i)

       {

           cin >> at >> st >> ft;

           p.push_back(make_pair(ft, make_pair(st, at)));     

       }

       //sort the activities

       sort(p.begin(), p.end());

       //initializes the last lt is 0

       int lt = 0;

       //declare the vector variable sd for selected Activities

       vector<int> sd;

       //push the selected activities

       sd.push_back(p[0].second.second);

       for (i = 1; i < tt; ++i)

       {

           if (p[i].second.first >= p[lt].first)

           {

               sd.push_back(p[i].second.second);

               lt = i;

           }

       }

       //print the given result

       cout << "Set " << sn << endl;

       cout << "Number of activities selected = " << sd.size() << "\n";

       cout << "Activities: ";

       for (int i:sd)

       {

           cout << i << " ";

       }

       cout << "\n";

       sn++;

   }

}

