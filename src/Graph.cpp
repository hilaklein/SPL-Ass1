#include "../include/Graph.h"
#include <vector>
using namespace std;


//Graph constructor
Graph::Graph(std::vector<std::vector<int>> matrix) : wasInfected(vector<int>()),yellow(vector<int>()), edges(vector<vector<int>>()) {
    wasInfected = vector<int>(matrix.size(), 0);
    yellow = vector<int>(matrix.size(), 0);
    edges = matrix;
    matrix.clear();
}

Graph::Graph() : wasInfected(),yellow(), edges() {}

vector<vector<int>> Graph::getEdges() const {
    return edges;
}

vector<int> Graph::getNeighbors(int nodeIndex) {
    vector<int> indexes = edges.at(nodeIndex);
    vector<int> output;
    int sizeIndexes = indexes.size();
    for (int i = 0; i < sizeIndexes; i++){
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
    for(int y : yellow){
        if(y==1){
            return true;
        }
    }
    int sizeWasInfected = wasInfected.size();
    for (int i = 0; i < sizeWasInfected; i++)
    {
        if (wasInfected.at(i)==1){
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
//
//bool Graph::canSpread() {
//    int sizeWasInfected = wasInfected.size();
//    for (int i = 0; i < sizeWasInfected; i++)
//    {
//        if (isInfected(i)){
//            vector<int> tempNeighbors = getNeighbors(i);
//            for (int k : tempNeighbors){
//                if (wasInfected.at(k) == 0) {
//                    tempNeighbors.clear();
//                    return true;
//                }
//            }
//            tempNeighbors.clear();
//        }
//    }
//    return false;
//}

void Graph::disconnectNode(int nodeToDisconnect) {
    int edgesSize = edges.size();
    for (int i = 0; i < edgesSize; i++) {
        edges.at(nodeToDisconnect).at(i) = 0;
        edges.at(i).at(nodeToDisconnect) = 0;
    }
}
