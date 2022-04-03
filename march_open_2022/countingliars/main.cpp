#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

typedef unsigned int uint;

class NumberLine {
    public:
        NumberLine() {
            
        }

        int howManyLying() {
            uint liars = -1;
            std::sort(greaterInequalities.begin(), greaterInequalities.end(), [](int a, int b) -> bool {
                return a > b;
            });
            std::sort(lesserInequalities.begin(), lesserInequalities.end());

            for(uint i = 0; i < greaterInequalities.size(); ++i) {
                for(uint j = 0; j < lesserInequalities.size(); ++j) {
                    if(lesserInequalities[j] >= greaterInequalities[i]) {
                        if(liars == -1) {
                            liars = i + j;
                        }else {
                            liars = std::min(liars, i + j);
                        }
                        break;
                    }
                }
            }

            if(liars == -1) {
                liars = std::min(greaterInequalities.size(), lesserInequalities.size());
            }

            return liars;
        }

        void addGreater(uint num) {
            greaterInequalities.push_back(num);
        }

        void addLesser(uint num) {
            lesserInequalities.push_back(num);
        }

    private:
        std::vector<uint> greaterInequalities;
        std::vector<uint> lesserInequalities;
};

int main() {
    uint cows;
    std::cin >> cows;

    std::string buffer;

    NumberLine numberLine = NumberLine();

    for(uint i = 0; i < cows; ++i) {
        std::cin >> buffer;
        char symbol = buffer[0];

        std::cin >> buffer;
        uint number = std::stoi(buffer);

        if(symbol == 'G') {
            numberLine.addGreater(number);
        }else {
            numberLine.addLesser(number);
        }
    }

    std::cout << numberLine.howManyLying() << std::endl;
    
    return 0;
}
