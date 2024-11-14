#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>


using namespace std;

int graph_creation(){

}

vector<vector<int>> get_neighbors(const vector<int>& solution){
    vector<vector<int>> neighbors;  
    for(size_t i  = 0; i < solution.size(); i++ ){
        for(size_t j = i + 1; i < solution.size(); j++){
            vector<int> neighbor = solution;
            swap(neighbor[i], neighbor[j]);
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

vector<int> tabu(vector<int>& initial_solution, int max_iterations, int tabu_list_size){
    vector<int> best_solution = initial_solution;
    vector<int> curren_solution = initial_solution;
    vector<vector<int>> tabu_list;

    for(int i = 0; i < max_iterations, i++){
        
    }


int main(){

}