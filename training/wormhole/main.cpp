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
TASK: wormhole
*/

struct Wormhole {
    Wormhole(int x, int y, int index) : x(x), y(y), index(index) {
        indexString = std::to_string(index);
    }

    bool operator<(const Wormhole& rhs) const {
        if(y < rhs.y) {
            return true;
        }else if(y > rhs.y) {
            return false;
        }else {
            if(x < rhs.x) {
                return true;
            }else {
                return false;
            }
        }
    }

    bool operator==(const Wormhole& rhs) const {
        return (x == rhs.x) && (y == rhs.y) && (index == rhs.index) && (exit == rhs.exit);
    }

    bool operator!=(const Wormhole& rhs) const {
        return (x != rhs.x) || (y != rhs.y) || (index != rhs.index) || (exit != rhs.exit);
    }

    int x;
    int y;
    int index;
    std::string indexString = "";

    Wormhole* exit = nullptr;
};

struct Connection {
    bool operator==(const Connection rhs) const {
        return entrance == rhs.entrance && exit == rhs.exit;
    }

    bool operator<(const Connection rhs) const {
        return exit < rhs.exit;
    }

    Connection(Wormhole* e) : entrance(e) {

    }

    Wormhole* entrance; //portal this connection represents
    Wormhole* exit = nullptr; //connected portal
};

struct ConnectionVectorHash {
    size_t operator()(const std::vector<Connection>& v) const {
        std::hash<int> hasher = std::hash<int>();
        size_t seed = 0;
        for (const Connection& i : v) {
            seed ^= hasher((long int)i.exit) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

//note that every instance of wormholes should have the same order of indexes, which is assumed in all of these functions
std::string CONNECTIONS_HASH(const std::vector<Connection>& connections) {
    std::string hash = "";

    for(const Connection& c : connections) {
        hash += ",";
        hash += c.exit->indexString;
    }

    return hash;
}

std::unordered_set<std::vector<Connection>, ConnectionVectorHash> connectionsUsed;

//note that every instance of wormholes should have the same order of indexes, which is assumed in all of these functions
void getLoops(const std::vector<Wormhole>& wormholes, int& loops, int& exit_now, std::vector<Connection>& connections, const int& totalNumberOfUniqueConnections, const std::size_t& wormhole_size) {
    for(int i = 0; i < wormhole_size; ++i) {
        for(int j = i + 1; j < wormhole_size; ++j) {
            if(connections[i].exit != nullptr || connections[j].exit != nullptr) {
                continue;
            }

            connections[i].exit = connections[j].entrance;
            connections[j].exit = connections[i].entrance;

            getLoops(wormholes, loops, exit_now, connections, totalNumberOfUniqueConnections, wormhole_size);

            if(exit_now == -1) { // acts as immediate return once all distinct combinations have been checked. this is b/c while it's very slow
                return;       // to find all the combinations, the number of them can be easily calculated.
            }

            connections[i].exit = nullptr;
            connections[j].exit = nullptr;
        }
    }

    for(Connection& connection : connections) {
        if(connection.exit == nullptr) {
            return;
        }
    }

    if(connectionsUsed.insert(connections).second) {
        bool possibilityLeadsToLoop = false;

        for(int i = 0; i < wormhole_size; ++i) {
            std::vector<int> portals;
            
            Wormhole* currentEntrance = connections[i].entrance;
            Wormhole* currentExit = connections[i].exit;
            while(true) {
                if(std::find(portals.begin(), portals.end(), currentEntrance->index) != portals.end()) {
                    possibilityLeadsToLoop = true;
                    break;
                }

                portals.push_back(currentEntrance->index);
                
                if(currentExit->index + 1 == wormhole_size || connections.at(currentExit->index + 1).entrance->y != connections.at(currentExit->index).entrance->y) {
                    break;
                }else {
                    currentEntrance = connections.at(currentExit->index + 1).entrance;
                    currentExit = connections.at(currentExit->index + 1).exit;
                }
            }

            if(possibilityLeadsToLoop) {
                ++loops;
                break;
            }
        }

        if(connectionsUsed.size() == totalNumberOfUniqueConnections) {
            exit_now = -1;
            return;
        }
    }
}

int main() {
    std::ifstream input ("wormhole.in");
    std::ofstream output ("wormhole.out");

    std::string buffer;
    std::getline(input, buffer);

    int N = std::stoi(buffer);

    std::vector<Wormhole> wormholes;

    for(int i = 0; i < N; ++i) {
        std::getline(input, buffer);
        
        std::stringstream stream (buffer);
        std::getline(stream, buffer, ' ');
        int x = std::stoi(buffer);

        std::getline(stream, buffer, ' ');
        int y = std::stoi(buffer);

        wormholes.push_back(Wormhole(x, y, wormholes.size()));
    }

    std::sort(wormholes.begin(), wormholes.end());

    for(int i = 0; i < wormholes.size(); ++i) {
        wormholes[i].index = i;
    }

    int loops = 0;
    int depth = 0;

    std::vector<Connection> connections;
    
    for(int i = 0; i < wormholes.size(); ++i) {
        connections.push_back(Connection(&wormholes[i]));
    }

    int totalNumberOfUniqueConnections = 1;
    for(int i = wormholes.size() - 1; i > 0; i -= 2) {
        totalNumberOfUniqueConnections *= i;
    }

    getLoops(wormholes, loops, depth, connections, totalNumberOfUniqueConnections, wormholes.size());

    std::string outputString = std::to_string(loops) + "\n";

    output.write(outputString.data(), outputString.size());

    return 0;
}