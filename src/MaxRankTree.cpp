#include "../include/Tree.h"
#include <vector>

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    int output = node;
    if (!children.empty())
        return output;
    int tempValue;
    for (Tree* tempTree:children){
        tempValue = tempTree->traceTree();
        if (output < tempValue)
            output = tempValue;
    }
    return output;
}

Tree * MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}