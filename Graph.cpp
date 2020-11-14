#include "Graph.h"
#include <vector>
using namespace std;

//Graph constructor
Graph::Graph(std::vector<std::vector<int>> matrix) {
    edges = matrix;
    for (int i = 0; i < edges.size(); i++)
        wasInfected.push_back(0);
}

//Graph copy-constructor
//Graph::Graph(const Graph &aGraph) {
//
//}


std::vector<int> Graph::getNeighbors(int nodeIndex) {
 return edges.at(nodeIndex);
}


void Graph::infectNode(int nodeInd) {
    wasInfected.at(nodeInd) = 1;
}

bool Graph::isInfected(int nodeInd) {
    return (wasInfected.at(nodeInd) == 1);
}
