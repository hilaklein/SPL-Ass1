#include <vector>
#include "../include/Session.h"
#include "../include/Agent.h"

using namespace std;


Virus::Virus(int nodeInd) : nodeInd(nodeInd){}
Virus::~Virus()= default;
Virus::Virus(const Virus& aVirus) : nodeInd(aVirus.nodeInd){}

Agent* Virus::clone() const{
    return new Virus(*this);
}

void Virus::act(Session &session) {
    Graph* tempGraph = &session.getGraph(); //receive current state of graph
    if ((tempGraph->wasInfected.at(nodeInd)) == 1) {
        session.enqueueInfected(nodeInd); //if node was never infected (in the infectedQueue), then mark it as infected
        tempGraph->infectNode(nodeInd);
        tempGraph->wasInfected.at(nodeInd) = 2;
    }
    Virus *addV;
    vector<int> neighbors = tempGraph->getNeighbors(nodeInd); //receiving current virus neighbors
    int sizeNeighbors = neighbors.size();
    for (int i = 0; i < sizeNeighbors; i++) { //running through curr virus neighbors to spread into one that was never infected
        if (tempGraph->wasInfected.at(neighbors.at(i))==0) {
            addV = new Virus(neighbors.at(i));
            tempGraph->wasInfected.at(neighbors.at(i)) = 1;
            session.addAgent(*addV); //add neighbor as new agent
            delete addV; //cause addAgent creates a deep copy of 'addV'
            i = sizeNeighbors;
        }
    }
    neighbors.clear();
}

