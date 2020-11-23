#include "../include/Session.h"
#include "../include/Agent.h"
#include <vector>
#include <iostream>
#include <fstream>
using json = nlohmann::json;

using namespace std;


Session::Session(const std::string &path) : numOfNodes(), cycleCounter(0), g(),
treeType(), agents(), infectedQueue() {
    ifstream configFile(path);
    json j;
    configFile >> j;

    numOfNodes = j["graph"].size();
    g = Graph(j["graph"]);
    string tempTreeType = j["tree"];
    char charTreeType = tempTreeType[0];
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

    initAgents(j);
    j.clear();
    tempTreeType.clear();
    configFile.close();
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
                                   g(other.g),treeType(other.treeType), agents(), infectedQueue(other.infectedQueue) {
    int size = other.agents.size();
    for(int i = 0; i < size; i++){
        agents.push_back(other.agents[i]);
    }
}


// copy assignment
Session & Session::operator=(const Session &other) {
    if (this == &other) return *this;
    numOfNodes = other.numOfNodes;
    cycleCounter = other.cycleCounter;
    g = other.g;
    treeType = other.treeType;
    infectedQueue = other.infectedQueue;
    if (!agents.empty()) {
        int size = agents.size();
        for (int i = 0; i < size; i++) {
            delete agents[i];
        }
    }
    agents.clear();
    int otherSize = other.agents.size();
    for (int i = 0; i < otherSize; i++) {
        agents.push_back(other.agents[i]);
    }
    return *this;
}

// move constructor
Session::Session(Session &&other) noexcept : numOfNodes(), cycleCounter(),
                                    g(), treeType(), agents(), infectedQueue() {
    numOfNodes = other.numOfNodes;
    cycleCounter = other.cycleCounter;
    g = other.g;
    treeType = other.treeType;
    int size = other.agents.size();
    for(int i = 0 ; i < size ; i++) {
        agents.push_back(other.agents[i]->clone());
        delete other.agents[i];
    }
    other.agents.clear();
    int infectedSize = other.infectedQueue.size();
    for(int i = 0; i < infectedSize; i++){
        infectedQueue.push_back(other.infectedQueue[i]);
    }
}

// move assignment
Session& Session::operator=(Session &&other) noexcept {
    if (this == &other)
        return *this;
    if (!agents.empty()) {
        int size = agents.size();
        for (int i = 0; i < size; i++) {
            delete agents[i];

        }
    }
    agents.clear();
    infectedQueue.clear();

    int otherSize = other.agents.size();
    for (int i = 0; i < otherSize; i++) {
        agents.push_back(other.agents[i]);
        other.agents.at(i) = nullptr;
    }
    numOfNodes = other.numOfNodes;
    cycleCounter = other.cycleCounter;
    g = other.g;
    treeType = other.treeType;
    infectedQueue = other.infectedQueue;
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

Graph& Session::getGraph() {return g;}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}


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
        cycleCounter++;
    }
    createOutput();
}

void Session::setGraph(const Graph &graph) {
    vector<vector<int>> otherEdges = graph.getEdges();
    vector<vector<int>> thisEdges = g.getEdges();
    int size = thisEdges.size();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
         thisEdges.at(i).at(j) = otherEdges.at(i).at(j);
        }
    }
}

void Session::initAgents(json& j) {
    int sizeAgents = j["agents"].size();
    for (int i = 0; i < sizeAgents; i++){
        string str = j["agents"][i][0];
        int nodeIndex = j["agents"][i][1];
        char type = str.at(0);
        switch (type) {
            case 'V': {
                addAgent(Virus(nodeIndex));
                g.yellow.at(nodeIndex) = 1;
                break;
            }
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
    int sizeTempNeighbors;
    for (int i = 0; i < numOfNodes; i++) {
        tempNeighbors = g.getNeighbors(i);
        sizeTempNeighbors = tempNeighbors.size();
        for (int k = 0; k < sizeTempNeighbors; k++) {
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



