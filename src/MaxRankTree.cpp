#include "../include/Tree.h"
#include <vector>

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    Tree* out = &traceMaxTree(this);
    int output = out->getNodeIndex();
    return output;
}

Tree& MaxRankTree::traceMaxTree(Tree* treeToRun) {
    if (treeToRun->getChildren().empty())
        return *treeToRun;
    Tree* output = treeToRun;
    for (Tree* tempTree : treeToRun->getChildren()){
        tempTree = &traceMaxTree(tempTree);
        if (tempTree->getChildren().size() > output->getChildren().size())
            output = tempTree;

    }
    return *output;
}

Tree * MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}