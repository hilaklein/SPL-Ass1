#include <vector>
#include "../include/Session.h"
#include "../include/Agent.h"

using namespace std;


Virus::Virus(int nodeInd) : nodeInd(nodeInd){}

Virus::Virus(const Virus& aVirus) : nodeInd(this->nodeInd){}

Agent* Virus::clone() const{
    return new Virus(*this);
}

void Virus::act(Session &session) { // Animal
    Graph* tempGraph = &session.getGraph(); //receive current state of graph
    if (!tempGraph->isInfected(nodeInd))
        session.enqueueInfected(nodeInd); //if node was never infected (in the infectedQueue), then mark it as infected
    vector<int> neighbors = tempGraph->getNeighbors(nodeInd); //receiving current virus neighbors
    for (int i = 0; i < session.numOfNodes; i++) { //running through curr virus neighbors to spread into one that was never infected
        //do nor spread into yourself -> you are already infected + check that neighbor.at(i) was never infected
        if (neighbors.at(i) == 1 && !tempGraph->isInfected(i)) {
            tempGraph->infectNode(i); //mark neighbor as infected
            Virus *addV = new Virus(i);
            session.addAgent(*addV); //add neighbor as new agent
            i = session.numOfNodes; //break
        }
    }
}

