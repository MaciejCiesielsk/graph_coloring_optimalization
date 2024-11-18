#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <climits>
#include <set>
#include <ctime>
using namespace std;

struct Move {
    int node;
    int color;
};

// Calculate the number of conflicts in the current coloring
int calculateConflicts(const vector<vector<int>> &adjList, const vector<int> &color) {
    int conflicts = 0;
    for (int i = 0; i < adjList.size(); i++) {
        for (int neighbor : adjList[i]) {
            if (color[i] == color[neighbor]) {
                conflicts++;
            }
        }
    }
    return conflicts / 2; // Each conflict is counted twice
}

int main() {
    ifstream file("queen6.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int nodes, maxIterations = 1000, tabuTenure = 7;
    file >> nodes;

    // Initialize adjacency list
    vector<vector<int>> adjList(nodes);

    int v1, v2;
    while (file >> v1 >> v2) {
        adjList[v1 - 1].push_back(v2 - 1); // Adjusting to 0-based indexing
        adjList[v2 - 1].push_back(v1 - 1); // Bidirectional edge
    }
    file.close();

    cout << "Graph Loaded with " << nodes << " nodes.\n";

    // Initial random coloring
    vector<int> color(nodes);
    int k = 13; // Number of colors (change as needed)
    srand(time(0));
    for (int i = 0; i < nodes; i++) {
        color[i] = rand() % k;
    }

    vector<vector<int>> tabuList(nodes, vector<int>(k, 0));
    int currentConflicts = calculateConflicts(adjList, color);

    int iterations = 0;
    vector<int> bestColor = color;
    int bestConflicts = currentConflicts;

    cout << "\nStarting Tabu Search...\n";

    while (iterations < maxIterations && bestConflicts > 0) {
        iterations++;

        // Explore neighborhood
        Move bestMove = {-1, -1};
        int minConflicts = INT_MAX;

        for (int node = 0; node < nodes; node++) {
            for (int newColor = 0; newColor < k; newColor++) {
                if (color[node] != newColor && tabuList[node][newColor] == 0) {
                    vector<int> tempColor = color;
                    tempColor[node] = newColor;
                    int tempConflicts = calculateConflicts(adjList, tempColor);

                    if (tempConflicts < minConflicts) {
                        minConflicts = tempConflicts;
                        bestMove = {node, newColor};
                    }
                }
            }
        }

        // Apply the best move
        if (bestMove.node != -1) {
            color[bestMove.node] = bestMove.color;
            currentConflicts = minConflicts;

            // Update Tabu List
            for (int i = 0; i < nodes; i++) {
                for (int j = 0; j < k; j++) {
                    if (tabuList[i][j] > 0) {
                        tabuList[i][j]--;
                    }
                }
            }
            tabuList[bestMove.node][bestMove.color] = tabuTenure;

            // Update the best solution
            if (currentConflicts < bestConflicts) {
                bestConflicts = currentConflicts;
                bestColor = color;
            }
        }

        /*cout << "Iteration: " << iterations
             << ", Conflicts: " << currentConflicts
             << ", Best Conflicts: " << bestConflicts << endl;*/
    }

    cout << "\nFinal Solution:\n";
    for (int i = 0; i < nodes; i++) {
        cout << "Node " << i + 1 << " -> Color " << bestColor[i] + 1 << endl;
    }

    int used = 0;

    for (int i = 0; i < nodes; i++) {
        if (used < bestColor[i] + 1){
            used = bestColor[i] + 1;
        }
    }

    std::cout << "Colors used: " << used << std::endl;

    //cout << "Conflicts: " << bestConflicts << endl;
    //cout << "Iterations: " << iterations << endl;

    return 0;
}
