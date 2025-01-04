#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

int main() {
    int numNodes = 200;        // Number of nodes
    double saturation = 0.5;  // 50% saturation

    // Calculate the target number of connections
    int maxConnections = (numNodes * (numNodes - 1)) / 2;
    int targetConnections = static_cast<int>(saturation * maxConnections);

    std::ofstream outputFile("data-small.txt");
    if (!outputFile) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    outputFile << numNodes << std::endl;  // Write the number of nodes at the top

    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::vector<std::pair<int, int>> edges; // Store edges as pairs

    // Generate random connections until we reach the target
    while (static_cast<int>(edges.size()) < targetConnections) {
        for (int i = 1; i <= saturation * numNodes; i++) {
            int nodeA = i;
            int nodeB = 1 + std::rand() % numNodes;

            // Ensure no self-connections and nodeA < nodeB to avoid duplicates
            if (nodeA != nodeB) {
                if (nodeA > nodeB) std::swap(nodeA, nodeB);

                std::pair<int, int> edge = {nodeA, nodeB};

                // Check if the edge already exists
                if (std::find(edges.begin(), edges.end(), edge) == edges.end()) {
                    edges.push_back(edge);
                }

                if (static_cast<int>(edges.size()) >= targetConnections) {
                    break;
                }
            }
        }
    }

    // Sort edges
    std::sort(edges.begin(), edges.end());

    // Write sorted edges to the file
    for (const auto &edge : edges) {
        outputFile << edge.first << " " << edge.second << std::endl;
    }

    outputFile.close();
    std::cout << "File with sorted edges generated" << std::endl;

    return 0;
}
