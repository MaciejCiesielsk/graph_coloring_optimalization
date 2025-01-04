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

    // Use a uniform probability to decide inclusion of each edge
    for (int nodeA = 1; nodeA <= numNodes; ++nodeA) {
        for (int nodeB = nodeA + 1; nodeB <= numNodes; ++nodeB) {
            double probability = static_cast<double>(std::rand()) / RAND_MAX;

            if (probability <= saturation) {
                edges.emplace_back(nodeA, nodeB);
                if (static_cast<int>(edges.size()) >= targetConnections) {
                    break;
                }
            }
        }
        if (static_cast<int>(edges.size()) >= targetConnections) {
            break;
        }
    }

    // Shuffle and truncate edges if oversaturated
    std::random_shuffle(edges.begin(), edges.end());
    if (static_cast<int>(edges.size()) > targetConnections) {
        edges.resize(targetConnections);
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
