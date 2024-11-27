#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// Define the objective function
int objective_function(const std::vector<int>& solution)
{ // Added const qualifier
    // TODO: Implement your objective function here
    // The objective function should evaluate
    // the quality of a given solution and
    // return a numerical value representing
    // the solution's fitness
    // Example: return std::accumulate(solution.begin(),
    // solution.end(), 0);
    return std::accumulate(solution.begin(), solution.end(),
                           0);
}

// Define the neighborhood function
std::vector<std::vector<int> >
get_neighbors(const std::vector<int>& solution)
{ // Added const qualifier
    std::vector<std::vector<int> > neighbors;
    for (size_t i = 0; i < solution.size(); i++) {
        for (size_t j = i + 1; j < solution.size(); j++) {
            std::vector<int> neighbor = solution;
            std::swap(neighbor[i], neighbor[j]);
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

// Define the Tabu Search algorithm
std::vector<int>
tabu_search(const std::vector<int>& initial_solution,
            int max_iterations, int tabu_list_size)
{ // Added const qualifier
    std::vector<int> best_solution = initial_solution;
    std::vector<int> current_solution = initial_solution;
    std::vector<std::vector<int> > tabu_list;

    for (int iter = 0; iter < max_iterations; iter++) {
        std::vector<std::vector<int> > neighbors
            = get_neighbors(current_solution);
        std::vector<int> best_neighbor;
        int best_neighbor_fitness
            = std::numeric_limits<int>::max();

        for (const std::vector<int>& neighbor : neighbors) {
            if (std::find(tabu_list.begin(),
                          tabu_list.end(), neighbor)
                == tabu_list.end()) {
                int neighbor_fitness
                    = objective_function(neighbor);
                if (neighbor_fitness
                    < best_neighbor_fitness) {
                    best_neighbor = neighbor;
                    best_neighbor_fitness
                        = neighbor_fitness;
                }
            }
        }

        if (best_neighbor.empty()) {
            // No non-tabu neighbors found,
            // terminate the search
            break;
        }

        current_solution = best_neighbor;
        tabu_list.push_back(best_neighbor);
        if (tabu_list.size() > tabu_list_size) {
            // Remove the oldest entry from the
            // tabu list if it exceeds the size
            tabu_list.erase(tabu_list.begin());
        }

        if (objective_function(best_neighbor)
            < objective_function(best_solution)) {
            // Update the best solution if the
            // current neighbor is better
            best_solution = best_neighbor;
        }
    }

    return best_solution;
}

int main()
{
    // Example usage
    // Provide an initial solution
    std::vector<int> initial_solution = { 1, 2, 3, 4, 5 };
    int max_iterations = 100;
    int tabu_list_size = 10;

    std::vector<int> best_solution = tabu_search(
        initial_solution, max_iterations, tabu_list_size);
    std::cout << "Best solution:";
    for (int val : best_solution) {
        std::cout << " " << val;
    }
    std::cout << std::endl;
    std::cout << "Best solution fitness: "
              << objective_function(best_solution)
              << std::endl;

    return 0;
}