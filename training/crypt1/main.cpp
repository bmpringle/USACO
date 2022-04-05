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
TASK: crypt1
*/

std::vector<int> getDigits(int i) {
    std::vector<int> result;

    while(i > 0) {
        result.push_back(i % 10);
        i /= 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

bool checkSolution(int o1, int o2, std::unordered_set<int>& digits) {
    std::vector<int> pSum1 = getDigits(o1 * (o2 % 10));

    if(pSum1.size() != 3) {
        return false;
    }

    for(int& digit : pSum1) {
        if(digits.count(digit) == 0) {
            return false;
        }
    }

    std::vector<int> pSum2 = getDigits(o1 * (o2 / 10));

    if(pSum2.size() != 3) {
        return false;
    }

    for(int& digit : pSum2) {
        if(digits.count(digit) == 0) {
            return false;
        }
    }

    std::vector<int> fSum = getDigits(o1 * (o2 % 10) * 10 + o1 * (o2 / 10)); 

    if(fSum.size() != 4) {
        return false;
    }

    for(int& digit : fSum) {
        if(digits.count(digit) == 0) {
            return false;
        }
    }

    return true;
}

std::string checkDigits(std::unordered_set<int>& digits) {
    std::unordered_set<int> operand1set;
    std::unordered_set<int> operand2set;

    for(const int& digit1 : digits) {
        for(const int& digit2 : digits) {
            operand2set.insert(digit1 * 10 + digit2);
            for(const int& digit3 : digits) {
                operand1set.insert(digit1 * 100 + digit2 * 10 + digit3);
            }
        }
    }

    int solutions = 0;

    for(const int& o1 : operand1set) {
        for(const int& o2 : operand2set) {
            if(checkSolution(o1, o2, digits)) {
                ++solutions;
            }
        }
    }

    return std::to_string(solutions) + "\n";
}

int main() {
    std::ifstream input ("crypt1.in");
    std::ofstream output ("crypt1.out");

    std::string buffer;
    std::getline(input, buffer);

    int N = std::stoi(buffer);

    std::unordered_set<int> digits;

    for(int i = 0; i < N; ++i) {
        std::getline(input, buffer, ' ');
        digits.insert(std::stoi(buffer));
    }

    std::string solutions = checkDigits(digits);

    output.write(solutions.data(), solutions.size());

    return 0;
}