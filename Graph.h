#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

using namespace std;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);

    Graph();
//    Graph(const Graph &aGraph); // - copy constructor
    std::vector<int> getNeighbors(int nodeIndex);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    vector<int> wasInfected;

private:
    std::vector<std::vector<int>> edges;
};

#endif
