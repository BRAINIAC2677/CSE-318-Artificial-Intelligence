#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main()
{
    int numVertices, numEdges;
    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    // Generate random seed based on current time
    std::srand(std::time(nullptr));

    // Create and open the output file
    std::ofstream outFile("graph.txt");

    // Output the number of vertices and edges
    outFile << numVertices << " " << numEdges << "\n";

    // Generate edges with random weights
    for (int i = 0; i < numEdges; ++i)
    {
        int u = std::rand() % numVertices + 1;         // Vertex u (range: 1 to numVertices)
        int v = std::rand() % numVertices + 1;         // Vertex v (range: 1 to numVertices)
        int w = std::rand() % 2000000001 - 1000000000; // Weight (range: -10^9 to 10^9)

        outFile << u << " " << v << " " << w << "\n";
    }

    // Close the output file
    outFile.close();

    return 0;
}
