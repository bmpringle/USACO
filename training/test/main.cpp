#include <iostream>
#include <fstream>
#include <sstream>

/*
ID: bmpringle
LANG: C++
TASK: test
*/

int main() {
    std::ifstream input ("test.in");
    std::ofstream output ("test.out");

    std::string buffer;
    std::getline(input, buffer, '\n');

    std::stringstream lineStream (buffer);

    std::getline(lineStream, buffer, ' ');
    int a = std::stoi(buffer);
    std::getline(lineStream, buffer, ' ');
    int b = std::stoi(buffer);

    std::string c = std::to_string(a + b) + '\n';

    output.write(c.data(), c.size());

    return 0;
}