#include "Dynamic_Programming.h"

#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

DynamicProgramming::DynamicProgramming(std::vector<std::vector<int>> towns)
{
    matrix = towns;
    number_of_towns = matrix[0].size();
    all_vertices_bits = 1 << number_of_towns; // all_vertices_bits = 2^number_of_towns
    // sub_problems to vector o rozmiarze number_of_towns na 2^number_of_towns wypełniony wartościami -1
    sub_problems = std::vector<std::vector<int>>(number_of_towns, std::vector<int>(all_vertices_bits, -1));
}

void DynamicProgramming::startDP()
{
    all_vertices_bits--; // ustawiamy 1 na indeksach odpowiadających wierzchołkom
    for (int i = 0; i < number_of_towns; i++)
        sub_problems[i][0] = matrix[i][0]; // droga od i do 0 czyli zbioru pustego, napotkamy je gdy nie ma już gdzie iść i trzeba zakończyć dalszą rekurencję

    route_cost = recDP(0, all_vertices_bits - 1); // obliczenie kosztu dla wierzchołka 0 jako start i zbioru wierzchołków poza zerowym
    calculateRoute();                             // wyciągniecie wyniku
}

// set_of_vertices to zbiór wierzchołków, 1 oznacza że wierzchołek jest obecny
// przykładowo 110 oznacza że bierzemy pod uwagę wierzchołki 1 i 2 a 0 nie
int DynamicProgramming::recDP(int start_vertex, int set_of_vertices)
{
    int result = -1;

    if (sub_problems[start_vertex][set_of_vertices] != -1) // jeżeli podproblem jest już rozwiązany to zwracany jest wynik
        return sub_problems[start_vertex][set_of_vertices];
    // jeśli nie to obliczamy potrzebny wynik
    for (int i = 0; i < number_of_towns; i++) // do zmiany maski, iterowanie przez wszystkie wierzchołki obecne w set_of_vertices
    {
        int mask = all_vertices_bits - (1 << i); // all_vertices_bits - 2^i w celu ustawienia 0 na i wierzchołku
        int masked = set_of_vertices & mask;     // masked to set_of_verices z zamaskowanym jednym z wierzchołków

        if (masked != set_of_vertices) // liczymy jeśli zamaskowaliśmy jeden z wierzchołków
        {
            int value = matrix[start_vertex][i] + recDP(i, masked); // koszt ze startu do i + koszt z i przez set_of_vertices poza i

            if (result == -1 || value < result) // jeżeli znaleziona droga jest lepsza niż poprzednia, result == -1 w przypadku gdy żadnej drogi jeszcze nie znaleziono
                result = value;
        }
    }
    sub_problems[start_vertex][set_of_vertices] = result;
    return result;
}

void DynamicProgramming::calculateRoute()
{
    route.push_back(0);               // wierzchołek początkowy
    int mask = all_vertices_bits - 1; // maska to wierzchołki bez początkowego
    while (mask != 0)                 // wykonujemy dopóki nie wykluczymy wszystkich miast
    {
        int min_sub_cost = INT_MAX;
        int index = INT_MAX;
        for (int i = 1; i < number_of_towns; i++) // można od 1 ponieważ od 0 i tak nie będziemy wychodzić
        {
            if ((mask | (1 << i)) != mask) // jeżeli wybrano miasto, które nie jest wyznaczone przez mask to pomijamy
                continue;

            int temp_mask = mask ^ (1 << i);                                      // ustawienie 0 dla obecnie rozpatrywanego miasta
            int temp_cost = sub_problems[i][temp_mask] + matrix[route.back()][i]; // koszt obliczonego podproblemu + koszt z miasta poprzedzającego w trasie do obecnego
            if (temp_cost < min_sub_cost)                                         // jeżeli obliczony koszt jest mniejszy niż najmniejszy dotychczas znaleziony
            {
                min_sub_cost = temp_cost;
                index = i;
            }
        }
        route.push_back(index); // dodanie do trasy znalezionego miasta
        mask -= (1 << index);   // wykluczenie znalezionego miasta z maski
    }
    route.push_back(0); // wierzchołek końcowy
}

void DynamicProgramming::printRoute()
{
    for (auto i = 0; i < route.size() - 1; i++)
        cout << route[i] << " -> ";
    cout << route[route.size() - 1] << endl;
    cout << "Cost = " << route_cost << endl;
}
