#include <vector>
#include "Session.h"
#include "Agent.h"
#include "Tree.h"

using namespace std;

enum BFS{}; //delete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

ContactTracer::ContactTracer() {}

Agent * ContactTracer::clone() {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    int dequeueNode = session.dequeueInfected();

    //1. dequeues a wantedNode from infectedQueue
//2. sends to BFS the wantedNode so it would build the tree with wantedNode as a root
//3. CT calls the traceTree method with a tree that it received from BFS
//4. CT receive the nodeToDisconnect from traceTree (depending on treeTYpe)
//5. CT removes all the nodeToDisconnect's edges
// CT builds the desired Tree by receiving the instance of the tree from Session's 'createTree' method;
}

Tree* ContactTracer::createBFS(Session &session, int rootNode) {
    Tree *outputTree = Tree::createTree(session, rootNode);
    Graph tempGraph(*session.getGraph());
    Tree *tempTree;
    vector<Tree *> queue;
    vector<int> wasAdded;

    for (int i = 0; i < tempGraph.getNeighbors(rootNode).size(); i++)
        wasAdded.push_back(0);

    queue.push_back(outputTree);

    while(!queue.empty()) {
        tempTree = queue.front();
        queue.erase(queue.begin());
        wasAdded.at(tempTree->getNodeIndex()) = 1;

        for (int t : tempGraph.getNeighbors(tempTree->getNodeIndex())) {

            if (wasAdded.at(t) == 0) {
                Tree* toAdd = tempTree->createTree(session, t);
                tempTree->addChild(*toAdd);
                wasAdded.at(t) = 1;
                queue.push_back(toAdd);
            }
        }
    }
    return outputTree;
}




//    virtual void act(Session& session)=0;
//    virtual Agent* clone()=0; //calls the desired copy CTR