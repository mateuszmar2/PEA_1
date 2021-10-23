#ifndef BRUTE_FORCE_H_
#define BRUTE_FORCE_H_

#include <vector>

class BruteForce
{
private:
    std::vector<std::vector<int>> matrix;
    int number_of_towns;
    std::vector<int> route;

public:
    BruteForce(std::vector<std::vector<int>> towns)
    {
        matrix = towns;
        number_of_towns = matrix[0].size();
    }
    // oblicz odległość przez całą ścieżkę do danego miasta
    int pathDistance(std::vector<int> route_to_calculate);
    void bruteForce(); // główna część algorytmu
    void printRoute();
};

#endif /* BRUTE_FORCE_H_ */