#include "Session.h"
#include "Agent.h"
#include <vector>

#include <iostream>
#include <fstream>
#include "cmake-build-debug/json.hpp"
using json = nlohmann::json;

using namespace std;

//public:
//Session(const std::string& path);
//
//void simulate();
//void addAgent(const Agent& agent);
//void setGraph(const Graph& graph);
//


//TreeType getTreeType() const;
//
//private:
//Graph g;
//TreeType treeType;
//std::vector<Agent*> agents;

Session::Session(const std::string &path) : cycleCounter(0), g() {
    ifstream configFile(path);
    json j;
    j << configFile;

    numOfNodes = j["graph"].size();
    infectedQueue = new vector<int>;
    g = Graph(j["graph"]); //buildMatrix(j["graph"])
    string tempTreeType = j["tree"];
    char charTreeType = tempTreeType[0];
    switch (charTreeType){
        case 'M' : treeType = MaxRank;
            break;
        case 'R' : treeType = Root;
            break;
        case 'C' : treeType = Cycle;
            break;
    }
    agents = (vector<Agent*>)j["agents"];

}

Session::~Session() {// destructor
    int size = agents.size();
    for (int i = size - 1; i >= 0; i--) {
        if (agents[i]) {
            delete agents[i];
        }
        agents.clear();
    }
}
Session::Session(Session &other) : agents(other.agents),g(other.g),treeType(other.treeType), infectedQueue(other.infectedQueue) {} // copy
Session & Session::operator=(const Session &other) {
    if(!agents.empty()) {
        int size = agents.size();
        for (int i = size - 1; i >= 0; i--) {
            delete agents[i];
        }
    }
    agents.clear();
    int otherChildSize = other.agents.size();
    for(int i = 0 ; i < otherChildSize ; i++) {
        Agent *a = (this)->agents[i];
        agents.push_back(a);
    }
    return *this;
} // copy assignment
Session::Session(Session &&other) : agents(other.agents),g(other.g),treeType(other.treeType), infectedQueue(other.infectedQueue) {
    int size = other.agents.size();
    for(int i = 0 ; i < size ; i++) {
        other.agents[i] = nullptr;
    }
    other.agents.clear();
} // move ctr
Session Session::operator=(Session &&other) {
    if (this != &other) { // A1=A1
        if (&agents) {
            int size = agents.size();
            for (int i = size - 1; i >= 0; i--) {
                if (agents[i]) {
                    delete agents[i];
                }
            }

            int otherChildSize = other.agents.size();
            for (int i = 0; i < otherChildSize; i++) {
                agents[i] = other.agents[i];
            }
        }
        //node = other.node;
    }
    return *this;
} // move assignment

void Session::enqueueInfected(int x) {
    infectedQueue->push_back(x);
}

int Session::dequeueInfected(){
    int outputNode = infectedQueue->front();
    infectedQueue->erase(infectedQueue->begin());
    return outputNode;
}

TreeType Session::getTreeType() const{
    return treeType;
}

Graph& Session::getGraph() {return g;}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

void Session::setGraph(const Graph &graph) {

}

void Session::simulate() {
    bool allAreInfected = g.isAllInfected();
    bool virusCanSpread = true; //!!!!!!!!!!!!!!!!need to be implemented later
    while(!allAreInfected || virusCanSpread) {
        int size = agents.size();
        for (int i = 0 ; i < size; i++){
            agents.at(i)->act(*this);
        }
        allAreInfected = g.isAllInfected();
        virusCanSpread = true; //!!!!!!!!!!!!!!!!need to be implemented later
    }
}

//(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
//void simulate();
//(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)

