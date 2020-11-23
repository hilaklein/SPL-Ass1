#include "../include/Tree.h"
#include <vector>

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

int CycleTree::traceTree() {
    int output = node;
    if (children.empty())
        return output;
    Tree* tempTree = this;
    for (int i = 0; i < currCycle; i++){
        tempTree = tempTree->getChildren().front();
        output = tempTree->getNodeIndex();
        if (tempTree->getChildren().empty()) {
            return output;
        }
    }
    return output;

}

Tree * CycleTree::clone() const {
    return new CycleTree(*this);
}