#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/*
ID: bmpringle
LANG: C++
TASK: gift1
*/

class Account {
    public:
        Account(std::string name) : name(name) {

        }

        void withdraw(int amount) {
            money -= amount;
        }

        void deposit(int amount) {
            money += amount;
        }

        std::string& getName() {
            return name;
        }

        void printAccount(std::ofstream& outputStream) {
            std::string output = name + " " + std::to_string(money) + "\n";

            outputStream.write(output.data(), output.size());
        }

    private:
        int money = 0;
        std::string name;
};

int main() {
    std::ifstream input ("gift1.in");
    std::ofstream output ("gift1.out");

    std::vector<Account> accounts = std::vector<Account>();

    //get input
    int NP = 0; //number of people
    int namesCounter = 0; //counter used to count lines of names read in

    //buffer used to read in lines of input
    std::string buffer;

    while(std::getline(input, buffer)) {
        if(NP == 0) {
            NP = std::stoi(buffer);
            continue;
        }

        if(NP != 0 && namesCounter < NP) {
            accounts.push_back(Account(buffer));
            ++namesCounter;
            continue;
        }

        //read in one transaction and calculate the results
        Account* giver;

        for(Account& account : accounts) {
            if(buffer == account.getName()) {
                giver = &account;
                break;
            }
        }
        
        std::getline(input, buffer);

        std::stringstream stream (buffer);

        std::getline(stream, buffer, ' ');

        int amountGiven = std::stoi(buffer);

        std::getline(stream, buffer, ' ');

        int numberGivenTo = std::stoi(buffer);

        std::vector<Account*> accountsGivenTo;

        for(int i = 0; i < numberGivenTo; ++i) {
            std::getline(input, buffer);

            for(Account& account : accounts) {
                if(buffer == account.getName()) {
                    accountsGivenTo.push_back(&account);
                    break;
                }
            }
        }

        int amountGivenPerAccount = 0;
        int leftoverMoney = 0;

        if(numberGivenTo > 0) {
            amountGivenPerAccount = amountGiven / numberGivenTo;
            leftoverMoney = amountGiven % numberGivenTo;
        }

        giver->withdraw(amountGiven);

        for(Account* account : accountsGivenTo) {
            account->deposit(amountGivenPerAccount);
        }

        giver->deposit(leftoverMoney);
    }
    
    for(int i = 0; i < accounts.size(); ++i) {
        accounts[i].printAccount(output);
    }

    return 0;
}