#ifndef BRANCH_AND_BOUND_H_
#define BRANCH_AND_BOUND_H_

#include <vector>

struct Node
{
    int number;            // numer wierzchołka
    std::vector<int> path; // ścieżka od korzenia
    int bound;             // dolna granica możliwych długości poniżej danego węzła
};

class BranchAndBound
{
private:
    std::vector<std::vector<int>> matrix;
    int number_of_towns;

public:
    // std::vector<std::vector<int>> reduceMatrix(std::vector<std::vector<int>> matrix_to_reduce, int &cost);
    BranchAndBound(std::vector<std::vector<int>> towns)
    {
        matrix = towns;
        number_of_towns = matrix[0].size();
    }
    // sprawdzenie czy dane miasto zostało już odwiedzone
    bool visited(Node node, int city, bool column);
    // odległość przez całą ścieżkę do danego miasta
    int pathDistance(Node node);
    // wyznaczenie dolnego ograniczenia poprzez
    // obliczenie sumy elementów odejmowanych od wierszy i kolumn
    int lowerBound(Node node);
};

#endif /* BRANCH_AND_BOUND_H_ */