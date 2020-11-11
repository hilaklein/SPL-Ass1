#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
//#include "Session.h"
//#include "Session.h"

class Agent{
public:
    Agent();
    
    virtual void act(Session& session)=0;
    virtual Agent* clone()=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    
    virtual void act(Session& session);
    void removeNodeEdges(int nodeIndex);
//1. dequeues a wantedNode from infectedQueue
//2. sends to BFS the wantedNode so it would build the tree with wantedNode as a root
//3. CT calls the traceTree method with a tree that it received from BFS
//4. CT receive the nodeToDisconnect from traceTree (depending on treeTYpe)
//5. CT removes all the nodeToDisconnect's edges


    // CT builds the desired Tree by receiving the instance of the tree from Session's 'createTree' method;
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    
    virtual void act(Session& session);
private:
    const int nodeInd;
};

#endif
