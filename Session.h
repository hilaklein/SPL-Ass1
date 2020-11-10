#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
using namespace std;

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);

    int numOfNodes; //number of given nodes

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    
private:
    //const vector<vector<int>> buildMatrix(string graph); -- seems like we dont need this one cause Graph constructor can receive j["graph"] as vector matrix
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;

protected:
    vector<int>* infectedQueue; //a queue which carry the indexes of the infected nodes.

};

#endif
