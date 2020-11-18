#include "../include/Tree.h"
#include <vector>

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() {
    return node;
}

Tree * RootTree::clone() const {
    return new RootTree(*this);
}