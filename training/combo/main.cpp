#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <set>
#include <unordered_set>

/*
ID: bmpringle
LANG: C++
TASK: combo
*/

void wrapAround(int& i, int lb, int ub) {
    if(i < lb) {
        i += ub;
    }

    if(i > ub) {
        i -= ub;
    }
}

int main() {
    std::ifstream input ("combo.in");
    std::ofstream output ("combo.out");

    std::vector<int> farmerCombination;
    std::vector<int> masterCombination;

    std::string buffer;
    std::getline(input, buffer);
    int N = std::stoi(buffer);

    std::getline(input, buffer);
    std::stringstream bufferStream1 (buffer);

    std::getline(bufferStream1, buffer, ' ');
    farmerCombination.push_back(std::stoi(buffer));

    std::getline(bufferStream1, buffer, ' ');
    farmerCombination.push_back(std::stoi(buffer));

    std::getline(bufferStream1, buffer, ' ');
    farmerCombination.push_back(std::stoi(buffer));

    std::getline(input, buffer);
    std::stringstream bufferStream2 (buffer);

    std::getline(bufferStream2, buffer, ' ');
    masterCombination.push_back(std::stoi(buffer));

    std::getline(bufferStream2, buffer, ' ');
    masterCombination.push_back(std::stoi(buffer));

    std::getline(bufferStream2, buffer, ' ');
    masterCombination.push_back(std::stoi(buffer));

    std::set<std::vector<int>> validCombinations;

    for(int i = -2; i < 3; ++i) {
        for(int j = -2; j < 3; ++j) {
            for(int k = -2; k < 3; ++k) {
                int _if = farmerCombination[0] + i;
                int _jf = farmerCombination[1] + j;
                int _kf = farmerCombination[2] + k;

                int _im = masterCombination[0] + i;
                int _jm = masterCombination[1] + j;
                int _km = masterCombination[2] + k;

                wrapAround(_if, 1, N);
                wrapAround(_jf, 1, N);
                wrapAround(_kf, 1, N);

                wrapAround(_im, 1, N);
                wrapAround(_jm, 1, N);
                wrapAround(_km, 1, N);

                if(_if <= N && _jf <= N && _kf <= N && _if > 0 && _jf > 0 && _kf > 0) {
                    validCombinations.insert({_if, _jf, _kf});
                }

                if(_im <= N && _jm <= N && _km <= N && _im > 0 && _jm > 0 && _km > 0) {
                    validCombinations.insert({_im, _jm, _km});
                }
            }
        }
    }

    std::string outputString = std::to_string(validCombinations.size()) + "\n";

    output.write(outputString.data(), outputString.size());

    return 0;
}