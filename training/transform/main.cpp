#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

/*
ID: bmpringle
LANG: C++
TASK: transform
*/

class Square {
    public:
        Square(int N, std::vector<bool> _tiles) : N(N) {
            for(int i = 0; i < N; ++i) {
                tiles.push_back(std::vector<bool>());
                for(int j = 0; j < N; ++j) {
                    tiles[i].push_back(false);
                    tiles[i][j] = _tiles[i * N + j];
                }
            }
        }
        
        Square(int N) : N(N) {
            for(int i = 0; i < N; ++i) {
                tiles.push_back(std::vector<bool>());
                for(int j = 0; j < N; ++j) {
                    tiles[i].push_back(false);
                }
            }
        }

        std::pair<int, int> rotate90(int i, int j) {
            double i_d = 0;
            double j_d = 0;

            i_d = -(j - (double) (N - 1) / 2.0) + (double) (N - 1) / 2.0;
            j_d = i - (double) (N - 1) / 2.0 + (double) (N - 1) / 2.0;

            i = i_d;
            j = j_d;

            return std::make_pair(i, j);
        }

        std::pair<int, int> rotate90(std::pair<int, int> ij) {
            int i = ij.first;
            int j = ij.second;

            double i_d = 0;
            double j_d = 0;

            i_d = -(j - (double) (N - 1) / 2.0) + (double) (N - 1) / 2.0;
            j_d = i - (double) (N - 1) / 2.0 + (double) (N - 1) / 2.0;

            i = i_d;
            j = j_d;

            return std::make_pair(i, j);
        }

        std::pair<int, int> reflect(int i, int j) {
            double j_d = 0;

            j_d = j - (double) (N - 1) / 2.0;
            j_d = -j_d;
            j_d = j_d + (double) (N - 1) / 2.0;

            j = j_d;

            return std::make_pair(i, j);
        }

        //returns 90, 180, 270, or -1 if invalid
        int isRotationOf(Square& s) {
            bool couldBe90 = true;
            bool couldBe180 = true;
            bool couldBe270 = true;

            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    if(get(i, j) != s.get(rotate90(i, j))) {
                        couldBe90 = false;
                    }
                    
                    if(get(i, j) != s.get(rotate90(rotate90(i, j)))) {
                        couldBe180 = false;
                    }       
                    
                    if(get(i, j) != s.get(rotate90(rotate90(rotate90(i, j))))) {
                        couldBe270 = false;
                    }
                          
                    if(!couldBe180 && !couldBe90 && !couldBe270) {
                        break;
                    }
                    
                }

                if(!couldBe180 && !couldBe90 && !couldBe270) {
                    break;
                }
            }

            if(couldBe90) {
                return 90;
            }

            if(couldBe180) {
                return 180;
            }

            if(couldBe270) {
                return 270;
            }
            return -1;
        }

        bool isReflectionOf(Square& s) {
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    if(get(i, j) != s.get(reflect(i, j))) {
                        return false;
                    }
                }
            }

            return true;
        }

        Square getReflectionOf() {
            Square nS = Square(N);

            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    nS.set(i, j, get(reflect(i, j)));
                }
            }

            return nS;
        }

        bool isCompositionOf(Square& s) {
            Square s1 = s.getReflectionOf();
            return (isRotationOf(s1) > 0);
        }

        bool get(int i, int j) {
            return tiles[i][j];
        }

        bool get(std::pair<int, int> ij) {
            return tiles[ij.first][ij.second];
        }

        void set(int i, int j, bool val) {
            tiles[i][j] = val;
        }

        bool operator==(Square s1) {
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    if(get(i, j) != s1.get(i, j)) {
                        return false;
                    }
                }
            }
            return true;
        }

    private:
        int N = 0;
        std::vector<std::vector<bool>> tiles;
};

int main() {
    std::ifstream input ("transform.in");
    std::ofstream output ("transform.out");

    std::string buffer;
    std::getline(input, buffer);
    int N = std::stoi(buffer);

    std::vector<bool> before;
    std::vector<bool> after;

    for(int i = 0; i < N; ++i) {
        std::getline(input, buffer);
        for(char c : buffer) {
            if(c == '@') {
                before.push_back(true);
            }else if(c == '-') {
                before.push_back(false);
            }
        }  
    }

    for(int i = 0; i < N; ++i) {
        std::getline(input, buffer);
        for(char c : buffer) {
            if(c == '@') {
                after.push_back(true);
            }else if(c == '-') {
                after.push_back(false);
            }
        }  
    }

    Square beforeSquare = Square(N, before);
    Square afterSquare = Square(N, after);

    if(afterSquare.isRotationOf(beforeSquare) == 90) {
        std::string outputString = "1\n";
        output.write(outputString.data(), outputString.size());
        return 0;
    }
    
    if(afterSquare.isRotationOf(beforeSquare) == 180) {
        std::string outputString = "2\n";
        output.write(outputString.data(), outputString.size());
        return 0;
    }
    if(afterSquare.isRotationOf(beforeSquare) == 270) {
        std::string outputString = "3\n";
        output.write(outputString.data(), outputString.size());
        return 0;
    }
    if(afterSquare.isReflectionOf(beforeSquare)) {
        std::string outputString = "4\n";
        output.write(outputString.data(), outputString.size());
        return 0;
    }
    if(afterSquare.isCompositionOf(beforeSquare)) {
        std::string outputString = "5\n";
        output.write(outputString.data(), outputString.size());
        return 0;
    }
    if(afterSquare == beforeSquare) {
        std::string outputString = "6\n";
        output.write(outputString.data(), outputString.size());
        return 0;
    }
    std::string outputString = "7\n";
    output.write(outputString.data(), outputString.size());

    return 0;
}