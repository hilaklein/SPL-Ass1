#include <vector>
#include "../include/Session.h"
#include "../include/Agent.h"

using namespace std;


Virus::Virus(int nodeInd) : nodeInd(nodeInd){}

Virus::Virus(const Virus& aVirus) : nodeInd(aVirus.nodeInd){}

Agent* Virus::clone() const{
    return new Virus(*this);
}

void Virus::act(Session &session) { // Animal
    Graph* tempGraph = &session.getGraph(); //receive current state of graph
    if (!tempGraph->isInfected(nodeInd))
        session.enqueueInfected(nodeInd); //if node was never infected (in the infectedQueue), then mark it as infected
    vector<int> neighbors = tempGraph->getNeighbors(nodeInd); //receiving current virus neighbors
    for (int ind : neighbors) { //running through curr virus neighbors to spread into one that was never infected
        //do nor spread into yourself -> you are already infected + check that neighbor.at(i) was never infected
        if (!tempGraph->isInfected(ind)) {
            tempGraph->infectNode(ind); //mark neighbor as infected
            Virus *addV = new Virus(ind);
            session.addAgent(*addV); //add neighbor as new agent
            //ind = session.numOfNodes; //break -> not needed after all
            delete addV; //cause addAgent creates a deep copy of 'addV'
        }
    }
    neighbors.clear();
}

