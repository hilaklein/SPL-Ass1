#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Tree.h"

class Agent{
public:
    Agent();
    
    virtual void act(Session& session)=0;
    virtual Agent* clone() const=0; //calls the desired copy CTR
};




class ContactTracer: public Agent{
public:
    ContactTracer();

    ContactTracer(const Agent& aCT); //copy constructor

    virtual void act(Session& session);

    virtual Agent* clone() const;

    Tree* createBFS(Session &session, int rootNode);
};





class Virus: public Agent{
public:
    Virus(int nodeInd);

    Virus(const Virus& aVirus); //copy-constructor
    
    virtual void act(Session& session);

    virtual Agent* clone() const;

private:
    const int nodeInd;
};

#endif
