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


vector<int> Graph::getNeighbors(int nodeIndex) { // change it so vector with neighbors only will be returned!!!!!!!!!!!!!!!!!!!!!!!!!!
 return edges.at(nodeIndex);
}


void Graph::infectNode(int nodeInd) {
    wasInfected.at(nodeInd) = 1;
}

bool Graph::isInfected(int nodeInd) {
    return (wasInfected.at(nodeInd) == 1);
}

bool Graph::isAllInfected() {
    for (int i : wasInfected) {
        if (i != 1) return false;
    }
    return true;
}
