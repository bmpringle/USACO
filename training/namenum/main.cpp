#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

/*
ID: bmpringle
LANG: C++
TASK: namenum
*/

std::vector<std::string> getAllNames(std::vector<int> number, std::map<std::string, bool> dictionary) {
    std::vector<std::vector<char>> possibleChars;

    for(int digit : number) {
        switch(digit) {
            case 0:
                possibleChars.push_back({'?'});
                break;
            case 1:
                possibleChars.push_back({'?'});
                break;
            case 2:
                possibleChars.push_back({'A', 'B', 'C'});
                break;
            case 3:
                possibleChars.push_back({'D', 'E', 'F'});
                break;
            case 4:
                possibleChars.push_back({'G', 'H', 'I'});
                break;
            case 5:
                possibleChars.push_back({'J', 'K', 'L'});
                break;
            case 6:
                possibleChars.push_back({'M', 'N', 'O'});
                break;
            case 7:
                possibleChars.push_back({'P', 'R', 'S'});
                break;
            case 8:
                possibleChars.push_back({'T', 'U', 'V'});
                break;
            case 9:
                possibleChars.push_back({'W', 'X', 'Y'});
                break;
        }
    }
    int size = 0;

    std::vector<std::string>* allNames = new std::vector<std::string>();
    std::vector<std::string>* tempBuffer = new std::vector<std::string>();
    allNames->push_back("");

    for(std::vector<char> charset : possibleChars) {    
        ++size;

        int allNamesSize = allNames->size();

        std::swap(allNames, tempBuffer);
  
        for(std::string& str : *tempBuffer) {
            for(char& c : charset) {
                std::string newStr = str + std::string(1, c);
                if(dictionary.count(newStr) > 0 && size == newStr.size()) {
                    if(size < possibleChars.size() || dictionary[newStr]) {
                        allNames->push_back(newStr);
                    }
                }
            }
        }

        tempBuffer->clear();
    }

    std::vector<std::string> allNamesCopy = *allNames;
    
    delete allNames;
    delete tempBuffer;

    return allNamesCopy;
}

int main() {
    std::ifstream input ("namenum.in");
    std::ifstream dict ("dict.txt");
    std::ofstream output ("namenum.out");

    std::string buffer;
    std::getline(input, buffer);

    std::vector<int> number;

    for(char c : buffer) {
        number.push_back(std::stoi(std::string(1, c)));
    }

    std::map<std::string, bool> dictionary = std::map<std::string, bool>();

    while(std::getline(dict, buffer)) {
        std::string buffer2 = "";
        for(char& c : buffer) {
            buffer2.push_back(c);
            if(dictionary.count(buffer2) == 0) {
                dictionary[buffer2] = false;
            }  
        }
        dictionary[buffer] = true;
    }

    std::vector<std::string> names = getAllNames(number, dictionary);
    
    std::sort(names.begin(), names.end()); //alphabetical sorting is the default
    
    for(std::string str : names) {
        std::string outputString = str + '\n';
        output.write(outputString.data(), outputString.size());
    }

    if(names.size() == 0) {
        std::string outputString = "NONE\n";
        output.write(outputString.data(), outputString.size());
    }

    return 0;
}