#include "../include/Graph.h"
#include <vector>
using namespace std;


//Graph constructor
Graph::Graph(std::vector<std::vector<int>> matrix) : wasInfected(vector<int>()), edges(vector<vector<int>>()) {
    wasInfected = vector<int>(matrix.size(), 0);
    edges = matrix;
    matrix.clear();
}

Graph::Graph() {}





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
            for (int k : tempNeighbors){
                if (wasInfected.at(k) == 0) {
                    tempNeighbors.clear();
                    return true;
                }
            }
            tempNeighbors.clear();
        }
    }
    return false;
}

void Graph::disconnectNode(int nodeToDisconnect) {
    vector<int> neighbors = getNeighbors(nodeToDisconnect);
    for (int i = 0; i < edges.size(); i++) {
        edges.at(nodeToDisconnect).at(i) = 0;
        edges.at(i).at(nodeToDisconnect) = 0;
    }
}
