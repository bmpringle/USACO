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
TASK: milk
*/

struct Farmer {
    Farmer(int price, int maxMilk) : price(price), maxMilk(maxMilk) {

    }

    bool operator<(const Farmer& rhs) const {
        return price < rhs.price;
    }

    int price; //in cents
    int maxMilk; //in units
};

int main() {
    std::ifstream input ("milk.in");
    std::ofstream output ("milk.out");

    int N, M;
    std::string buffer;

    std::getline(input, buffer);

    std::stringstream bufferStream1 (buffer);

    std::getline(bufferStream1, buffer, ' ');
    N = std::stoi(buffer);

    std::getline(bufferStream1, buffer, ' ');
    M = std::stoi(buffer);

    std::multiset<Farmer> farmers;

    for(int i = 0; i < M; ++i) {
        int P, A;

        std::getline(input, buffer);

        std::stringstream bufferStream2 (buffer);

        std::getline(bufferStream2, buffer, ' ');
        P = std::stoi(buffer);

        std::getline(bufferStream2, buffer, ' ');
        A = std::stoi(buffer);

        farmers.insert(Farmer(P, A));
    }

    //this will be in order from least to most expensive because operator< in the Farmer class means that the multiset will be sorted as such
    int cost = 0;
    int milkBought = 0;

    for(const Farmer& farmer : farmers) { 
        if(N - milkBought <= farmer.maxMilk) {
            cost += (N - milkBought) * farmer.price;
            milkBought += (N - milkBought);
            break;
        }else {
            cost += farmer.maxMilk * farmer.price;
            milkBought += farmer.maxMilk;
        }
    }

    if(milkBought < N) {
        throw std::runtime_error("Not enough milk to buy to fufill requirements!");
    }

    if(milkBought > N) {
        throw std::runtime_error("We bought more milk than required for some reason! Something has gone VERY wrong.");
    }

    std::string outputString = std::to_string(cost) + "\n";
    output.write(outputString.data(), outputString.size());

    return 0;
}