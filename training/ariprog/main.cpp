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
TASK: ariprog
*/

struct Result {
    Result(int s, int g) : start(s), gap(g) {

    }

    void write(std::ofstream& ostream) const {
        std::string strOut = std::string(std::to_string(start) + " " + std::to_string(gap) + "\n");
        ostream.write(strOut.data(), strOut.size());
        std::cout << start << " " << gap << std::endl;
    }

    bool operator<(Result rhs) const {
        if(gap == rhs.gap) {
            return start < rhs.start;
        }

        return gap < rhs.gap;
    }

    int start;
    int gap;
};

int main() {
    std::ifstream input ("ariprog.in");
    std::ofstream output ("ariprog.out");

    std::string buffer;

    std::getline(input, buffer);
    int sequenceLength = std::stoi(buffer);

    std::getline(input, buffer);
    int pqLimit = std::stoi(buffer);

    std::unordered_set<int> bisquareVector;

    int largestBisquare = 0;

    for(int p = 0; p <= pqLimit; ++p) {
        for(int q = 0; q <= pqLimit; ++q) {
            bisquareVector.insert(p * p + q * q);

            if(p * p + q * q > largestBisquare) {
                largestBisquare = p * p + q * q;
            }
        }
    }

    int sequenceGap = 0;
    std::set<Result> results;

    for(const int& bisquare : bisquareVector) {
        if(bisquare > 10000) {
            continue;
        }
        int maxSequenceGap = (largestBisquare - bisquare) / (sequenceLength - 1);
        //std::cout << maxSequenceGap << std::endl;
        for(int sequenceGap = 1; sequenceGap <= maxSequenceGap; ++sequenceGap) {
            bool isValidSequence = true;

            for(int currentLength = 0; currentLength < sequenceLength - 1; ++currentLength) {
                if(bisquareVector.count(bisquare + (currentLength + 1) * sequenceGap) == 0) {
                    isValidSequence = false;
                    break;
                }
            }

            if(isValidSequence) {
                results.insert(Result(bisquare, sequenceGap));
            }
        }
    }

    for(const Result& r : results) {
        std::string strOut = std::string(std::to_string(r.start) + " " + std::to_string(r.gap) + "\n");
        output.write(strOut.data(), strOut.size());
    }

    if(results.size() == 0) {
        output.write("NONE\n", 5);
    }

    return 0;
}