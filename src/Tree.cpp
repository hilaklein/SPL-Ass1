#include "../include/Tree.h"
#include <vector>
#include "../include/Session.h"
using namespace std;

Tree::Tree() : node(0), children() {}

Tree::Tree(int rootLabel) : node(rootLabel), children(vector<Tree*>()) {

}

// destructor
Tree::~Tree() {
    int size = children.size();
    for (int i = size - 1; i >= 0; i--) {
        if (children[i]) {
            delete children[i];
        }
        children.clear();
    }
}

// copy constructor
Tree::Tree(const Tree &other) : node(other.node), children() {
    int size = other.children.size();
    for(int i = 0; i < size; i++){
        children.push_back(other.children[i]);
    }
}


// copy assignment
Tree & Tree::operator=(const Tree &other) {
    if (this == &other) return *this;
    node = other.node;
    if (!children.empty()) {
        int size = children.size();
        for (int i = 0; i < size; i++) {
            delete children[i];
        }
    }
    children.clear();
    int otherSize = other.children.size();
    for (int i = 0; i < otherSize; i++) {
        children.push_back(other.children[i]);
    }
    return *this;
}

// move constructor
Tree::Tree(Tree &&other) noexcept : node(other.node), children() {
    int size = other.children.size();
    for(int i = 0 ; i < size ; i++) {
        children.push_back(other.children[i]->clone());
        delete other.children[i];
    }
    other.children.clear();
}

// move assignment
Tree & Tree::operator=(Tree &&other) noexcept {
    if (this == &other)
        return *this;
    if (!children.empty()) {
        int size = children.size();
        for (int i = 0; i < size; i++) {
            delete children[i];

        }
    }
    children.clear();

    int otherSize = other.children.size();
    for (int i = 0; i < otherSize; i++) {
        children.push_back(other.children[i]);
        other.children.at(i) = nullptr;
    }
    node = other.node;
    return *this;
}

void Tree::addChild(const Tree& child){
    children.push_back(child.clone());
}

Tree& Tree::getChild(int nodeIndex) const {
    Tree* t = nullptr;
    for (Tree *itr:children) {
        if (itr->node == nodeIndex) {
            t = itr;
            return *t;
        }
    }
    return *t;
}

Tree* Tree::createTree(Session& session, int rootLabel) {
    Tree* t = nullptr;
    switch (session.getTreeType()) {
        case MaxRank :
            t = new MaxRankTree(rootLabel);
            return t;
        case Root :
            t = new RootTree(rootLabel);
            return t;
        case Cycle :
            t = new CycleTree(rootLabel, session.cycleCounter);
            return t;
        default : return t;
    }
}

int Tree:: getNodeIndex() const {return node;}

vector<Tree *> Tree::getChildren() const {
    return children;
}