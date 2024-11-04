#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    int numNodes = 20;        // Number of nodes
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

    int connectionsMade = 0;

    // Generate random connections until we reach the target
    while (connectionsMade < targetConnections) {
        for (int i = 1; i < saturation*numNodes; i ++){
            int nodeA = i;
            int nodeB = 1 + std::rand() % numNodes;

        // Ensure no self-connections and nodeA < nodeB to avoid duplicates
        if (nodeA != nodeB && nodeA < nodeB) {
            outputFile << nodeA << " " << nodeB << std::endl;
            connectionsMade++;
        }
        }
    }


    outputFile.close();
    std::cout << "File with nodes generated" << std::endl;

    return 0;
}
