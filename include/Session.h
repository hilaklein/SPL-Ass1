#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "../cmake-build-debug/json.hpp"
using namespace std;
using json = nlohmann::json;

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
    Session& operator=(const Session &other); // copy Assignment
    Session(Session &&other) noexcept; // move ctr
    Session& operator=(Session &&other) noexcept; // move assignment

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph); // from the office-hours: {g = graph;}
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    Graph& getGraph(); // const;
    bool infQueueIsEmpty();

    int numOfNodes; //number of given nodes
    int cycleCounter;

private:
    void createOutput();
    void initAgents(json& j);
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;


protected:
    vector<int> infectedQueue; //a queue which carry the indexes of the infected nodes.

};

#endif
