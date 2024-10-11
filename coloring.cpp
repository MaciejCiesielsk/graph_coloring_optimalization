#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main(){
    int node, edge, i, j, v1, v2;
    char** A;
    srand(time(NULL));
    // wczytywanie liczby wierzcholkow i krawedz - potem bedzie to generowane z pliku jakiegos
    cout << "Enter  number of nodes: ";
    cin >> node;
    cout << endl << "Enter number of egdes: ";
    cin >> edge;

    A = new char *[node]; //tablica wskaznikow tworzona 
    for(i = 0; i<node; i++){
        A[i] = new char [node]; // wiersze w tablicy
    }

    //wypelnienie macierzy zerami
    for(i = 0; i < node; i++){
        for(j = 0; j < node; j++){
            A[i][j] = 0;
        }
    }

    //randomowo generowane ktore wierzcholki sie lacza
    for(i = 0; i < edge; i++){
        v1 = rand() % node;
        v2 = rand() % node;
        A [v1][v2] = 1;
    }
    cout << endl;

    // wypisywanie macierzy
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

    // wypisywanie z indeksami
    for (i = 0; i < node; i++) {
        cout << setw(2) << i << "|";
        for (j = 0; j < node; j++) {
            cout << setw(3) << (int)A[i][j];
        }
        cout << endl;
    }

    // zwolnienie pamieci
    for (i = 0; i < node; i++) {
        delete[] A[i];
    }
    delete[] A;
    return 0;
}