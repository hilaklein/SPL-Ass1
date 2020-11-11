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

Session::Session(const std::string &path) : allInfected(true), containVirus(true) {
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

void Session::simulate() {
//    int size = Session::agents.size();
//    while(allInfected || containVirus){ // while not all infected or there is still a virus on graph
//        for(int i = 0 ; i < size ; i++){
//            agents[i]->act(*this);
//        }
//        size = agents.size();
//    }
}
void Session::enqueueInfected(int x) {
    infectedQueue->push_back(x);
}

int Session::dequeueInfected(){
    //int indValue = infectedQueue->*pop_back();
    infectedQueue->erase(infectedQueue->begin());

}

TreeType Session::getTreeType() const{
    return treeType;
}


//help method to convert a json into vector matrix
//vector<vector<int>>& buildMatrix(string graph){
//    vector<vector<int>> matrix;
//    int rowSize = graph[0].
//    int colSize;
//}

//Graph graph = new Graph(matrix);


//void addAgent(Agent agent){
//    Agent* clone = agent.clone();
//}

