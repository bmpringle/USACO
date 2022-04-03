#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

/*
ID: bmpringle
LANG: C++
TASK: milk2
*/

enum STATE_CHANGE {
    ADD,
    REMOVE
};

int main() {
    std::ifstream input ("milk2.in");
    std::ofstream output ("milk2.out");

    std::string buffer = "";
    std::getline(input, buffer);

    int N = std::stoi(buffer);
    std::vector<std::pair<STATE_CHANGE, int> > milkingTimes;

    for(int i = 0; i < N; ++i) {
        std::getline(input, buffer);
        std::stringstream bufferStream (buffer);
        std::getline(bufferStream, buffer, ' ');
        int startTime = std::stoi(buffer);
        std::getline(bufferStream, buffer, ' ');
        int endTime = std::stoi(buffer);
        milkingTimes.push_back(std::make_pair(ADD, startTime));
        milkingTimes.push_back(std::make_pair(REMOVE, endTime));
    }

    std::sort(milkingTimes.begin(), milkingTimes.end(), [](std::pair<int, int> first, std::pair<int, int> second) {
        return first.second < second.second; 
    });

    //each element of the vector is a pair of {number of cows being milked, duration}
    std::vector<std::pair<int, int> > milkingTimeLengths = std::vector<std::pair<int, int> >();
    int cowsBeingMilked = 0;
    int startTime = 0;
    bool startRecording = false;

    for(auto time : milkingTimes) {
        if(startTime != 0 || cowsBeingMilked != 0) {
            startRecording = true;
        }

        if(startRecording && (time.second - startTime) > 0) {
            milkingTimeLengths.push_back(std::make_pair(cowsBeingMilked, time.second - startTime));
        }
        
        if(time.first == ADD) {
            ++cowsBeingMilked;
        }else {
            --cowsBeingMilked;
        }
        startTime = time.second;
    }

    int largestMilkingDuration = 0;
    int largestNoMilkingDuration = 0;

    int continuousMilkingDuration = 0;
    int continuousNoMilkingDuration = 0;
    
    for(auto time : milkingTimeLengths) {
        if(time.first > 0) {
            continuousNoMilkingDuration = 0;
            continuousMilkingDuration += time.second;
        }else {
            continuousMilkingDuration = 0;
            continuousNoMilkingDuration += time.second;
        }

        if(continuousMilkingDuration > largestMilkingDuration) {
            largestMilkingDuration = continuousMilkingDuration;
        }

        if(continuousNoMilkingDuration > largestNoMilkingDuration) {
            largestNoMilkingDuration = continuousNoMilkingDuration;
        }
    }
    
    std::string outputString = std::to_string(largestMilkingDuration) + " " + std::to_string(largestNoMilkingDuration) + "\n";

    output.write(outputString.data(), outputString.size());

    return 0;
}