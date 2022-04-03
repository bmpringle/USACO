#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <unordered_map>

/*
ID: bmpringle
LANG: C++
TASK: dualpal
*/

bool isPalindromeInBase(int number, int base) { //base must be between 2 and 10, inclusive
    std::vector<int> digits; //digits in the base specified by the variable base

    /* 
     * note that the digits will be reversed in the vector at the end of this operation, 
     * so if the digits should be 1352, in digits they are {2, 5, 3, 1}. This doesn't matter
     * because checking for a palindrome will yeild the same result regardless, so there's no reason
     * to bother correcting it.
    */

    while(number > 0) {
        digits.push_back(number % base);
        number /= base;
    }

    //check if the result is a palindrrome
    for(int i = 0; i < digits.size() / 2; ++i) {
        if(digits[i] != digits[digits.size() - i - 1]) {
            return false;
        }
    }

    return true;
}

bool isDualPalindrome(int number) {
    int numberOfPalindromes = 0;

    for(int i = 2; i <= 10; ++i) {
        if(isPalindromeInBase(number, i)) {
            ++numberOfPalindromes;
        }

        if(numberOfPalindromes == 2) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream input ("dualpal.in");
    std::ofstream output ("dualpal.out");

    std::string buffer;

    std::getline(input, buffer, ' ');

    int N = std::stoi(buffer);

    std::getline(input, buffer, ' ');

    int S = std::stoi(buffer);

    int dualPalindromesFound = 0;

    std::string outputString = "";

    for(int i = S + 1; dualPalindromesFound < N; ++i) {
        if(isDualPalindrome(i)) {
            outputString += std::to_string(i) + "\n";
            ++dualPalindromesFound;
        }
    }

    output.write(outputString.data(), outputString.size());
    return 0;
}