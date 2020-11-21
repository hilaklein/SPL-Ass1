#include "../include/Graph.h"
#include <vector>
#include <iostream>
using namespace std;

//Graph constructor
Graph::Graph(std::vector<std::vector<int>> matrix) : wasInfected(vector<int>()), edges(vector<vector<int>>()) {
    wasInfected = vector<int>(matrix.size(), 0);
    cout << "printing 'matrix' (in Graph constructor): " << endl;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j];
        }
        cout<<endl;
    }
    edges = matrix;
    cout << "printing 'edges' (in Graph constructor): " << endl;
    for (int i = 0; i < edges.size(); i++)
    {
        for (int j = 0; j < edges[i].size(); j++)
        {
            cout << edges[i][j];
        }
        cout<<endl;
    }
    matrix.clear();
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
                if (tempNeighbors.at(k) == 1) {
                    tempNeighbors.clear();
                    return true;
                }
            }
            tempNeighbors.clear();
        }
    }
    return false;
}
