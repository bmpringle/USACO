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
TASK: palsquare
*/

std::unordered_map<char, int> digitToBase10 = {
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'A', 10},
    {'B', 11},
    {'C', 12},
    {'D', 13},
    {'E', 14},
    {'F', 15},
    {'G', 16},
    {'H', 17},
    {'I', 18},
    {'J', 19},
    {'K', 20},
    {'L', 21},
    {'M', 22},
    {'N', 23},
    {'O', 24},
    {'P', 25},
    {'Q', 26},
    {'R', 27},
    {'S', 28},
    {'T', 29},
    {'U', 30},
    {'V', 31},
    {'W', 32},
    {'X', 33},
    {'Y', 34},
    {'Z', 35},
};

std::unordered_map<int, char> base10ToDigit = {
    {0, '0'},
    {1, '1'},
    {2, '2'},
    {3, '3'},
    {4, '4'},
    {5, '5'},
    {6, '6'},
    {7, '7'},
    {8, '8'},
    {9, '9'},
    {10, 'A'},
    {11, 'B'},
    {12, 'C'},
    {13, 'D'},
    {14, 'E'},
    {15, 'F'},
    {16, 'G'},
    {17, 'H'},
    {18, 'I'},
    {19, 'J'},
    {20, 'K'},
    {21, 'L'},
    {22, 'M'},
    {23, 'N'},
    {24, 'O'},
    {25, 'P'},
    {26, 'Q'},
    {27, 'R'},
    {28, 'S'},
    {29, 'T'},
    {30, 'U'},
    {31, 'V'},
    {32, 'W'},
    {33, 'X'},
    {34, 'Y'},
    {35, 'Z'},
};

std::vector<int> getDigits(std::string data) {
    std::vector<int> digits;
    for(char& c : data) {
        digits.push_back(digitToBase10[c]);
    }
    return digits;
}

std::string getString(std::vector<int> digits) {
    std::string data = "";

    for(int& digit : digits) {
        data += base10ToDigit[digit];
    }

    return data;
}

class AltBaseInt {
    public:
        AltBaseInt(std::string data, int base) : data(data), base(base) {

        }

        AltBaseInt(int data, int base) : data(std::to_string(data)), base(base) { //for bases less than 10

        }

        void operator++() {

            AltBaseInt one = AltBaseInt(1, base);

            data = operator+(one).getData();
        }

        AltBaseInt operator*(AltBaseInt rhs) {
            if(base != rhs.getBase()) {
                throw std::invalid_argument("right hand side and left hand side of the + operator don't have the same base!");
            }

            AltBaseInt lhs = *this;
            lhs.toBase(10);
            rhs.toBase(10);

            AltBaseInt result = AltBaseInt(std::to_string(std::stoi(lhs.getData()) * std::stoi(rhs.getData())), 10);
            result.toBase(base);

            return result;
        }

        AltBaseInt operator+(AltBaseInt& i1) {
            if(base != i1.getBase()) {
                throw std::invalid_argument("right hand side and left hand side of the + operator don't have the same base!");
            }
            std::vector<int> digits1 = getDigits(data);
            std::vector<int> digits2 = getDigits(i1.getData());
            std::vector<int> product = std::vector<int>();
            int size = std::max(digits1.size(), digits2.size());
            product.reserve(size + 1);

            for(int i = 0; i < std::max(digits1.size(), digits2.size()) + 1; ++i) {
                product.push_back(0);
            }

            for(int i = size - 1; size >= 0; ++i) {
                int digit1 = 0;
                int digit2 = 0;

                if(i < digits1.size()) {
                    digit1 = digits1[i];
                }
                if(i < digits2.size()) {
                    digit2 = digits2[i];
                }

                product.at(i + 1) += (digit1 + digit2);

                if(product.at(i + 1) >= base) {
                    product.at(i + 1) -= base;
                    product.at(i) += 1;
                }
            }

            if(product.at(0) == 0) {
                product.erase(product.begin());
            }

            return AltBaseInt(getString(product), base);
        }
    
        std::string& getData() {
            return data;
        }

        int getBase() {
            return base;
        }

        void setBase(int _base) {
            base = _base;
        }

        void setData(std::string _data) {
            data = _data;
        }


        void toBase(int newBase) {
            std::vector<int> digits = getDigits(getData());

            int b10Value = 0;
            for(int i = 0; i < digits.size(); ++i) {
                b10Value += digits[i] * std::pow(getBase(), digits.size() - i - 1);
            }

            digits.clear();
            int exp = 0;
            int digitCount = 0;
            int prevEXP = 0;

            while(b10Value > 0) {
                if(b10Value - std::pow(newBase, exp) >= 0) {
                    ++exp;
                }else {
                    --exp;

                    if(digitCount == 0) {
                        digitCount = exp + 1;
                    }

                    int digit;

                    for(digit = 0; b10Value >= 0; ++digit) {
                        b10Value -= std::pow(newBase, exp);
                    }
                    b10Value += std::pow(newBase, exp);
                    --digit;

                    while(prevEXP - exp > 1) {
                        --prevEXP;
                        digits.push_back(0);
                    }
                    digits.push_back(digit);
                    prevEXP = exp;
                    exp = 0;
                }
            }

            while(digits.size() < digitCount) {
                digits.push_back(0);
            }
            if(digits.size() > digitCount) {
                throw std::runtime_error("digits size > digitCount. something is VERY wrong");
            }

            if(digits.size() == 0) {
                digits.push_back(0);
            }

            base = newBase;

            data = getString(digits);
        }

        bool isSquarePalindromic() {
            AltBaseInt square = *this * *this;
            std::string squareData = square.getData();

            for(int i = 0; i < squareData.size() - i; ++i) {
                if(squareData[i] != squareData[squareData.size() - i - 1]) {
                    return false;
                }
            }

            return true;
        }

    private:
        std::string data;
        int base;
};

int main() {
    std::ifstream input ("palsquare.in");
    std::ofstream output ("palsquare.out");

    std::string buffer;
    std::getline(input, buffer); 
    int B = std::stoi(buffer);

    for(int N = 1; N <= 300; ++N) {
        AltBaseInt number = AltBaseInt(N, 10);
        number.toBase(B);
        if(number.isSquarePalindromic()) {
            AltBaseInt square = number * number;
            std::string outputString = number.getData() + " " + square.getData() + "\n";
            output.write(outputString.data(), outputString.size());
        }
    }
    return 0;
}