#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <numeric>
#include <chrono>

using namespace std;

vector<int> greedy() {
    vector<int> solution;
    ifstream file("gc500.txt");
    int node, v1, v2;
    srand(time(NULL));
    file >> node;

    vector<vector<int>> adj_matrix(node, vector<int>(node, 0));

    while (file >> v1 >> v2) {
        if (v1 != v2 && v1 >= 0 && v1 < node && v2 >= 0 && v2 < node && adj_matrix[v1][v2] == 0) {
            adj_matrix[v1][v2] = 1;
            adj_matrix[v2][v1] = 1;
        }
    }
    file.close();

    vector<int> color(node, -1);
    vector<bool> available(node, true);

    color[0] = 0;

    for (int i = 1; i < node; i++) {
        for (int j = 0; j < node; j++) {
            if (adj_matrix[i][j] == 1 && color[j] != -1) {
                available[color[j]] = false;
            }
        }

        int c;
        for (c = 0; c < node; c++) {
            if (available[c])
                break;
        }
        color[i] = c;
        solution.push_back(color[i]);

        fill(available.begin(), available.end(), true);
    }
    solution.shrink_to_fit();

    return solution;
}

int objective_function(const vector<int>& solution) {
    return accumulate(solution.begin(), solution.end(), 0);
}

vector<vector<int>> get_neighbors(const vector<int>& solution, const vector<vector<int>>& adj_matrix) {
    vector<vector<int>> neighbors;
    for (size_t i = 0; i < solution.size(); i++) {
        for (int color = 0; color < *max_element(solution.begin(), solution.end()) + 2; color++) {
            bool can_color = true;
            for (size_t j = 0; j < solution.size(); j++) {
                if (adj_matrix[i][j] == 1 && solution[j] == color) {
                    can_color = false;
                    break;
                }
            }
            if (can_color && solution[i] != color) {
                vector<int> neighbor = solution;
                neighbor[i] = color;
                neighbors.push_back(neighbor);
            }
        }
    }
    return neighbors;
}

vector<int> tabu_search(const vector<int>& initial_solution, const vector<vector<int>>& adj_matrix, int max_iterations, int tabu_list_size, const chrono::steady_clock::time_point& start_time, const chrono::minutes& timeout) {
    vector<int> best_solution = initial_solution;
    vector<int> current_solution = initial_solution;
    vector<vector<int>> tabu_list;

    srand(time(NULL));

    for (int i = 1; i < max_iterations; i++) {
        // Check if the time limit has been exceeded
        auto now = chrono::steady_clock::now();
        if (now - start_time >= timeout) {
            cout << "Execution time exceeded 3 minutes. Stopping search.\n";
            break;
        }

        vector<vector<int>> neighbors = get_neighbors(current_solution, adj_matrix);
        vector<int> best_neighbor;
        int best_neighbor_fitness = numeric_limits<int>::max();

        for (const auto& neighbor : neighbors) {
            int neighbor_fitness = objective_function(neighbor);
            if (find(tabu_list.begin(), tabu_list.end(), neighbor) == tabu_list.end() || neighbor_fitness < objective_function(best_solution)) {
                if (neighbor_fitness < best_neighbor_fitness) {
                    best_neighbor = neighbor;
                    best_neighbor_fitness = neighbor_fitness;
                }
            }
        }

        if (best_neighbor.empty()) {
            break;
        }

        current_solution = best_neighbor;
        tabu_list.push_back(current_solution);
        if (tabu_list.size() > tabu_list_size) {
            tabu_list.erase(tabu_list.begin());
        }

        if (objective_function(current_solution) < objective_function(best_solution)) {
            best_solution = current_solution;
        }
    }
    return best_solution;
}

int main() {
    auto start_time = chrono::steady_clock::now();
    chrono::minutes timeout(3); // Set timeout to 3 minutes

    vector<int> initial_solution = greedy();
    int max_iterations = 200;
    int tabu_list_size = 1000;

    ifstream file("gc500.txt");
    int node, v1, v2;
    file >> node;

    vector<vector<int>> adj_matrix(node, vector<int>(node, 0));

    while (file >> v1 >> v2) {
        if (v1 != v2 && v1 >= 0 && v1 < node && v2 >= 0 && v2 < node && adj_matrix[v1][v2] == 0) {
            adj_matrix[v1][v2] = 1;
            adj_matrix[v2][v1] = 1;
        }
    }
    file.close();

    vector<int> best_solution = tabu_search(initial_solution, adj_matrix, max_iterations, tabu_list_size, start_time, timeout);
    cout << "Best solution: ";
    for (int val : best_solution) {
        cout << val + 1 << " ";
    }
    cout << endl;
    cout << "Highest Color Number: " << *max_element(best_solution.begin(), best_solution.end()) + 1 << endl;
    return 0;
}
