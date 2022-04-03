#include <math.h>
#include <iostream>

std::string reverseToIndex(std::string str, int index) {
    std::string result = "";

    for(int i = 0; i < index; ++i) {
        result += str[index - i];
    }


    result += str.substr(index + 1);


    //std::cout << str << " w/ index " << index << " reversed to " << result << std::endl;
    return result;
}

int getStringScore(std::string str) {
    int score = 0;

    for(int i = 0; i < str.size(); i +=2) {
        if(str[i] == 'G') {
            ++score;
        }
    }
    return score;
}

void iterateOverInput(std::string& str, int& reverses) {
    for(int i = 0; i < str.size(); i += 2) {
        std::string newStr = reverseToIndex(str, i);

        if(getStringScore(newStr) > getStringScore(str)) {
            ++reverses;
            str = newStr;
            iterateOverInput(str, reverses);
            return;
        }
    } 
}

int main() {
    int n;
    std::cin >> n;

    std::string buffer;
    std::cin >> buffer;

    int reverses = 0;
    iterateOverInput(buffer, reverses);

    std::cout << reverses << std::endl;
    
    return 0;
}

//G G G H G H H G H H H G H G


//A B C D E F G H I J K