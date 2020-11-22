#include "../include/Tree.h"
#include <vector>

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

//int MaxRankTree::traceTree() {
//    int output = node;
//    if (children.empty())
//        return output;
//    int tempValue;
//    for (Tree* tempTree:children){
//        tempValue = tempTree->traceTree();
//        if (output < tempValue)
//            output = tempValue;
//    }
//    return output;
//}

//Tree* MaxRankTree::traceTree(Tree* curr) {
//    if (curr->getChildren().size() == 0)
//        return curr;
//    Tree* out
//    for (Tree* tempTree : curr->getChildren()){
//
//    }
//
//}




int MaxRankTree::traceTree() {
    int output = node;
    if (children.empty())
        return 0;
    int tempValue;
    for (Tree* tempTree:children){
        tempValue = children.size();
        if (tempTree->getChildren().size() > tempValue) {
            tempValue = tempTree->getChildren().size();
            output = tempTree->getNodeIndex();
        }
        tempTree->traceTree();
    }
    return output;
}

Tree * MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}