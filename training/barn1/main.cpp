#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <set>

/*
ID: bmpringle
LANG: C++
TASK: barn1
*/

int main() {
    std::ifstream input ("barn1.in");
    std::ofstream output ("barn1.out");

    int M, S, C;

    std::string buffer;
    std::getline(input, buffer);

    std::stringstream bufferStream (buffer);

    std::getline(bufferStream, buffer, ' ');
    M = std::stoi(buffer);

    std::getline(bufferStream, buffer, ' ');
    S = std::stoi(buffer);

    std::getline(bufferStream, buffer, ' ');
    C = std::stoi(buffer);

    std::set<int> stalls;
    
    for(int i = 0; i < C; ++i) {
        std::getline(input, buffer);
        stalls.insert(std::stoi(buffer));
    }

    int boardsUncovered = 0;

    std::multiset<int, std::greater<int>> stallDistances;
    int prevStall = 0;
    for(int stallNumber : stalls) {
        if(prevStall == 0) {
            boardsUncovered += stallNumber - 1;
            prevStall = stallNumber;
            continue;
        }
        stallDistances.insert(stallNumber - prevStall - 1);
        prevStall = stallNumber;
    }

    boardsUncovered += S - prevStall;

    int boards = 1;
    for(int stallDistance : stallDistances) {
        if(boards < M) {
            boardsUncovered += stallDistance;
        }
        ++boards;
    }

    std::string outputString = std::to_string(S - boardsUncovered) + "\n";
    output.write(outputString.data(), outputString.size());

    return 0;
}