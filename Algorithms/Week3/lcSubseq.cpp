#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


int lcsDyn(std::string st1, std::string st2, int st1Len, int st2Len);

int main(int argc, char* argv[]) {

std::string string1(argv[1]);
std::string string2(argv[2]);


int result = lcsDyn(string1, string2, string1.length(), string2.length());

std::cout << result << std::endl;

return 0;
}

int lcsDyn(std::string st1, std::string st2, int st1Len, int st2Len) {

    std::vector<std::vector<int> > resultMatrix;

    resultMatrix.resize(st1Len + 1, std::vector<int>(st2Len + 1, 0));
    int max = 0;
    

    for (int i = 1; i < resultMatrix.size(); i++) {
        for (int j = 1; j < resultMatrix[i].size(); j++){
            if (st1[i-1] == st2[j-1]) {
                resultMatrix[i][j] = resultMatrix[i-1][j-1] + 1;
            }
            else
            {
                resultMatrix[i][j] = std::max(resultMatrix[i][j-1], resultMatrix[i-1][j]);
            }
            if (resultMatrix[i][j] > max) {
                max = resultMatrix[i][j];
            }
        }   
    }
    
    return max;
}