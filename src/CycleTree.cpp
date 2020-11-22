#include "../include/Tree.h"
#include <vector>

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}
int CycleTree::traceTree() {
    int output = node;
    Tree* tempTree = children.front();
    for (int i = 0; i < currCycle; i++){
        if (tempTree == 0)
            return output;
        tempTree = tempTree->getChildren().front();
        output = tempTree->getNodeIndex();
    }
    delete tempTree;
    return output;

}

Tree * CycleTree::clone() const {
    return new CycleTree(*this);
}

//destructor - not needed - there is Tree destructor, and 'currCircle' is  on the stack

//copy constructor
CycleTree::CycleTree(const CycleTree &other) : Tree(other), currCycle(other.currCycle){}

//copy assignment
CycleTree & CycleTree::operator=(const CycleTree &other) {
    if (this == &other) // A1=A1
        return *this;
    this->operator=(other);
    currCycle = other.currCycle;
}

//move constructor
CycleTree::CycleTree(CycleTree &&other) : Tree(*&other),currCycle(other.currCycle) {} //maybe need to send Tree(other) only

//move assignment
CycleTree CycleTree::operator=(CycleTree &&other) {
    if (this == &other)
        return *this;
    this->operator=(*&other); //maybe need to send operator=(other) only
    currCycle = std::move(other.currCycle);
}