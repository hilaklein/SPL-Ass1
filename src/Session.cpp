#include "../include/Session.h"
#include "../include/Agent.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "../cmake-build-debug/json.hpp"
using json = nlohmann::json;

using namespace std;


Session::Session(const std::string &path) : numOfNodes(0), cycleCounter(0), g(), treeType(), agents(vector<Agent*>()), infectedQueue(vector<int>()) {
    ifstream configFile(path);
    json j;
    j << configFile;
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
Session::Session(Session &other) : agents(other.agents),g(other.g),treeType(other.treeType), infectedQueue(other.infectedQueue) {}


// copy assignment
Session & Session::operator=(const Session &other) { //if statement in case A1=A1??????????????????????????
    if(!agents.empty()) {
        int size = agents.size();
        for (int i = size - 1; i >= 0; i--) {
            delete agents[i];
        }
    }
    agents.clear();
    int otherChildSize = other.agents.size();
    for(int i = 0 ; i < otherChildSize; i++) {
        Agent *a = (this)->agents[i];  //need to be other.agents?????????????????????????????????????????
        agents.push_back(a);
    }
    return *this;
}

// move constructor
Session::Session(Session &&other) : agents(other.agents),g(other.g),treeType(other.treeType), infectedQueue(other.infectedQueue) {
    int size = other.agents.size();
    for(int i = 0 ; i < size ; i++) {
        other.agents[i] = nullptr;
    }
    other.agents.clear();
}

// move assignment
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

void Session::setGraph(const Graph &graph) {

}

void Session::simulate() {
    cout << "Session: simulate: line before createOutput()" << endl;
    createOutput(); // -> remove this line back to the bottom of the method in the end of the tests
    cout << "Session: simulate: line after createOutput()" << endl;
    bool allAreInfected = g.isAllInfected();
    bool virusCanSpread = g.canSpread();
    int debugIndex = 0;
    while(!allAreInfected || virusCanSpread) {
        cout << "session: simulate: while loop: debugger loop indicator. loop #" << debugIndex << endl;
        debugIndex++;
        int size = agents.size();
        for (int i = 0 ; i < size; i++){
            agents.at(i)->act(*this);
            cout << "session: simulate: while loop: for loop: debugger loop indicator. loop #" << i << endl;
        }
        allAreInfected = g.isAllInfected();
        virusCanSpread = g.canSpread();
    }
    cout << "session: simulate: while loop ended " << endl;
    //createOutput(); -> remove the 'commentOut' after tests
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
        }
    }
}

void Session::createOutput() {
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
    //vector<int> toPrint = g.wasInfected;
    //cout << "Session: createOutput: line before j['infected']: wasInfected:" << toPrint. << endl;
    j["infected"] = g.wasInfected;
    output << j;
    j.clear();
}



