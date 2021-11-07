#ifndef DYNAMIC_PROGRAMMING_H_
#define DYNAMIC_PROGRAMMING_H_

#include <vector>

class DynamicProgramming
{
private:
    std::vector<std::vector<int>> matrix;
    int number_of_towns;
    int route_cost;
    int all_vertices_bits;
    std::vector<int> route; // route to wierzchołki ułożone w kolejności tworzącej szukaną ścieżkę
    // w sub_problems zapisane są koszty drogi z początkowego do pierwszej składowej i z niej do i przez wierzchołki oznaczone przez drugą składową
    // np w sub_problems[2][x] jest koszt z 0 do 2 + koszt z 2 do i przez wierzchołki wyznaczane bitowo przez x
    std::vector<std::vector<int>> sub_problems;
    // ta metoda na podstawie wyników znajdujących się w track oblicza i wypełnia route
    void calculateRoute();

public:
    DynamicProgramming(std::vector<std::vector<int>> towns);
    void startDP(); // rozpoczęcie algorytmu
    // start_vertex to wierzchołek początkowy z jakiego wychodzimy, set_of_vertices to zbiór wierzchołków wyrażony bitowo
    // metoda liczy koszt najlepszej ścieżki od startowego do i przez wierzchołki ze zbioru
    int recDP(int start_vertex, int set_of_vertices); // główna, rekurencyjna część algorytmu
    void printRoute();                                // wyświela wynik
};

#endif /* DYNAMIC_PROGRAMMING_H_ */
