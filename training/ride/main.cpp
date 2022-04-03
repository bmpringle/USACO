#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

/*
ID: bmpringle
LANG: C++
TASK: ride
*/
static std::map<unsigned char, int> CHAR_TO_INT = {
    {'a', 1},
    {'b', 2},
    {'c', 3},
    {'d', 4},
    {'e', 5},
    {'f', 6},
    {'g', 7},
    {'h', 8},
    {'i', 9},
    {'j', 10},
    {'k', 11},
    {'l', 12},
    {'m', 13},
    {'n', 14},
    {'o', 15},
    {'p', 16},
    {'q', 17},
    {'r', 18},
    {'s', 19},
    {'t', 20},
    {'u', 21},
    {'v', 22},
    {'w', 23},
    {'x', 24},
    {'y', 25},
    {'z', 26}
};

int main() {
    std::ifstream input ("ride.in");
    std::ofstream output ("ride.out");

    std::string buffer;

    std::getline(input, buffer); //gets the name of the comet

    int cometCode = 1;
    for(char c : buffer) {
        cometCode *= CHAR_TO_INT[std::tolower(c)];
    }

    cometCode = cometCode % 47;

    std::getline(input, buffer); //gets the name of the group

    int groupCode = 1;
    for(char c : buffer) {
        groupCode *= CHAR_TO_INT[std::tolower(c)];
    }
    
    groupCode = groupCode % 47;
    

    if(cometCode == groupCode) {
        output.write("GO\n", 3);
    }else {
        output.write("STAY\n", 5);
    }

    return 0;
}
