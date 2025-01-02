#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>

using namespace std;

// Struktura grafu
struct Graph 
{
    int vertices;                          // Liczba wierzchołków
    vector<vector<int>> adjacencyList;     // Lista sąsiedztwa

    Graph(int v) : vertices(v) 
    {
        adjacencyList.resize(v);           // Inicjalizacja listy sąsiedztwa
    }

    void addEdge(int u, int v) 
    {
        adjacencyList[u].push_back(v);     // Dodanie krawędzi z u do v
        adjacencyList[v].push_back(u);     // Dodanie krawędzi z v do u
    }

    const vector<int>& neighbors(int u) const 
    {
        return adjacencyList[u];           // Zwraca sąsiadów wierzchołka u
    }
};

// Funkcja celu: liczba konfliktów w danym kolorowaniu
int calculateConflicts(const Graph& graph, const vector<int>& colors) 
{
    int conflicts = 0;
    for (int u = 0; u < graph.vertices; ++u) 
    {
        for (int v : graph.neighbors(u)) 
        {
            if (colors[u] == colors[v]) // Konflikt: sąsiadujące wierzchołki mają ten sam kolor
            {  
                ++conflicts;
            }
        }
    }
    return conflicts / 2;                  // Konflikty liczymy podwójnie, dzielimy na końcu
}

// Zachłanne kolorowanie (szybkie przybliżenie rozwiązania)
vector<int> greedyColoring(const Graph& graph) 
{
    int n = graph.vertices;
    vector<int> colors(n, -1);             // Kolor -1 oznacza brak koloru
    vector<bool> available(n, true);      // Tablica dostępnych kolorów

    for (int u = 0; u < n; ++u) 
    {
        for (int v : graph.neighbors(u)) // Sprawdzenie zajętych kolorów sąsiadów
        { 
            if (colors[v] != -1) {
                available[colors[v]] = false;
            }
        }
        // Wybór najmniejszego dostępnego koloru
        for (int c = 0; c < n; ++c) {
            if (available[c]) {
                colors[u] = c;
                break;
            }
        }
        // Przywrócenie dostępności kolorów
        for (int v : graph.neighbors(u)) {
            if (colors[v] != -1) {
                available[colors[v]] = true;
            }
        }
    }
    return colors;
}
int maks(vector<int> colors)
{
    int maks = 0;
    for (int i = 0; i < colors.size(); i++)
    {
        if (colors[i] > maks)
        {
            maks = colors[i];
        }
    }
    return maks;
}
// Algorytm Tabu Search
vector<int> tabuSearch(Graph& graph, int maxColors, int maxIterations, int tabuTenure) 
{
    int n = graph.vertices;
    vector<int> colors = greedyColoring(graph); // Inicjalizacja zachłanna
    unordered_map<int, int> tabuList;           // Lista tabu
    vector<int> bestColors = colors;            // Najlepsze rozwiązanie
  
    int bestConflicts = calculateConflicts(graph, colors);

    for (int iteration = 0; iteration < maxIterations; ++iteration) 
    {
        //int currentConflicts = calculateConflicts(graph, colors);
        //if (currentConflicts == 0) break;       // Koniec, gdy brak konfliktów

        int bestNeighborConflicts = numeric_limits<int>::max();
        int bestVertex = -1, bestColor = -1;

        for (int vertex = 0; vertex < n; ++vertex) 
        {
            int originalColor = colors[vertex];
            for (int color = 0; color < maxColors; ++color) 
            {
                if (color == originalColor) continue;

                colors[vertex] = color;         // Zmień kolor wierzchołka
                int neighborConflicts = calculateConflicts(graph, colors);

                // Sprawdzenie warunków tabu
                if (tabuList[vertex] > iteration && neighborConflicts >= bestConflicts) 
                {
                    continue;
                }

                // Aktualizacja najlepszego sąsiada
                if (neighborConflicts < bestNeighborConflicts) 
                {
                    bestNeighborConflicts = neighborConflicts;
                    bestVertex = vertex;
                    bestColor = color;
                }
            }
            colors[vertex] = originalColor;    // Przywrócenie koloru
        }

        // Wykonanie najlepszego ruchu
        if (bestVertex != -1) 
        {
            //cout << bestVertex << " " << bestColor << endl;
            colors[bestVertex] = bestColor;
            tabuList[bestVertex] = iteration + tabuTenure; // Aktualizacja listy tabu
        }
        if (bestNeighborConflicts < bestConflicts) 
        {
            bestColors = colors;
            bestConflicts = bestNeighborConflicts;
        }
        int currentConflicts = calculateConflicts(graph, colors);
        if (currentConflicts == 0 && maks(colors) == maxColors - 1)// Koniec, gdy brak konfliktów
        {
            return colors;
        }       
    }
    cout << "DUPA"<<endl;
    return bestColors; // Zwróć najlepsze znalezione rozwiązanie
}

int main() 
{
    ifstream dane;
    dane.open("queen6.txt");

    // Tworzenie grafu
    int vertices;
    dane >> vertices;
    Graph graph(vertices);
    /*graph.addEdge(0, 1);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);*/
    int a, b;
    while (!dane.eof())
    {
        dane >> a >> b;
        graph.addEdge(a-1, b-1);
    }
    // Parametry algorytmu
    int maxColors = 7;       // Maksymalna liczba kolorów
    int maxIterations = 1000; // Maksymalna liczba iteracji
    int tabuTenure = 50;      // Liczba iteracji ruchu na liście tabu
    vector<int> result;
    // Wykonanie Tabu Search
    //for (int i = maxColors;i>6;i--)
    //{
        result = tabuSearch(graph, maxColors, maxIterations, tabuTenure);
    //}
    

    // Wyświetlenie wyniku
    cout << "Kolorowanie grafu:" << endl;
    for (int i = 0; i < result.size(); ++i) 
    {
        cout << "Wierzcholek " << i << ": Kolor " << result[i] << endl;
    }

    cout << "Minimalna liczba kolorow: " << maks(result) + 1 << endl;

    return 0;
}