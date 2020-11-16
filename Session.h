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
    virtual ~Session(); // destructor
    Session(Session& other); // copy constructor
    Session &operator=(const Session &other); // copy Assignment
    Session(Session &&other); // move ctr
    Session operator=(Session &&other); // move assignment
    bool allInfected;
    bool containVirus;
    int numOfNodes; //number of given nodes

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;

    int cycleCounter;
    
private:
    //const vector<vector<int>> buildMatrix(string graph); -- seems like we dont need this one cause Graph constructor can receive j["graph"] as vector matrix
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;

protected:
    vector<int>* infectedQueue; //a queue which carry the indexes of the infected nodes.

};

#endif
