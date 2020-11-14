#include <vector>
#include "Session.h"
#include "Agent.h"
#include "Tree.h"

using namespace std;


Virus::Virus(int nodeInd) : nodeInd(nodeInd){}

Virus::Virus(const Virus& aVirus) : nodeInd(this->nodeInd){}

Agent* Virus::clone() {
    return new Virus(*this);
}

void Virus::act(Session &session) {
    
}



//class Virus: public Agent{
//public:
//    Virus(int nodeInd);
//
//    virtual void act(Session& session);
//
//    virtual Agent* clone();
//
//private:
//    const int nodeInd;
//};

