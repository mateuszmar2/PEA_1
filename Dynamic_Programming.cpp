#include "Dynamic_Programming.h"

#include <iostream>
#include <climits>

using namespace std;

DynamicProgramming::DynamicProgramming(std::vector<std::vector<int>> towns)
{
    matrix = towns;
    number_of_towns = matrix[0].size();
    all_verticles_bits = 1 << number_of_towns; // all_verticles_bits = 2^number_of_towns
    // sub_problems i track to vectory o rozmiarze number_of_towns na 2^number_of_towns wypełnione wartościami -1
    sub_problems = std::vector<std::vector<int>>(number_of_towns, std::vector<int>(all_verticles_bits, -1));
    track = std::vector<std::vector<int>>(number_of_towns, std::vector<int>(all_verticles_bits, -1));
}

void DynamicProgramming::startDP()
{
    all_verticles_bits--; // ustawiamy 1 na indeksach odpowiadających wierzchołkom
    for (int i = 0; i < number_of_towns; i++)
        sub_problems[i][0] = matrix[i][0]; // droga od i do 0 czyli zbioru pustego, napotkamy je gdy nie ma już gdzie iść i trzeba zakończyć dalszą rekurencję

    route_cost = recDP(0, all_verticles_bits - 1); // obliczenie kosztu dla wierzchołka 0 jako start i zbioru wierzchołków poza zerowym
    calculateRoute(0, all_verticles_bits - 1);     // wyciągniecie wyniku
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
        int mask = all_verticles_bits - (1 << i); // all_verticles_bits - 2^i w celu ustawienia 0 na i wierzchołku
        int masked = set_of_vertices & mask;      // masked to set_of_verices z zamaskowanym jednym z wierzchołków

        if (masked != set_of_vertices) // liczymy jeśli zamaskowaliśmy jeden z wierzchołków
        {
            int value = matrix[start_vertex][i] + recDP(i, masked); // koszt ze startu do i + koszt z i przez set_of_vertices poza i

            if (result == -1 || value < result) // jeżeli znaleziona droga jest lepsza niż poprzednia, result == -1 w przypadku gdy żadnej drogi jeszcze nie znaleziono
            {
                result = value;
                track[start_vertex][set_of_vertices] = i; // w track zapisujemy ścieżke, po kolei jak należy iść przez wierzchołki
                                                          // np jeśli mamy track[0][11...110] czyli z 0 przez wszystkie inne to będzie tam pierwszy wierzchołek do jakiego należy się udać
            }
        }
    }
    sub_problems[start_vertex][set_of_vertices] = result;
    return result;
}

void DynamicProgramming::calculateRoute(int start_vertex, int set_of_vertices)
{
    route.push_back(0);                           // wierzchołek startowy
    int x = track[start_vertex][set_of_vertices]; // do x kolejny, do którego należy się udać
    while (x != -1)                               // dopóki nie przeszliśmy całej ścieżki
    {
        route.push_back(x);                       // wrzucenie wierzchołka x do trasy
        int mask = all_verticles_bits - (1 << x); // ustawienie na 0 wierzchołka x
        int masked = set_of_vertices & mask;      // masked to set_of_vertices bez wierzchołka x
        x = track[x][masked];                     // do x kolejny, do którego należy się udać
        set_of_vertices = masked;                 // kolejny przeszukiwany zbiór będzie już bez znalezionego wcześniej wierzchołka
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
