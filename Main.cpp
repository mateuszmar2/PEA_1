#include "Towns.h"
#include "Branch_and_Bound.h"
#include <iostream>
#include <limits>

using namespace std;

void menu()
{
    Towns towns;
    char choice;
    char filename[50];
    do
    {
        cout << endl
             << "Which action you want to perform? Type appropriate number " << endl;
        cout << "p - Print data " << endl;
        cout << "l - Load data from file " << endl;
        cout << "b - Branch and Bound algorithm " << endl;
        cout << "d - Dynamic programming algorithm " << endl;
        cout << "f - BruteForce algorithm " << endl;
        cout << "e - Exit the program " << endl;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 'p': // wypisanie
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            towns.printData();
            break;
        case 'l': // załadowanie danych z pliku
            cout << "Enter file name: ";
            cin >> filename;
            cout << endl;
            towns.loadDataFromFile(filename);
            break;
        case 'b': // B&B
        {
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            BranchAndBound bnb(towns.getTowns());
            break;
        }
        case 'd': // DP
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            break;
        case 'f': // BF
            if (towns.getTowns().empty())
            {
                cout << "Load data first" << endl;
                break;
            }
            break;
        case 'e': // wyjście
            break;
        default:
            cout << "Type appropriate number" << endl;
            break;
        }
    } while (choice != 'e');
}

int main()
{
    menu();

    return 0;
}
