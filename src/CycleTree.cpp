#include "../include/Tree.h"
#include <vector>

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

int CycleTree::traceTree() {
    int output = node;
    if (children.empty())
        return output;
    Tree* tempTree = children.front();
    for (int i = 0; i < currCycle; i++){
        if (tempTree->getChildren().empty()) {
            output = tempTree->getNodeIndex();
            return output;
        }
        tempTree = tempTree->getChildren().front();
        output = tempTree->getNodeIndex();
    }
    return output;

}

Tree * CycleTree::clone() const {
    return new CycleTree(*this);
}