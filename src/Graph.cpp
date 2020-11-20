#include "../include/Graph.h"
#include <vector>
using namespace std;

//Graph constructor
Graph::Graph(std::vector<std::vector<int>> matrix) : wasInfected(edges.size(), 0), edges(vector<vector<int>>()) {
    edges = matrix;
}

Graph::Graph() {}

// copy-constructor
// destructor: release edges, release wasInfected
// copy assignment
// move constructor
// move assignment

//Graph::Graph(const Graph& aGraph) {
//
//}


vector<int> Graph::getNeighbors(int nodeIndex) {
    vector<int> indexes = edges.at(nodeIndex);
    vector<int> output;
    for (int i = 0; i < indexes.size(); i++){
        if (indexes.at(i) == 1)
            output.push_back(i);
    }
    indexes.clear();
    return output;
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

bool Graph::canSpread() {
    for (int i = 0; i < wasInfected.size(); i++)
    {
        if (isInfected(i)){
            vector<int> tempNeighbors = getNeighbors(i);
            for (int k = 0; k < tempNeighbors.size(); k++){
                if (tempNeighbors.at(k) == 0) {
                    tempNeighbors.clear();
                    return true;
                }
            }
            tempNeighbors.clear();
        }
    }
    return false;
}
