#include "Branch_and_Bound.h"
#include <climits>

using namespace std;

// std::vector<std::vector<int>> BranchAndBound::reduceMatrix(std::vector<std::vector<int>> matrix_to_reduce, int &cost)
// {
//     int min = INT_MAX;
//     cost = 0;
//     for (int i = 0; i < matrix_to_reduce[0].size(); i++)
//     {
//         for (int i = 0; i < matrix_to_reduce[0].size(); i++)
//         {
//         }
//     }
// }
int BranchAndBound::pathDistance(Node node)
{
    int path_distance = 0;
    // zliczenie sumy odległości w ścieżce aż do danego wierzchołka
    for (int i = 0; i < node.path.size() - 1; i++)
        path_distance += matrix[node.path[i]][node.path[i + 1]];
    return path_distance;
}
bool BranchAndBound::visited(Node node, int city, bool column)
{
    // w przypadku wierszy nie chcemy ograniczać ostatniej pozycji w ścieżce
    int limit = -1;
    int i = 0;
    if (column)
    {
        i++;       // jeżeli sprawdzamy kolumny, to pomijamy miejsce startu ponieważ musimy tam wrócić
        limit = 0; // w przypadku kolumn możemy ograniczyć
    }
    for (i; i < node.path.size() + limit; i++)
        if (node.path[i] == city) // sprawdzenie czy podane miasto zostało już odwiedzone
            return true;
    return false;
}
int BranchAndBound::lowerBound(Node node)
{
    int bound = pathDistance(node); // dolne ograniczenie złożone z dotychczasowych długości
    for (int i = 0; i < number_of_towns; i++)
    {
        if (visited(node, i, false))
            continue; // jeśli miasto zostało odwiedzone to pomijamy

        int minimum = INT_MAX;

        for (int j = 0; j < number_of_towns; i++)
        {
            if (visited(node, j, true))
                continue; // jeśli nie będziemy wracać do tego miasta to pomijamy
            if (i == j)
                continue;                                       // pomiń ponieważ to jest to samo miasto
            if (node.path[node.path.size() - 1] == i && j == 0) // żeby nie zakończyć przedwcześnie
                continue;                                       // jeśli ostatnia pozycja w ścieżce prowadziłaby do startu to pomijamy
            if (matrix[i][j] < minimum && matrix[i][j] > 0)
                minimum = matrix[i][j];
        }
        if (minimum != INT_MAX)
            bound += minimum;
    }
    return bound;
}
