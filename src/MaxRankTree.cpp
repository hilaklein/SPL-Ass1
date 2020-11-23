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

//Tree* MaxRankTree::traceTree(Tree* curr) {
//    if (curr->getChildren().size() == 0)
//        return curr;
//    Tree* out
//    for (Tree* tempTree : curr->getChildren()){
//
//    }
//
//}

//int MaxRankTree::traceTree() {
//    int output = node;
//
//    if (children.empty())
//        return 0;
//
//    int tempValue = children.size();
//    int childValue;
//    for (Tree* tempTree : children){
//        childValue = tempTree->getChildren().size();
//
//        if (childValue > tempValue) {
//            tempValue = childValue;
//            output = tempTree->getNodeIndex();
//        }
//        tempTree = tempTree->traceTree();
//    }
//    return output;
//}

Tree * MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}