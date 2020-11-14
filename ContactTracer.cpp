#include <vector>
#include "Session.h"
#include "Agent.h"
#include "Tree.h"

using namespace std;

ContactTracer::ContactTracer() {}

ContactTracer::ContactTracer(const Agent& aCT) {}

Agent * ContactTracer::clone() {
    return new ContactTracer(*this);
}

//1. dequeues a wantedNode from infectedQueue
//2. sends to BFS the wantedNode so it would build the tree with wantedNode as a root
//3. CT calls the traceTree method with a tree that it received from BFS
//4. CT receive the nodeToDisconnect from traceTree (depending on treeTYpe)
//5. CT removes all the nodeToDisconnect's edges
void ContactTracer::act(Session &session) {
    int dequeueNode = session.dequeueInfected();
    Tree* currTree = createBFS(session, dequeueNode);
    int nodeToDisconnect = currTree->traceTree();
    Graph tempGraph(*session.getGraph());
    vector<int> neighbors = tempGraph.getNeighbors(nodeToDisconnect);
    for (int i = 0; i < neighbors.size(); i++) {
        neighbors.at(i) = 0;
        tempGraph.getNeighbors(i).at(nodeToDisconnect) = 0;
    }
}

Tree* ContactTracer::createBFS(Session &session, int rootNode) {
    Tree *outputTree = Tree::createTree(session, rootNode);
    Graph tempGraph(*session.getGraph());
    Tree *tempTree;
    vector<Tree *> queue;
    vector<int> wasAdded;

    for (int i = 0; i < session.numOfNodes; i++)
        wasAdded.push_back(0);

    queue.push_back(outputTree);

    while(!queue.empty()) {
        tempTree = queue.front();
        queue.erase(queue.begin());
        wasAdded.at(tempTree->getNodeIndex()) = 1;
        vector<int> currNeighbors = tempGraph.getNeighbors(tempTree->getNodeIndex());

        for (int i = 0; i < currNeighbors.size(); i++) {
            if (currNeighbors.at(i) != 0 && wasAdded.at(i) == 0) {
                Tree* toAdd = tempTree->createTree(session, i);
                tempTree->addChild(*toAdd);
                wasAdded.at(i) = 1;
                queue.push_back(toAdd);
            }
        }
    }
    return outputTree;
}