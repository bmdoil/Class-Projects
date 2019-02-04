
#include <iostream>
#include <vector>

using namespace std;


int main() {

    //read file
    freopen("act.txt", "r", stdin);

    int tot = 1, act, startTime, finishTime, setNum = 1;
    int i;


    while (cin >> tot) {
        //Use vector pair syntax to implement Set. Vectors make this much easier than multi-d arrays
        vector<pair<int, pair<int, int> > > Activities;
        for (i = 0; i < tot; ++i) {
            cin >> act >> startTime >> finishTime;
            //Set finish time as the index to sort over
            Activities.push_back(make_pair(finishTime, make_pair(startTime, act)));
        }
        //sort on finish time
        sort(Activities.begin(), Activities.end());

        int lastSelected = 0;

        vector<int> selectedAct;
        //Push first activity onto selectedAct
        selectedAct.push_back(Activities[0].second.second);
        //Push activities that meet the criteria of startTime >= finishTime of lastSelected
        for (i = 1; i < tot; ++i) {
            if (Activities[i].second.first >= Activities[lastSelected].first) {
                selectedAct.push_back(Activities[i].second.second);
                lastSelected = i;
            }
        }

        cout << "Set: " << setNum << endl;
        cout << "Num of activities: " << selectedAct.size() << endl;
        cout << "Activities: ";
        for (int i:selectedAct) {
            cout << i << " ";
        }
        cout << endl;
        setNum++;
    }
}
