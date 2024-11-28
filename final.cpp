#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <numeric>
#include <chrono>

using namespace std;

vector<int> greedy(vector<vector<int>> adj_matrix){
    vector<int> solution; 
    adj_matrix = adj_matrix;
    int node;

    vector<int> color(node, -1);
    vector<bool> available(node, true);

    color[0] = 0;

    for (int i = 1; i < node; i++)
    {
        for (int j = 0; j < node; j++)
        {
            if (adj_matrix[i][j] == 1 && color[j] != -1)
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
        solution.push_back(color[i]);

        fill(available.begin(), available.end(), true);
    }

    return solution;
}

int checker(const vector<int>& solution){
    return accumulate(solution.begin(), solution.end(), 0);
}

vector<vector<int>> neighbor_check(const vector<vector<int>>& adj_matrix, vector<int> solution){
    vector<vector<int>> matrix = adj_matrix;
    vector<vector<int>> neighbors;

    for(int i = 0; i < solution.size(); i++){
        for (int j = 0; j < matrix.size(); j++) {
            if (matrix[i][j] == 1 && solution[i] == solution[j]) {
            neighbors.push_back({i, j});
            }
        }
    }


    return neighbors;
}

vector<int> tabu(vector<vector<int>> adj_matrix, int max_iterations, int tabu_size, vector<int> initial_solution){
    vector<int> best_solution = initial_solution;
    vector<int> current_solution = initial_solution;
    vector<vector<int>> tabu_list;

    srand(time(NULL));

    for(int i = 0; i <max_iterations; i++){
        vector<vector<int>> neighbors = neighbor_check(adj_matrix, current_solution);
    }

    return best_solution;
}


int main(){
    ifstream file("queen6.txt");
    int node, v1, v2;
    srand(time(NULL));
    file >> node;

    vector<vector<int>> adj_matrix(node, vector<int>(node, 0));

    while (file >> v1 >> v2)
    {
        if (v1 != v2 && v1 >= 0 && v1 < node && v2 >= 0 && v2 < node && adj_matrix[v1][v2] == 0)
        {
            adj_matrix[v1][v2] = 1;
            adj_matrix[v2][v1] = 1;
        }
    }
    file.close();
    vector<int> initial_solution = greedy(adj_matrix);
    for(int i = 0; i < initial_solution.size(); i++){
        cout << initial_solution[i] << " ";
    }
    cout << endl;
    return 0;
}