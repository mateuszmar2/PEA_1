#include "Towns.h"
#include <iostream>
#include <fstream>

using namespace std;

void Towns::loadDataFromFile(const char *filename)
{
    ifstream file;
    file.open(filename);

    if (!file)
        cout << "File open error" << endl;
    else
    {
        int temp;
        file >> temp; // liczba miast
        if (temp <= 0)
        {
            cout << "The number of towns is incorrect" << endl;
            return;
        }
        // vector wypełniony taką ilością vectorów, z wartością 0, ile jest miast
        vector<vector<int>> temp_towns(temp, vector<int>(temp, 0));
        // w kolejnych liniach odległości z danego miasta do wszystkich pozostałych miast
        for (int i = 0; i < temp; i++)
        {
            for (int j = 0; j < temp; j++)
            {
                file >> temp_towns[i][j];
                if (file.peek() == EOF && j != temp - 1)
                {
                    cout << "Not enough data compared to the number of towns" << endl;
                    return;
                }
            }
        }
        Towns::towns = temp_towns;
        file.close();
        for (int i = 0; i < temp; i++)
            towns[i][i] = -1;
        Towns::printData();
    }
}
void Towns::printData()
{
    for (auto x : towns)
    {
        for (int y : x)
            cout << y << "\t";
        cout << endl;
    }
}

vector<vector<int>> Towns::getTowns()
{
    return towns;
}
