#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    ifstream file("data.txt");
    int node, edge, i, j, v1, v2;
    char **A;
    srand(time(NULL));
    // wczytywanie liczby wierzcholkow i krawedz - potem bedzie to generowane z pliku jakiegos
    /*
     cout << "Enter  number of nodes: ";
    cin >> node;
    cout << endl
         << "Enter number of egdes: ";
    cin >> edge;
    */
    file >> node;

    A = new char *[node]; // tablica wskaznikow tworzona
    for (i = 0; i < node; i++)
    {
        A[i] = new char[node]; // wiersze w tablicy
    }

    // wypelnienie macierzy zerami
    for (i = 0; i < node; i++)
    {
        for (j = 0; j < node; j++)
        {
            A[i][j] = 0;
        }
    }

        while (file >> v1 >> v2)
    {   
        // Ensure no self-loops or duplicate edges
        if (v1 != v2 && A[v1][v2] == 0 && v1 >= 0 && v1 < node && v2 >= 0 && v2 < node)
        {
            A[v1][v2] = 1;
            A[v2][v1] = 1;
        }
    }

    file.close();

    // wypisywanie macierzy czytelnie
    cout << "\n    ";
    for (i = 0; i < node; i++) {
        cout << setw(3) << i;
    }
    cout << endl;


    cout << "   ";
    for (i = 0; i < node; i++) {
        cout << "---";
    }
    cout << endl;

    for (i = 0; i < node; i++) {
        cout << setw(2) << i << "|";
        for (j = 0; j < node; j++) {
            cout << setw(3) << (int)A[i][j];
        }
        cout << endl;
    }

    vector<int> color(node, -1);
    vector<bool> available(node, true);

    color[0] = 0;

    for (i = 1; i < node; i++)
    {
        for (j = 0; j < node; j++)
        {
            if (A[i][j] == 1 && color[j] != -1)
            {
                available[color[j]] = false;
            }
        }

        int c;
        for (c = 0; c < node; c++)
        {
            if (available[c])
                break;
        }
        color[i] = c;

        fill(available.begin(), available.end(), true);
    }

    cout << "\nNode Colors:\n";
    for (i = 0; i < node; i++)
    {
        cout << "Node " << i << " -> Color " << color[i] << endl;
    }

    // zwolnienie pamieci
    for (i = 0; i < node; i++)
    {
        delete[] A[i];
    }
    delete[] A;

    // kolorowanie grafu

    return 0;
}