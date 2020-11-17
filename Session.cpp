#include "Session.h"
#include "Agent.h"
#include <vector>

#include <iostream>
#include <fstream>
#include "cmake-build-debug/json.hpp"
using json = nlohmann::json;

using namespace std;


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

Graph& Session::getGraph()/* const */ {return g;}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

void Session::setGraph(const Graph &graph) {

}

void Session::simulate() {
    bool allAreInfected = g.isAllInfected();
    bool virusCanSpread = g.canSpread();
    while(!allAreInfected || virusCanSpread) {
        int size = agents.size();
        for (int i = 0 ; i < size; i++){
            agents.at(i)->act(*this);
        }
        allAreInfected = g.isAllInfected();
        virusCanSpread = g.canSpread();
    }
}

