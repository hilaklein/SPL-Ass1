#include "../include/Session.h"
#include "../include/Agent.h"
#include <vector>
#include <iostream>
#include <fstream>
using json = nlohmann::json;

using namespace std;


Session::Session(const std::string &path) : numOfNodes(0), cycleCounter(0), g(),
treeType(), agents(vector<Agent*>()), infectedQueue(vector<int>()) {
    ifstream configFile(path);
    json j;
    configFile >> j;
    cout<<"running in Session" << endl;

    numOfNodes = j["graph"].size();
    g = Graph(j["graph"]);
    string tempTreeType = j["tree"];
    char charTreeType = tempTreeType[0];
    cout<<"running in Session: before switch" << endl;

    switch (charTreeType){
        case 'M' : treeType = MaxRank;
            break;
        case 'R' : treeType = Root;
            break;
        case 'C' : treeType = Cycle;
            break;
        default:
            break;
    }
    cout<<"running in Session: before agents initialization" << endl;

    initAgents(j);
    j.clear();
    tempTreeType.clear();
    configFile.close();
    cout<<"running in Session: after j.clear" << endl;

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

// copy constructor
Session::Session(Session &other) : numOfNodes(other.numOfNodes),cycleCounter(other.cycleCounter),
agents(),g(other.g),treeType(other.treeType), infectedQueue() {
    int size =other.agents.size();
    for(int i = 0; i <size; i++){
        infectedQueue.push_back(other.infectedQueue[i]);
        agents.push_back(other.agents[i]);
    }
}


// copy assignment
Session & Session::operator=(const Session &other) {
    if (this == &other) return *this;
    if (!agents.empty()) {
        int size = agents.size();
        for (int i = size - 1; i >= 0; i--) {
            delete agents[i];
        }
    }
    agents.clear();
    int otherChildSize = other.agents.size();
    for (int i = 0; i < otherChildSize; i++) {
        Agent *a = other.agents[i];
        agents.push_back(a);
    }
    return *this;
}

// move constructor
Session::Session(Session &&other) : numOfNodes(other.numOfNodes), cycleCounter(other.cycleCounter),
                                    /*g(*&other.g),*/ treeType(other.treeType), agents(*&other.agents), infectedQueue(*&other.infectedQueue), g(std::move(other.g)) {

    int size = other.agents.size();
    for(int i = 0 ; i < size ; i++) {
        other.agents[i] = nullptr;
    }
    other.agents.clear();
}

// move assignment
Session& Session::operator=(Session &&other) noexcept {
    if (this == &other)
        return *this;
    int size = agents.size();
    for (int i = 0; i < size; i++) {
        if (agents[i]) {
            delete agents[i];
        }
        agents.clear();
    }

    int otherChildSize = other.agents.size();
    for (int i = 0; i < otherChildSize; i++) {
        agents.push_back(other.agents[i]);
    }
    return *this;
}

void Session::enqueueInfected(int x) {
    infectedQueue.push_back(x);
}

int Session::dequeueInfected(){
    int outputNode = infectedQueue.front();
    infectedQueue.erase(infectedQueue.begin());
    return outputNode;
}

TreeType Session::getTreeType() const{
    return treeType;
}

Graph& Session::getGraph()/* const */ {return g;}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

//void Session::setGraph(const Graph &graph) {}

void Session::simulate() {
    bool allAreInfected = false;
    bool virusCanSpread = true;
    while(!allAreInfected && virusCanSpread) {
        int size = agents.size();
        for (int i = 0 ; i < size; i++){
            agents.at(i)->act(*this);
        }
        allAreInfected = g.isAllInfected();
        virusCanSpread = g.canSpread();
    }
    createOutput();
}

void Session::initAgents(json& j) {
    for (int i = 0; i < j["agents"].size(); i++){
        string str = j["agents"][i][0];
        int nodeIndex = j["agents"][i][1];
        char type = str.at(0);
        switch (type) {
            case 'V': addAgent(Virus(nodeIndex));
                break;
            case 'C': addAgent(ContactTracer());
                break;
            default:
                break;
        }
    }
}

void Session::createOutput() {
    if (std::ifstream ("./output.json"))
        remove("./output.json");

    std::ofstream output("./output.json");
    json j;
    vector<int> tempNeighbors;
    vector<int> zeros (numOfNodes, 0);
    vector<int> addV = zeros;
    for (int i = 0; i < numOfNodes; i++) {
        tempNeighbors = g.getNeighbors(i);
        for (int k = 0; k < tempNeighbors.size(); k++) {
            addV.at(tempNeighbors.at(k)) = 1;
        }
        j["graph"][i] = addV;
        addV = zeros;
    }

    vector<int> infectedNodes;
    for (int i = 0; i < numOfNodes; i++){
        if (g.wasInfected.at(i) == 1)
            infectedNodes.push_back(i);
    }

    j["infected"] = infectedNodes;
    output << j;
    tempNeighbors.clear();
    zeros.clear();
    addV.clear();
    infectedNodes.clear();
    j.clear();
}

bool Session::infQueueIsEmpty() {
    return this->infectedQueue.empty();
}



