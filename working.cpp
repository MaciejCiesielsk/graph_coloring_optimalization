#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <limits>

using namespace std;

vector<int> tabucol(const vector<vector<int>>& graph, int numberOfColors, int tabuSize = 7, int reps = 100, int maxIterations = 10000, bool debug = false) {
    int n = graph.size();
    vector<int> colors(numberOfColors);
    for (int i = 0; i < numberOfColors; ++i) {
        colors[i] = i;
    }

    vector<int> solution(n);
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        solution[i] = colors[rand() % numberOfColors];
    }

    deque<pair<int, int>> tabuQueue;
    unordered_map<int, int> aspirationLevel;
    int iterations = 0;
    int conflictCount = 0;

    while (iterations < maxIterations) {
        unordered_set<int> moveCandidates;
        conflictCount = 0;

        // Find conflicting nodes
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (graph[i][j] > 0 && solution[i] == solution[j]) {
                    moveCandidates.insert(i);
                    moveCandidates.insert(j);
                    ++conflictCount;
                }
            }
        }

        if (conflictCount == 0) {
            if (debug) cout << "Found a valid coloring.\n";
            return solution;
        }

        vector<int> moveCandidatesList(moveCandidates.begin(), moveCandidates.end());
        vector<int> newSolution = solution;
        int newConflicts = numeric_limits<int>::max();
        int selectedNode = -1, selectedColor = -1;

        for (int r = 0; r < reps; ++r) {
            int node = moveCandidatesList[rand() % moveCandidatesList.size()];
            int newColor = colors[rand() % (numberOfColors - 1)];
            if (solution[node] == newColor) {
                newColor = colors.back();
            }

            vector<int> tempSolution = solution;
            tempSolution[node] = newColor;

            int tempConflicts = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    if (graph[i][j] > 0 && tempSolution[i] == tempSolution[j]) {
                        ++tempConflicts;
                    }
                }
            }

            if (tempConflicts < newConflicts) {
                newConflicts = tempConflicts;
                selectedNode = node;
                selectedColor = newColor;
                newSolution = tempSolution;

                if (tempConflicts <= aspirationLevel[conflictCount]) {
                    aspirationLevel[conflictCount] = tempConflicts - 1;
                    break;
                }
            }
        }

        tabuQueue.push_back({selectedNode, solution[selectedNode]});
        if (tabuQueue.size() > tabuSize) {
            tabuQueue.pop_front();
        }

        solution = newSolution;
        iterations++;
        if (debug && iterations % 500 == 0) {
            cout << "Iteration: " << iterations << "\n";
        }
    }

    if (conflictCount != 0) {
        cout << "No valid coloring found with " << numberOfColors << " colors.\n";
        return {};
    } else {
        cout << "Found coloring.\n";
        return solution;
    }
}

vector<vector<int>> readGraphFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    int edges;
    file >> edges;

    int maxNode = 0;
    vector<pair<int, int>> edgeList;
    for (int i = 0; i < edges; ++i) {
        int u, v;
        file >> u >> v;
        edgeList.emplace_back(u, v);
        maxNode = max(maxNode, max(u, v));
    }

    // Create adjacency matrix
    vector<vector<int>> graph(maxNode + 1, vector<int>(maxNode + 1, 0));
    for (const auto& edge : edgeList) {
        graph[edge.first][edge.second] = 1;
        graph[edge.second][edge.first] = 1; // Undirected graph
    }

    return graph;
}

int main() {
    string filename = "miles250.txt"; // Replace with your filename
    vector<vector<int>> graph = readGraphFromFile(filename);

    int numberOfColors = 6; // Adjust the number of colors as needed
    vector<int> result = tabucol(graph, numberOfColors, 7, 100, 10000, true);

    if (!result.empty()) {
        cout << "Solution: ";
        for (int color : result) {
            cout << color << " ";
        }
        cout << "\n";
    }

    return 0;
}
