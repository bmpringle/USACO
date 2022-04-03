#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

typedef unsigned int uint;

class Recipe {
    public:
        Recipe() {

        }
        std::vector<int> getIngredients() {
            return ingredients;
        }

        int getResult() {
            return result;
        }

        Recipe(int result, std::vector<int> ingredients) : ingredients(ingredients), result(result) {

        }

    private:
        int result = 0; 
        std::vector<int> ingredients;
};

class RecipeHierarchy {
    public:
        RecipeHierarchy(std::vector<Recipe> recipes) {
            for(Recipe r : recipes) {
                recipesMap[r.getResult()] = r;
            }
        }

        bool craftOnePieceOfMetal(int metalToCraft, std::vector<int>& materials) {
            std::vector<int> materialsBeforeAttempt = materials;

            for(std::pair<const int, Recipe>& recipePair : recipesMap) {
                Recipe r = recipePair.second;
                if(r.getResult() == metalToCraft) {
                    //std::cout << "found recipe for " << metalToCraft << std::endl;
                    auto ingredients = r.getIngredients();

                    for(int metalType : ingredients) {
                        if(materials[metalType] > 0) {
                            --materials[metalType];
                        }else {
                            //std::cout << "couldn't get enough " << metalType << " to craft " << metalToCraft << " from stores, attempting to craft some" << std::endl;

                            if(!craftOnePieceOfMetal(metalType, materials)) {
                                //std::cout << "couldn't get enough " << metalType << " to craft " << metalToCraft << std::endl;
                                materials = materialsBeforeAttempt;
                                return false;
                            }
                        }
                    }
                    //std::cout << "crafted one piece of " << metalToCraft << std::endl;
                    bool changed = false;
                    for(int i = 0; i < materials.size(); ++i) {
                        if(materials[i] != materialsBeforeAttempt[i]) {
                            changed = true;
                        }
                    }
                    if(!changed) {
                        abort();
                    }
                    return true;
                }
            }
            //std::cout << "no recipe for " << metalToCraft << std::endl;
           return false;
        }

        int canCraftAmountOfMetal(int metalToCraft, std::vector<int> materials) {
           int amount = 0;

            while(craftOnePieceOfMetal(metalToCraft, materials)) {
                ++amount;

                if(amount > 100000) {
                    abort();
                }
            }

            amount += materials[metalToCraft];

            return amount;
        }
    private:
        std::map<int, Recipe> recipesMap;
};

int main() {
    uint N;
    uint K;

    std::vector<int> metalStores;
    std::vector<Recipe> recipes;

    std::cin >> N;

    for(uint i = 0; i < N; ++i) {
        uint metal;

        std::cin >> metal;

        metalStores.push_back(metal);
    }

    while(metalStores.size() <= N) {
        metalStores.push_back(0);
    }

    std::cin >> K;

    for(uint i = 0; i < K; ++i) {
        int result;
        std::vector<int> ingredients;

        std::cin >> result;

        uint M;

        std::cin >> M;

        for(uint j = 0; j < M; ++j) {
            int ingredient;
            std::cin >> ingredient;
            ingredients.push_back(ingredient - 1);
        }
        
        recipes.push_back(Recipe(result - 1, ingredients));
    }

    bool allRecipesAreOneToOne = true;

    for(Recipe r : recipes) {
        if(r.getIngredients().size() > 1) {
            allRecipesAreOneToOne = false;
        }
    }

    if(allRecipesAreOneToOne) {
        int amount = 0;
        int currentMetalType = N - 1;
        bool done = false;

        while(!done) {
            done = true;

            amount += metalStores[currentMetalType];

            for(Recipe r : recipes) {
                if(r.getResult() == currentMetalType) {
                    currentMetalType = r.getIngredients()[0];
                    done = false;
                    break;
                }
            }
        }

        std::cout << amount << std::endl;
        return 0;
    }

    RecipeHierarchy hierarchy = RecipeHierarchy(recipes);

    std::cout << hierarchy.canCraftAmountOfMetal(N - 1, metalStores) << std::endl;
    
    return 0;
}
