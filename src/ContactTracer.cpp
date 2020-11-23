#include <vector>
#include "../include/Session.h"
#include "../include/Agent.h"

using namespace std;

ContactTracer::ContactTracer() = default;
ContactTracer::~ContactTracer() = default;
ContactTracer::ContactTracer(const ContactTracer& aCT) {}

Agent * ContactTracer::clone() const{
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    if (session.infQueueIsEmpty()) return;
    int dequeueNode = session.dequeueInfected(); // dequeues a wantedNode from infectedQueue
    Tree* currTree = createBFS(session, dequeueNode); //sends to BFS the wantedNode so it would build a tree with wantedNode as a root
    int nodeToDisconnect = currTree->traceTree(); // calls the traceTree() and receives the nodeToDisconnect (depending on treeTYpe)
    //Graph* tempGraph = &session.getGraph();
    //!disconnectNode (which will be Graph.cpp method) logic insert here, instead of trying to disconnect remotely, cause it doesnt working:

    session.getGraph().disconnectNode(nodeToDisconnect);
//    vector<int> neighbors = tempGraph->getNeighbors(nodeToDisconnect);
//    for (int i = 0; i < neighbors.size(); i++) { //removes all the nodeTo Disconnect is edges
//        neighbors.at(i) = 0;
//        tempGraph->getNeighbors(i).at(nodeToDisconnect) = 0;
//    }
    delete currTree;
    //neighbors.clear();
}

Tree* ContactTracer::createBFS(Session &session, int rootNode) {
    Tree* outputTree = Tree::createTree(session, rootNode); //create desired type tree
    Graph* tempGraph = &session.getGraph(); //receive current state of graph
    Tree* tempTree;
    vector<Tree *> queue; //queue of nodes to run a BFS algorithm on them
    vector<int> wasAdded(session.numOfNodes, 0); //nodes that were already added to tree as someone's child - prevents to add some node two times as child

    queue.push_back(outputTree); //adding first node - it'll be the root of desired BFS tree
    Tree* toAdd;
    while(!queue.empty()) {
        tempTree = queue.front(); //dequeue 1st stage
        queue.erase(queue.begin()); // dequeue 2nd stage
        wasAdded.at(tempTree->getNodeIndex()) = 1; //marking the dequeued node as 'taken care of'
        vector<int> currNeighbors = tempGraph->getNeighbors(tempTree->getNodeIndex()); //curr node's neighbors - they are potential children

        for (int i : currNeighbors) { //running through curr node's neighbors
            if (wasAdded.at(i) == 0) {
                toAdd = Tree::createTree(session, i); //creating a neighbor as a new tree
                tempTree->addChild(*toAdd); //add a neighbor as a new child to curr tree;
                // !!!addChild creates tempTree clone so there is a need to release the memory here!!!
                wasAdded.at(i) = 1; //marking the neighbor as 'taken care of'
                queue.push_back(&(tempTree->getChild(i))); //adding neighbor to queue for next BFS 'scans'
                delete toAdd;// -> leave it comment out: i think it deletes toAdd also as tempTree child -> the reason is that tempTree.addChild pushes toAdd as a pointer and
                // not as new instance, because tempTree children vector is vector of pointers
            }
        }
    }
    //delete tempTree; - don't think this is needed here cause we still be needed Trees' data on the heap
    queue.clear();
    wasAdded.clear();
    return outputTree;
}