#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

using namespace std;

class Graph{
public:
    Graph(vector<vector<int>> matrix);

    Graph();
    vector<int> getNeighbors(int nodeIndex);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    vector<int> wasInfected;
    bool isAllInfected();
    bool canSpread();
    void disconnectNode(int nodeToDisconnect);

private:
    std::vector<std::vector<int>> edges;
};

#endif
