#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

/*
ID: bmpringle
LANG: C++
TASK: beads
*/

int calculatePotentialResult(std::string& potentialString) {
    std::vector<int> beadGroupCounts;

    //key is 2 vector positions, maps to overlap between them
    std::map<std::vector<int>, int> overlapMap;

    bool complete = false;
    int index = 0;
    int endIndex = 0;

    while(potentialString[index] == 'w') {
        ++index;
        ++endIndex;
    }

    char currentColor = ' ';

    int groupSizeBuffer = 0;

    bool overlapFlag = false;
    int overlapBuffer = 0;

    while(!complete) {
        if(overlapFlag) {
            groupSizeBuffer = overlapBuffer;

            overlapFlag = false;
            overlapBuffer = 0;

            while(potentialString[index] == 'w') {
                ++index;
                index %= potentialString.size();

                if(index == endIndex) {
                    complete = true;
                    break;
                }
            }
        }

        currentColor = potentialString[index];

        bool processingGroup = potentialString[index] == currentColor;

        while(processingGroup) {
            ++index;
            index %= potentialString.size();

            ++groupSizeBuffer;

            if(index == endIndex) {
                complete = true;
                break;
            }

            processingGroup = potentialString[index] == currentColor;

            if(potentialString[index] == 'w') {
                overlapFlag = true;
                int wCounter = 1;
                int iCounter = 1;
                while(potentialString[index + iCounter] == 'w') {
                    ++wCounter;
                    ++iCounter;
                    iCounter %= potentialString.size();
                }

                std::vector<int> tempVector = {(int) beadGroupCounts.size(), (int) beadGroupCounts.size() + 1};
                
                for(int i = 1; i <= iCounter; ++i) {
                    if(index + i == potentialString.size()) {
                        tempVector = {0, (int) beadGroupCounts.size()};
                    }
                }
                
                overlapMap[tempVector] = wCounter;

                overlapBuffer = wCounter;

                groupSizeBuffer += wCounter;
            }
        }

        beadGroupCounts.push_back(groupSizeBuffer);
        
        groupSizeBuffer = 0;

        if(beadGroupCounts.size() == 1 && complete) {
            return beadGroupCounts[0];
        }

        if(complete) {
            if(potentialString[potentialString.size() - 1] == potentialString[0]) {
                for(std::pair<const std::vector<int>, int>& pair : overlapMap) {
                    if(pair.first[1] == beadGroupCounts.size() - 1) {
                        overlapMap[{0, pair.first[0]}] = pair.second;
                    }
                }

                int lastGroup = beadGroupCounts.back();
                beadGroupCounts.pop_back();
                beadGroupCounts.at(0) += lastGroup;
            }
        }
    }

    int result = 0;

    for(int i = 0; i < beadGroupCounts.size(); ++i) {
        int group1 = beadGroupCounts[i];
        int group2 = 0;

        int overcount = 0;
        std::vector<int> tempVector;

        if(i != 0) {
            group2 = beadGroupCounts[i - 1];
            tempVector = {i - 1, i};
        }else {
            group2 = beadGroupCounts[beadGroupCounts.size() - 1];
            tempVector = {0, (int) beadGroupCounts.size() - 1};
        }

        if(overlapMap.count(tempVector) > 0) {
            overcount = overlapMap[tempVector];
        }

        if(group1 + group2 - overcount > result) {
            result = group1 + group2 - overcount;
        }
    }
    return result;
}

void createAndEvaluateStrings(int& result, std::string& currentString) { 
    int i = 0;

    while(currentString[i] == 'w') {
        ++i;
        i %= currentString.size();
    }
    
    for(int count = 0; count < currentString.size(); ++count, ++i, i %= currentString.size()) {
        if(currentString[i] == 'w') {
            int prevIndex = (i - 1);
            
            if(prevIndex < 0) {
                prevIndex = currentString.size() + prevIndex;
            }

            if(currentString[prevIndex] == currentString[(i + 1) % currentString.size()] && currentString[prevIndex] != 'w') {
                currentString[i] = currentString[prevIndex];
                continue;
            }

            int wIndex = 0;

            while(currentString[(i + 1 + wIndex) % currentString.size()] == 'w' && wIndex < currentString.size()) {
                ++wIndex;
            }

            if(currentString[prevIndex] == currentString[(i + 1 + wIndex) % currentString.size()]) {
                for(int j = i; j < (i + 1 + wIndex); j = (j + 1)) {
                    currentString[j % currentString.size()] = currentString[prevIndex];
                }
                continue;
            }
        }
    }
    result = std::max(result, calculatePotentialResult(currentString));
}

int main() {
    std::ifstream input ("beads.in");
    std::ofstream output ("beads.out");

    std::string buffer;
    std::getline(input, buffer);

    int beadCount = std::stoi(buffer);

    std::getline(input, buffer);

    char check = ' ';
    bool flag = true;

    for(char c : buffer) {
        if(check == ' ') {
            check = c;
        }else {
            if(check != c) {
                flag = false;
            }
        }
    }

    if(flag) {
        std::string out = std::to_string(buffer.size()) + "\n";
        output.write(out.data(), out.size());

        return 0;
    }

    int result = 0;
    createAndEvaluateStrings(result, buffer);

    std::string out = std::to_string(result) + "\n";
    output.write(out.data(), out.size());

    return 0;
}